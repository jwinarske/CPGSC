
set(sources
    crcrevrs.c
    crcrupd.c
    crc16tab.c
    crchware.c 
    mkcrctbl.c
    crctab.c
    crcupdat.c
    polydiv.c
)

add_library(crc STATIC ${sources})

add_executable(crc_main crc.c)
set_target_properties(crc_main PROPERTIES OUTPUT_NAME "crc")
target_link_libraries(crc_main crc)
add_dependencies(crc_main crc)
