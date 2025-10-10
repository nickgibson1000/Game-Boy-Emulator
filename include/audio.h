#ifndef AUDIO_H
#define AUDIO_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"

void write_audio_registers(void* CPU_HANDLE, uint16_t address, uint8_t value);

#endif // AUDIO_H