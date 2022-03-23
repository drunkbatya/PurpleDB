#include <stdio.h>
#include <stdlib.h>


int main() {


}


select_for_modules(int id, char * module_name, int mem_level, int ) {
    if (read_binary_file(db) == 0) {
        free(filename);
        printf("n/a");
    }
}



int read_binary_file(char *filename) {
    struct my_struct record;
    FILE *ptr = fopen(filename, "r");
    if (ptr == NULL) {
        return 0;
    } else {
        int len = get_records_count_in_file(ptr);
        for (int i = 0; i < len; i++) {
            record = read_record_from_file(ptr, i);
            print_struct(&record);
        }
        fclose(ptr);
    }
    return 1;
}
