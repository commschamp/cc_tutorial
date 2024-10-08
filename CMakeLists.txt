cmake_minimum_required (VERSION 3.10)
project ("cc_tutorial")

option (OPT_WARN_AS_ERR "Treat warnings as error" ON)
option (OPT_USE_CCACHE "Use ccache" OFF)
option (OPT_FORCE_EXTRA_BOOST_LIBS "Force linking to extra boost libraries" OFF)
option (OPT_USE_SANITIZERS "Compile with sanitizers." OFF)

# Extra configuration variables
# OPT_CCACHE_EXECUTABLE - Custom ccache executable

#####################################################

set (MIN_COMMSDSL_VERSION "6.3.4")

if ("${CMAKE_CXX_STANDARD}" STREQUAL "")
    set(CMAKE_CXX_STANDARD 11)
endif ()

if (("${CMAKE_VERSION}" VERSION_GREATER_EQUAL "3.30") AND
    (NOT DEFINED CMAKE_POLICY_DEFAULT_CMP0167))
    # Find boost cmake configuration from the boost installation
    cmake_policy(SET CMP0167 NEW)
endif ()

include(GNUInstallDirs)

find_package(Boost REQUIRED COMPONENTS system)

if (OPT_FORCE_EXTRA_BOOST_LIBS)
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
    set (extra_opts)
    if (OPT_WARN_AS_ERR)
        list (APPEND extra_opts WARN_AS_ERR)
    endif()

    if (OPT_USE_CCACHE)
        list (APPEND extra_opts USE_CCACHE)
        if (NOT "${OPT_CCACHE_EXECUTABLE}" STREQUAL "")
            list (APPEND extra_opts CCACHE_EXECTUABLE "${OPT_CCACHE_EXECUTABLE}")
        endif ()
    endif ()

    if (OPT_USE_SANITIZERS)
        list (APPEND extra_opts DEFAULT_SANITIZERS)
    endif ()

    include (${cc_compile_file})
    cc_compile(${extra_opts})
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

    if (OPT_FORCE_EXTRA_BOOST_LIBS)
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
        $<$<CXX_COMPILER_ID:GNU>:-Wno-old-style-cast -Wno-string-conversion>
        $<$<CXX_COMPILER_ID:Clang>:-Wno-old-style-cast -Wno-string-conversion>
        $<$<CXX_COMPILER_ID:MSVC>:-D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS>
    )       

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

    if (OPT_FORCE_EXTRA_BOOST_LIBS)
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

