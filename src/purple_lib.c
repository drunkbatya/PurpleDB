// Copyright [2022] <griselle, sparelis, laynadre>

#include <stdio.h>
#include "client.h"
#include "purple_lib.h"

int getstr(char *buf) {
    int ch;
    char *new_ptr;

    ch = 0;
    new_ptr = buf;
    while (ch != '\n' && ch != -1) {
        *new_ptr = getchar();
        ch = *new_ptr;
        new_ptr++;
        if (new_ptr - buf > SHELL_BUF_SIZE - 1)
            return (0);
    }
    *new_ptr = '\0';
    return (1);
}
