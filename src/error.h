// Copyright [2022] <drunkbatya, koterin, grusnydance>

#ifndef SRC_ERROR_H_
#define SRC_ERROR_H_

#include <stdio.h>
#include "client.h"

// FILE ERRORS
uint8_t error_writing_in_file(void);
uint8_t error_reading_file(void);

// INTERNAL ERRORS
void error_corrupted_table_structure(char *table_name);
uint8_t error_shell_buff_overflow(uint8_t exitcode);
uint8_t error_writing_column_count(void);

// LOGICAL ERRORS
void error_empty_table(char *table_name);
void error_null_column_number(void);
void error_invalid_id(void);
void error_not_int(char *strint);
void error_record_not_found(void);
void error_unknown_column(char *column, char *table_name);
void error_unknown_condition(char *column);
void error_nothing_to_delete(void);
void error_all_records_deleted(void);
uint8_t error_unknown_table(char *table_name);
uint8_t error_string_too_long(char *str, int str_size);

// PARSE ERRORS
void error_shell_query_parse(void);
void error_miss_semicolon(void);
void error_wrong_operator(char *op);
uint8_t error_unpaired_char(char c, uint8_t exitcode);

#endif  // SRC_ERROR_H_
