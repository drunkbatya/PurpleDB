// Copyright [2022] <drunkbatya>

#include "select.h"

uint8_t select(char **arr)
{
    char file_path[strlen(arr[0]) + 2];

    strcpy(file_path, arr[0]);
    strcat(file_path, ".db");
    return (1);
}
