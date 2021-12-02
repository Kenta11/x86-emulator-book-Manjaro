#ifndef FAT_H
#define FAT_H

#include <stdint.h>

struct __attribute__((packed)) FATCommonHeader {
  uint8_t BS_jmpBoot[3];
  char BS_OEMName[8];
  uint16_t BPB_BytsPerSec;
  uint8_t BPB_SecPerClus;
  uint16_t BPB_RsvdSecCnt;
  uint8_t BPB_NumFATs;
  uint16_t BPB_RootEntCnt;
  uint16_t BPB_TotSec16;
  uint8_t BPB_Media;
  uint16_t BPB_FATSz16;
  uint16_t BPB_SecPerTrk;
  uint16_t BPB_NumHeads;
  uint32_t BPB_HiddSec;
  uint32_t BPB_TotSec32;
};

struct __attribute__((packed)) FAT12andFAT16SpecificHeader {
  uint8_t BS_DrvNum;
  uint8_t BS_Reserved1;
  uint8_t BS_BootSig;
  uint32_t BS_VolID;
  char BS_VolLab[11];
  char BS_FilSysType[8];
};

struct __attribute__((packed)) FAT32SpecificHeader {
  uint32_t BPB_FATSz32;
  uint16_t BPB_ExtFlags;
  uint16_t BPB_FSVer;
  uint32_t BPB_RootClus;
  uint16_t BPB_FSInfo;
  uint16_t BPB_BkBootSec;
  char BPB_Reserved[12];
  uint8_t BS_DrvNum;
  uint8_t BS_Reserved1;
  uint8_t BS_BootSig;
  uint32_t BS_VolID;
  char BS_VolLab[11];
  char BS_FilSysType[8];
};

struct __attribute__((packed)) FATHeader {
  struct FATCommonHeader common;
  union {
    struct FAT12andFAT16SpecificHeader fat12_and_fat16;
    struct FAT32SpecificHeader fat32;
  };
};

unsigned char ParseFATType(const struct FATCommonHeader *fat);
void PrintPBR(const struct FATHeader *fat);

#endif // FAT_H
