cmake_minimum_required (VERSION 3.1)
project ("cc_tutorial")

option (WARN_AS_ERR "Treat warnings as error" ON)
option (UNIX_USE_CCACHE "Treat warnings as error" ON)
option (FORCE_EXTRA_BOOST_LIBS "Force linking to extra boost libraries" OFF)
option (USE_SANITIZERS "Compile with sanitizers." OFF)

set (CMAKE_CXX_STANDARD 11 CACHE STRING "The C++ standard to use")
set (MIN_COMMSDSL_VERSION "6.2.4")

include(GNUInstallDirs)

find_package(Boost REQUIRED COMPONENTS system)

if (FORCE_EXTRA_BOOST_LIBS)
    set (EXTRA_BOOST_TARGETS Boost::date_time Boost::regex)
    find_package(Boost COMPONENTS REQUIRED date_time regex)
endif ()    
    
find_package(Threads REQUIRED)    
find_package(LibComms REQUIRED)
find_program(COMMSDSL2COMMS commsdsl2comms PATH_SUFFIXES bin REQUIRED)

execute_process(COMMAND "${COMMSDSL2COMMS}" --version OUTPUT_VARIABLE commsdsl2comms_version)
if ("${commsdsl2comms_version}" VERSION_LESS "${MIN_COMMSDSL_VERSION}")
    message (FATAL_ERROR "Version of commsdsl2comms is too old, required minimum is v${MIN_COMMSDSL_VERSION}.")
endif ()

set (COMMON_SERVER_LIB "common_server")
set (COMMON_CLIENT_LIB "common_client")

#######################################################

set (cc_compile_file ${LibComms_DIR}/CC_Compile.cmake)
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
    
    set (output_dir "${CMAKE_CURRENT_BINARY_DIR}/${name}/output")
    string(REPLACE ";" "\n" schema_files "${DSL_PARSE_SCHEMAS}")
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${name}/schema_files.txt "${schema_files}")
    
    add_custom_target(${name}_prot_rm 
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${output_dir}
    )

    add_custom_command(
        OUTPUT ${output_dir}
        DEPENDS ${DSL_PARSE_SCHEMAS} ${src_files} ${name}_prot_rm 
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${output_dir}
        COMMAND ${COMMSDSL2COMMS} --warn-as-err ${multi_schema_param} ${code_input_param} "--comms-tag=${CC_COMMS_TAG}" 
            -o ${output_dir} -i ${CMAKE_CURRENT_BINARY_DIR}/${name}/schema_files.txt
    )

    add_custom_target(${name}_dsl ALL
        COMMAND ${CMAKE_COMMAND}
            -DGENERATED="${output_dir}/include" -DOUTPUT="${PROJECT_SOURCE_DIR}/${type}/${name}/include"
            -P "${PROJECT_SOURCE_DIR}/CopyGenerated.cmake"
        DEPENDS ${name}_prot_rm ${output_dir} "${PROJECT_SOURCE_DIR}/CopyGenerated.cmake" ${DSL_PARSE_SCHEMAS} ${src_files}  
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

