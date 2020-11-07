#ifndef AMBER16_H
#define AMBER16_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// Clock
void amber16_clock_rise();
void anber16_clock_fall();

// ALU
void amber16_alu(bool cin, uint8_t func, uint16_t op1, uint16_t op2, uint16_t* res, bool nOE, bool* zf, bool* sf, bool* cf);

// Memory module
void amber16_memory(bool nCE, bool nLE, bool nOE, uint16_t* data, uint8_t addr_16_18, uint16_t addr_0_15);
void amber16_memory_dump(char * filename);

// Register file
void amber16_regfile(uint8_t s1, uint8_t s2, bool nRE1, bool nRE2, bool nWE1, uint16_t* r1, uint16_t* r2, uint16_t w1);
#endif
