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
add_subdirectory (tutorial5)
add_subdirectory (tutorial6)
add_subdirectory (tutorial7)
add_subdirectory (tutorial8)
add_subdirectory (tutorial9)
add_subdirectory (tutorial10)
add_subdirectory (tutorial11)
add_subdirectory (tutorial12)
add_subdirectory (tutorial13)
add_subdirectory (tutorial14)
add_subdirectory (tutorial15)
add_subdirectory (tutorial16)
add_subdirectory (tutorial17)
add_subdirectory (tutorial18)
add_subdirectory (tutorial19)
add_subdirectory (tutorial20)
add_subdirectory (tutorial21)
add_subdirectory (tutorial22)
add_subdirectory (tutorial23)
add_subdirectory (tutorial24)
add_subdirectory (tutorial25)
