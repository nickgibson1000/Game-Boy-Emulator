#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "audio.h"

typedef struct {
    uint8_t A, F, B, C, D, E, H, L;
    uint16_t PC, SP;
    uint8_t memory[0x10000]; // 64KB
} cpu_t;

void* initialize_CPU();
int boot_sequence(void* CPU_HANDLE, void* CARTRIDGE_HANDLE);
void write_io_register(void* CPU_HANDLE, uint16_t address, uint8_t value);


#endif // CPU_H