#include <stdio.h>
#include "../include/emulator.h"



int main(int argc, char** argv)
{

    if (argc < 2) 
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file;
    file = fopen(argv[1], "rb");

    if (file == NULL) {
        printf("Error: Could not open file %s\n", argv[1]);
        return 1;
    }

    // Store the rom file as a uint buffer
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    
    uint8_t *rom = malloc(size);
    fread(rom, 1, size, file);
    fclose(file);



    Emulator_t *emu = emulator_create(rom);
    emulator_run(emu);


    return 0;
}