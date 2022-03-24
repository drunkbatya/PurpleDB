// Copyright [2022] <griselle, sparelis, laynadre>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "client.h"
#include "purple_lib.h"
#include "shared.h"
#include "hardcode.h"

// main shell loop
int client(void) {
    char shell_buf[SHELL_BUF_SIZE];

    shell_buf[0] = 0;
    while (shell_buf[0] != EOF) {
        printf(PS1);
        if (!getstr(shell_buf)) {
            error_shell_buff_overflow();
            continue;
        }
        if (!parse_query(shell_buf)) {
            error_shell_query_parse();
            continue;
        }
    }
    return (1);
}

int parse_query(char *str) {
    if (str == NULL)
        return (0);
    if (strlen(str) == 1)
        return (1);
    if (strlen(str) < 3)
        return (0);
    if (strncmp(str, "exit", 4) == 0)
        program_exit();
    if (*(str + strlen(str) - 2) != ';')
        return (error_miss_semicolon());
    if (strncmp(str, "select ", 7) == 0) {
        if (!parse_select_query(str))
            return (0);
        return (1);
    }
    if (strncmp(str, "insert into ", 12) == 0) {
        if (!parse_insert_query(str))
            return (0);
        return (1);
    }
    if (strncmp(str, "delete from ", 12) == 0) {
        if (!parse_delete_query(str))
            return (0);
        return (1);
    }
    if (strncmp(str, "update ", 7) == 0) {
        if (!parse_update_query(str))
            return (0);
        return (1);
    }
    if (strncmp(str, "show tables;", 12) == 0)
        return (show_tables());
    if (strncmp(str, "describe table modules;", 23) == 0)
        return (describe_modules());
    if (strncmp(str, "describe table levels;", 22) == 0)
        return (describe_levels());
    if (strncmp(str, "describe table status_events;", 29) == 0)
        return (describe_status());
    return (0);
}

int parse_select_query(char *str) {
    // column, from_op, table_name, where_op
    // where, equal_op, where_val
    char *lecs[7];
    int lecs_counter;
    int check_out;

    lecs_counter = 0;
    strtok(str, " ");  // skip select
    while (lecs_counter < 7) {
        lecs[lecs_counter] = strtok(NULL, " ");
        space_backslasher(lecs[lecs_counter]);
        lecs_counter++;
    }
    check_out = check_select_query_no_where(lecs);
    if (!check_out)
        return (0);
    if (check_out == 2) {
        if (!check_select_query_where(lecs))
            return (0);
    } else {
        lecs[4] = "*";  // where, empty str - ALL
        lecs[6] = "";  // where_val
    }
    lecs[1] = lecs[2];  // table_name
    lecs[2] = lecs[4];  // where
    lecs[3] = lecs[6];  // where_val
    pretty_print_select(lecs);
    select(lecs);
    return (1);
}

int parse_insert_query(char *str) {
    // table_name, values_op, value1,
    // value2, value3, value4, value5
    //
    // in our way we have only 3 or 5 unit structures
    char *lecs[7];
    int lecs_counter;
    int check_out;

    lecs_counter = 0;
    strtok(str, " (),");  // skip insert
    strtok(NULL, " (),");  // skip into
    while (lecs_counter < 7) {
        lecs[lecs_counter] = strtok(NULL, " (),");
        space_backslasher(lecs[lecs_counter]);
        lecs_counter++;
    }
    check_out = check_insert_query_3arg(lecs);
    if (!check_out)
        return (0);
    if (check_out == 2) {
        if (!check_insert_query_5arg(lecs))
            return (0);
    } else {
        lecs[5] = "";
        lecs[6] = "";
    }
    lecs[1] = lecs[2];  // value1
    lecs[2] = lecs[3];  // value2
    lecs[3] = lecs[4];  // value3
    lecs[4] = lecs[5];  // value4
    lecs[5] = lecs[6];  // value5
    pretty_print_insert(lecs);
    insert(lecs);
    return (1);
}

int parse_delete_query(char *str) {
    // table_name, where_op, where,
    // equal_op, where_val
    char *lecs[5];
    int lecs_counter;

    lecs_counter = 0;
    strtok(str, " ");  // skip delete
    strtok(NULL, " ");  // skip from
    while (lecs_counter < 5) {
        lecs[lecs_counter] = strtok(NULL, " ");
        space_backslasher(lecs[lecs_counter]);
        lecs_counter++;
    }
    if (!check_delete_query(lecs))
        return (0);
    lecs[1] = lecs[2];  // where this
    lecs[2] = lecs[4];  // equal this
    pretty_print_delete(lecs);
    // delete(lecs);
    return (1);
}

int parse_update_query(char *str) {
    // table_name, set_op, column, equal_op
    // new_value, where_op, where, equal_op,
    // where_val
    char *lecs[9];
    int lecs_counter;
    int check_out;

    lecs_counter = 0;
    strtok(str, " ");  // skip select
    while (lecs_counter < 9) {
        lecs[lecs_counter] = strtok(NULL, " ");
        space_backslasher(lecs[lecs_counter]);
        lecs_counter++;
    }
    check_out = check_update_query(lecs);
    if (!check_out)
        return (0);
    lecs[1] = lecs[2];  // column
    lecs[2] = lecs[4];  // new_value
    lecs[3] = lecs[6];  // where
    lecs[4] = lecs[8];  // where_val
    pretty_print_update(lecs);
    update(lecs);
    return (1);
}

int check_select_query_no_where(char **lecs) {
    if (lecs[0] == NULL || strchr(lecs[0], ';'))  // column
        return (0);
    if (lecs[1] == NULL || strcmp(lecs[1], "from"))
        return (0);
    if (lecs[2] == NULL)  // table_name
        return (0);
    if (strchr(lecs[2], ';')) {
        *(strchr(lecs[2], ';')) = '\0';
        if (!strlen(lecs[2]))
            return (0);
        return (1);
    }
    return (2);
}

int check_select_query_where(char **lecs) {
    if (lecs[3] == NULL || strcmp(lecs[3], "where"))
        return (0);
    if (lecs[4] == NULL || strchr(lecs[4], ';'))  // where this
        return (0);
    if (lecs[5] == NULL || strcmp(lecs[5], "="))
        return (0);
    if (lecs[6] == NULL)  // equals this
        return (0);
    if (strchr(lecs[6], ';')) {
        *(strchr(lecs[6], ';')) = '\0';  // remove ';'
        if (!strlen(lecs[6]))
            return (0);
    }
    return (1);
}

int check_insert_query_3arg(char **lecs) {
    if (lecs[0] == NULL || strchr(lecs[0], ';'))  // table_name
        return (0);
    if (lecs[1] == NULL || strcmp(lecs[1], "values"))
        return (0);
    if (lecs[2] == NULL || strchr(lecs[2], ';'))  // value1
        return (0);
    if (lecs[3] == NULL || strchr(lecs[3], ';'))  // value2
        return (0);
    if (lecs[4] == NULL || strchr(lecs[4], ';'))  // value3
        return (0);
    if (strchr(lecs[5], ';')) {  // TODO(griselle): fix unpair parentesis
        *(strchr(lecs[5], ';')) = '\0';
        if (strlen(lecs[5]))
            return (0);
        return (1);
    }
    return (2);
}

int check_insert_query_5arg(char **lecs) {
    if (lecs[5] == NULL || strchr(lecs[0], ';'))  // value4
        return (0);
    if (lecs[6] == NULL)  // value5
        return (0);
    if (strchr(lecs[6], ';')) {
        *(strchr(lecs[6], ';')) = '\0';
        if (!strlen(lecs[6]))
            return (0);
    }
    return (1);
}

int check_delete_query(char **lecs) {
    if (lecs[0] == NULL || strchr(lecs[0], ';'))  // table_name
        return (0);
    if (lecs[1] == NULL || strcmp(lecs[1], "where"))
        return (0);
    if (lecs[2] == NULL || strchr(lecs[2], ';'))  // where this
        return (0);
    if (lecs[3] == NULL || strcmp(lecs[3], "="))
        return (0);
    if (lecs[4] == NULL)  // equals this
        return (0);
    if (strchr(lecs[4], ';')) {
        *(strchr(lecs[4], ';')) = '\0';  // remove ';'
        if (!strlen(lecs[4]))
            return (0);
    }
    return (1);
}

int check_update_query(char **lecs) {
    if (lecs[0] == NULL || strchr(lecs[0], ';'))  // table_name
        return (0);
    if (lecs[1] == NULL || strcmp(lecs[1], "set"))
        return (0);
    if (lecs[2] == NULL || strchr(lecs[2], ';'))  // column
        return (0);
    if (lecs[3] == NULL || strcmp(lecs[3], "="))
        return (0);
    if (lecs[4] == NULL || strchr(lecs[4], ';'))  // new_value
        return (0);
    if (lecs[5] == NULL || strcmp(lecs[5], "where"))
        return (0);
    if (lecs[6] == NULL || strchr(lecs[6], ';'))  // where this
        return (0);
    if (lecs[7] == NULL || strcmp(lecs[7], "="))
        return (0);
    if (lecs[8] == NULL)  // equals this
        return (0);
    if (strchr(lecs[8], ';')) {
        *(strchr(lecs[8], ';')) = '\0';  // remove ';'
        if (!strlen(lecs[8]))
            return (0);
    }
    return (1);
}

char *space_backslasher(char *str) {
    char *new_ptr;

    new_ptr = str;
    while (new_ptr && *new_ptr != '\0') {
        if (*new_ptr == '\\')
            *new_ptr = ' ';
        new_ptr++;
    }
    return (str);
}

void program_exit(void) {
    // save all shit
    printf("Bye..\n");
    exit(0);
}
