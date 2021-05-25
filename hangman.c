#include "hangman.h"
#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CANTREALLOCMEMORY NULL

enum { WITHPOINT = -1, WITHOUTPOINT = 0 };

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

int trim_memory(char** array, int* value, int count)
{
    *value = count;
    char** h = realloc(array, *value * sizeof(char*));
    if (h != NULL) {
        array = h;
        return MEMTRUNCATED;
    }
    return CANTTRUNCMEM;
}

void free_mem(char** dir_name, int value_dic, char** words, int value_words)
{
    for (int r = value_dic - 1; r >= 0; r--) {
        free(dir_name[r]); // очищаем память выделенную под массив слов
    }
    free(dir_name);
    for (int r = value_words - 1; r >= 0; r--) {
        free(words[r]); // очищаем память выделенную под массив слов
    }
    free(words);
}

int choice_theme(int value_dic)
{
    char choice[255];
    int theme = 0;

    while (fgets(choice, 255, stdin)) { // можно проверять на правильность
        if (check_digit(choice, strlen(choice)) == -1) {
            return -1;
        }
        theme = atoi(choice);
        if (theme > value_dic) {
            return -1;
        } else {
            break;
        }
    }
    return theme;
}

int get_rand(int min, int max)
{
    return (int)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

int fill_arr(char* empty, int length, char* symbols)
{
    if (strlen(symbols) == 1) {
        for (int i = 0; i < length; i++) {
            empty[i] = symbols[0];
        }
    } else {
        for (int i = 0; i < length; i++) {
            empty[i] = symbols[i];
        }
    }
    empty[length] = '\0';

    return 0;
}

int mem_expansion(int* value, char** str)
{
    *value *= 2;
    char** h = realloc(str, *value * sizeof(char*));
    if (h == NULL) {
        return CANTREALLOCMEM;
    }
    str = h;
    return REALLOCEDMEM;
}

int skip_point(char name[])
{
    if (name[0] == '.') {
        return WITHPOINT;
    }
    return WITHOUTPOINT;
}

void cut_name(char* name, char** dir_name, int count_dic)
{
    char temp[255];
    strcpy(temp, name);
    cut_ext(temp);
    dir_name[count_dic] = (char*)malloc(strlen(temp) + 1);
    strcpy(dir_name[count_dic], temp);
}

char** open_dir(int* value_dic)
{
    DIR* dir;
    struct dirent* entry;

    dir = opendir("dictionary");
    if (!dir) {
        return CANTOPENDIRECT;
    }

    *value_dic = 200;
    char** dir_name = (char**)malloc((*value_dic) * sizeof(char*));
    int check_mem;
    int count_dic = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (count_dic == *value_dic) {
            check_mem = mem_expansion(value_dic, dir_name);
            if (check_mem == CANTREALLOCMEM) {
                return CANTREALLOCMEMORY;
            }
        }
        if (skip_point(entry->d_name) == WITHPOINT) {
            continue;
        }
        cut_name(entry->d_name, dir_name, count_dic);
        count_dic++;
    }
    closedir(dir);
    int check_trim;
    check_trim = trim_memory(dir_name, value_dic, count_dic);
    if (check_trim == CANTTRUNCMEM) {
        return CANTTRUNCMEMORY;
    }
    return dir_name;
}
