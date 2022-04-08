// Copyright [2022] <drunkbatya, koterin, GrusnyDance>

#include "pretty_print.h"

void pretty_print_select(char **arr)
{
    printf(BOLD"SELECT"NC);
    printf("\n\t"CYAN);
    printf("%s", arr[1]);
    printf("\n"NC);
    printf(BOLD"FROM"NC);
    printf("\n\t"CYAN);
    printf("%s", arr[0]);
    if (!strcmp(arr[2], "*")) {
        printf("\n"NC);
        return;
    }
    printf("\n"NC);
    printf(BOLD"WHERE"NC);
    printf("\n\t"CYAN);
    printf("%s %s %s", arr[2], arr[3], arr[4]);
    printf("\n"NC);
}

void pretty_print_insert(char **arr)
{
    printf(BOLD"INSERT INTO"NC);
    printf("\n\t"CYAN);
    printf("%s", arr[0]);
    printf("\n"NC);
    printf(BOLD"VALUES"NC);
    printf("\n\t"CYAN);
    printf("%s,", arr[1]);
    printf("\n\t%s,", arr[2]);
    if (!strlen(arr[4])) {
        printf("\n\t%s", arr[3]);
        printf("\n"NC);
        return;
    }
    printf("\n\t%s,", arr[3]);
    printf("\n\t%s,", arr[4]);
    printf("\n\t%s", arr[5]);
    printf("\n"NC);
}

void pretty_print_delete(char **arr)
{
    printf(BOLD"DELETE FROM"NC);
    printf("\n\t"CYAN);
    printf("%s", arr[0]);
    printf("\n"NC);
    printf(BOLD"WHERE"NC);
    printf("\n\t"CYAN);
    printf("%s %s %s", arr[2], arr[3], arr[4]);
    printf("\n"NC);
}

void pretty_print_update(char **arr)
{
    printf(BOLD"UPDATE "NC);
    printf("\n\t"CYAN);
    printf("%s", arr[0]);
    printf("\n"NC);
    printf(BOLD"SET"NC);
    printf("\n\t"CYAN);
    printf("%s = %s", arr[1], arr[2]);
    printf("\n"NC);
    printf(BOLD"WHERE"NC);
    printf("\n\t"CYAN);
    printf("%s %s %s", arr[2], arr[3], arr[4]);
    printf("\n"NC);
}

void pretty_print_create(char **arr, uint16_t column_count)
{
    uint16_t count;

    count = 0;
    printf(BOLD"CREATE TABLE "NC);
    printf(CYAN"%s", arr[0]);
    arr++;  // to skip table name and leave count = 0
    printf("\n"NC);
    printf("(\n");
    while (count < (column_count * 2))
    {
        printf("\t%s ", arr[count]);
        printf(CYAN"%s", arr[count + 1]);
        if (count == column_count - 1)
            printf("\n"NC);
        else
            printf(",\n"NC);
        count += 2;
    }
    printf(")\n");
}
