#include "hangman.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int exit_condition = 1;

    while (exit_condition) {
        DIR* dir;
        struct dirent* entry;

        dir = opendir("dictionary");
        if (!dir) {
            printf("Can not read directory.\n");
            return -1;
        }

        int value_dic = 200;
        char** dir_name = (char**)malloc(value_dic * sizeof(char*));

        int count_dic = 0;
        while ((entry = readdir(dir)) != NULL) {
            if (count_dic == value_dic) {
                value_dic *= 2;
                char** h = realloc(dir_name, value_dic * sizeof(char*));
                if (h == NULL) {
                    return -1;
                }
                dir_name = h;
            }
            if (strcmp(entry->d_name, ".") == 0
                || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            char temp[255];
            strcpy(temp, entry->d_name);
            cut_ext(temp);
            dir_name[count_dic] = (char*)malloc(strlen(temp) + 1);
            strcpy(dir_name[count_dic], temp);
            count_dic++;
        }

        closedir(dir);
        value_dic = count_dic;

        int check_trim;
        check_trim = memory_trim(dir_name, &value_dic, count_dic);
        if (check_trim == -1) {
            printf("Memory is not truncated\n");
            return -1;
        }

        system("clear");
        theme_menu(dir_name, value_dic);
        printf("Please, choose theme for your game.\n");

        char choice[255];
        int a = 0;

        while (fgets(choice, 255, stdin)) { // можно проверять на правильность
            if (check_digit(choice, strlen(choice)) == -1) {
                printf("It isn't correct punct of menu. Try again.\n");
                continue;
            }
            a = atoi(choice);
            if (a > value_dic) {
                printf("It isn't correct punct of menu. Try again.\n");
            } else {
                break;
            }
        }

        char part_of_path[] = "dictionary//";
        char* file_name = strcat(dir_name[a - 1], ".txt");
        char* path_name = strcat(part_of_path, file_name);

        FILE* fp = fopen(path_name, "r");
        if (fp == NULL) {
            printf("Cannot open file.\n");
            return -1;
        }

        int value_words = 200;
        char** words = (char**)malloc(value_words * sizeof(char*));
        char tmp[255];
        int count_word = 0;

        while (fgets(tmp, 255, fp)) {
            if (count_word == value_words) {
                value_words *= 2;
                char** h = realloc(words, value_words * sizeof(char*));
                if (h == NULL) {
                    return -1;
                }
                words = h;
            }
            words[count_word] = (char*)malloc(strlen(tmp) + 1);
            strcpy(words[count_word], tmp);
            count_word++;
        }
        value_words = count_word;

        check_trim = memory_trim(words, &value_words, count_dic);
        if (check_trim == -1) {
            printf("Memory is not truncated\n");
            return -1;
        }
        fclose(fp);

        printf("\n%s\n", words[0]);
        exit_condition = 0;
        free_mem(dir_name, value_dic, words, value_words);
    }
    return 0;
}
