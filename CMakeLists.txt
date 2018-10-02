cmake_minimum_required(VERSION 3.11)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "MinSizeRel" CACHE STRING "Choose the type of build, options are: Debug, Release, or MinSizeRel." FORCE)
    message(STATUS "No build type specified, defaulting to Release.")
endif()

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/cmake")

project(sio LANGUAGES C)

#################################
# common                        #
#################################
set(CMAKE_C_STANDARD 99)

add_definitions(
    -Dnear=
    -Dfar=
    -Dnear=
    -Dfar=
)

if(NOT MSVC)
    add_definitions(
        -D_interrrupt=
        -DINTPTR=
        -DNO_EOL_OUTPUT
        -D_disable=
        -D_enable=
    )

    #set(CMAKE_C_CFLAGS "${CMAKE_C_CFLAGS} -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections ")
    #set(CMAKE_C_CFLAGS "${CMAKE_C_CFLAGS} -fno-common -Wall -fno-exceptions -Wno-aggressive-loop-optimizations ")
    #set(CMAKE_C_CFLAGS "${CMAKE_C_CFLAGS} -Wno-char-subscripts -Wno-unused-but-set-variable -Werror -Wno-uninitialized ")
else()

    add_definitions(
        #/DCOM1SIO
    )

    add_definitions(-D_CONSOLE -D_MBCS -D_CRT_SECURE_NO_WARNINGS)

    # FOR MSOFT C6 & 7
    #                                    No Stack Probes
    #                                    |  Structure Packing
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Gs /Zp")

endif()


set(SIO_INC_DIR ${CMAKE_SOURCE_DIR}/inc)


#################################
# targets                       #
#################################

#add_subdirectory(src/asm)
add_subdirectory(src/buos)
add_subdirectory(src/crc)
add_subdirectory(src/fax)
add_subdirectory(src/ibmpc)
add_subdirectory(src/misc)
add_subdirectory(src/modem)
add_subdirectory(src/progs)
add_subdirectory(src/sio)
add_subdirectory(src/termfunc)
add_subdirectory(src/u16x50)
add_subdirectory(src/xmodem)
