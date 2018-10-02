
set(sources 
    u_intmgr.c
    isr_serr.c
    isr_232.c
    isr_rcv.c
#   isr_xrcv.c
    isr_tx.c
    i_dummy.c
    s_config.c
    s_iadmin.c
    s_restor.c
    s_revect.c
    uvset232.c
    uvsetbr.c
    uvstat32.c
    uvstbits.c
)

include_directories(${SIO_INC_DIR})

add_library(u16x50 STATIC ${sources})
