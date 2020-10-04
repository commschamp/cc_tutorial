function (lib_server)
    set (name ${COMMON_SERVER_LIB})
    
    set (src
        src/Session.cpp
        src/TcpServer.cpp
        src/tcp_server_main.cpp
    )
    
    add_library(${name} STATIC ${src})
    target_link_libraries(
        ${name} PUBLIC Boost::system Boost::boost)
        
    target_include_directories(
        ${name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)        

    target_compile_options(${name} PRIVATE
        $<$<CXX_COMPILER_ID:GNU>:-Wno-string-conversion>
        $<$<CXX_COMPILER_ID:Clang>:-Wno-string-conversion>
        $<$<CXX_COMPILER_ID:MSVC>:-D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS>
    )         
endfunction ()

#######################################################

function (lib_client)
    set (name ${COMMON_CLIENT_LIB})
    
    set (src
        src/Session.cpp
        src/TcpClient.cpp
        src/tcp_client_main.cpp
    )
    
    add_library(${name} STATIC ${src})
    target_link_libraries(
        ${name} PUBLIC Boost::system Boost::boost)
        
    target_include_directories(
        ${name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)        
endfunction ()

#######################################################

lib_server()
lib_client()

