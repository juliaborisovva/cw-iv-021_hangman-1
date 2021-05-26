#include "hangman.h"
#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main()
{
    int exit_condition = 1;
    srand(time(NULL));

    while (exit_condition) {
        int value_dic;
        char** dir_name = open_dir(&value_dic);
        if (dir_name == CANTOPENDIRECT) {
            return CANTOPENDIR;
            printf("Can not read directory.\n");
        } else if (dir_name == CANTTRUNCMEMORY) {
            printf("Memory is not truncated\n");
            return CANTTRUNCMEM;
        }

        system("clear");
        theme_menu(dir_name, value_dic);
        printf("Please, choose theme for your game.\n");
        int theme;

        while (1) {
            theme = choose_theme(value_dic);
            if (theme < 1) {
                printf("It isn't correct punct of menu. Try again.\n");
                continue;
            } else {
                break;
            }
        }

        char part_of_path[] = "dictionary//";
        char* file_name = strcat(dir_name[theme - 1], ".txt");
        char* path_name = strcat(part_of_path, file_name);

        FILE* fp = fopen(path_name, "r");
        if (fp == NULL) {
            printf("Cannot open file.\n");
            return CANTOPENFILE;
        }

        int value_words = 200;
        char** words = (char**)malloc(value_words * sizeof(char*));
        char tmp[255];
        int count_word = 0;

        while (fgets(tmp, 255, fp)) {
            if (count_word == value_words) {
                int check_mem = mem_expansion(&value_words, words);
                if (check_mem == -1) {
                    return CANTREALLOCMEM;
                }
            }

            words[count_word] = (char*)malloc(strlen(tmp) + 1);
            strcpy(words[count_word], tmp);
            count_word++;
        }
        value_words = count_word;

        int check_trim = trim_memory(words, &value_words, count_word);
        if (check_trim == CANTTRUNCMEM) {
            printf("Memory is not truncated\n");
            return CANTTRUNCMEM;
        }
        fclose(fp);

        int word_number = get_rand(0, value_words - 1);
        size_t length = strlen(words[word_number]);

        char guessed_word[length];
        char hidden_word[length];
        char underline[] = "_";

        fill_arr(guessed_word, length, words[word_number]);
        fill_arr(hidden_word, length - 1, underline);

        int result = play_game(guessed_word, hidden_word, length);
        if (result == WIN) {
            printf("\nYou win!\n");
        } else {
            printf("\nYou lose!\n");
        }

        exit_condition = 0;

        free_mem(dir_name, value_dic, words, value_words);
    }
    return 0;
}
