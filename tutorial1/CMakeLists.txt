set (name "tutorial1")

set (schema_files
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/schema.xml
)

set (server_src
    src/Tutorial1ServerSession.cpp
)

dsl_parse(${name} SCHEMAS ${schema_files})
bin_server(${name} ${server_src})

