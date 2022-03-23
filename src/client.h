// Copyright [2022] <griselle, sparelis, laynadre>

#ifndef SRC_CLIENT_H_
#define SRC_CLIENT_H_

#define PS1 "PurpleDB :-( "
#define WELCOME "Welcome to PurpleDB!\n\n"
#define SHELL_BUF_SIZE 60

#define NC "\033[0m"
#define CYAN "\033[0;36m"
#define BOLD "\033[1m"

int client(void);
int parse_query(char *str);
int parse_select_query(char *str);
void pretty_print_select(char *table_name, char *column, char *where, char *where_val);
#endif  // SRC_CLIENT_H_
