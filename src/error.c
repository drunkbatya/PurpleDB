// Copyright [2022] <drunkbatya, koterin, grusnydance>

#include <stdio.h>

void error_null_column_number()
{
    printf("\nError! Columns amount must be more than 0\n");
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

void error_invalid_id() {
    printf("\nId already exists\n");
}

void error_nothing_to_delete() {
    printf("\nNo record matches your query\n");
}

void error_all_records_deleted() {
    printf("\nAll records were deleted previously\n");
}
