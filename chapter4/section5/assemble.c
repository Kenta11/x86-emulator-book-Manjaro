#include "assemble.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

static unsigned char
parseFATType(const char* str);

static void
printBPBStructure(const char* str);

static void
printAssemblyCodeForFAT32(const char* str);

static void
printAssemblyCodeForFAT16(const char* str);

static void
printdb(const char* str);

static void
printdw(const char* str);

static void
printdd(const char* str);

static void
printString(const char* str, size_t s);

static void
printLabel(const char* str);

void
printAssemblyCode(const char *str) {
    switch(parseFATType(str)) {
        case 32:
            printAssemblyCodeForFAT32(str);
            break;
        default:
            printAssemblyCodeForFAT16(str);
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
printAssemblyCodeForFAT32(const char* str) {
    printBPBStructure(str);

    printdd(&str[36]);
    printdw(&str[40]);
    printdw(&str[42]);
    printdd(&str[44]);
    printdw(&str[48]);
    printdw(&str[50]);
    printf("    times 64 - ($ - $$) db 0\n");
    printdb(&str[64]);
    printdb(&str[65]);
    printdb(&str[66]);
    printdd(&str[67]);
    printString(&str[71], 11);
    printString(&str[82], 8);
    printLabel("entry");
    putchar('\n');
    printf("    times 510 - ($ - $$) db 0\n");
    printf("    db 0x55, 0xaa\n");
}

static void
printAssemblyCodeForFAT16(const char* str) {
    printBPBStructure(str);

    printdb(&str[36]);
    printdb(&str[37]);
    printdb(&str[38]);
    printdd(&str[39]);
    printString(&str[43], 11);
    printString(&str[54], 8);
    printLabel("entry");
    putchar('\n');
    printf("    times 510 - ($ - $$) db 0\n");
    printf("    db 0x55, 0xaa\n");
}

static void
printBPBStructure(const char* str) {
    if (str[0] == (char)0xEB && str[2] == (char)0x90) {
        printf("    jmp short entry\n");
        printf("    nop\n");
    } else if (str[0] == (char)0xEB) {
        printf("    jmp entry\n");
    } else {
        fprintf(stderr, "Unknown opecode: %02x\n", str[0]);
        exit(1);
    }

    printString(&str[3], 8);
    printdw(&str[11]);
    printdb(&str[13]);
    printdw(&str[14]);
    printdb(&str[16]);
    printdw(&str[17]);
    printdw(&str[19]);
    printdb(&str[21]);
    printdw(&str[22]);
    printdw(&str[24]);
    printdw(&str[26]);
    printdd(&str[28]);
    printdd(&str[32]);
}

static void
printdb(const char* str) {
    printf("    db %d\n", *(uint8_t*)str);
}

static void
printdw(const char* str) {
    printf("    dw %d\n", *(uint16_t*)str);
}

static void
printdd(const char* str) {
    printf("    dd %d\n", *(uint32_t*)str);
}

static void
printString(const char* str, size_t s) {
    printf("    db \"");
    for (size_t i = 0; i < s; i++) {
        putchar(str[i]);
    }
    printf("\"\n");
}

static void
printLabel(const char* str) {
    printf("%s:\n", str);
}
