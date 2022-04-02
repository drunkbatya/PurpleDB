// Copyright [2022] <drunkbatya, koterin, GrusnyDance>

#include "shared.h"

void *read_record_from_file(FILE *fptr, uint32_t offset, uint16_t size)
{
    void *record;

    record = malloc(size);
    if (record == NULL)
        return (record);
    fseek(fptr, offset, SEEK_SET);
    fread(record, size, 1, fptr);
    rewind(fptr);
    return (record);
}

uint8_t write_record_in_file(FILE *fptr, uint32_t offset, uint16_t size, const void *record)
{
    printf("offset is %d\n", offset);
    fseek(fptr, offset, SEEK_SET);
    fwrite(record, size, 1, fptr);
    fflush(fptr);
    rewind(fptr);
/*
    if (fseek(fptr, offset, SEEK_SET))
        return (0);  //TODO: describe errors
    if (fwrite(record, size, 1, fptr) == 0)
        return (0);
    if (fflush(fptr))
        return (0);
    rewind(fptr);
  */  return (1);
}

// Read first byte of file to get number of columns in table.
// Max size is sizeof(uint8_t) - 255 columns.
// Type defined by COLUMN_COUNTER in structure.h .
COLUMN_COUNTER read_column_count(char *file_path)
{
    FILE *ptr;
    COLUMN_COUNTER *column_count_ptr;
    COLUMN_COUNTER column_count;

    ptr = fopen(file_path, "rb");
    if (ptr == NULL)
        return (0);
    column_count_ptr = read_record_from_file(ptr, 0, sizeof(COLUMN_COUNTER));
    printf("col count = %d\n", (int)(*column_count_ptr));  //TODO
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
    column_count = read_column_count(file_path);
    if (!column_count)
        return (0);
    fptr = fopen(file_path, "r");
    if (fptr == NULL)
        return (0);
    while (count < column_count)
    {
        column = read_record_from_file(fptr, sizeof(COLUMN_COUNTER) \
                + (count * sizeof(t_header)), sizeof(t_header));
        if (column == NULL)
        {
            safe_fclose(fptr);
            return (0);
        }
        if (column->datatype == integer)
            size += sizeof(INTEGER);
        if (column->datatype == string)
            size += STRING_SIZE;
        count++;
    }
    return (size);
}

uint16_t get_rows_count(char *file_path)
{
    FILE *fptr;
    uint16_t size;
    uint16_t row_size;
    COLUMN_COUNTER column_count;

    column_count = read_column_count(file_path);
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
