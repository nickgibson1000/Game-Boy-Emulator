#include <stdio.h>
#include "../include/cpu.h"



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

    void *CPU = initialize();
    boot_sequence(CPU, file);


    return 0;
}