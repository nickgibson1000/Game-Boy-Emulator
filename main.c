#include <stdio.h>
#include "cpu.h"



int main(void)
{
    void *CPU = intialize();
    boot_sequence(CPU);


    return 0;
}