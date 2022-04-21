// Copyright [2022] <drunkbatya, koterin, grusnydance>

#include "error.h"

uint8_t error_writing_in_file(void)
{
    printf("\nError! Couldn't write into a file\n");
    return (0);
}

uint8_t error_string_too_long(char *str, int str_size)
{
    printf("\nError! Couldn't write the line '%s',"
                " because the field size is only %d characters long\n", str, str_size);
    return (0);
}

uint8_t error_writing_column_count(void)
{
    printf("\nError! Something went wrong during column structure setting\n");
    return (0);
}

uint8_t error_reading_file(void)
{
    printf("\nError! Couldn't read the specified file\n");
    return (0);
}

void error_empty_table(char *table_name)
{
    printf("\nError! Table %s is empty\n", table_name);
}

void error_corrupted_table_structure(char *table_name)
{
    printf("\nError! Table %s structure was corrupted\n", table_name);
}

void error_null_column_number(void)
{
    printf("\nError! Columns amount must be more than 0\n");
}

uint8_t error_unknown_table(char *table_name)
{
    printf("\nError! No table '%s' found\n", table_name);
    return (0);
}

void error_record_not_found(void)
{
    printf("\nError! Record not found\n");
}

void error_unknown_column(char *column, char *table_name)
{
    printf("\nError! No column '%s' in table '%s' found\n", column, table_name);
}

void error_unknown_condition(char *column)
{
    printf("\nError! Cannot assign condition: no column '%s' found\n", column);
}

void error_not_int(char *strint)
{
    printf("\nError! '%s' is not an integer\n", strint);
}

void error_invalid_id(void)
{
    printf("\nId already exists\n");
}

void error_nothing_to_delete(void)
{
    printf("\nNo record matches your query\n");
}

void error_all_records_deleted(void)
{
    printf("\nAll records were deleted previously\n");
}

uint8_t error_unpaired_char(char c, uint8_t exitcode)
{
    printf("\nError! Missing '%c' character\n", c);
    return (exitcode);
}

uint8_t error_shell_buff_overflow(uint8_t exitcode)
{
    printf("\nError! Query is too large - max %d chars\n", SHELL_BUF_SIZE);
    return (exitcode);
}

void error_shell_query_parse(void)
{
    printf("\nError! Incorrect query\n");
}

void error_miss_semicolon(void)
{
    printf("\nError! Incorrect query: missing semicolon - ';'\n");
}

void error_wrong_operator(char *op)
{
    printf("\nError! Wrong WHERE operator '%s'\n", op);
}

void error_table_exist(char *name)
{
    printf("\nError table '%s' already exist!\n", name);
}
