// Copyright [2022] <drunkbatya, koterin, grusnydance>

#include "update.h"

// Convert string str to int value, and insert to table via fptr.
uint8_t insert_integer_update(char *str, FILE *fptr, uint32_t offset)
{
    INTEGER num;

    num = atoi(str);  // TODO(grusnydance): check if not an int (atoi = 0)
    if (write_record_in_file(fptr, offset, sizeof(INTEGER), &num) == 0)
        return (0);
    return (1);
}

// Insert string str to table via fptr.
// Data will be copied to new zeroed array and written to table.
uint8_t insert_string_update(char *str, FILE *fptr, uint32_t offset)
{
    char arr[STRING_SIZE];

    if (strlen(str) > STRING_SIZE - 1)
        return (0);  // TODO(drunkbatya): add exception
    memset(arr, 0, STRING_SIZE);
    strcpy(arr, str);
    if (write_record_in_file(fptr, offset, STRING_SIZE, arr) == 0)
        return (0);
    return (1);
}

uint32_t find_offset_for_column(char *arr, FILE *fptr, uint8_t col_number, int * type_pointer)
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

uint32_t find_offset_for_row(FILE *fptr, COLUMN_COUNTER column_number)
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

// Update data in existing table.
// Arr format: [table_name] [name of column to update]
// [value to update] [where column name] [equals column value]
void update(char **arr)
{
    FILE *fptr;
    char file_path[strlen(arr[0]) + 4];
    uint32_t offset1;
    int first_type;
    uint32_t offset2;
    int sec_type;
    COLUMN_COUNTER column_number;
    uint32_t where_col_offset;
    uint32_t col_to_update_offset;
    uint32_t offset_of_whole_row;
    uint16_t count;
    int32_t diff;
    int32_t size1;

    strcpy(file_path, arr[0]);
    strcat(file_path, ".db");
    if (check_if_table_exists(file_path) == 0)
        return;

    column_number = read_column_number(file_path);
    if (column_number < 1) {
        error_null_column_number();
        return;
    }

    fptr = fopen(file_path, "rb+");

    where_col_offset = find_offset_for_column(arr[3], fptr, column_number, &first_type);
    col_to_update_offset = find_offset_for_column(arr[1], fptr, column_number, &sec_type);
    offset_of_whole_row = find_offset_for_row(fptr, column_number);
    count = get_rows_count(file_path);
    offset1 = sizeof(COLUMN_COUNTER) + sizeof(t_header) * column_number + where_col_offset;
    offset2 = sizeof(COLUMN_COUNTER) + sizeof(t_header) * column_number + col_to_update_offset;
    diff = offset1 - offset2;
    if (first_type == integer) size1 = sizeof(INTEGER);
    if (first_type == string) size1 = STRING_SIZE;

    for (int i = 1; i <= count; i++)
    {
        void *record = calloc(1, size1);
        fseek(fptr, offset1, SEEK_SET);
        fread(record, size1, 1, fptr);
        if (((first_type == integer) && (*((int*)record) == atoi(arr[4]))) ||
                 ((first_type == string) && (strcmp(record, arr[4]) == 0))) {
                rewind(fptr);
                if (sec_type == integer) {
                    insert_integer_update(arr[2], fptr, offset1 - diff);
                }
                if (sec_type == string) {
                    insert_string_update(arr[2], fptr, offset1 - diff);
                }
        }
        free(record);
        record = NULL;
        offset1 += offset_of_whole_row;
    }
    safe_fclose(fptr);
    return;
}
