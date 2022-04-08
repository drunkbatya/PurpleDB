// Copyright [2022] <drunkbatya, koterin, GrusnyDance>

#ifndef SRC_PRETTY_PRINT_H_
#define SRC_PRETTY_PRINT_H_

#include <stdio.h>
#include "client.h"

void pretty_print_select(char **arr);
void pretty_print_insert(char **arr);
void pretty_print_delete(char **arr);
void pretty_print_update(char **arr);
void pretty_print_create(char **arr, uint16_t column_count);

#endif  // SRC_PRETTY_PRINT_H_
