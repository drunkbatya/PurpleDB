// Copyright [2022] <drunkbatya>

#include "main.h"

int main(void)
{
    // create table my_table (id integer, name string);
    char *arr[7];
    arr[0] = "my_table";
    arr[1] = "id";
    arr[2] = "integer";
    arr[3] = "name";
    arr[4] = "string";
    arr[5] = "age";
    arr[6] = "integer";
    if (create_table(arr, 3) == 0)
    {
        printf("Create table error!\n");
        return (1);
    }
    
    char *insert_arr[4];
    insert_arr[0] = "my_table";
    insert_arr[1] = "310";
    insert_arr[2] = "Dasha is so cool!";
    insert_arr[3] = "24";
 
    if (insert(insert_arr) == 0)
    {
        printf("Insert error!\n");
        return (1);
    }
    insert_arr[0] = "my_table";
    insert_arr[1] = "410";
    insert_arr[2] = "Dasha cool!";
    insert_arr[3] = "25";
 
    if (insert(insert_arr) == 0)
    {
        printf("Insert error!\n");
        return (1);
    }
    insert_arr[0] = "my_table";
    insert_arr[1] = "045";
    insert_arr[2] = "fghjkl;";
    insert_arr[3] = "256";
 
    if (insert(insert_arr) == 0)
    {
        printf("Insert error!\n");
        return (1);
    }
    insert_arr[0] = "my_table";
    insert_arr[1] = "8976";
    insert_arr[2] = "Dashhhhhh";
    insert_arr[3] = "06";
 
    if (insert(insert_arr) == 0)
    {
        printf("Insert error!\n");
        return (1);
    }
    printf("Rows: %d\n", get_rows_count("my_table.db"));
    if (p_select(arr) == 0)
    {
        printf("Select error!\n");
        return (1);
    }
    return (0);
}
