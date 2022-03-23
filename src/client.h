// Copyright [2022] <griselle, sparelis, laynadre>

#ifndef SRC_CLIENT_H_
#define SRC_CLIENT_H_

#define PS1 "PurpleDB :-( "
#define WELCOME "Welcome to PurpleDB!\n\n"
#define SHELL_BUF_SIZE 40

int client(void);
int parse_query(char *str);
int parse_select_query(char *str);
#endif  // SRC_CLIENT_H_
