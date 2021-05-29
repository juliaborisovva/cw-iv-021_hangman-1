#pragma once

#define CANTOPENDIRECT NULL
#define CANTMALLOCMEMORY NULL
#define CANTCALLOCMEMORY NULL
#define CANTREALLOCMEMORY NULL
#define CANNOTOPENFILE NULL

enum {
    CANTOPENDIR = -1,
    CANTOPENFILE = -2,
    CANTREALLOCMEM = -3,
    CANTCALLOCMEM = -4,
    CANTMALLOCMEM = -5,
    WITHOUTERROR = 0
};

enum { WIN = 1, LOSE = 2 };

enum { INCORRECT = -2, PLAY = 1, EXIT = 0 };

enum { INCORTHEME = -1 };

void print_hangman(int n);

void cut_ext(char* fname);

void print_theme_menu(char** dir_name, int value_dic);

int check_theme(char* arr, int value_dic);

void free_mem(char** dir_name, int value_dic, char** words, int value_words);

char** mem_resize(int value, char** array);

int choose_theme(int value_dic);

int get_rand(int min, int max);

void fill_arr(char* empty, int length, char* symbols);

int skip_point(char* name);

void cut_name(char* name, char** dir_name, int count_dic);

char** open_dir(int* value_dic, int* num_error);

int check_usage(char* used_ch, int max, char letter);

int check_letter(char choice[]);

char enter_letter(char* used_ch, int max);

int check_match(
        char* guessed, char* hidden, int len, char letter, int* num_guess_ch);

int play_game(char guessed_word[], char hidden_word[], int length);

int play_again();

int play_again_main();

char* concat_path_name(char* dir_name, int* num_error);

char** get_words_array(int* value_words, char path[], int* num_error);

int check_error(int error);
