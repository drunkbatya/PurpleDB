// Copyright [2022] <drunkbatya>

#ifndef SRC_STRUCTURE_H_
#define SRC_STRUCTURE_H_

typedef enum e_datatype
{
    integer,
    string,
    error
} t_datatype;

typedef struct s_header
{
    char column_name[40];
    t_datatype datatype;
} t_header;

#define COLUMN_COUNT_SHIFT sizeof(uint8_t)
#endif  // SRC_STRUCTURE_H_
