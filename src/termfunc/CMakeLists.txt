
set(sources 
    cbuff.c
    dial_re.c
    dnload.c
    locbuff.c
    setup232.c
    setfmt.c
    upload.c
)

include_directories(${SIO_INC_DIR})

add_library(termfunc STATIC ${sources})
