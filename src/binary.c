#include <stdio.h>
#include <stdlib.h>
#include "binary.h"
#include "main.h"

int get_records_count_in_file(FILE *pfile) {
    return get_file_size_in_bytes(pfile) / sizeof(levels);
}

int get_records_count_in_file_modules(FILE *pfile) {
    return get_file_size_in_bytes(pfile) / sizeof(modules);
}

int get_file_size_in_bytes(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);    // Move the position pointer to the end of the file.
    size = ftell(pfile);          // Read to the current position pointer.
    rewind(pfile);                // For n pointer back to the beginning of the file.
    return size;
}

