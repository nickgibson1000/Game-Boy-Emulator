#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "audio.h"
#include "cartridge.h"

typedef struct cpu {
    uint8_t A, F, B, C, D, E, H, L;
    uint16_t HL;
    uint16_t PC, SP;
    uint8_t bg_palette_mapping[4]; // Stores 4 shades of greyscale
    uint8_t memory[0x10000]; // 64KB
} cpu_t;

cpu_t* initialize_CPU();
int boot_sequence(cpu_t* CPU, cartridge_t* cartridge);
void write_io_register(cpu_t* CPU, uint16_t address, uint8_t value);
void update_bg_palette_reg(cpu_t* CPU, uint16_t address, uint8_t value);
void load_logo_to_VRAM(cpu_t* CPU, cartridge_t* cartridge);
uint8_t left_shift_byte(uint8_t* value);
uint8_t right_shift_byte(uint8_t* value);
void read_in_buffer(uint8_t* buffer, size_t buffer_size, uint16_t offset, FILE* file);

void rotate_left_carry(cpu_t* CPU, uint8_t* value);
void rotate_right_carry(cpu_t* CPU, uint8_t* value);



#endif // CPU_H