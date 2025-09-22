#include "cpu.h"


void *initialize()
{
    cpu_t *CPU = malloc(sizeof(cpu_t));
    if(CPU == NULL)
    {
        fprintf(stderr, "ERROR: NULL handle \n");
    }

    return (void *)CPU;
}

int boot_sequence(void *CPU_HANDLE) 
{
    // Grab handle
    cpu_t *CPU = (cpu_t*) CPU_HANDLE;


    // Set our program counter to memory address 0x00
    CPU->PC = 0x0100; // Execution starts here
    CPU->SP = 0xFFFE; // Top of stack
    CPU->A = 0x0000;
    CPU->memory[0xFF50] = 0x0001; // Set value telling system to disable boot ROM

    // Intialize VRAM section of memory to 0
    for(int i = 0x8000; i <= 0x9FFF; i++) {
        CPU->memory[i] = 0;
    }

    




}