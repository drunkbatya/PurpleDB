// Copyright [2022] <drunkbatya>

#ifndef SRC_SHARED_H_
#define SRC_SHARED_H_

#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "structure.h"
#include "error.h"

int check_if_table_exists(char *file_path);
t_header *read_header_from_file(FILE *fptr, uint32_t offset, uint16_t size);
void *read_record_from_file(FILE *fptr, uint32_t offset, uint16_t size);
uint32_t get_file_size(FILE *file);
uint8_t write_record_in_file(FILE *fptr, uint32_t offset, uint16_t size, const void *record);
COLUMN_COUNTER read_column_number(char *file_path);
uint16_t get_rows_count(char *file_path);
void safe_free(void *ptr);
void safe_fclose(void *ptr);
#endif  // SRC_SHARED_H_
