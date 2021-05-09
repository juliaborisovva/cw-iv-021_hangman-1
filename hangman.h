#pragma once

void cut_ext(char* fname);

void theme_menu(char** dir_name, int value_dic);

int check_digit(char* arr, int max);

void free_mem(char** dir_name, int value_dic, char** words, int value_words);

int memory_trim(char** array, int* value, int count);

int choice_theme(int value_dic);

int get_rand(int min, int max);

int fill_arr(char* empty, int length, char* symbols);
