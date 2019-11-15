cmake_minimum_required (VERSION 3.1)
project ("cc_tutorial")

option (WARN_AS_ERR "Treat warnings as error" ON)
option (UNIX_USE_CCACHE "Treat warnings as error" ON)


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

set (COMMON_SERVER_LIB "common_server")
set (COMMON_CLIENT_LIB "common_client")

add_subdirectory (lib)
