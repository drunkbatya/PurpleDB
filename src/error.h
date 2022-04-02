// Copyright [2022] <drunkbatya, koterin, grusnydance>

#ifndef SRC_ERROR_H_
#define SRC_ERROR_H_

void error_unknown_table(char *table_name);

int error_shell_query_parse(void);
int error_miss_semicolon(void);
void invalid_id_error();
void error_record_not_found();
void error_unknown_column(char *column, char *table_name);
void error_unknown_condition(char *column);
void error_not_int(char *strint);
void nothing_to_delete_error();
void all_records_deleted_error();

#endif  // SRC_ERROR_H_
