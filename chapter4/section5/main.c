#include "assemble.h"
#include "fat.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define HEADER_SIZE_OF_FAT 90

void
usage(void) {
    fprintf(stderr, "Usage: boots [--asm] <filename>\n");
}

int
main(const int argc, const char **argv) {
    bool asmValid = false;
    char *filename;

    if (argc == 2) {
        filename = (char *)argv[1];
    } else if (argc == 3) {
        if (strcmp(argv[1], "--asm")) {
            usage();
            return 1;
        }
        asmValid = true;
        filename = (char *)argv[2];
    } else {
        usage();
        return 1;
    }

    FILE *fp;
    char str[HEADER_SIZE_OF_FAT];

    if ((fp = fopen(filename, "rb")) == NULL) {
        fprintf(stderr, "File `%s` cannot be opened.\n", filename);
        return 1;
    }

    if (fread(str, 1, HEADER_SIZE_OF_FAT, fp) != HEADER_SIZE_OF_FAT) {
        fprintf(stderr, "File size is too small.\n");
        return 1;
    }

    fclose(fp);

    if (asmValid) {
        printAssemblyCode(str);
    } else {
        printPBR(str);
    }

    return 0;
}
