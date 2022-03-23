// Copyright [2022] <griselle, sparelis, laynadre>

#include <stdio.h>
#include "client.h"

int error_shell_buff_overflow(void) {
    printf("\nError! Query is too large - max %d chars\n", SHELL_BUF_SIZE);
    return (1);
}

int error_shell_query_parse(void) {
    printf("\nError! Incorrect query\n");
    return (1);
}

int error_miss_semicolon(void) {
    printf("\nError! Incorrect query: miss semicolon - ';'\n");
    return (1);
}
