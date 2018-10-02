
set(sources
    s_fgetc.c
    s_fputc.c
    s_getc.c
    s_iflush.c
    s_inchar.c
    s_ircv.c
    s_putc.c
    s_ircvst.c
    s_ixmit.c
    s_ixmits.c
    s_rcv.c
    s_rcvst.c
    s_txemp.c
    s_xmit.c
    s_xmits.c
    vset232.c
    vsetbits.c
    vsetbr.c
    vstat232.c
    xon_xoff.c
    noflow.c
    rts_cts.c
    232_ion.c
    ser_ion.c
    tx_ion.c
    rcv_ion.c
    232_ioff.c
    ser_ioff.c
    tx_ioff.c
    rcv_ioff.c
)

include_directories(${SIO_INC_DIR})

add_library(buos STATIC ${sources})
