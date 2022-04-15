// Copyright [2022] <drunkbatya, koterin, grusnydance>

#include "delete.h"

// Convert string str to int value, and insert to table via fptr.
uint8_t insert_integer_delete(void *str, FILE *fptr, uint32_t offset)
{
    INTEGER num;

    num = *((int*)str);  // TODO(grusnydance): check if not an int (atoi = 0)
    if (write_record_in_file(fptr, offset, sizeof(INTEGER), &num) == 0)
        return (0);
    return (1);
}

// Insert string str to table via fptr.
// Data will be copied to new zeroed array and written to table.
uint8_t insert_string_delete(void *str, FILE *fptr, uint32_t offset)
{
    char arr[STRING_SIZE];

    if (strlen(str) > STRING_SIZE - 1)
        return (error_string_too_long(str, (STRING_SIZE - 1)));
    memset(arr, 0, STRING_SIZE);
    strcpy(arr, str);
    if (write_record_in_file(fptr, offset, STRING_SIZE, arr) == 0)
        return (0);
    return (1);
}

uint32_t find_offset_for_column_delete(char *arr, FILE *fptr, uint8_t col_number, int * type_pointer)
{
    uint32_t res = 0;
    uint32_t offset = sizeof(COLUMN_COUNTER);
    t_header *local = NULL;

    for (int i = 1; i <= col_number; i++)
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

uint32_t find_offset_for_row_delete(FILE *fptr, COLUMN_COUNTER column_number)
{
    uint32_t res = 0;
    uint32_t offset = sizeof(COLUMN_COUNTER);

    for (int i = 1; i <= column_number; i++)
    {
        t_header *local = read_record_from_file(fptr, offset, sizeof(t_header));
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

uint32_t get_size_by_datatype_delete(int *pointer)
{
    if (*pointer == integer)
        return (sizeof(INTEGER));
    if (*pointer == string)
        return (STRING_SIZE);
    return 0;
}

void rewrite_file(int start_index, uint16_t count, COLUMN_COUNTER column_number,
     int *reserve_array, FILE *fptr, uint32_t new_offset, uint32_t offset_of_whole_row)
{
    void *grab_value_for_shift;
    for (int j = start_index; j <= count - 1; j++) {
        for (int k = 0; k < column_number; k++) {
            if (reserve_array[k] == integer) {
                grab_value_for_shift = read_record_from_file(fptr,
                        new_offset + offset_of_whole_row, sizeof(INTEGER));
                insert_integer_delete(grab_value_for_shift, fptr, new_offset);
                new_offset += sizeof(INTEGER);
            }
            if (reserve_array[k] == string) {
                grab_value_for_shift = read_record_from_file(fptr,
                        new_offset + offset_of_whole_row, STRING_SIZE);
                insert_string_delete(grab_value_for_shift, fptr, new_offset);
                new_offset += STRING_SIZE;
            }
            free(grab_value_for_shift);
        }
        rewind(fptr);
    }
}

int detect_lines_to_delete(uint16_t count, uint32_t size1, FILE *fptr,
 uint32_t where_col_offset, uint32_t diff, int var_type, char **arr,
 COLUMN_COUNTER column_number, int *reserve_array, uint32_t offset_of_whole_row)
{
    int delete_lines_count = 0;
    for (int i = 0; i < count; i++)
    {
        // uint32_t new_offset;

        void *record = calloc(1, size1);
        fseek(fptr, where_col_offset, SEEK_SET);
        fread(record, size1, 1, fptr);
        if (match_is_true(&var_type, record, arr[2], arr[3])) {
            rewind(fptr);
            if (i == count - 1) {
                delete_lines_count++;
                break;
            }
            // new_offset = where_col_offset - diff;
            rewrite_file(i, count, column_number, reserve_array,
                fptr, (where_col_offset - diff), offset_of_whole_row);
            i--;
            count--;
            rewind(fptr);
            delete_lines_count++;
        }
        free(record);
        record = NULL;
        where_col_offset += offset_of_whole_row;
    }
    free(reserve_array);
    return delete_lines_count;
}

void truncate_file(int delete_lines_count, uint32_t offset_of_whole_row, FILE *fptr)
{
    if (delete_lines_count > 0) {
        uint32_t shift = offset_of_whole_row * delete_lines_count;
        uint32_t res = get_file_size(fptr) - shift;
        ftruncate(fileno(fptr), res);
    } else {
        error_nothing_to_delete();
    }
}

// Delete data in existing table.
// Arr format: [table_name]
// [where column name] [operator] [column value]
void delete(char **arr)
{
    FILE *fptr;
    char path[strlen(arr[0]) + 4];
    COLUMN_COUNTER column_number;
    uint32_t where_col_offset;
    int var_type;
    uint32_t offset_of_whole_row;
    uint16_t count;
    int32_t diff;
    uint32_t size1;
    int *reserve_array;
    uint32_t delete_lines;

    strcpy(path, arr[0]);
    strcat(path, ".db");
    if (check_if_table_exists(path) == 0)
        return;
    column_number = read_column_number(path);
    if (column_number < 1) {
        error_null_column_number();
        return;
    }
    fptr = fopen(path, "rb+");
    where_col_offset = find_offset_for_column_delete(arr[1], fptr, column_number, &var_type);
    diff = where_col_offset;  // bytes from the start of the row to where column
    offset_of_whole_row = find_offset_for_row_delete(fptr, column_number);
    count = get_rows_count(path);  // numbers of rows in the table
    where_col_offset = sizeof(COLUMN_COUNTER) + sizeof(t_header) * column_number + where_col_offset;
    reserve_array = calloc(column_number, sizeof(int));
    get_headers_structure(fptr, column_number, reserve_array);
    size1 = get_size_by_datatype_delete(&var_type);
    delete_lines = detect_lines_to_delete(count, size1, fptr, where_col_offset, diff,
                         var_type, arr, column_number, reserve_array, offset_of_whole_row);
    truncate_file(delete_lines, offset_of_whole_row, fptr);
    safe_fclose(fptr);
    return;
}
