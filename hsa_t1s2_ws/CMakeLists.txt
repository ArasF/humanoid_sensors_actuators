cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_TOOLCHAIN_FILE "/opt/avr/share/cmake/avr.cmake" CACHE FILEPATH "Toolchain file")


# define project name
project(hsa_t1s1_ws C ASM)


include("/usr/share/btk/cmake/btk.cmake")
include("/opt/avr/share/cmake/avr_tools.cmake")


#set(CMAKE_VERBOSE_MAKEFILE true)


set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)


set(AVR_MCPU atmega32)
set(AVR_FREQ 1000000)


avr_init()


btk_add_subproject(${SRC_DIR}/uart)
btk_add_subproject(${SRC_DIR}/uart_512bit_adder)



message(STATUS "PROJECT_TARGET_LIST:")
foreach(target ${PROJECT_TARGET_LIST})
    message("  ${target}")
endforeach()