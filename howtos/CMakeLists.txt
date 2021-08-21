function (dsl_howto_parse name)
    dsl_parse ("howtos" ${name} ${ARGN})
endfunction ()

function (bin_howto_server name)
    bin_server ("howtos" ${name} ${ARGN})
endfunction ()

function (bin_howto_client name)
    bin_client ("howtos" ${name} ${ARGN})
endfunction ()

add_subdirectory (howto1)
add_subdirectory (howto2)
add_subdirectory (howto3)
add_subdirectory (howto4)
add_subdirectory (howto5)
add_subdirectory (howto6)
add_subdirectory (howto7)
add_subdirectory (howto8)
add_subdirectory (howto9)
add_subdirectory (howto10)

