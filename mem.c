#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
/**
 * This module emulates 1MB of AS6C4008 (512K x 8BIT) static memory
 * The two chipsets are put together to construct a 512K x 16BIT memory
 * Therefore, each word is 16 bits and the memory capacity is 512KWords
 * 
 * Logically, the memory is segmented into 8 segments. The size of
 * each segment is 2^16 x 16BITS = 128KB = 64KWords
 **/
#define MEMSIZE_WORDS (512*1024)
static uint8_t mem_l[MEMSIZE_WORDS];
static uint8_t mem_h[MEMSIZE_WORDS];

/**
 * @fn amber16_memory
 * @param nCE: ChipEnable signal (Active Low, IN)
 * @param nLE: LoadEnable signal (Active Low, IN)
 * @param nOE: OutputEnable signal (Active Low, IN)
 * @param data: D15...D0 signals (IN/OUT)
 * @param addr_16_18: A18..A16 signals (IN) - Used for the segment number part of the address
 * @param addr_0_15:  A15..A0 signals (IN) - Offest part of the address
 */
void amber16_memory(bool nCE, bool nLE, bool nOE, uint16_t* data, uint8_t addr_16_18, uint16_t addr_0_15){
    int addr = (((int)addr_16_18)<<16) | (int)addr_0_15;
    if (nCE) // Chip not enabled
        return; 
    else if (!nCE && nLE && nOE) // Chip enabled but no I/O operation active
        return;
    else if (!nCE && nLE && !nOE) // READ
        *data = (((uint16_t)mem_h[addr])<<8) | mem_l[addr];
    else if (!nCE && !nLE){ // WRITE
        mem_h[addr] = (uint8_t)((*data)>>8);
        mem_l[addr] = (uint8_t)((*data) & 0xFF);
    }
}

/**
 * @fn amber16_memory_dump
 * @brief For debuggin purposes
 */
void amber16_memory_dump(char * filename){
    FILE* fd = fopen(filename, "wb");
    uint32_t i;
    uint16_t buf;
    for (i = 0 ; i < MEMSIZE_WORDS ; i++){
        amber16_memory(0, 1, 0, &buf, (uint8_t)(i>>16), (uint16_t)(i & 0xFFFF));
        fwrite(&buf, 2, 1, fd);
    }
    fclose(fd);
}
