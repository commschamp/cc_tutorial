get_filename_component(name ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set (schema_files
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/main.xml
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/msg1.xml
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/msg2.xml
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/msg3.xml
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/msg4.xml
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/msg5.xml
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/msg6.xml
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/msg7.xml
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/msg8.xml
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/msg9.xml
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/msg10.xml
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/msg11.xml
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/msg12.xml
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/msg13.xml
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/msg14.xml
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/msg15.xml
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/msg16.xml
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/msg17.xml
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/msg18.xml
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

