
set(sources 
    bigbuff.c
    getkbch.c
    putbin.c
    rfopen.c
    wfopen.c
    str_atoi.c
    haktc.c
)

add_library(misc STATIC ${sources})
