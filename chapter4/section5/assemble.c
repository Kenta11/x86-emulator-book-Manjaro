#include "assemble.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "fat.h"

static void PrintDB(const char *str) {
  printf("    db %d\n", *(uint8_t *)str);
}

static void PrintDW(const char *str) {
  printf("    dw %d\n", *(uint16_t *)str);
}

static void PrintDD(const char *str) {
  printf("    dd %d\n", *(uint32_t *)str);
}

static void PrintString(const char *str, size_t s) {
  printf("    db \"");
  for (size_t i = 0; i < s; i++) {
    putchar(str[i]);
  }
  printf("\"\n");
}

static void PrintLabel(const char *str) { printf("%s:\n", str); }

static void PrintBPBStructure(const char *str) {
  if (str[0] == (char)0xEB && str[2] == (char)0x90) {
    printf("    jmp short entry\n");
    printf("    nop\n");
  } else if (str[0] == (char)0xEB) {
    printf("    jmp entry\n");
  } else {
    fprintf(stderr, "Unknown opecode: %02x\n", str[0]);
    exit(1);
  }

  PrintString(&str[3], 8);
  PrintDW(&str[11]);
  PrintDB(&str[13]);
  PrintDW(&str[14]);
  PrintDB(&str[16]);
  PrintDW(&str[17]);
  PrintDW(&str[19]);
  PrintDB(&str[21]);
  PrintDW(&str[22]);
  PrintDW(&str[24]);
  PrintDW(&str[26]);
  PrintDD(&str[28]);
  PrintDD(&str[32]);
}

static void PrintFAT32AssebmlyCode(const char *str) {
  PrintBPBStructure(str);

  PrintDD(&str[36]);
  PrintDW(&str[40]);
  PrintDW(&str[42]);
  PrintDD(&str[44]);
  PrintDW(&str[48]);
  PrintDW(&str[50]);
  printf("    times 64 - ($ - $$) db 0\n");
  PrintDB(&str[64]);
  PrintDB(&str[65]);
  PrintDB(&str[66]);
  PrintDD(&str[67]);
  PrintString(&str[71], 11);
  PrintString(&str[82], 8);
  PrintLabel("entry");
  putchar('\n');
  printf("    times 510 - ($ - $$) db 0\n");
  printf("    db 0x55, 0xaa\n");
}

static void PrintFAT12orFAT16AssemblyCode(const char *str) {
  PrintBPBStructure(str);

  PrintDB(&str[36]);
  PrintDB(&str[37]);
  PrintDB(&str[38]);
  PrintDD(&str[39]);
  PrintString(&str[43], 11);
  PrintString(&str[54], 8);
  PrintLabel("entry");
  putchar('\n');
  printf("    times 510 - ($ - $$) db 0\n");
  printf("    db 0x55, 0xaa\n");
}

void PrintAssemblyCode(const char *str) {
  switch (ParseFATType((const struct FATCommonHeader *)str)) {
  case 32:
    PrintFAT32AssebmlyCode(str);
    break;
  default:
    PrintFAT12orFAT16AssemblyCode(str);
    break;
  }
}
