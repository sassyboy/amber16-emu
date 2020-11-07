#include <stdlib.h>
#include <stdio.h>

#include "amber16.h"

void load_firmware(char* file){
    FILE* fd = fopen(file, "rb");
    uint16_t buff;
    uint32_t addr = 0;
    while (fread(&buff, 2, 1, fd)){
        amber16_memory(0, 0, 1, &buff, (uint8_t)addr>>16, (uint16_t)addr & 0xFFFF);
        addr++;
    }
    fclose(fd);
}

int main(int argc, char** argv){
    if (argc < 2){
        printf("Usage: amber16 mem_file\n");
        return 0;
    }
    load_firmware(argv[1]);

    //Test code
    uint16_t op1, op2;
    amber16_regfile(0, 0, 1, 1, 0, &op1, &op2, 1209); // reg[0] = 1209
    printf("op1 = %u, op2 = %u\n", op1, op2);
    amber16_regfile(3, 0, 1, 0, 0, &op1, &op2, 123); // reg[3] = 1 && op2 = reg[0]
    printf("op1 = %u, op2 = %u\n", op1, op2);
    amber16_regfile(0, 3, 0, 0, 1, &op1, &op2, 555); // op1 = reg[0], op2 = reg[3]
    printf("op1 = %u, op2 = %u\n", op1, op2);
    return 0;
}
