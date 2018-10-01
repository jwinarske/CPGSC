
set(sources 
    cbuff.c
    dial_re.c
    dnload.c
    locbuff.c
    setup232.c
    setfmt.c
    upload.c
)

if(UNIX)
    list(APPEND source _kbhit.c)
endif()

add_library(termfunc STATIC ${sources})
