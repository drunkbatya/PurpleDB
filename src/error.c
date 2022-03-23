// Copyright [2022] <griselle, sparelis, laynadre>

#include <stdio.h>
#include "client.h"

int error_shell_buff_overflow(void) {
    printf("\nError! Query is too large - max %d chars\n", SHELL_BUF_SIZE);
    return (0);
}
