#ifndef EMULATOR_H
#define EMULATOR_H

#include <stdio.h>


#include "../include/cpu.h"
#include "../include/cartridge.h"
#include "../include/display.h"
#include "../include/audio.h"
#include "../include/controls.h"


/* Forward declarations */
typedef struct display display_t;

typedef struct Emulator
{
    cpu_t *CPU;
    cartridge_t *cartridge;
    display_t *display;
    audio_t *audio;
    controls_t *controls;

} Emulator_t;


Emulator_t *emulator_create(uint8_t *rom);
void emulator_run(Emulator_t *emu);
void emulator_destroy(Emulator_t *emu);

#endif // EMULATOR_H