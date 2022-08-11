cmake_minimum_required (VERSION 3.1)
project ("cc_tutorial")

option (WARN_AS_ERR "Treat warnings as error" ON)
option (UNIX_USE_CCACHE "Treat warnings as error" ON)
option (FORCE_EXTRA_BOOST_LIBS "Force linking to extra boost libraries" OFF)
option (USE_SANITIZERS "Compile with sanitizers." OFF)

# Additional variables to be used if needed
# ---------------------------
# COMMSDSL2COMMS - Path to "commsdsl2comms" binary if such is already built.
# CC_COMMS_INSTALL_DIR - Path to CommsChampion external install directory (if such already built).
# COMMSDSL_TAG - Tag / branch of commsdsl project (if built internally)
# CC_COMMS_TAG - Tag / branch of COMMS library project (if built internally)
# COMMSDSL_C_COMPILER - "C" Compiler for commsdsl project
# COMMSDSL_CXX_COMPILER - "C++" Compiler for commsdsl project

if ("${COMMSDSL_TAG}" STREQUAL "")
    set (COMMSDSL_TAG "v5.0")
endif ()

if ("${CC_COMMS_TAG}" STREQUAL "")
    set (CC_COMMS_TAG "v5.0")
endif ()

if (NOT CMAKE_CXX_STANDARD)
    set (CMAKE_CXX_STANDARD 11)
endif ()

include(GNUInstallDirs)

find_package(Boost REQUIRED
    COMPONENTS system)

if (FORCE_EXTRA_BOOST_LIBS)
    set (EXTRA_BOOST_TARGETS Boost::date_time Boost::regex)
    find_package(Boost COMPONENTS REQUIRED date_time regex)
endif ()    
    
find_package(Threads REQUIRED)    

set (COMMON_SERVER_LIB "common_server")
set (COMMON_CLIENT_LIB "common_client")

set (EXTERNALS_DIR "${PROJECT_SOURCE_DIR}/externals")

#######################################################

if ("${CC_COMMS_INSTALL_DIR}" STREQUAL "")
    execute_process (
        COMMAND ${CMAKE_COMMAND} -E make_directory "${EXTERNALS_DIR}"
    )

    set (cc_src_dir "${EXTERNALS_DIR}/comms")
    set (cc_bin_dir "${PROJECT_BINARY_DIR}/comms")
    set (CC_COMMS_INSTALL_DIR "${cc_bin_dir}/install")

    include (${PROJECT_SOURCE_DIR}/cmake/CC_Prefetch.cmake)
    cc_prefetch(SRC_DIR "${cc_src_dir}" TAG "${CC_COMMS_TAG}")
    include(${cc_src_dir}/cmake/CC_CommsExternal.cmake)

    cc_comms_build_during_config(
        SRC_DIR ${cc_src_dir}
        BUILD_DIR ${cc_bin_dir}
        TAG ${CC_COMMS_TAG}
        CMAKE_ARGS
            -DCC_BUILD_UNIT_TESTS=OFF 
            -DCMAKE_INSTALL_PREFIX=${CC_COMMS_INSTALL_DIR}
    )

endif ()
    
list (APPEND CMAKE_PREFIX_PATH "${CC_COMMS_INSTALL_DIR}")
find_package(LibComms NO_MODULE REQUIRED)

set (cc_compile_file ${CC_COMMS_INSTALL_DIR}/lib/LibComms/cmake/CC_Compile.cmake)
if (EXISTS ${cc_compile_file})
    set (warn_as_err_opt)
    if (WARN_AS_ERR)
        set (warn_as_err_opt WARN_AS_ERR)
    endif()

    set (ccache_opt)
    if (UNIX_USE_CCACHE)
        set (ccache_opt USE_CCACHE)
    endif ()

    include (${cc_compile_file})
    cc_compile(${warn_as_err_opt} ${ccache_opt})
endif ()

set (CC_TUTORIAL_SANITIZER_OPTS)
if (USE_SANITIZERS AND (NOT ${CMAKE_VERSION} VERSION_LESS "3.13") AND
    ((CMAKE_COMPILER_IS_GNUCC) OR ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")))
    set (CC_TUTORIAL_SANITIZER_OPTS 
        -fno-omit-frame-pointer 
        -fno-sanitize-recover=address 
        -fsanitize=address
        -fno-sanitize-recover=undefined
        -fsanitize=undefined)
endif ()

#######################################################
set (COMMSDSL_TGT "commsdsl_tgt")
if ("${COMMSDSL2COMMS}" STREQUAL "")
        execute_process (
            COMMAND ${CMAKE_COMMAND} -E make_directory "${EXTERNALS_DIR}"
        )   
        include(ExternalProject)
        set (commsdsl2comms_tag "${COMMSDSL_TAG}")
        set (commsdsl2comms_main_dir "${PROJECT_BINARY_DIR}/commsdsl")
        set (commsdsl2comms_src_dir "${EXTERNALS_DIR}/commsdsl")
        set (commsdsl2comms_bin_dir "${commsdsl2comms_main_dir}/build")
        set (commsdsl2comms_install_dir "${commsdsl2comms_main_dir}/install")

        if ("${COMMSDSL_C_COMPILER}" STREQUAL "")
            set (COMMSDSL_C_COMPILER ${CMAKE_C_COMPILER})
        endif ()        

        if ("${COMMSDSL_CXX_COMPILER}" STREQUAL "")
            set (COMMSDSL_CXX_COMPILER ${CMAKE_CXX_COMPILER})
        endif ()
        
        ExternalProject_Add(
            "${COMMSDSL_TGT}"
            PREFIX "${commsdsl2comms_bin_dir}"
            STAMP_DIR "${commsdsl2comms_bin_dir}"
            GIT_REPOSITORY "https://github.com/commschamp/commsdsl.git"
            GIT_TAG "${commsdsl2comms_tag}"
            SOURCE_DIR "${commsdsl2comms_src_dir}"
            CMAKE_ARGS
                -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${commsdsl2comms_install_dir}
                -DCOMMSDSL_NO_TESTS=ON -DCMAKE_C_COMPILER=${COMMSDSL_C_COMPILER} 
                -DCMAKE_CXX_COMPILER=${COMMSDSL_CXX_COMPILER}
                -DCOMMSDSL_INSTALL_LIBRARY=OFF
                -DCOMMSDSL_EXTERNALS_DIR=${EXTERNALS_DIR} 
            BINARY_DIR "${commsdsl2comms_bin_dir}"
        )
        
        set (COMMSDSL2COMMS "${commsdsl2comms_install_dir}/bin/commsdsl2comms")
endif ()

#######################################################

function (dsl_parse type name)
    set (prefix DSL_PARSE)
    set (options MULTI_SCHEMA)
    set (oneValueArgs SRC_DIR)
    set (mutiValueArgs SCHEMAS)
    cmake_parse_arguments(${prefix} "${options}" "${oneValueArgs}" "${mutiValueArgs}" ${ARGN})
    
    if ("${DSL_PARSE_SCHEMAS}" STREQUAL "")
        message (FATAL_ERROR "Schema files are not provides")
    endif ()
    
    set (code_input_param)
    set (src_files)
    if (NOT "${DSL_PARSE_SRC_DIR}" STREQUAL "")
        set (code_input_param -c ${DSL_PARSE_SRC_DIR})
        file (GLOB_RECURSE src_files "${DSL_PARSE_SRC_DIR}/*") 
    endif ()

    set (multi_schema_param)
    if (DSL_PARSE_MULTI_SCHEMA)
        set (multi_schema_param "-s")
    endif ()
    
    set (commsdsl_tgt_dep)
    if (TARGET ${COMMSDSL_TGT})
        set (commsdsl_tgt_dep ${COMMSDSL_TGT})
    endif ()

    set (output_dir "${CMAKE_CURRENT_BINARY_DIR}/${name}/output")
    string(REPLACE ";" "\n" schema_files "${DSL_PARSE_SCHEMAS}")
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${name}/schema_files.txt "${schema_files}")
    
    add_custom_target(${name}_prot_rm 
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${output_dir}
    )

    add_custom_command(
        OUTPUT ${output_dir}
        DEPENDS ${DSL_PARSE_SCHEMAS} ${src_files} ${commsdsl_tgt_dep} ${name}_prot_rm 
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${output_dir}
        COMMAND ${COMMSDSL2COMMS} --warn-as-err ${multi_schema_param} ${code_input_param} "--comms-tag=${CC_COMMS_TAG}" 
            -o ${output_dir} -i ${CMAKE_CURRENT_BINARY_DIR}/${name}/schema_files.txt
    )

    add_custom_target(${name}_dsl ALL
        COMMAND ${CMAKE_COMMAND}
            -DGENERATED="${output_dir}/include" -DOUTPUT="${PROJECT_SOURCE_DIR}/${type}/${name}/include"
            -P "${PROJECT_SOURCE_DIR}/CopyGenerated.cmake"
        DEPENDS ${name}_prot_rm ${output_dir} "${PROJECT_SOURCE_DIR}/CopyGenerated.cmake" ${DSL_PARSE_SCHEMAS} ${src_files} ${commsdsl_tgt_dep} 
    )
    
endfunction ()

#######################################################

function (bin_server type name)
    set (bin_name ${name}_server)
    add_executable(${bin_name} ${ARGN})
    target_link_libraries(
        ${bin_name} PRIVATE ${COMMON_SERVER_LIB} cc::comms Boost::system Boost::boost ${CMAKE_THREAD_LIBS_INIT})

    if (FORCE_EXTRA_BOOST_LIBS)
        target_link_libraries(
            ${bin_name} PRIVATE ${EXTRA_BOOST_TARGETS})
    endif () 

    if (TARGET Boost::regex)
        target_link_libraries(
            ${bin_name} PRIVATE Boost::regex)
    endif ()        
        
    add_dependencies(${bin_name} ${name}_dsl)
        
    target_include_directories(
        ${bin_name} PRIVATE ${PROJECT_SOURCE_DIR}/${type}/${name}/include)        

    target_compile_options(${bin_name} PRIVATE
        $<$<CXX_COMPILER_ID:GNU>:-Wno-old-style-cast -Wno-string-conversion ${CC_TUTORIAL_SANITIZER_OPTS}>
        $<$<CXX_COMPILER_ID:Clang>:-Wno-old-style-cast -Wno-string-conversion ${CC_TUTORIAL_SANITIZER_OPTS}>
        $<$<CXX_COMPILER_ID:MSVC>:-D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS>
    )       


    if (NOT "${CC_TUTORIAL_SANITIZER_OPTS}" STREQUAL "")
        target_link_options(${bin_name} PRIVATE
            $<$<CXX_COMPILER_ID:GNU>:${CC_TUTORIAL_SANITIZER_OPTS}>
            $<$<CXX_COMPILER_ID:Clang>:${CC_TUTORIAL_SANITIZER_OPTS}>
        )         
    endif ()
        
    install(TARGETS ${bin_name}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )        
endfunction ()

#######################################################

function (bin_client type name)
    set (bin_name ${name}_client)
    add_executable(${bin_name} ${ARGN})
    target_link_libraries(
        ${bin_name} PRIVATE ${COMMON_CLIENT_LIB} cc::comms Boost::system Boost::boost ${CMAKE_THREAD_LIBS_INIT})

    if (FORCE_EXTRA_BOOST_LIBS)
        target_link_libraries(
            ${bin_name} PRIVATE ${EXTRA_BOOST_TARGETS})
    endif ()         
        
    add_dependencies(${bin_name} ${name}_dsl)
        
    target_include_directories(
        ${bin_name} PRIVATE ${PROJECT_SOURCE_DIR}/${type}/${name}/include)        

    target_compile_options(${bin_name} PRIVATE
        $<$<CXX_COMPILER_ID:GNU>:-Wno-old-style-cast -Wno-string-conversion ${CC_TUTORIAL_SANITIZER_OPTS}>
        $<$<CXX_COMPILER_ID:Clang>:-Wno-old-style-cast -Wno-string-conversion ${CC_TUTORIAL_SANITIZER_OPTS}>
        $<$<CXX_COMPILER_ID:MSVC>:-D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS>
    )        

    if (NOT "${CC_TUTORIAL_SANITIZER_OPTS}" STREQUAL "")
        target_link_options(${bin_name} PRIVATE
            $<$<CXX_COMPILER_ID:GNU>:${CC_TUTORIAL_SANITIZER_OPTS}>
            $<$<CXX_COMPILER_ID:Clang>:${CC_TUTORIAL_SANITIZER_OPTS}>
        )         
    endif ()     
        
    install(TARGETS ${bin_name}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )        
endfunction ()

#######################################################

add_subdirectory (lib)
add_subdirectory (tutorials)
add_subdirectory (howtos)

