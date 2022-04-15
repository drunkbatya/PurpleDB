// Copyright [2022] <drunkbatya, koterin, grusnydance>

#include "shared.h"
#include <stdlib.h>
#include <string.h>

uint8_t check_if_table_exists(char *file_path)
{
    FILE *fptr;

    fptr = fopen(file_path, "r");
    if (fptr == NULL)
        return (error_unknown_table(file_path));
    safe_fclose(fptr);
    return (1);
}

void get_headers_structure(FILE *fptr, COLUMN_COUNTER column_number, int *reserve_array)
{
    uint32_t offset;
    COLUMN_COUNTER count;
    t_header *header;

    offset = sizeof(COLUMN_COUNTER);
    count = 0;
    while (count < column_number)
    {
        header = read_record_from_file(fptr, offset, sizeof(t_header));
        reserve_array[count] = header->datatype;
        offset += sizeof(t_header);
        count++;
        safe_free(header);
    }
}

void safe_free_headers(t_header **headers, COLUMN_COUNTER column_number)
{
    COLUMN_COUNTER count;

    count = 0;
    while ((headers != NULL) && (count < column_number))
    {
        if (headers[count] != NULL)
            safe_free(headers[count]);
        count++;
    }
    safe_free(headers);
}

t_header **get_headers(FILE *fptr, COLUMN_COUNTER column_number)
{
    COLUMN_COUNTER count;
    uint32_t offset;
    t_header **out;

    count = 0;
    offset = sizeof(COLUMN_COUNTER);
    out = malloc(column_number * sizeof(t_header *));
    while (count < column_number)
    {
        out[count] = read_record_from_file(fptr, offset, sizeof(t_header));
        if (out[count] == NULL)
            safe_free_headers(out, column_number);
        offset += sizeof(t_header);
        count++;
    }
    return (out);
}

void *read_record_from_file(FILE *fptr, uint32_t offset, uint16_t size)
{
    void *record;

    record = calloc(1, size);
    if (record == NULL)
        return (record);
    fseek(fptr, offset, SEEK_SET);
    fread(record, size, 1, fptr);
    rewind(fptr);
    return (record);
}

uint8_t write_record_in_file(FILE *fptr, uint32_t offset, uint16_t size, void *record)
{
    if (fseek(fptr, offset, SEEK_SET) == 1)
        return (error_writing_in_file());
    if (fwrite(record, size, 1, fptr) == 0)
        return (error_writing_in_file());
    if (fflush(fptr) != 0)
        return (error_writing_in_file());
    rewind(fptr);
    return (1);
}

// Read first byte of file to get number of columns in table.
// Max size is sizeof(uint8_t) - 255 columns.
// Type defined by COLUMN_COUNTER in structure.h .
COLUMN_COUNTER read_column_number(char *file_path)
{
    FILE *ptr;
    COLUMN_COUNTER *column_count_ptr;
    COLUMN_COUNTER column_count;

    ptr = fopen(file_path, "r");
    if (ptr == NULL)
        return (error_writing_in_file());
    column_count_ptr = read_record_from_file(ptr, 0, sizeof(COLUMN_COUNTER));
    if (column_count_ptr == NULL)
    {
        safe_fclose(ptr);
        return (0);
    }
    column_count = *column_count_ptr;
    safe_fclose(ptr);
    safe_free(column_count_ptr);
    return (column_count);
}

uint32_t get_file_size(FILE *fptr)
{
    uint32_t size;

    fseek(fptr, 0, SEEK_END);
    size = ftell(fptr);
    rewind(fptr);
    return (size);
}

uint16_t get_row_size(char *file_path)
{
    FILE *fptr;
    uint16_t size;
    t_header *column;
    COLUMN_COUNTER count;
    COLUMN_COUNTER column_count;

    size = 0;
    count = 0;
    column_count = read_column_number(file_path);
    if (!column_count)
        return (0);
    fptr = fopen(file_path, "r");
    if (fptr == NULL)
        return (error_reading_file());
    while (count < column_count)
    {
        column = read_record_from_file(fptr, sizeof(COLUMN_COUNTER) \
                + (count * sizeof(t_header)), sizeof(t_header));
        if (column == NULL)
        {
            safe_fclose(fptr);
            free(column);
            error_corrupted_table_structure(file_path);
            return (0);
        }
        if (column->datatype == integer)
            size += sizeof(INTEGER);
        if (column->datatype == string)
            size += STRING_SIZE;
        count++;
        safe_free(column);
        column = NULL;
    }
    fclose(fptr);
    return (size);
}

uint16_t get_rows_count(char *file_path)
{
    FILE *fptr;
    uint16_t size;
    uint16_t row_size;
    COLUMN_COUNTER column_count;

    column_count = read_column_number(file_path);
    if (!column_count)
        return (0);
    row_size = get_row_size(file_path);
    fptr = fopen(file_path, "r");
    if (fptr == NULL)
        return (0);
    size = get_file_size(fptr) - sizeof(COLUMN_COUNTER) - (column_count * sizeof(t_header));
    safe_fclose(fptr);
    return (size / row_size);
}

void safe_free(void *ptr)
{
    if (ptr == NULL)
        return;
    free(ptr);
}

void safe_fclose(void *ptr)
{
    if (ptr == NULL)
        return;
    fclose(ptr);
}

// get column's size by datatype
uint16_t get_size_by_datatype(t_header *column)
{
    if (column->datatype == integer)
        return (sizeof(INTEGER));
    if (column->datatype == string)
        return (STRING_SIZE);
    return (0);
}

// Binary calculator to proceed WHERE conditions
uint8_t bin_calc_int(int64_t num1, int64_t num2, char *op)
{
    if (strcmp(op, "=") == 0)
        return (num1 == num2);
    if (strcmp(op, "<") == 0)
        return (num1 < num2);
    if (strcmp(op, ">") == 0)
        return (num1 > num2);
    error_wrong_operator(op);
    return (0);
}

// Needed by is_where_condition_true() function.
// Check WHERE condition for some columns.
uint8_t check_where(FILE *fptr, uint16_t offset, t_header *column, char **arr)
{
    INTEGER *integer_ptr;
    char *string_ptr;

    if (column->datatype == integer)
    {
        integer_ptr = read_record_from_file(fptr, offset, sizeof(INTEGER));
        if (bin_calc_int(*integer_ptr, atoi(arr[4]), arr[3]) == 0)
        {
            safe_free(integer_ptr);
            return (0);
        }
        safe_free(integer_ptr);
        return (1);
    }
    if (column->datatype == string)
    {
        if (strcmp("=", arr[3]))  // strings may be just equal or not
            return (0);
        string_ptr = read_record_from_file(fptr, offset, STRING_SIZE);
        if (strcmp(string_ptr, arr[4]))
        {
            safe_free(string_ptr);
            return (0);
        }
        safe_free(string_ptr);
        return (1);
    }
    return (0);
}

// check WHERE condition for some rows
uint8_t is_where_condition_true(FILE *fptr, char **arr, t_header **columns_arr, \
        uint16_t offset, COLUMN_COUNTER columns)
{
    COLUMN_COUNTER column_count;

    column_count = 0;
    if (strcmp(arr[2], "*") == 0)
        return (1);
    while (column_count < columns)
    {
        if (strcmp(columns_arr[column_count]->column_name, arr[2]))
        {
            offset += get_size_by_datatype(columns_arr[column_count]);
            column_count++;
            continue;
        }
        return (check_where(fptr, offset, columns_arr[column_count], arr));
    }
    return (0);  // TODO(drunkbatya): error no column
}

uint32_t find_offset_for_column(char *arr, FILE *fptr, uint8_t col_number, int * type_pointer)
{
    uint32_t res = 0;
    uint32_t offset = sizeof(COLUMN_COUNTER);
    t_header *local = NULL;

    for (int i = 0; i < col_number; i++)
    {
        local = read_record_from_file(fptr, offset, sizeof(t_header));
        if (strcmp(arr, local->column_name) == 0)
        {
            if (local->datatype == integer) {
                *type_pointer = local->datatype;
            } else if (local->datatype == string) {
                *type_pointer = local->datatype;
            }
            free(local);
            break;
        }
        offset += sizeof(t_header);
        if (local->datatype == integer) {
            res += sizeof(INTEGER);
        } else if (local->datatype == string) {
            res += STRING_SIZE;
        }
        free(local);
    }
    return res;
}

uint32_t find_offset_for_row(FILE *fptr, COLUMN_COUNTER column_number)
{
    uint32_t res = 0;
    uint32_t offset = sizeof(COLUMN_COUNTER);
    t_header *local = NULL;

    for (int i = 0; i < column_number; i++)
    {
        local = read_record_from_file(fptr, offset, sizeof(t_header));
        offset += sizeof(t_header);
        if (local->datatype == integer) {
            res += sizeof(INTEGER);
        } else if (local->datatype == string) {
            res += STRING_SIZE;
        }
        free(local);
    }
    return res;
}

uint32_t get_size_by_datatype_simple(int *pointer)
{
    if (*pointer == integer)
        return (sizeof(INTEGER));
    if (*pointer == string)
        return (STRING_SIZE);
    return 0;
}

int match_is_true(int *datatype, void *record, char *array_op, char *array_val)
{
    if (*datatype == integer) {
        if (bin_calc_int(*((int*)record), atoi(array_val), array_op))
            return 1;
    }
    if ((*datatype == string) && (strcmp(record, array_val) == 0))
        return (1);
    return 0;
}
