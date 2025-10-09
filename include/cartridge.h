#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>



typedef struct {
    char filename[256];
    uint8_t cartridge[0x8000]; // 32KB (RIGHT NOW WE ASSUME NO BANK SWITCHING)
} cartridge_t;


#endif // CPU_H