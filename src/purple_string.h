// Copyright [2022] <drunkbatya, koterin, GrusnyDance>

#ifndef SRC_PURPLE_STRING_H_
#define SRC_PURPLE_STRING_H_

#include <stdio.h>
#include <string.h>
#include "error.h"

uint8_t quoted_space_driver(char *str);
uint8_t check_unpair_char(char *str, char c);
void remove_char_from_str(char *str, char c);
uint8_t getstr(char *buf);

#endif  // SRC_PURPLE_STRING_H_
