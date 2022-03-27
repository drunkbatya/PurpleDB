// Copyright [2022] <drunkbatya>

#include "file.h"

void *read_record_from_file(FILE *file, uint16_t index, uint16_t struct_size)
{
    uint32_t offset;
    void *record;

    record = malloc(struct_size);
    if (record == NULL)
        return (record);
    offset = index * struct_size;
    fseek(file, offset, SEEK_SET);
    fread(record, struct_size, 1, file);
    rewind(file);
    return (record);
}

uint8_t write_record_in_file(FILE *file, uint16_t index, uint16_t struct_size, const void *record)
{
    uint32_t offset;

    offset = index * struct_size;
    if (fseek(file, offset, SEEK_SET))
        return (0);
    if (!fwrite(record, struct_size, 1, file))
        return (0);
    if (fflush(file))
        return (0);
    rewind(file);
    return (1);
}
uint16_t get_file_size(FILE *file)
{
    uint16_t size;

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);
    return (size);
}

uint16_t get_records_count(FILE *file, uint16_t struct_size)
{
    return (get_file_size(file) / struct_size);
}

void safe_free(void *ptr)
{
    if (ptr == NULL)
        return;
    free(ptr);
    ptr = NULL;
}

void safe_fclose(void *ptr)
{
    if (ptr == NULL)
        return;
    fclose(ptr);
    ptr = NULL;
}
