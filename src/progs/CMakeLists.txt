
add_executable(term7 term7.c)

target_link_libraries(term7
    # asm
    ibmpc
    u16x50
    buos crc misc modem 
    termfunc xmodem sio
)
add_dependencies(term7
    # asm
    ibmpc 
    u16x50
    buos crc misc modem 
    termfunc xmodem sio
)
