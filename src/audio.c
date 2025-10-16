#include "../include/audio.h"
#include "../include/cpu.h"


void write_audio_registers(cpu_t* CPU, uint16_t address, uint8_t value)
{
    CPU->memory[address] = value;
}