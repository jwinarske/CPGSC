
if(MSVC)
    enable_language(ASM_MASM)

    # LARGEMODEL / SMALLMODEL
    set(MODEL_SIZE SMALLMODEL)

    set(CMAKE_ASM_MASM_FLAGS "${CMAKE_ASM_MASM_FLAGS} /D${MODEL_SIZE} ")
    # /DCOM1SIO /DCOM2SIO /DCOM3SIO /DCOM4SIO")

    add_library(cpgsc STATIC cpgsc.asm)
endif()
