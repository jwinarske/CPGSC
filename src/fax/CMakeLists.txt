
set(sources 
    t4enctbl.c
    bits2run.c
    run2bits.c
    t4encode.c
    t4decode.c
    t4_trees.c
)

include_directories(${SIO_INC_DIR})

add_library(fax STATIC ${sources})

add_executable(bmap2run bmap2run.c)
target_link_libraries(bmap2run fax)
add_dependencies(bmap2run fax)

add_executable(makebmp makebmp.c)
target_link_libraries(makebmp fax)
add_dependencies(makebmp fax)

add_executable(run2bmp run2bmp.c)
target_link_libraries(run2bmp fax)
add_dependencies(run2bmp fax)

add_executable(run2t4 run2t4.c)
target_link_libraries(run2t4 fax)
add_dependencies(run2t4 fax)

add_executable(t4torun t4torun.c)
target_link_libraries(t4torun fax)
add_dependencies(t4torun fax)

include(CTest)

add_test(NAME makebmp COMMAND makebmp)
add_test(NAME bmap2run COMMAND bmap2run)
add_test(NAME run2t4 COMMAND run2t4)
add_test(NAME t4torun COMMAND t4torun)
add_test(NAME run2bmp COMMAND run2bmp)
