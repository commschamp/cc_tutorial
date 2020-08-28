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
