// Copyright [2022] <drunkbatya, koterin, grusnydance>

#include <stdio.h>

int error_shell_query_parse(void) {
    printf("\nError! Incorrect query\n");
    return (1);
}

int error_miss_semicolon(void) {
    printf("\nError! Incorrect query: missing semicolon - ';'\n");
    return (1);
}

void error_unknown_table(char *table_name) {
    printf("\nError! No table '%s' found\n", table_name);
}

void error_record_not_found() {
    printf("\nError! Record not found\n");
}

void error_unknown_column(char *column, char *table_name) {
    printf("\nError! No column '%s' in table '%s' found\n", column, table_name);
}

void error_unknown_condition(char *column) {
    printf("\nError! Cannot assign condition: no column '%s' found\n", column);
}

void error_not_int(char *strint) {
    printf("\nError! '%s' is not an integer\n", strint);
}

void invalid_id_error() {
    printf("\nId already exists\n");
}

void nothing_to_delete_error() {
    printf("\nNo record matches your query\n");
}

void all_records_deleted_error() {
    printf("\nAll records were deleted previously\n");
}
