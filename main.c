#include "hangman.h"
#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_PATH 268

int main()
{
    int exit_condition = 1;
    srand(time(NULL));

    while (exit_condition) {
        int value_dic;
        char** dir_name = open_dir(&value_dic);
        if (dir_name == CANTOPENDIRECT) {
            printf("Can not read directory.\n");
            return CANTOPENDIR;
        } else if (dir_name == CANTMALLOCMEMORY) {
            printf("Memory is not malloced\n");
            return CANTMALLOCMEM;
        } else if (dir_name == CANTREALLOCMEMORY) {
            printf("Memory is not reallocated\n");
            return CANTREALLOCMEM;
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

        char path[MAX_PATH];
        concat_path_name(path, dir_name[theme - 1]);

        FILE* fp = fopen(path, "r");
        if (fp == NULL) {
            printf("Cannot open file.\n");
            return CANTOPENFILE;
        }

        int value_words = 200;
        char** words = (char**)malloc(value_words * sizeof(char*));
        if (words == NULL) {
            return CANTMALLOCMEM;
        }
        char tmp[255];
        int count_word = 0;

        while (fgets(tmp, 255, fp)) {
            if (count_word == value_words) {
                value_words *= 2;
                char** h = mem_resize(value_words, words);
                if (h == NULL) {
                    return CANTREALLOCMEM;
                }
                words = h;
            }

            words[count_word] = (char*)malloc(strlen(tmp) + 1);
            if (words[count_word] == NULL) {
                free(words);
                return CANTMALLOCMEM;
            }
            strcpy(words[count_word], tmp);
            count_word++;
        }

        value_words = count_word;
        char** h = mem_resize(value_words, words);
        if (h == CANTREALLOCMEMORY) {
            printf("Memory is not truncated\n");
            return CANTREALLOCMEM;
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

        free_mem(dir_name, value_dic, words, value_words);

        exit_condition = play_again_main();
    }
    return 0;
}
