#include "assemble.h"
#include "fat.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void PrintUsage(void) {
  fprintf(stderr, "Usage: boots [--asm] <file_path>\n");
}

void ParseOption(const int argc, char **argv, bool *is_assembly_mode,
                  char **file_path) {
  switch (argc) {
  case 2:
    *is_assembly_mode = false;
    *file_path = (char *)argv[1];
    break;
  case 3:
    if (strcmp(argv[1], "--asm")) {
      PrintUsage();
      exit(1);
    } else {
      *is_assembly_mode = true;
      *file_path = (char *)argv[2];
      break;
    }
  default:
    PrintUsage();
    exit(1);
  }
}

int main(const int argc, char **argv) {
  bool is_assembly_mode;
  char *file_path;

  ParseOption(argc, argv, &is_assembly_mode, &file_path);

  FILE *fp = fopen(file_path, "rb");
  if (fp == NULL) {
    fprintf(stderr, "File `%s` cannot be opened.\n", file_path);
    return 1;
  }

  struct FATHeader fat;
  if (fread(&fat, 1, sizeof fat, fp) != sizeof fat) {
    fprintf(stderr, "File size is too small.\n");
    return 1;
  }

  fclose(fp);

  if (is_assembly_mode) {
    PrintAssemblyCode((const char *)&fat);
  } else {
    PrintPBR(&fat);
  }

  return 0;
}
