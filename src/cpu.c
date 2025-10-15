#include "../include/cpu.h"
#include "../include/cartridge.h"


cpu_t* initialize_CPU()
{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
    cpu_t* CPU = malloc(sizeof(cpu_t));
    if(CPU == NULL)
    {
        fprintf(stderr, "ERROR: NULL handle \n");
        exit(-1);
    } 

    // Intialize everything in the struct to 0
    memset(CPU, 0, sizeof(cpu_t));

    return CPU;
}


/*
 The boot sequence in the LR35902 Game Boy CPU is an unskipable 256 bytes ROM,
 that intializes hardware, displays the Nintendo logo with a sound and verifies the
 inserted cartridge.
*/
int boot_sequence(cpu_t* CPU, cartridge_t* cartridge) 
{
    
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

    write_io_register(CPU, 0xFF26, CPU->A);
    write_io_register(CPU, 0xFF00 + CPU->C, CPU->A);

    CPU->C++;
    CPU->A = 0xF3;
    
    write_io_register(CPU, 0xFF00 + CPU->C, CPU->A);
    write_io_register(CPU, 0xFF25, CPU->A);

    CPU->A = 0x77;

    write_io_register(CPU, 0xFF24, CPU->A);



    // Set up BGP (Background Pallet Register)

    CPU->A = 0xFC;
    write_io_register(CPU, 0xFF47, CPU->A);


    // Load the nintendo logo in the cartridge header into the game boys VRAM
    // We do these same few lines a little later in this boot sequence.
    // We could easily combine them for simplicity but to maintain
    // high emualtion accuracy, we will keep them seperate for now
    load_logo_to_VRAM(CPU, cartridge);

    




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
    // Note that this does NOT load the logo into the VRAM section of memory
    // This is loaded here to be used for the logo comparison routine
    // This bitmap is also loaded into VRAM earlier on in the boot ROM
    // by pointing to the logo data in the CARTRIDGE header and loading it that way.
    memcpy(&CPU->memory[0xa8], logo, 48);




    // Trademark symbol in upper right next to logo
    uint8_t trademark_symbol[8] = {
    0x3c, 0x42, 0xb9, 0xa5, 0xb9, 0xa5, 0x42, 0x3c
    };
    
    // Load the trademark symbol into memory 0xd8 -> 0xdf
    memcpy(&CPU->memory[0xd8], trademark_symbol, 8);


    // Jump to the start of the cartridge header
    uint16_t offset = 0x0104;
    int result = fseek(cartridge->file, offset, SEEK_SET);

    if(result != 0)
    {
        fprintf(stderr, "Failed to jump to offset %d in cartridge\n", offset);
        exit(-1);
    }

    // Holds the catridge header
    uint8_t logo_buffer[48];

    size_t bytes_to_read = sizeof(logo_buffer); 
    size_t bytes_read = fread(logo_buffer, 1, bytes_to_read, cartridge->file);


    if (bytes_read < bytes_to_read) 
    {
        if (feof(cartridge->file)) 
        {
            fprintf(stderr,"Stopped reading cartridge header prematurely.\n");
        } 
        else if (ferror(cartridge->file)) 
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
            exit(-1);
        }
    }

    

    fprintf(stdout, "Header OK.\n");


    // Checksum is from 0x0134 - 0x014C (24 bytes)
    uint8_t checksum_buffer[25];

    bytes_to_read = sizeof(checksum_buffer); 
    bytes_read = fread(checksum_buffer, 1, bytes_to_read, cartridge->file);

    if (bytes_read < bytes_to_read) 
    {
        if (feof(cartridge->file)) 
        {
            fprintf(stderr,"Stopped reading cartridge header prematurely.\n");
        } 
        else if (ferror(cartridge->file)) 
        {
            fprintf(stderr, "Error reading cartridge header.\n");
        }
        exit(-1);
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
    fread(&expected_checksum, 1, 1, cartridge->file);
    
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

    return 0;
}






// IO registers are from 0xFF00 - 0xFF7F
void write_io_register(cpu_t* CPU, uint16_t address, uint8_t value)
{
    switch(address)
    {
        case 0xFF00:        
            break;
        case 0xFF01:          
            break;
        case 0xFF02:
            break;
        case 0xFF04:
            break;
        case 0xFF05:
            break;
        case 0xFF06:
            break;
        case 0xFF07:
            break;    
        case 0xFF0F:
            break;
        case 0xFF10:
            break;
        case 0xFF11:
            write_audio_registers(CPU, address, value);
            break;
        case 0xFF12:
            write_audio_registers(CPU, address, value);
            break;
        case 0xFF13:
            break;
        case 0xFF14:
            break;
        case 0xFF16:
            break;
        case 0xFF17:
            break;
        case 0xFF18:
            break;
        case 0xFF19:
            break;
        case 0xFF1A:
            break;
        case 0xFF1B:
            break;
        case 0xFF1C:
            break;
        case 0xFF1D:
            break;
        case 0xFF1E:
            break;
        case 0xFF20:
            break;
        case 0xFF21:
            break;
        case 0xFF22:
            break;
        case 0xFF23:
            break;
        case 0xFF24:
            break;
        case 0xFF25:
            write_audio_registers(CPU, address, value);
            break;
        case 0xFF26:
            write_audio_registers(CPU, address, value);
            break;
        case 0xFF30:
            break;
        case 0xFF31:
            break;
        case 0xFF32:
            break;
        case 0xFF33:
            break;
        case 0xFF34:
            break;
        case 0xFF35:
            break;
        case 0xFF36:
            break;
        case 0xFF37:
            break;
        case 0xFF38:
            break;
        case 0xFF39:
            break;
        case 0xFF3A:
            break;
        case 0xFF3B:
            break;
        case 0xFF3C:
            break;
        case 0xFF3D:
            break;
        case 0xFF3E:
            break;
        case 0xFF3F:
            break;
        case 0xFF40:
            break;
        case 0xFF41:
            break;
        case 0xFF42:
            break;
        case 0xFF43:
            break;
        case 0xFF44:
            break;
        case 0xFF45:
            break;
        case 0xFF46:
            break;
        case 0xFF47: // BG color palette register
            update_bg_palette_reg(CPU, address, value);
            break;
        case 0xFF48:
            break;
        case 0xFF49:
            break;
        case 0xFF4A:
            break;
        case 0xFF4B:
            break;
        case 0xFF4C:
            break;
        case 0xFF4D:
            break;
        case 0xFF4F:
            break;
        case 0xFF50:
            break;
        case 0xFF51:
            break;
        case 0xFF52:
            break;
        case 0xFF53:
            break;
        case 0xFF54:
            break;
        case 0xFF55:
            break;
        case 0xFF56:
            break;
        case 0xFF68:
            break;
        case 0xFF69:
            break;
        case 0xFF6A:
            break;
        case 0xFF6B:
            break;
        case 0xFF6C:
            break;
        case 0xFF70:
            break;
        case 0xFF76:
            break;
        case 0xFF77:
            break;
        case 0xFFFF:
            break;

        default:
            fprintf(stderr, "Unkown Register at Address: %02x \n", address);
            exit(-1);
    }
}


void update_bg_palette_reg(cpu_t* CPU, uint16_t address, uint8_t value)
{
    
    CPU->memory[address] = value;

    // Decode 2-bit mapping
    CPU->bg_palette_mapping[0] = value & 0x03;
    CPU->bg_palette_mapping[1] = (value >> 2) & 0x03;
    CPU->bg_palette_mapping[2] = (value >> 4) & 0x03;
    CPU->bg_palette_mapping[3] = (value >> 6) & 0x03;
}

void load_logo_to_VRAM(cpu_t* CPU, cartridge_t* cartridge)
{
    
}
