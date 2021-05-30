#include "libhangman/hangman.h"
#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main()
{
    int exit_condition = PLAY;
    int num_error;
    int error = WITHOUTERROR;
    srand(time(NULL));

    while (exit_condition) {
        int value_dic;
        char** dir_name = open_dir(&value_dic, &num_error, "../dictionary");
        if ((error = check_error(num_error)) != WITHOUTERROR) {
            return error;
        }

        system("clear");
        print_theme_menu(dir_name, value_dic);
        printf("Please, choose theme for your game:\n");
        int theme;
        while ((theme = choose_theme(value_dic)) == INCORTHEME) {
            system("clear");
            print_theme_menu(dir_name, value_dic);
            printf("It isn't correct punct of menu. Try again.\n");
            continue;
        }

        char* path = concat_path_name(dir_name[theme - 1], &num_error);
        if ((error = check_error(num_error)) != WITHOUTERROR) {
            return error;
        }

        int value_words;
        char** words = get_words_array(&value_words, path, &num_error);
        if ((error = check_error(num_error)) != WITHOUTERROR) {
            return error;
        }

        int word_number = get_rand(0, value_words - 1);
        int length = strlen(words[word_number]) - 1;

        char guessed_word[length];
        char hidden_word[length];
        char underline[] = "_";

        fill_arr(guessed_word, length, words[word_number]);
        fill_arr(hidden_word, length, underline);

        int result = play_game(guessed_word, hidden_word, length);
        if (result == WIN) {
            printf("\nYou win!\n");
        } else {
            printf("\nYou lose!\n");
        }

        free_mem(dir_name, value_dic, words, value_words);

        printf("\nDo you want to play again? Y/N\n");
        while ((exit_condition = play_again()) == INCORRECT) {
            system("clear");
            printf("\nDo you want to play again? Y/N\n");
            printf("\nIncorrect answer, please try again.\n");
            continue;
        }
        if (exit_condition == EXIT) {
            printf("\nThank you. Good bye!\n");
        }
    }
    return 0;
}
