// Copyright [2022] <griselle, sparelis, laynadre>

#ifndef SRC_ERROR_H_
#define SRC_ERROR_H_

int error_shell_buff_overflow(void);
int error_shell_query_parse(void);
int error_miss_semicolon(void);
int error_unknown_db(char *table_name);
void invalid_id_error();
void error_record_not_found();
void error_unknown_column(char *column, char *table_name);
void error_unknown_condition(char *table_name);
void error_not_int(char *strint);

#endif  // SRC_ERROR_H_
