get_filename_component(name ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set (schema_files
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/schema_ext.xml
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/schema.xml
)

set (server_src
    src/ServerSession.cpp
)

set (client_src
    src/ClientSession.cpp
)

dsl_tutorial_parse(${name} SCHEMAS ${schema_files} SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dsl_src MULTI_SCHEMA)

bin_tutorial_server(${name} ${server_src})
bin_tutorial_client(${name} ${client_src})

