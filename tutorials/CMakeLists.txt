function (dsl_tutorial_parse name)
    dsl_parse ("tutorials" ${name} ${ARGN})
endfunction ()

function (bin_tutorial_server name)
    bin_server ("tutorials" ${name} ${ARGN})
endfunction ()

function (bin_tutorial_client name)
    bin_client ("tutorials" ${name} ${ARGN})
endfunction ()

add_subdirectory (tutorial1)
add_subdirectory (tutorial2)
add_subdirectory (tutorial3)
add_subdirectory (tutorial4)
