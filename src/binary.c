// Copyright [2022] <griselle, sparelis, laynadre>

#include <stdio.h>
#include <stdlib.h>
#include "binary.h"
#include "main.h"

int get_records_count_in_file_status(FILE *pfile) {
    return (get_file_size_in_bytes(pfile) / sizeof(status_events));
}

int get_file_size_in_bytes(FILE *pfile) {
    int size;
    
    size = 0;
    fseek(pfile, 0, SEEK_END);
    size = ftell(pfile);
    rewind(pfile);
    return (size);
}

