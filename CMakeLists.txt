cmake_minimum_required(VERSION 3.20)
project("GameBoyEmulator")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


add_executable(GameBoyEmulator
    src/audio.c
    src/cpu.c
    src/cartridge.c
    src/instructions.c
    src/main.c
)

target_include_directories(GameBoyEmulator PRIVATE include)
