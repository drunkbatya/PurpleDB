#include <stlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

void print_directory();
    DIR *d;
    d = opendir(".//");
    if (d) {
        struct dirent *dir;
        while ((dir = readdir(d)) != NULL) {
            char *full_path = calloc(150, sizeof(char));
            strcpy(full_path, "ai_modules/");
            strcat(full_path, dir->d_name);
            if (strstr(full_path, ".h") != NULL) {
                FILE *ptr = fopen(full_path, "w");
                fclose(ptr);
            }
            free(full_path);
        }
        closedir(d);
    }
}

