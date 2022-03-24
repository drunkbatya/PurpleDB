// Copyright [2022] <griselle, sparelis, laynadre>

#ifndef SRC_CLIENT_H_
#define SRC_CLIENT_H_

#define PS1 "PurpleDB :-( "
#define WELCOME "Welcome to PurpleDB!\n\n"
#define SHELL_BUF_SIZE 200

#define NC "\033[0m"
#define CYAN "\033[0;36m"
#define BOLD "\033[1m"

int client(void);
int parse_query(char *str);
int parse_select_query(char *str);
int parse_insert_query(char *str);
int parse_delete_query(char *str);
int parse_update_query(char *str);
int check_select_query_no_where(char **lecs);
int check_select_query_where(char **lecs);
int check_insert_query_3arg(char **lecs);
int check_insert_query_5arg(char **lecs);
int check_delete_query(char **lecs);
int check_update_query(char **lecs);
char *space_backslasher(char *str);
void program_exit(void);
#endif  // SRC_CLIENT_H_
