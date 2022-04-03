// Copyright [2022] <drunkbatya, koterin, GrusnyDance>

#ifndef SRC_CLIENT_H_
#define SRC_CLIENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "purple_string.h"
#include "error.h"
#include "pretty_print.h"

#define PS1 "PurpleDB :-( "
#define WELCOME "Welcome to PurpleDB!\n\n"
#define SHELL_BUF_SIZE 250

#define NC "\033[0m"
#define CYAN "\033[0;36m"
#define BOLD "\033[1m"
#define PURPLE "\033[0;35m"

void client(void);
void parse_query(char *str);
uint8_t parse_select_query(char *str);
uint8_t parse_insert_query(char *str);
uint8_t parse_delete_query(char *str);
uint8_t parse_update_query(char *str);
uint8_t check_select_query_no_where(char **lecs);
uint8_t check_select_query_where(char **lecs);
uint8_t check_insert_query_3arg(char **lecs);
uint8_t check_insert_query_5arg(char **lecs);
uint8_t check_delete_query(char **lecs);
uint8_t check_update_query(char **lecs);
void program_exit(void);

#endif  // SRC_CLIENT_H_
