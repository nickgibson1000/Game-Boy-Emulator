#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char filename[256];
    uint8_t* rom; // Cartridge
    uint8_t memory[0x8000]; // 32KB (RIGHT NOW WE ASSUME NO BANK SWITCHING)
} cartridge_t;

cartridge_t* initialize_cartridge(uint8_t *rom);

#endif // CARTRIDGE_H