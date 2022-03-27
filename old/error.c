// Copyright [2022] <griselle, sparelis, laynadre>

#include <stdio.h>
#include "client.h"

int error_shell_buff_overflow(void) {
    printf("\nError! Query is too large - max %d chars\n", SHELL_BUF_SIZE);
    return (1);
}

int error_shell_query_parse(void) {
    printf("\nError! Incorrect query\n");
    return (1);
}

int error_miss_semicolon(void) {
    printf("\nError! Incorrect query: missing semicolon - ';'\n");
    return (1);
}

int error_unknown_db(char *table_name) {
    printf("\nError! No table '%s' found\n", table_name);
    return (1);
}

void error_record_not_found() {
    printf("Error! Record not found\n");
}

void error_unknown_column(char *column, char *table_name) {
    printf("Error! No column '%s' in table '%s' found\n", column, table_name);
}

void error_unknown_condition(char *column) {
    printf("Error! Cannot assign condition '%s', no such column found\n", column);
}

void error_not_int(char *strint) {
    printf("Error! '%s' is not an integer\n", strint);
}

void invalid_id_error() {
    printf("Id already exists\n");
}
