#pragma once

#define CANTTRUNCMEMORY NULL
#define CANTOPENDIRECT NULL

enum {
    CANTOPENDIR = -1,
    CANTOPENFILE = -1,
    CANTTRUNCMEM = -1,
    CANTREALLOCMEM = -1,
    MEMTRUNCATED = 0,
    REALLOCEDMEM = 0
};

void cut_ext(char* fname);

void theme_menu(char** dir_name, int value_dic);

int check_digit(char* arr, int max);

void free_mem(char** dir_name, int value_dic, char** words, int value_words);

int trim_memory(char** array, int* value, int count);

int choice_theme(int value_dic);

int get_rand(int min, int max);

int fill_arr(char* empty, int length, char* symbols);

int mem_expansion(int* value_dic, char** dir_name);

int skip_point(char* name);

void cut_name(char* name, char** dir_name, int count_dic);

char** open_dir(int* value_dic);
