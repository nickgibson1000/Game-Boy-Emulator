#include "../include/cpu.h"


void *initialize(FILE* cartridge)
{
    cpu_t *CPU = malloc(sizeof(cpu_t));
    if(CPU == NULL)
    {
        fprintf(stderr, "ERROR: NULL handle \n");
        exit(-1);
    } 

    // Intialize everything in the struct to 0
    memset(CPU, 0, sizeof(cpu_t));

    return (void *)CPU;
}


/*
 The boot sequence in the LR35902 Game Boy CPU is an unskipable 256 bytes ROM,
 that intializes hardware, displays the Nintendo logo with a sound and verifies the
 inserted cartridge.
*/
int boot_sequence(void *CPU_HANDLE, FILE* cartridge) 
{
    
    cpu_t *CPU = (cpu_t*) CPU_HANDLE;


    // Set our program counter to memory address 0x00
    CPU->PC = 0x0100; // Execution starts here
    CPU->SP = 0xFFFE; // Top of stack
    CPU->A = 0x0000; // Register A is set to 0
    

    // Intialize VRAM section of memory to 0
    for(int i = 0x8000; i <= 0x9FFF; i++) 
    {
        CPU->memory[i] = 0;
    }


    // Setup Audio

    CPU->C = 0x11;
    CPU->A = 0x80;

    CPU->memory[0xFF26] = CPU->A;
    CPU->memory[0xFF00 + CPU->C] = CPU->A;

    CPU->C++;
    CPU->A = 0xF3;
    
    CPU->memory[0xFF00 + CPU->C] = CPU->A;
    CPU->memory[0xFF25] = CPU->A;

    CPU->A = 0x77;
    CPU->memory[0xFF24] = CPU->A;


    // Set up BGP (Background Pallet Register)

    CPU->A = 0xFC;
    CPU->memory[0xFF47] = CPU->A;





    // Nintendo logo bitmap
    uint8_t logo[48] = {
    0xce, 0xed, 0x66, 0x66, 0xcc, 0x0d, 0x00, 0x0b,
    0x03, 0x73, 0x00, 0x83, 0x00, 0x0c, 0x00, 0x0d,
    0x00, 0x08, 0x11, 0x1f, 0x88, 0x89, 0x00, 0x0e,
    0xdc, 0xcc, 0x6e, 0xe6, 0xdd, 0xdd, 0xd9, 0x99,
    0xbb, 0xbb, 0x67, 0x63, 0x6e, 0x0e, 0xec, 0xcc,
    0xdd, 0xdc, 0x99, 0x9f, 0xbb, 0xb9, 0x33, 0x3e
    };

    // Load the bitmap into memory  0x00a8 -> 0x00d7
    memcpy(&CPU->memory[0xa8], logo, 48);




    // Trademark symbol in upper right next to logo
    uint8_t trademark_symbol[8] = {
    0x3c, 0x42, 0xb9, 0xa5, 0xb9, 0xa5, 0x42, 0x3c
    };
    
    // Load the trademark symbol into memory 0xd8 -> 0xdf
    memcpy(&CPU->memory[0xd8], trademark_symbol, 8);


    // Jump to the start of the cartridge header
    uint16_t offset = 0x0104;
    int result = fseek(cartridge, offset, SEEK_SET);

    if(result != 0)
    {
        fprintf(stderr, "Failed to jump to offset %d in cartridge\n", offset);
        return 1;
    }

    // Holds the catridge header
    uint8_t logo_buffer[48];

    size_t bytes_to_read = sizeof(logo_buffer); 
    size_t bytes_read = fread(logo_buffer, 1, bytes_to_read, cartridge);


    if (bytes_read < bytes_to_read) 
    {
        if (feof(cartridge)) 
        {
            fprintf(stderr,"Stopped reading cartridge header prematurely.\n");
        } 
        else if (ferror(cartridge)) 
        {
            fprintf(stderr, "Error reading cartridge header.\n");
        }
    }

    // Compare the header of the cartridge with the systems expected header
    for(int i = 0; i < sizeof(logo_buffer); i++)
    {
        if(logo_buffer[i] != logo[i])
        {
            fprintf(stderr, "Mismatch in header bytes at byte %d\n", i);
            fprintf(stderr, "Cartridge: %x\n",logo_buffer[i]);
            fprintf(stderr, "System: %x\n", logo[i]);
            return 1;
        }
    }

    

    fprintf(stdout, "Header OK.\n");


    // Checksum is from 0x0134 - 0x014C (24 bytes)
    uint8_t checksum_buffer[25];

    bytes_to_read = sizeof(checksum_buffer); 
    bytes_read = fread(checksum_buffer, 1, bytes_to_read, cartridge);

    if (bytes_read < bytes_to_read) 
    {
        if (feof(cartridge)) 
        {
            fprintf(stderr,"Stopped reading cartridge header prematurely.\n");
        } 
        else if (ferror(cartridge)) 
        {
            fprintf(stderr, "Error reading cartridge header.\n");
        }
    }

    uint8_t checksum = 0;

    // Compare the checksum of the cartridge with the systems expected checksum
    for(int i = 0; i < sizeof(checksum_buffer); i++)
    {

        checksum = checksum - checksum_buffer[i] - 1;
        fprintf(stdout, "%02X ", checksum_buffer[i]);
    }

    printf("\n");
    

    // DEBUG: Print checksum
    //fprintf(stdout, "\n%02X \n", checksum);

    // Read the actual checksum byte from ROM
    uint8_t expected_checksum;
    fread(&expected_checksum, 1, 1, cartridge);
    
    // DEBUG: Print the expected checksum value
    //fprintf(stdout, "%02x", stored_checksum);

    if(checksum != expected_checksum)
    {
        fprintf(stderr, "Checksum BAD.\n");
        return 1;
    }
    else
    {
        fprintf(stdout, "Checksum OK.\n");
    }

    // LD A, $01
    CPU->A = 1;
    CPU->memory[0xFF50] = CPU->A; // Disable boot ROM
}



void write_io_register(void* CPU_HANDLE, uint16_t address, uint8_t value)
{

    cpu_t *CPU = (cpu_t*) CPU_HANDLE;



}