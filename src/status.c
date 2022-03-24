// Copyright [2022] <griselle, sparelis, laynadre>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "status.h"
#include "shared.h"
#include "main.h"
#include "error.h"
#include "binary.h"

void select_for_status(char **field, char **where) {
    status_events local;
    FILE *ptr = fopen(STATUS_PATH, "r");
    int identifier;
    int len = get_records_count_in_file_status(ptr);
    int counter = 0;
    int check_field;
    char temp[30];

    for (int i = 0; i < 5; i++) {
        if (field[i][0] == '*')
            identifier = 5;
        if (field[i][0] == '1') {
            identifier = i;
            break;
        }
    }
    for (int i = 0; i < 5; i++) {
        if (!strlen(where[i]))
            continue;
        check_field = i;
        for (int j = 0; j < (int)strlen(where[i]); j++) {
            temp[j] = where[i][j];
        }
        temp[(int)strlen(where[i])] = '\0';
    }
    for (int i = 0; i < len; i++) {
        local = read_record_from_file_status(ptr, i);
        if (compare_status(&local, check_field, temp)) {
            counter++;
            if (counter == 1)
                print_mask_status(identifier);
            print_struct_status(&local, identifier);
        }
    }
    print_outro_status(identifier);
    fclose(ptr);
    if (counter == 0)
        error_record_not_found();
}

void print_mask_status(int identifier) {
    if (identifier == 0) {
        printf(" --------\n");
        printf("| id     |\n");
        printf("|--------|\n");
    } else if (identifier == 1) {
        printf(" -------------------\n");
        printf("| module_name       |\n");
        printf("|-------------------|\n");
    } else if (identifier == 2) {
        printf(" -------------------\n");
        printf("| mem_level_modules |\n");
        printf("|-------------------|\n");
    } else if (identifier == 3) {
        printf(" ----------\n");
        printf("| cell_num |\n");
        printf("|----------|\n");
    } else if (identifier == 4) {
        printf(" ---------------\n");
        printf("| deletion_flag |\n");
        printf("|---------------|\n");
    } else if (identifier == 5) {
        printf(" ---------------------------------------------------------------------------\n");
        printf("| id     | module_name       | mem_level_modules | cell_num | deletion_flag |\n");
        printf("|---------------------------------------------------------------------------|\n");
    }
}

void print_outro_status(int identifier) {
    if (identifier == 0) {
        printf(" --------\n");
    } else if (identifier == 1) {
        printf(" -------------------\n");
    } else if (identifier == 2) {
        printf(" -------------------\n");
    } else if (identifier == 3) {
        printf(" ----------\n");
    } else if (identifier == 4) {
        printf(" ---------------\n");
    } else if (identifier == 5) {
        printf(" ---------------------------------------------------------------------------\n");
    }
}

int compare_status(status_events *local, int check_field, char *temp) {
    if ((check_field == 0) && (local->event_id == atoi(temp)))
        return (1);
    if ((check_field == 1) && (local->module_id == atoi(temp)))
        return (1);
    if ((check_field == 2) && (local->new_status == atoi(temp)))
        return (1);
    if ((check_field == 3) && (strcmp(local->status_change_date, temp) == 0))
        return (1);
    if ((check_field == 4) && (strcmp(local->status_change_time, temp) == 0))
        return (1);
    return (0);
}


status_events read_record_from_file_status(FILE *pfile, int index) {
    status_events record;
    int offset;
    
    offset = index * sizeof(status_events);
    fseek(pfile, offset, SEEK_SET);
    fread(&record, sizeof(status_events), 1, pfile);
    rewind(pfile);
    return (record);
}

void print_struct_status(status_events *local, int identifier) {
    if (identifier == 0) {
        printf("| %-6d |\n", local->event_id);
    } else if (identifier == 1) {
        printf("| %-17d |\n", local->module_id);
    } else if (identifier == 2) {
        printf("| %-17d |\n", local->new_status);
    } else if (identifier == 3) {
        printf("| %-8s |\n", local->status_change_date);
    } else if (identifier == 4) {
        printf("| %-13s |\n", local->status_change_time);
    } else if (identifier == 5) {
        printf("| %-7d", local->event_id);
        printf("| %-18d", local->module_id);
        printf("| %-18d", local->new_status);
        printf("| %-9s", local->status_change_date);
        printf("| %-13s |", local->status_change_time);
        printf("\n");
    }
}
