#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    uint8_t A, F, B, C, D, E, H, L;
    uint16_t PC, SP;
    uint8_t memory[0x10000]; // 64KB
} cpu_t;

void *initialize();
int boot_sequence(void *CPU, FILE* cartridge);


#endif // CPU_H