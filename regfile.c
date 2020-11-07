#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/**
 * This module emulates a dual-port register file (2 reads, 1 write)
 * consisting 4x16BIT registers using 8 74HC670 chips, a 16-bit.
 * 74HC670s allow simultaneous writing into one location
 * while reading another.
 * This does not include the input/output port registers or the
 * flags register
 **/
static uint16_t port1[4];
static uint16_t port2[4];

void amber16_regfile(uint8_t s1, uint8_t s2, bool nRE1, bool nRE2, bool nWE1, uint16_t* r1, uint16_t* r2, uint16_t w1){
    if (!nWE1){ // Port 1 can be only read or written, not both
        port1[s1 & 0x3] = port2[s1 & 0x3] = w1;
    } else if (!nRE1){
        *r1 = port1[s1 & 0x3];
    }
    // Port 2 can be always read
    if (!nRE2)
        *r2 = port2[s2 & 0x3];
    
    //Report errors
    //1) Trying to read and write to the same register at the same time
    if (!nWE1 && !nRE1)
        printf("ERROR in %s: nWE1 and nRE1 active at the same time\n", __FUNCTION__);
    if (!nWE1 && !nRE2 && (s1 & 0x3) == (s2 & 0x3))
        printf("ERROR in %s: nWE1 and nRE2 active and s1==s2 at the same time\n", __FUNCTION__);
}
