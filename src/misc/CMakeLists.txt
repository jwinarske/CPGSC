
set(sources 
    bigbuff.c
    getkbch.c
    putbin.c
    rfopen.c
    wfopen.c
    str_atoi.c
    haktc.c
    fgets_wrapper.c
)

include_directories(${SIO_INC_DIR})

add_library(misc STATIC ${sources})
