#include "hangman.h"
#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MAX_LENGTH = 255 };

enum { WITHPOINT = -1, WITHOUTPOINT = 0 };

enum { USEDLETTER = -1, UNUSEDLETTER = 0 };

enum { INCORLETTER = '0', INCORRECTLETTER = -1, CORRECTLETTER = 0 };

void print_hangman(int n)
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

void print_theme_menu(char** dir_name, int value_dic)
{
    printf("Theme menu:\n\n");
    for (int i = 0; i < value_dic; i++) {
        printf("%d - theme \"%s\"\n", i + 1, dir_name[i]);
    }
    printf("\n");
}

int check_theme(char* arr, int value_dic)
{
    int theme = atoi(arr);
    for (size_t i = 0; i < strlen(arr); i++) {
        if ((isdigit(arr[i]) || arr[i] == '\n') && theme <= value_dic
            && theme > 0) {
            continue;
        } else {
            return INCORTHEME;
        }
    }
    return theme;
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

int choose_theme(int value_dic)
{
    char choice[MAX_LENGTH];
    int theme;
    fgets(choice, MAX_LENGTH, stdin);
    if ((theme = check_theme(choice, value_dic)) == INCORTHEME) {
        return INCORTHEME;
    }
    return theme;
}

int get_rand(int min, int max)
{
    return (int)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

void fill_arr(char* empty, int length, char* symbols)
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
}

char** mem_resize(int value, char** array)
{
    char** h = realloc(array, value * sizeof(char*));
    if (h == NULL) {
        return CANTREALLOCMEMORY;
    }
    return h;
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
    char temp[MAX_LENGTH];
    strcpy(temp, name);
    cut_ext(temp);
    dir_name[count_dic] = (char*)malloc(strlen(temp) + 1);
    strcpy(dir_name[count_dic], temp);
}

char** open_dir(int* value_dic, int* num_error)
{
    DIR* dir;
    struct dirent* entry;

    dir = opendir("../dictionary");
    if (!dir) {
        *num_error = CANTOPENDIR;
        return CANTOPENDIRECT;
    }

    *value_dic = 200;
    char** dir_name = (char**)malloc((*value_dic) * sizeof(char*));
    if (dir_name == NULL) {
        *num_error = CANTMALLOCMEM;
        return CANTMALLOCMEMORY;
    }

    int count_dic = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (count_dic == *value_dic) {
            *value_dic *= 2;
            char** h = mem_resize(*value_dic, dir_name);
            if (h == NULL) {
                free(dir_name);
                *num_error = CANTREALLOCMEM;
                return CANTREALLOCMEMORY;
            }
            dir_name = h;
        }
        if (skip_point(entry->d_name) == WITHPOINT) {
            continue;
        }
        cut_name(entry->d_name, dir_name, count_dic);
        count_dic++;
    }
    closedir(dir);

    *value_dic = count_dic;
    char** h = mem_resize(*value_dic, dir_name);
    if (h == CANTREALLOCMEMORY) {
        free(dir_name);
        *num_error = CANTREALLOCMEM;
        return CANTREALLOCMEMORY;
    }
    *num_error = WITHOUTERROR;
    dir_name = h;
    return dir_name;
}

char** get_words_array(int* value_words, char path[], int* num_error)
{
    FILE* fp = fopen(path, "r");
    if (fp == NULL) {
        *num_error = CANTOPENFILE;
        return CANNOTOPENFILE;
    }

    *value_words = 200;
    char** words = (char**)malloc((*value_words) * sizeof(char*));
    if (words == NULL) {
        *num_error = CANTMALLOCMEM;
        return CANTMALLOCMEMORY;
    }
    char tmp[MAX_LENGTH];
    int count_word = 0;

    while (fgets(tmp, MAX_LENGTH, fp)) {
        if (count_word == *value_words) {
            *value_words *= 2;
            char** h = mem_resize(*value_words, words);
            if (h == NULL) {
                *num_error = CANTREALLOCMEM;
                return CANTREALLOCMEMORY;
            }
            words = h;
        }

        words[count_word] = (char*)malloc(strlen(tmp) + 1);
        if (words[count_word] == NULL) {
            free(words);
            *num_error = CANTMALLOCMEM;
            return CANTMALLOCMEMORY;
        }
        strcpy(words[count_word], tmp);
        count_word++;
    }

    *value_words = count_word;
    char** h = mem_resize(*value_words, words);
    if (h == CANTREALLOCMEMORY) {
        *num_error = CANTREALLOCMEM;
        return CANTREALLOCMEMORY;
    }
    words = h;
    fclose(fp);
    *num_error = WITHOUTERROR;
    return words;
}

char* concat_path_name(char* dir_name, int* num_error)
{
    char* path_dir = "../dictionary/";
    char* expansion = ".txt";
    int length = strlen(path_dir) + strlen(expansion) + strlen(dir_name);
    char* path = (char*)calloc(length, sizeof(char));
    if (path == NULL) {
        *num_error = CANTCALLOCMEM;
        return CANTCALLOCMEMORY;
    }
    strcat(path, path_dir);
    strcat(path, dir_name);
    strcat(path, expansion);
    *num_error = WITHOUTERROR;
    return path;
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

int check_letter(char choice[])
{
    if (strlen(choice) - 1 > 1) {
        return INCORRECTLETTER;
    }
    if (isdigit(choice[0]) != 0 || ispunct(choice[0]) != 0) {
        return INCORRECTLETTER;
    }
    if (choice[0] == '\n' || choice[0] == ' ' || choice[0] == '\t') {
        return INCORRECTLETTER;
    }
    return CORRECTLETTER;
}

char enter_letter(char* used_ch, int max)
{
    char choice[MAX_LENGTH];
    fgets(choice, MAX_LENGTH, stdin);
    if (check_letter(choice) == INCORRECTLETTER) {
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
        print_hangman(num_error);

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

int play_again()
{
    char exit_status[MAX_LENGTH];

    fgets(exit_status, MAX_LENGTH, stdin);
    // можно проверять на правильность
    int yes = strncasecmp(exit_status, "Y", 1);
    int no = strncasecmp(exit_status, "N", 1);
    if ((yes != 0 && no != 0) || strlen(exit_status) > 2) {
        return INCORRECT;
    }
    if (yes == 0) {
        return PLAY;
    }
    if (no == 0) {
        return EXIT;
    }
    return EXIT;
}

int check_error(int error)
{
    switch (error) {
    case -1:
        printf("Can not read directory.\n");
        return CANTOPENDIR;
    case -2:
        printf("Cannot open file.\n");
        return CANTOPENFILE;
    case -3:
        printf("Memory is not reallocated\n");
        return CANTREALLOCMEM;
    case -4:
        printf("The paths did not merge.\n");
        return CANTCALLOCMEM;
    case -5:
        printf("Memory is not malloced\n");
        return CANTMALLOCMEM;
    default:
        return WITHOUTERROR;
    }
}
