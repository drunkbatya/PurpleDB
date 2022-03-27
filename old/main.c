// Copyright [2022] <griselle, sparelis, laynadre>

#include <stdio.h>
#include "client.h"

int main(void) {
    printf(WELCOME);
    if (!client())
        return (1);
    return (0);
}
