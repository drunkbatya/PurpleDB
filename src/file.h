// Copyright [2022] <drunkbatya>

#ifndef SRC_FILE_H_
#define SRC_FILE_H_

#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "structure.h"

void *read_record_from_file(FILE *fptr, uint32_t offset, uint16_t size);
uint16_t get_file_size(FILE *file);
int8_t write_record_in_file(FILE *fptr, uint32_t offset, uint16_t size, const void *record);
uint16_t get_records_count(FILE *file, uint16_t struct_size);
void safe_free(void *ptr);
void safe_fclose(void *ptr);
#endif  // SRC_FILE_H_
