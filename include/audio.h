#ifndef AUDIO_H
#define AUDIO_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

typedef struct audio
{

} audio_t;

// Forward declaration of cpu_t
typedef struct cpu cpu_t;

audio_t *initialize_audio();

void write_audio_registers(cpu_t* CPU, uint16_t address, uint8_t value);


#endif // AUDIO_H