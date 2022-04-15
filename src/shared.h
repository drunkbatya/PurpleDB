// Copyright [2022] <drunkbatya, koterin, GrusnyDance>

#ifndef SRC_SHARED_H_
#define SRC_SHARED_H_

#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "error.h"

uint8_t check_if_table_exists(char *file_path);
void get_headers_structure(FILE *fptr, COLUMN_COUNTER column_number, int *reserve_array);
t_header read_for_structures(FILE *pfile, uint32_t offset);
void free_headers_struct(COLUMN_COUNTER column_number, t_header **hstr);
void *read_record_from_file(FILE *fptr, uint32_t offset, uint16_t size);
uint32_t get_file_size(FILE *file);
uint8_t write_record_in_file(FILE *fptr, uint32_t offset, uint16_t size, void *record);
COLUMN_COUNTER read_column_number(char *file_path);
uint16_t get_rows_count(char *file_path);
uint16_t get_row_size(char *file_path);
void safe_free(void *ptr);
void safe_fclose(void *ptr);
uint16_t get_size_by_datatype(t_header *column);
t_header **get_headers(FILE *fptr, COLUMN_COUNTER column_number);
void safe_free_headers(t_header **headers, COLUMN_COUNTER column_number);
uint8_t bin_calc_int(int64_t num1, int64_t num2, char *op);
uint8_t is_where_condition_true(FILE *fptr, char **arr, t_header **columns_arr, \
        uint16_t offset, COLUMN_COUNTER columns);
uint32_t find_offset_for_column(char *arr, FILE *fptr, uint8_t col_number, \
        int * type_pointer);
uint32_t find_offset_for_row(FILE *fptr, COLUMN_COUNTER column_number);
uint32_t get_size_by_datatype_simple(int *pointer);
int match_is_true(int *datatype, void *record, char *array_op, char *array_val);
#endif  // SRC_SHARED_H_
