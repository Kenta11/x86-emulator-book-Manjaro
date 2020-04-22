#include "fat.h"

#include <stdint.h>
#include <stdio.h>

static unsigned char
parseFATType(const char* str);

static void
printBPBStructure(const char* str);

static void
printBSStructureFAT16(const char* str);

static void
printBSStructureFAT32(const char* str);

void
printPBR(const char *str) {
    unsigned char fat_type = parseFATType(str);

    printf("Calculated fat type is FAT%d\n", fat_type);

    printBPBStructure(str);

    switch(fat_type) {
        case 32:
            printBSStructureFAT32(str);
            break;
        default:
            printBSStructureFAT16(str);
            break;
    }
}

static unsigned char
parseFATType(const char *str) {
    switch(*(uint16_t*)&str[17]) {
        case 0:
            return 32;
        case 512:
            return 16;
        default:
            return 12;
    }
}

static void
printBPBStructure(const char* str) {
    printf("%-20s %02x %02x %02x\n", "BS_jmpBoot:", (uint8_t)str[0], (uint8_t)str[1], (uint8_t)str[2]);

    printf("%-20s ", "BS_OEMName:");
    for (int i = 3; i < 3 + 8; i++) {
        putchar(str[i]);
    }
    putchar('\n');

    printf("%-20s %u\n", "BPB_BytsPerSec:", *(uint16_t*)&str[11]);

    printf("%-20s %u\n", "BPB_SecPerClus:", *(uint8_t*)&str[13]);

    printf("%-20s %u\n", "BPB_RsvdSecCnt:", *(uint16_t*)&str[14]);

    printf("%-20s %u\n", "BPB_NumFATs:", *(uint8_t*)&str[16]);

    printf("%-20s %u\n", "BPB_RootEntCnt:", *(uint16_t*)&str[17]);

    printf("%-20s %u\n", "BPB_TotSec16:", *(uint16_t*)&str[19]);

    printf("%-20s %02x\n", "BPB_Media:", *(uint8_t*)&str[21]);

    printf("%-20s %u\n", "BPB_FATSz16:", *(uint16_t*)&str[22]);

    printf("%-20s %u\n", "BPB_SecPerTrk:", *(uint16_t*)&str[24]);

    printf("%-20s %u\n", "BPB_NumHeads:", *(uint16_t*)&str[26]);

    printf("%-20s %u\n", "BPB_HiddSec:", *(uint32_t*)&str[28]);

    printf("%-20s %u\n", "BPB_TotSec32:", *(uint32_t*)&str[32]);
}

static void
printBSStructureFAT16(const char* str) {
    printf("%-20s %u\n", "BS_DrvNum:", *(uint8_t*)&str[36]);

    printf("%-20s %u\n", "BS_Reserved1:", *(uint8_t*)&str[37]);

    printf("%-20s %u\n", "BS_BootSig:", *(uint8_t*)&str[38]);

    printf("%-20s %u\n", "BS_VolID:", *(uint32_t*)&str[39]);

    printf("%-20s ", "BS_VolLab:");
    for (int i = 43; i < 43 + 11; i++) {
        putchar(str[i]);
    }
    putchar('\n');

    printf("%-20s ", "BS_FilSysType:");
    for (int i = 54; i < 54 + 8; i++) {
        putchar(str[i]);
    }
    putchar('\n');
}

static void
printBSStructureFAT32(const char* str) {
    printf("%-20s %u\n", "BS_DrvNum:", *(uint8_t*)&str[64]);

    printf("%-20s %u\n", "BS_Reserved1:", *(uint8_t*)&str[65]);

    printf("%-20s %u\n", "BS_BootSig:", *(uint8_t*)&str[65]);

    printf("%-20s %u\n", "BS_VolID:", *(uint32_t*)&str[67]);

    printf("%-20s ", "BS_VolLab:");
    for (int i = 71; i < 71 + 11; i++) {
        putchar(str[i]);
    }
    putchar('\n');

    printf("%-20s ", "BS_FilSysType:");
    for (int i = 82; i < 82 + 8; i++) {
        putchar(str[i]);
    }
    putchar('\n');
}
