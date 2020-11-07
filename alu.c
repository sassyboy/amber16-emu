#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/**
 * This module emulates an ALU using sixteen 74F153 (Dual 4-input multiplexer)
 * and four 74F283 (4-bit adder) and a custom logic to detect zero
 **/


void amber16_alu(bool cin, uint8_t func, uint16_t op1, uint16_t op2, uint16_t* res, bool nOE, bool* zf, bool* sf, bool* cf){
    
}
