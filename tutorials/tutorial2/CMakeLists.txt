get_filename_component(name ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set (schema_files
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/main.xml
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/msg1.xml
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/msg2.xml
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/msg3.xml
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/msg4.xml
)

set (server_src
    src/ServerSession.cpp
)

set (client_src
    src/ClientSession.cpp
)


dsl_tutorial_parse(${name} SCHEMAS ${schema_files})

bin_tutorial_server(${name} ${server_src})
bin_tutorial_client(${name} ${client_src})

