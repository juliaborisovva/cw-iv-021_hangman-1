#include "hangman.h"
#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CANTREALLOCMEMORY NULL

enum { WITHPOINT = -1, WITHOUTPOINT = 0 };

enum { USEDLETTER = -1, UNUSEDLETTER = 0 };

enum { INCORLETTER = '0' };

void hangman(int n)
{
    switch (n) {
    case 9:
        printf("+ + + + + +\n+   ____  +\n+  |   |  +\n+  |   0  +\n+  "
               "|  /|\\ "
               "+\n+ _|_ / \\ "
               "+\n+ + + + + +");
        break;
    case 8:
        printf("+ + + + + +\n+   ____  +\n+  |   |  +\n+  |   0  +\n+  "
               "|  /|\\ "
               "+\n+ _|_ /   "
               "+\n+ + + + + +");
        break;
    case 7:
        printf("+ + + + + +\n+   ____  +\n+  |   |  +\n+  |   0  +\n+  "
               "|  /|\\ "
               "+\n+ _|_     "
               "+\n+ + + + + +");
        break;
    case 6:
        printf("+ + + + + +\n+   ____  +\n+  |   |  +\n+  |   0  +\n+  "
               "|  /|  "
               "+\n+ _|_     "
               "+\n+ + + + + +");
        break;
    case 5:
        printf("+ + + + + +\n+   ____  +\n+  |   |  +\n+  |   0  +\n+  "
               "|   |  "
               "+\n+ _|_     "
               "+\n+ + + + + +");
        break;
    case 4:
        printf("+ + + + + +\n+   ____  +\n+  |   |  +\n+  |   0  +\n+  "
               "|      "
               "+\n+ _|_     "
               "+\n+ + + + + +");
        break;
    case 3:
        printf("+ + + + + +\n+   ____  +\n+  |      +\n+  |      +\n+  "
               "|      "
               "+\n+ _|_     "
               "+\n+ + + + + +");
        break;
    case 2:
        printf("+ + + + + +\n+         +\n+         +\n+         +\n+  "
               "       "
               "+\n+ _|_   "
               "  +\n+ + + + + +");
        break;
    case 1:
        printf("+ + + + + +\n+         +\n+         +\n+         +\n+  "
               "       "
               "+\n+ ___   "
               "  +\n+ + + + + +");
        break;
    case 0:
        printf("+ + + + + +\n+         +\n+         +\n+         +\n+  "
               "       "
               "+\n+         "
               "+\n+ + + + + "
               "+");
        break;
    default:
        break;
    }
}

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

int check_usage(char* used_ch, int max, char letter)
{
    for (int i = 0; i < max; i++) {
        if (used_ch[i] == tolower(letter)) {
            return USEDLETTER;
        }
    }
    return UNUSEDLETTER;
}

char enter_letter(char* used_ch, int max)
{
    char choice[255];

    fgets(choice, 255, stdin); // можно проверять на правильность
    if (strlen(choice) - 1 > 1) {
        return INCORLETTER;
    }
    if (isdigit(choice[0]) != 0 || ispunct(choice[0]) != 0) {
        return INCORLETTER;
    }
    if (check_usage(used_ch, max, choice[0]) != UNUSEDLETTER) {
        return INCORLETTER;
    }
    return choice[0];
}

int check_match(
        char* guessed, char* hidden, int len, char letter, int* num_guess_ch)
{
    int no_match = 0;
    for (int i = 0; i < len; i++) {
        if (tolower(guessed[i]) == tolower(letter)) {
            (*num_guess_ch)--;
            hidden[i] = tolower(letter);
        } else {
            no_match++;
        }
    }
    return no_match;
}

int play_game(char guessed_word[], char hidden_word[], int length)
{
    int num_error = 0;
    int num_guess_ch = length - 1;
    char used_ch[26];
    int used_ch_end = 0;

    while (num_guess_ch >= 0 || num_error <= 9) {
        system("clear");
        hangman(num_error);

        if (num_error == 9) {
            printf("\t%s\n", guessed_word);
        } else {
            printf("\t%s\n", hidden_word);
        }

        printf("You have %d errors\n", num_error);
        printf("Used letters:\n");
        for (int i = 0; i < used_ch_end; i++) {
            printf("%c", used_ch[i]);
        }
        if (num_guess_ch == 0) {
            return WIN;
        }
        if (num_error == 9) {
            return LOSE;
        }

        printf("\nEnter letter:\n");
        char letter = enter_letter(used_ch, used_ch_end);
        if (letter == INCORLETTER) {
            continue;
        }

        int no_match = check_match(
                guessed_word, hidden_word, length - 1, letter, &num_guess_ch);
        if (no_match == length - 1) {
            num_error++;
        }
        used_ch[used_ch_end] = tolower(letter);
        used_ch_end++;
    }
    return LOSE;
}
