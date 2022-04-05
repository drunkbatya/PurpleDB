// Copyright [2022] <drunkbatya, koterin, grusnydance>

#ifndef SRC_ERROR_H_
#define SRC_ERROR_H_

#include <stdio.h>
#include "client.h"

void error_unknown_table(char *table_name);
void error_null_column_number(void);
void error_invalid_id(void);
void error_record_not_found(void);
void error_unknown_column(char *column, char *table_name);
void error_unknown_condition(char *column);
void error_not_int(char *strint);
void error_nothing_to_delete(void);
void error_all_records_deleted(void);
uint8_t error_unpaired_char(char c, uint8_t exitcode);
uint8_t error_shell_buff_overflow(uint8_t exitcode);
void error_shell_query_parse(void);
void error_miss_semicolon(void);
void error_read_table(char *table_name);
void error_wrong_operator(char *op, char *datatype);

#endif  // SRC_ERROR_H_
