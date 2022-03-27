// Copyright [2022] <drunkbatya>

#ifndef SRC_FILE_H_
#define SRC_FILE_H_

#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "structure.h"

void *read_record_from_file(FILE *file, uint16_t index, uint16_t struct_size);
uint16_t get_file_size(FILE *file);
uint8_t write_record_in_file(FILE *file, uint16_t index, uint16_t struct_size, const void *record);
uint16_t get_records_count(FILE *file, uint16_t struct_size);
uint8_t can_create_new_file(char *file_path);
void safe_free(void *ptr);
void safe_fclose(void *ptr);
#endif  // SRC_FILE_H_
