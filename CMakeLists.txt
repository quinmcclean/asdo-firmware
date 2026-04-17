cmake_minimum_required(VERSION 3.13)
set(PICO_W_PROJECT_NAME asdo_firmware)
# Shared Pico W setup: SDK path, board, standards.
# Include from each project's CMakeLists.txt before project().
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if(EXISTS ${picoVscode})
    include(${picoVscode})
endif()

set(PICO_BOARD pico_w CACHE STRING "Board type")

if(DEFINED ENV{PICO_SDK_PATH} AND NOT PICO_SDK_PATH)
    set(PICO_SDK_PATH $ENV{PICO_SDK_PATH} CACHE PATH "Path to Pico SDK")
endif()
if(NOT PICO_SDK_PATH)
    set(PICO_SDK_PATH "$ENV{HOME}/.pico-sdk/sdk/2.2.0" CACHE PATH "Path to Pico SDK")
endif()
get_filename_component(PICO_SDK_PATH "${PICO_SDK_PATH}" REALPATH)
# If path has no version (e.g. .../sdk), use 2.2.0
if(NOT EXISTS ${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
    set(PICO_SDK_PATH "${PICO_SDK_PATH}/2.2.0" CACHE PATH "Path to Pico SDK" FORCE)
endif()

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(${PICO_W_PROJECT_NAME} C CXX ASM)
pico_sdk_init()

add_executable(${PICO_W_PROJECT_NAME})
target_sources(${PICO_W_PROJECT_NAME} 
  PRIVATE 
    src/main.c
    src/ui.c)

pico_set_program_name(${PICO_W_PROJECT_NAME} "${PICO_W_PROJECT_NAME}")
pico_set_program_version(${PICO_W_PROJECT_NAME} "0.1")

target_link_libraries(${PICO_W_PROJECT_NAME}
    pico_stdlib
    pico_cyw43_arch_none
    pico_multicore
)
target_include_directories(${PICO_W_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

pico_add_extra_outputs(${PICO_W_PROJECT_NAME})

pico_enable_stdio_uart(${PICO_W_PROJECT_NAME} 1)
pico_enable_stdio_usb(${PICO_W_PROJECT_NAME} 1)
