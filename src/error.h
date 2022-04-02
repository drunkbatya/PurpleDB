// Copyright [2022] <drunkbatya, koterin, grusnydance>

#ifndef SRC_ERROR_H_
#define SRC_ERROR_H_

void error_unknown_table(char *table_name);
void error_null_column_number();
void error_invalid_id();
void error_record_not_found();
void error_unknown_column(char *column, char *table_name);
void error_unknown_condition(char *column);
void error_not_int(char *strint);
void error_nothing_to_delete();
void error_all_records_deleted();

#endif  // SRC_ERROR_H_
