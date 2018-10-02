
set(sources
    s_open.c
    asc_parm.c
    clearerr.c
    er_strs.c
    get232.c
    getbaud.c
    getfmat.c
    set232.c
    setbaud.c
    setfmat.c
    stat232.c
    statserr.c
    s_close.c
    s_clrsio.c
    s_fgetln.c
    s_fgets.c
    s_fputs.c
    s_icntrl.c
    s_iphpop.c
    s_kbort.c
    s_ocntrl.c
    s_pshpop.c
    s_puts.c
    tr_rcvon.c
    tx_write.c
    tx_iwrit.c
    s_write.c
    br2bcode.c
)

include_directories(${SIO_INC_DIR})

add_library(sio STATIC ${sources})
