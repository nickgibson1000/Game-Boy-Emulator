#include "test_framework.h"


int main(void)
{   
    test_initializations();
    test_CPUPostBootRom();


    printf("\n");
    printf("Tests Passed: %i\n", passed_tests);
    printf("Tests Failed: %i\n", failed_tests);
    printf("Total Tests : %i\n", total_tests);
    return 0;
}

// Intialize Emulator and all its subsystems
void build_up_tests()
{

}

// Free all memory used
void tear_down_tests()
{
    
}


void test_initializations()
{
    uint8_t *fake_rom = 0;
    Emulator_t *emulator = emulator_create(fake_rom);

    ASSERT_NOT_EQUAL(emulator, NULL);
    ASSERT_NOT_EQUAL(emulator->CPU, NULL);
    ASSERT_NOT_EQUAL(emulator->cartridge, NULL);
    ASSERT_NOT_EQUAL(emulator->audio, NULL);
    ASSERT_NOT_EQUAL(emulator->controls, NULL);
}


void test_CPUPostBootRom()
{

}