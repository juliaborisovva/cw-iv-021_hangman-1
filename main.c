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
        i++;
    }

    closedir(dir);

    value_dic = i;
    char** h = realloc(dir_name, value_dic * sizeof(char*));
    if (h == NULL) {
        return -1;
    }
    dir_name = h;

    system("clear");
    theme_menu(dir_name, value_dic);
    printf("Please, choose theme for your game.\n");

    char choice[255];
    int a = 0;

    while (fgets(choice, 255, stdin)) { // можно проверять на правильность
        if (check_digit(choice, strlen(choice)) == -1) {
            printf("It isn't correct punct of menu. Try again.\n");
            continue;
        }
        a = atoi(choice);
        if (a > value_dic) {
            printf("It isn't correct punct of menu. Try again.\n");
        } else {
            break;
        }
    }
    printf("%s\n", choice); // вывод выбора
}