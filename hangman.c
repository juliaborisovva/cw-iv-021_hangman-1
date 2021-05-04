#include "hangman.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void cut_ext(char* fname)
{
    char* end = fname + strlen(fname);

    while (end > fname && *end != '.') {
        --end;
    }

    if (end > fname) {
        *end = '\0';
    }
}

void theme_menu(char** dir_name, int value_dic)
{
    printf("Theme menu:\n\n");
    for (int i = 0; i < value_dic; i++) {
        printf("%d - theme \"%s\"\n", i + 1, dir_name[i]);
    }
}

int check_digit(char* arr, int max)
{
    for (int i = 0; i < max; i++) {
        if (isdigit(arr[i]) || arr[i] == '\n') {
            continue;
        } else {
            return -1;
        }
    }
    return 0;
}