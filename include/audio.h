#ifndef AUDIO_H
#define AUDIO_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

// Forward declaration of cpu_t
typedef struct cpu cpu_t;

void write_audio_registers(cpu_t* CPU, uint16_t address, uint8_t value);

#endif // AUDIO_H