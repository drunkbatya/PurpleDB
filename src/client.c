// Copyright [2022] <griselle, sparelis, laynadre>

#include <stdio.h>
#include <string.h>
#include "error.h"
#include "client.h"
#include "purple_lib.h"

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
    if (*(str + strlen(str) - 2) != ';')
        return (error_miss_semicolon());
    if (!strncmp(str, "select ", 7)) {
        if (!parse_select_query(str))
            return (0);
        return (1);
    }
    return (0);
}

int parse_select_query(char *str) {
    char *table_name;
    char *column;
    char *temp;
    char *where;
    char *where_val;

    // select * from modules where id = 1;
    // select * from modules;
    strtok(str, " "); // skip select
    column = strtok(NULL, " ");
    if (column == NULL || strchr(column, ';'))
        return (0);
    temp = strtok(NULL, " ");
    if (temp == NULL || strcmp(temp, "from"))
        return (0);
    table_name = strtok(NULL, " ");
    if (table_name == NULL)
        return (0);
    if (strchr(table_name, ';')) {
        *(strchr(table_name, ';')) = '\0';
        if (!strlen(table_name))
            return (0);
        where = "*";
        where_val = "*";
    } else {
        temp = strtok(NULL, " ");
        if (temp == NULL || strcmp(temp, "where"))
            return (0);
        where = strtok(NULL, " ");
        if (where == NULL || strchr(where, ';'))
            return (0);
        temp = strtok(NULL, " ");
        if (temp == NULL || strcmp(temp, "="))
            return (0);
        where_val = strtok(NULL, " ");
        if (where_val == NULL)
            return (0);
        if (strchr(where_val, ';')) {
            *(strchr(where_val, ';')) = '\0';
            if (!strlen(where_val))
                return (0);
        }
    }
    printf("|%s|\n", table_name);
    //pretty_print_select(table_name, column, where, where_val);
    //select(char *table_name, char *column, char *where, char *where_val);
    return (1);
}

// void pretty_print_select(char *table_name, char *column, char *where, char *where_val)
