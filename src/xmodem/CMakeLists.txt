
set(sources
    x_msg.c
    x_rcv.c
    x_rcvcrc.c
    x_sndcrc.c
    x_snd.c
    x_sndchk.c
    x_rcvchk.c
    x_global.c
    x_makpkt.c
    x_cvinst.c
    x_except.c
)

include_directories(${SIO_INC_DIR})

add_library(xmodem STATIC ${sources})
