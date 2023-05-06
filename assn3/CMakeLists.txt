project("ASSN3")

add_subdirectory(
    src
    build
)

add_subdirectory(
    tests
    build/tests
)

include(CTest)

function(parser_test test_name)
    add_test(
        NAME ASSN3::parser::${test_name}
        COMMAND build/tests/parser.test.out parser::${test_name}
    )
endfunction(parser_test)

function(drawer_test test_name)
    add_test(
        NAME ASSN3::drawer::${test_name}
        COMMAND build/tests/drawer.test.out drawer::${test_name}
    )
endfunction(drawer_test)

function(artist_test test_name)
    add_test(
        NAME ASSN3::artist::${test_name}
        COMMAND build/tests/artist.test.out artist::${test_name}
    )
endfunction(artist_test)

parser_test(Split)
parser_test(LoadImage)
parser_test(LoadConfig)
parser_test(WriteResult)

artist_test(classic)
artist_test(iclassic)
artist_test(sobelx)
artist_test(sobely)
artist_test(gradient)
artist_test(digit)

drawer_test(drawer)
drawer_test(downsample)
drawer_test(upsample)
drawer_test(scale)
