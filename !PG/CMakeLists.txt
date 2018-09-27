cmake_minimum_required(VERSION 3.11)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "MinSizeRel" CACHE STRING "Choose the type of build, options are: Debug, Release, or MinSizeRel." FORCE)
    message(STATUS "No build type specified, defaulting to Release.")
endif()

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/cmake")

project(sio LANGUAGES ASM C)

#################################
# common                        #
#################################
set(CMAKE_C_STANDARD 99)

add_definitions(
    -Dnear=
    -Dfar=
    -D_interrrupt=
    -DINTPTR=
    -DNO_EOL_OUTPUT
)

#set(CMAKE_C_CFLAGS "${CMAKE_C_CFLAGS} -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections ")
#set(CMAKE_C_CFLAGS "${CMAKE_C_CFLAGS} -fno-common -Wall -fno-exceptions -Wno-aggressive-loop-optimizations ")
#set(CMAKE_C_CFLAGS "${CMAKE_C_CFLAGS} -Wno-char-subscripts -Wno-unused-but-set-variable -Werror -Wno-uninitialized ")

set(SIO_INC_PATH ${CMAKE_SOURCE_DIR}/inc)

include_directories(${SIO_INC_PATH})

#################################
# libraries                     #
#################################
set(BUOSLIB buos)
set(BUOSLIB_SRC_DIR ${CMAKE_SOURCE_DIR}/src/${BUOSLIB})
file(GLOB ${BUOSLIB}_sources ${BUOSLIB_SRC_DIR}/*.c)
#add_library(${BUOSLIB} STATIC ${${BUOSLIB}_sources})

add_subdirectory(src/crc)
if(FALSE)
set(CRCLIB crc)
set(CRCLIB_SRC_DIR "${CMAKE_SOURCE_DIR}/src/${CRCLIB}")
file(GLOB ${CRCLIB}_sources ${CRCLIB_SRC_DIR}/*.c)
list(REMOVE_ITEM ${CRCLIB}_sources ${CRCLIB_SRC_DIR}/crc.c)
add_library(${CRCLIB} STATIC ${${CRCLIB}_sources})

add_executable(crc_test ${CRCLIB_SRC_DIR}/crc.c)
target_link_libraries(crc_test crc)
add_dependencies(crc_test crc)
endif()

set(FAXLIB fax)
set(FAXLIB_SRC_DIR "${CMAKE_SOURCE_DIR}/src/${FAXLIB}")
set(${FAXLIB}_sources 
    ${FAXLIB_SRC_DIR}/bits2run.c
    ${FAXLIB_SRC_DIR}/run2bits.c
    ${FAXLIB_SRC_DIR}/t4_tress.c
    ${FAXLIB_SRC_DIR}/t4decode.c
    ${FAXLIB_SRC_DIR}/t4encode.c
    ${FAXLIB_SRC_DIR}/t4enctbl.c
    )

if(FALSE)
add_library(${FAXLIB} STATIC ${${FAXLIB}_sources})
add_executable(bmap2run ${${FAXLIB}_sources} ${FAXLIB_SRC_DIR}/bmap2run.c)
add_dependencies(bmap2run fax)
add_executable(makebmp ${${FAXLIB}_sources} ${FAXLIB_SRC_DIR}/makebmp.c)
add_dependencies(makebmp fax)
add_executable(run2bmp ${${FAXLIB}_sources} ${FAXLIB_SRC_DIR}/run2bmp.c)
add_dependencies(run2bmp fax)
add_executable(run2t4 ${${FAXLIB}_sources} ${FAXLIB_SRC_DIR}/run2t4.c)
add_dependencies(run2t4 fax)
add_executable(t4torun ${${FAXLIB}_sources} ${FAXLIB_SRC_DIR}/t4torun.c)
add_dependencies(t4torun fax)
endif()

set(IBMPCLIB ibmpc)
set(IBMPCLIB_SRC_DIR "${CMAKE_SOURCE_DIR}/src/${IBMPCLIB}")
file(GLOB ${IBMPCLIB}_sources ${IBMPCLIB_SRC_DIR}/*.c)
#add_library(${IBMPCLIB} STATIC ${${IBMPCLIB}_sources})

set(MISCLIB misc)
set(MISCLIB_SRC_DIR "${CMAKE_SOURCE_DIR}/src/${MISCLIB}")
file(GLOB ${MISCLIB}_sources ${MISCLIB_SRC_DIR}/*.c)
#add_library(${MISCLIB} STATIC ${${MISCLIB}_sources})

set(MODEMLIB modem)
set(MODEMLIB_SRC_DIR "${CMAKE_SOURCE_DIR}/src/${MODEMLIB}")
file(GLOB ${MODEMLIB}_sources ${MODEMLIB_SRC_DIR}/*.c)
#add_library(${MODEMLIB} STATIC ${${MODEMLIB}_sources})

set(_SIO _sio)
set(_SIOLIB_SRC_DIR "${CMAKE_SOURCE_DIR}/src/${_SIO}")
file(GLOB ${_SIOLIB}_sources ${_SIOLIB_SRC_DIR}/*.c)
#add_library(${_SIOLIB} STATIC ${${_SIOLIB}_sources})

set(TERMFUNCLIB termfunc)
set(TERMFUNCLIB_SRC_DIR "${CMAKE_SOURCE_DIR}/src/${TERMFUNCLIB}")
file(GLOB ${TERMFUNCLIB}_sources ${TERMFUNCLIB_SRC_DIR}/*.c)
#add_library(${TERMFUNCLIB} STATIC ${${TERMFUNCLIB}_sources})

set(U16X50LIB u16x50)
set(U16X50LIB_SRC_DIR "${CMAKE_SOURCE_DIR}/src/${U16X50LIB}")
file(GLOB ${U16X50LIB}_sources ${U16X50LIB_SRC_DIR}/*.c)
#add_library(${U16X50LIB} STATIC ${${U16X50LIB}_sources})

set(XMODEMLIB xmodem)
set(XMODEMLIB_SRC_DIR "${CMAKE_SOURCE_DIR}/src/${XMODEMLIB}")
file(GLOB ${XMODEMLIB}_sources ${XMODEMLIB_SRC_DIR}/*.c)
#add_library(${XMODEMLIB} STATIC ${${XMODEMLIB}_sources})

set(PROGS progs)
set(PROGS_SRC_DIR "${CMAKE_SOURCE_DIR}/src/${PROGS}")
file(GLOB ${PROGS}_sources ${PROGS_SRC_DIR}/*.c)
#add_executable(${PROGS} ${${PROGS}_sources})

