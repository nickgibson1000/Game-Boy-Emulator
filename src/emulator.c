#include "../include/emulator.h"



Emulator_t *emulator_create(uint8_t *rom)
{

    Emulator_t *emulator = malloc(sizeof(Emulator_t));
    if(emulator == NULL)
    {
        fprintf(stderr, "ERROR: NULL emulator handle \n");
        exit(-1);
    }

    // Intialize subsystems
    emulator->CPU = initialize_CPU();                            // Good
    emulator->cartridge = initialize_cartridge(rom);             // Good
    emulator->display = initialize_display();                    // Good
    emulator->audio = initialize_audio();
    emulator->controls = initialize_controls();
    emulator_run(emulator);


    return emulator;
}


void emulator_run(Emulator_t *emu)
{

    // CPU boot sequence
    boot_sequence(emu->CPU, emu->cartridge);

    //SDL_RenderClear(emu->display->renderer);
    //SDL_RenderPresent(emu->display->renderer);
    //SDL_Delay(5000);

}


void emulator_destroy(Emulator_t *emu)
{


    cleanup_display(emu->display);

}