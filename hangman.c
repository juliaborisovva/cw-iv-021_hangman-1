#include "hangman.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
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

int memory_trim(char** array, int* value, int count)
{
    *value = count;
    char** h = realloc(array, *value * sizeof(char*));
    if (h != NULL) {
        array = h;
        return 0;
    } else {
        return -1;
    }
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