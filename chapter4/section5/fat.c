#include "fat.h"

#include <stdint.h>
#include <stdio.h>

unsigned char ParseFATType(const struct FATCommonHeader *fat) {
  switch (fat->BPB_RootEntCnt) {
  case 0:
    return 32;
  case 512:
    return 16;
  default:
    return 12;
  }
}

static void PrintBPBStructure(const struct FATCommonHeader *fat) {
  printf("%-20s", "BS_jmpBoot:");
  for (int i = 0; i < 3; i++) {
    printf(" %02x", fat->BS_jmpBoot[i]);
  }
  putchar('\n');

  printf("%-20s ", "BS_OEMName:");
  for (int i = 0; i < 8; i++) {
    putchar(fat->BS_OEMName[i]);
  }
  putchar('\n');

  printf("%-20s %u\n", "BPB_BytsPerSec:", fat->BPB_BytsPerSec);
  printf("%-20s %u\n", "BPB_SecPerClus:", fat->BPB_SecPerClus);
  printf("%-20s %u\n", "BPB_RsvdSecCnt:", fat->BPB_RsvdSecCnt);
  printf("%-20s %u\n", "BPB_NumFATs:", fat->BPB_NumFATs);
  printf("%-20s %u\n", "BPB_RootEntCnt:", fat->BPB_RootEntCnt);
  printf("%-20s %u\n", "BPB_TotSec16:", fat->BPB_TotSec16);
  printf("%-20s %02x\n", "BPB_Media:", fat->BPB_Media);
  printf("%-20s %u\n", "BPB_FATSz16:", fat->BPB_FATSz16);
  printf("%-20s %u\n", "BPB_SecPerTrk:", fat->BPB_SecPerTrk);
  printf("%-20s %u\n", "BPB_NumHeads:", fat->BPB_NumHeads);
  printf("%-20s %u\n", "BPB_HiddSec:", fat->BPB_HiddSec);
  printf("%-20s %u\n", "BPB_TotSec32:", fat->BPB_TotSec32);
}

static void PrintBSStructureFat12orFAT16(const struct FATHeader *fat) {
  printf("%-20s %u\n", "BS_DrvNum:", fat->fat12_and_fat16.BS_DrvNum);
  printf("%-20s %u\n", "BS_Reserved1:", fat->fat12_and_fat16.BS_Reserved1);
  printf("%-20s %u\n", "BS_BootSig:", fat->fat12_and_fat16.BS_BootSig);
  printf("%-20s %u\n", "BS_VolID:", fat->fat12_and_fat16.BS_VolID);

  printf("%-20s ", "BS_VolLab:");
  for (int i = 0; i < 11; i++) {
    putchar(fat->fat12_and_fat16.BS_VolLab[i]);
  }
  putchar('\n');

  printf("%-20s ", "BS_FilSysType:");
  for (int i = 0; i < 8; i++) {
    putchar(fat->fat12_and_fat16.BS_FilSysType[i]);
  }
  putchar('\n');
}

static void PrintBSStructureFAT32(const struct FATHeader *fat) {
  printf("%-20s %u\n", "BS_DrvNum:", fat->fat32.BS_DrvNum);
  printf("%-20s %u\n", "BS_Reserved1:", fat->fat32.BS_Reserved1);
  printf("%-20s %u\n", "BS_BootSig:", fat->fat32.BS_BootSig);
  printf("%-20s %u\n", "BS_VolID:", fat->fat32.BS_VolID);

  printf("%-20s ", "BS_VolLab:");
  for (int i = 0; i < 11; i++) {
    putchar(fat->fat32.BS_VolLab[i]);
  }
  putchar('\n');

  printf("%-20s ", "BS_FilSysType:");
  for (int i = 0; i < 8; i++) {
    putchar(fat->fat32.BS_FilSysType[i]);
  }
  putchar('\n');
}

void PrintPBR(const struct FATHeader *fat) {
  unsigned char fat_type = ParseFATType(&fat->common);

  printf("Calculated fat type is FAT%d\n", fat_type);

  PrintBPBStructure(&fat->common);

  switch (fat_type) {
  case 32:
    PrintBSStructureFAT32(fat);
    break;
  default:
    PrintBSStructureFat12orFAT16(fat);
    break;
  }
}
