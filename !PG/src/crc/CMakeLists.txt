
set(sources
    crc16tab.c crchware.c crcrevrs.c 
    crcrupd.c crctab.c crcupdat.c
    mkcrctbl.c polydiv.c
)

add_library(crc STATIC ${sources})

add_executable(crc_main crc.c)
set_target_properties(crc_main PROPERTIES OUTPUT_NAME "crc")
target_link_libraries(crc_main crc)
add_dependencies(crc_main crc)


