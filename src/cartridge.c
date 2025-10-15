#include "../include/cartridge.h"

cartridge_t* intialize_cartridge(FILE* cartridge_file)
{
    cartridge_t* cartridge = malloc(sizeof(cartridge_t));
    if(cartridge == NULL)
    {
        fprintf(stderr, "ERROR: NULL handle \n");
        exit(-1);
    } 

    // Intialize everything in the struct to 0
    memset(cartridge, 0, sizeof(cartridge_t));

    cartridge->file = cartridge_file;

    return cartridge;
}