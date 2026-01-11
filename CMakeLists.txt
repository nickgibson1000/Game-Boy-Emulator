cmake_minimum_required(VERSION 3.20)
project(GameBoyEmulator C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(SDL2 REQUIRED)

add_executable(GameBoyEmulator
    src/audio.c
    src/cpu.c
    src/cartridge.c
    src/instructions.c
    src/emulator.c
    src/controls.c
    src/display.c
    src/main.c
)

target_include_directories(GameBoyEmulator PRIVATE include)
target_link_libraries(GameBoyEmulator PRIVATE SDL2::SDL2)