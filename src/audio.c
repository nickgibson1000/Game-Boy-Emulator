#include "../include/audio.h"
#include "../include/cpu.h"


void write_audio_registers(void* CPU_HANDLE, uint16_t address, uint8_t value)
{
    cpu_t* CPU = (cpu_t*) CPU_HANDLE;
    CPU->memory[address] = value;
}