cmake_minimum_required (VERSION 3.1)
project ("cc_tutorial")

option (WARN_AS_ERR "Treat warnings as error" ON)
option (UNIX_USE_CCACHE "Treat warnings as error" ON)
option (FORCE_EXTRA_BOOST_LIBS "Force linking to extra boost libraries" OFF)

# Additional variables to be used if needed
# ---------------------------
# COMMSDSL2COMMS - Path to "commsdsl2comms" binary if such is already built.
# CC_MAIN_INSTALL_DIR - Path to CommsChampion external install directory (if such already built).
# COMMSDSL_TAG - Tag / branch of commsdsl project (if built internally)
# CC_TAG - Tag / branch of comms_champion project (if built internally)

if ("${COMMSDSL_TAG}" STREQUAL "")
    set (COMMSDSL_TAG "v3.5.1")
endif ()

if ("${CC_TAG}" STREQUAL "")
    set (CC_TAG "v3.0.1")
endif ()

if (NOT CMAKE_CXX_STANDARD)
    set (CMAKE_CXX_STANDARD 11)
endif ()

if ((CMAKE_COMPILER_IS_GNUCC) OR ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"))
    set (extra_flags_list
        "-Wall" "-Wextra" "-Wcast-align" "-Wcast-qual" "-Wctor-dtor-privacy"
        "-Wmissing-include-dirs"
        "-Woverloaded-virtual" "-Wredundant-decls" "-Wshadow" "-Wundef" "-Wunused"
        "-Wno-unknown-pragmas" "-fdiagnostics-show-option"
    )

    if (CMAKE_COMPILER_IS_GNUCC)
        list (APPEND extra_flags_list
            "-Wnoexcept" "-Wlogical-op" "-Wstrict-null-sentinel"
        )

    endif ()

    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        list (APPEND extra_flags_list "-Wno-dangling-field -Wno-unused-command-line-argument")
    endif ()
    
    if (WARN_AS_ERR)
        list (APPEND extra_flags_list "-Werror")
    endif ()
    
    string(REPLACE ";" " " extra_flags "${extra_flags_list}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${extra_flags}")
    
elseif (MSVC)

    if (${CMAKE_CXX_STANDARD} EQUAL 17)
        add_definitions(-D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
    endif ()

    if (WARN_AS_ERR)
        add_definitions("/WX")
    endif ()
endif ()

if ((UNIX) AND (UNIX_USE_CCACHE))
    find_program(CCACHE_FOUND ccache)
    if(CCACHE_FOUND)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
    endif()
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

add_subdirectory (lib)

set (EXTERNALS_DIR "${PROJECT_SOURCE_DIR}/externals")

#######################################################

if ("${CC_MAIN_INSTALL_DIR}" STREQUAL "")
    execute_process (
        COMMAND ${CMAKE_COMMAND} -E make_directory "${EXTERNALS_DIR}"
    )

    set (cc_src_dir "${EXTERNALS_DIR}/comms_champion")
    set (cc_bin_dir "${PROJECT_BINARY_DIR}/comms_champion")
    set (CC_MAIN_INSTALL_DIR "${cc_bin_dir}/install")

    include (${PROJECT_SOURCE_DIR}/cmake/CC_Prefetch.cmake)
    cc_prefetch(SRC_DIR "${cc_src_dir}" TAG "${CC_TAG}")
    include(${cc_src_dir}/cmake/CC_External.cmake)

    cc_build_during_config(
        SRC_DIR ${cc_src_dir}
        BUILD_DIR ${cc_bin_dir}
        TAG ${CC_TAG}
        CMAKE_ARGS
            -DCC_COMMS_LIB_ONLY=ON -DCC_NO_UNIT_TESTS=ON
            -DCMAKE_INSTALL_PREFIX=${CC_MAIN_INSTALL_DIR}
    )

endif ()
    
list (APPEND CMAKE_PREFIX_PATH "${CC_MAIN_INSTALL_DIR}")
find_package(LibComms NO_MODULE REQUIRED)

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
        
        set (boost_static_libs_param)
        if (Boost_USE_STATIC_LIBS)
            set (boost_static_libs_param "-DBoost_USE_STATIC_LIBS=ON")
        endif()

        ExternalProject_Add(
            "${COMMSDSL_TGT}"
            PREFIX "${commsdsl2comms_bin_dir}"
            STAMP_DIR "${commsdsl2comms_bin_dir}"
            GIT_REPOSITORY "https://github.com/commschamp/commsdsl.git"
            GIT_TAG "${commsdsl2comms_tag}"
            SOURCE_DIR "${commsdsl2comms_src_dir}"
            CMAKE_ARGS
                -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${commsdsl2comms_install_dir}
                -DCOMMSDSL_NO_TESTS=ON -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER} 
                -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -DBOOST_ROOT=${BOOST_ROOT}
                ${boost_static_libs_param}
            BINARY_DIR "${commsdsl2comms_bin_dir}"
        )
        
        set (COMMSDSL2COMMS "${commsdsl2comms_install_dir}/bin/commsdsl2comms")
        
        if (UNIX)
            set (COMMSDSL2COMMS "${COMMSDSL2COMMS}.sh")
        endif ()
endif ()

#######################################################

function (dsl_parse type name)
    set (prefix DSL_PARSE)
    set (options)
    set (oneValueArgs SRC_DIR)
    set (mutiValueArgs SCHEMAS)
    cmake_parse_arguments(${prefix} "${options}" "${oneValueArgs}" "${mutiValueArgs}" ${ARGN})
    
    if ("${DSL_PARSE_SCHEMAS}" STREQUAL "")
        message (FATAL_ERROR "Schema files are not provides")
    endif ()
    
    set (code_input_param)
    set (src_files)
    if (NOT "${DSL_PARSE_SRC_DIR}" STREQUAL "")
        set (code_input_param "-c${DSL_PARSE_SRC_DIR}")
        file (GLOB_RECURSE src_files "${DSL_PARSE_SRC_DIR}/*") 
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
        COMMAND ${COMMSDSL2COMMS} --warn-as-err ${code_input_param} "--cc-tag=${CC_TAG}" 
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
        
    install(TARGETS ${bin_name}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )        
endfunction ()

#######################################################

add_subdirectory (tutorials)
add_subdirectory (howtos)

