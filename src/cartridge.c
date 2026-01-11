#include "../include/cartridge.h"

cartridge_t* initialize_cartridge(uint8_t *rom)
{
    cartridge_t* cartridge = malloc(sizeof(cartridge_t));
    if(cartridge == NULL)
    {
        fprintf(stderr, "ERROR: NULL handle \n");
        exit(-1);
    } 

    // Intialize everything in the struct to 0
    memset(cartridge, 0, sizeof(cartridge_t));

    cartridge->rom = rom;

    return cartridge;
}