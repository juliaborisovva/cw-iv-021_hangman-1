#include "hangman.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    DIR* dir;
    struct dirent* entry;

    dir = opendir("dictionary");
    if (!dir) {
        printf("Cannot read directory.\n");
        return -1;
    }

    int value_dic = 200;
    char** dir_name = (char**)malloc(value_dic * sizeof(char*));

    int i = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (i == value_dic) {
            value_dic *= 2;
            char** h = realloc(dir_name, value_dic * sizeof(char*));
            if (h == NULL) {
                return -1;
            }
            dir_name = h;
        }
        if (strcmp(entry->d_name, ".") == 0
            || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char temp[255];
        strcpy(temp, entry->d_name);

        cut_ext(temp);
        dir_name[i] = (char*)malloc(strlen(temp) + 1);
        strcpy(dir_name[i], temp);
        printf("\"%s\"\n", dir_name[i]);
        i++;
    }

    closedir(dir);

    value_dic = i;
    char** h = realloc(dir_name, value_dic * sizeof(char*));
    if (h == NULL) {
        return -1;
    }
    dir_name = h;
}
