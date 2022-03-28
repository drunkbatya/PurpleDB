// Copyright [2022] <drunkbatya>

#include "file.h"

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

int8_t write_record_in_file(FILE *fptr, uint32_t offset, uint16_t size, const void *record)
{
    if (fseek(fptr, offset, SEEK_SET))
        return (0);
    if (!fwrite(record, size, 1, fptr))
        return (0);
    if (fflush(fptr))
        return (0);
    rewind(fptr);
    return (1);
}
uint16_t get_file_size(FILE *fptr)
{
    uint16_t size;

    fseek(fptr, 0, SEEK_END);
    size = ftell(fptr);
    rewind(fptr);
    return (size);
}

uint16_t get_records_count(FILE *fptr, uint16_t struct_size)
{
    return (get_file_size(fptr) / struct_size);
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
