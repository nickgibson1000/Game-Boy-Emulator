#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct {
    char filename[256];
    FILE* file;
    uint8_t memory[0x8000]; // 32KB (RIGHT NOW WE ASSUME NO BANK SWITCHING)
} cartridge_t;

void* intialize_cartridge(FILE* cartridge_file);

#endif // CARTRIDGE_H