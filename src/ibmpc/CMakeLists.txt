
set(sources 

    ibmpc.c
)

include_directories(${SIO_INC_DIR})

add_library(ibmpc STATIC ${sources})
