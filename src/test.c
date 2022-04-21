// Copyright [2022] <drunkbatya, koterin, grusnydance>

#include "test.h"

int main(void)
{
    // create table my_table (id integer, name string, age integer);
    char *arr[7];
    arr[0] = "my_table";
    arr[1] = "id";
    arr[2] = "integer";
    arr[3] = "name";
    arr[4] = "string";
    arr[5] = "age";
    arr[6] = "integer";
    if (p_create(arr, 3) == 0)
    {
        printf("Create table error!\n");
        return (1);
    }

    arr[1] = "310";
    arr[2] = "Dasha is so cool!";
    arr[3] = "24";
    insert(arr);

    arr[1] = "410";
    arr[2] = "Dasha cool!";
    arr[3] = "25";
    insert(arr);

    arr[1] = "045";
    arr[2] = "fghjkl;";
    arr[3] = "256";
    insert(arr);

    arr[1] = "id";
    arr[2] = "100500";
    arr[3] = "age";
    arr[4] = "<";
    arr[5] = "25";
    update(arr);

    arr[1] = "name";
    arr[2] = "Everybody cool";
    arr[3] = "name";
    arr[4] = "=";
    arr[5] = "Dasha is so cool!";
    update(arr);

    arr[1] = "age";
    arr[2] = "=";
    arr[3] = "25";
    delete(arr);

    printf("Rows: %d\n", get_rows_count("my_table.db"));
    arr[1] = "*";
    arr[2] = "*";
    arr[3] = "";
    p_select(arr);
    return (0);
}
