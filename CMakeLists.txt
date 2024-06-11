# Template for a MSP430 project
cmake_minimum_required(VERSION 3.22)

set(MSP430_MCU  msp430fr6972)
set(MSP430_MCU_FREQ 1000000UL)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/msp430.cmake")

# Name your project
project(pluto)

#device dependent config, here for launchpad


add_subdirectory(common)
add_subdirectory(target)

# msp430_add_executable(execu)

# target_link_libraries(execu hardware)