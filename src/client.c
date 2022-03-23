// Copyright [2022] <griselle, sparelis, laynadre>

#include <stdio.h>
#include "error.h"
#include "client.h"
#include "purple_lib.h"

// main shell loop
int client(void) {
    char shell_buf[SHELL_BUF_SIZE];

    while (shell_buf[0] != EOF) {
        printf(PS1);
        if (!getstr(shell_buf))
            return (error_shell_buff_overflow());
    }
    return (1);
}
