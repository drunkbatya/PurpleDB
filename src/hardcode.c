// Copyright [2022] <griselle, sparelis, laynadre>

#include <stdio.h>
#include <string.h>
#include "hardcode.h"
#include "client.h"

void pretty_print_select(char **arr) {
    printf(BOLD"SELECT"NC);
    printf("\n\t"CYAN);
    printf("%s", arr[0]);
    printf("\n"NC);
    printf(BOLD"FROM"NC);
    printf("\n\t"CYAN);
    printf("%s", arr[1]);
    if (!strcmp(arr[2], "*")) {
        printf("\n"NC);
        return;
    }
    printf("\n"NC);
    printf(BOLD"WHERE"NC);
    printf("\n\t"CYAN);
    printf("%s = %s", arr[2], arr[3]);
    printf("\n"NC);
}

void pretty_print_insert(char **arr) {
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

void pretty_print_delete(char **arr) {
    printf(BOLD"DELETE FROM"NC);
    printf("\n\t"CYAN);
    printf("%s", arr[0]);
    printf("\n"NC);
    printf(BOLD"WHERE"NC);
    printf("\n\t"CYAN);
    printf("%s = %s", arr[1], arr[2]);
    printf("\n"NC);
}

void pretty_print_update(char **arr) {
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
    printf("%s = %s", arr[3], arr[4]);
    printf("\n"NC);
}

int show_tables(void) {
    printf(BOLD"SHOW TABLES"NC);
    printf("\n\n");
    printf(" -----name------\n");
    printf("| modules       |\n");
    printf("| levels        |\n");
    printf("| status_events |\n");
    printf(" ---------------\n");
    return (1);
}

int describe_modules(void) {
    printf(BOLD"DESCRIBE TABLE"NC);
    printf(CYAN);
    printf(" modules");
    printf("\n\n"NC);
    printf(" ---------name-----------type---\n");
    printf("| id                 | int      |\n");
    printf("| module_name        | char[30] |\n");
    printf("| mem_level_modules  | int      |\n");
    printf("| cell_num           | int      |\n");
    printf("| deletion_flag      | int      |\n");
    printf(" -------------------------------\n");
    return (1);
}

int describe_levels(void) {
    printf(BOLD"DESCRIBE TABLE"NC);
    printf(CYAN);
    printf(" levels");
    printf("\n\n"NC);
    printf(" ---------name-----------type---\n");
    printf("| mem_level_levels   | int      |\n");
    printf("| cell_amount        | int      |\n");
    printf("| protect_flag       | int      |\n");
    printf(" -------------------------------\n");
    return (1);
}

int describe_status(void) {
    printf(BOLD"DESCRIBE TABLE"NC);
    printf(CYAN);
    printf(" status_events");
    printf("\n\n"NC);
    printf(" ---------name-----------type---\n");
    printf("| event_id           | int      |\n");
    printf("| module_id          | int      |\n");
    printf("| new_status         | int      |\n");
    printf("| status_change_date | char[12] |\n");
    printf("| status_change_time | char[9]  |\n");
    printf(" -------------------------------\n");
    return (1);
}
