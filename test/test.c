#include "ctest.h"
#include "libhangman/hangman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CTEST(Check_theme, Correct)
{
    char* choice = "3";
    int value_dic = 4;
    int theme = check_theme(choice, value_dic);
    int exp = atoi(choice);
    ASSERT_EQUAL(exp, theme);
}

CTEST(Check_theme, Incorrect_sign)
{
    char* choice = "k";
    int value_dic = 4;
    int theme = check_theme(choice, value_dic);
    int exp = INCORTHEME;
    ASSERT_EQUAL(exp, theme);
}

CTEST(Check_theme, Negative_theme)
{
    char* choice = "-1";
    int value_dic = 4;
    int theme = check_theme(choice, value_dic);
    int exp = INCORTHEME;
    ASSERT_EQUAL(exp, theme);
}

CTEST(Check_theme, Non_existent_theme)
{
    char* choice = "5";
    int value_dic = 4;
    int theme = check_theme(choice, value_dic);
    int exp = INCORTHEME;
    ASSERT_EQUAL(exp, theme);
}

CTEST(Concat_path_name, Correct_path)
{
    int num_error;
    char* dir_name = "animals";
    char* path = concat_path_name(dir_name, &num_error);
    char* exp = "../dictionary/animals.txt";
    ASSERT_STR(exp, path);
    ASSERT_EQUAL(WITHOUTERROR, num_error);
}

CTEST(Check_letter, Is_letter)
{
    char* choice = "i";
    int real = check_letter(choice);
    int exp = CORRECTLETTER;
    ASSERT_EQUAL(exp, real);
}

CTEST(Check_letter, Is_not_letter1)
{
    char* choice = "5";
    int real = check_letter(choice);
    int exp = INCORRECTLETTER;
    ASSERT_EQUAL(exp, real);
}

CTEST(Check_letter, Is_not_letter2)
{
    char* choice = ";";
    int real = check_letter(choice);
    int exp = INCORRECTLETTER;
    ASSERT_EQUAL(exp, real);
}

CTEST(Check_usage, Used)
{
    char* used_ch = "abcd";
    char choice[1] = {'a'};
    int real = check_usage(used_ch, strlen(used_ch), choice[0]);
    int exp = USEDLETTER;
    ASSERT_EQUAL(exp, real);
}

CTEST(Check_usage, Unused)
{
    char* used_ch = "abcd";
    char choice[1] = {'i'};
    int real = check_usage(used_ch, strlen(used_ch), choice[0]);
    int exp = UNUSEDLETTER;
    ASSERT_EQUAL(exp, real);
}

CTEST(Check_match, Match)
{
    char* word = "panda";
    size_t length = strlen(word);
    int num_guess_ch = length - 1;
    char guessed_word[length];
    char hidden_word[length];
    char underline[] = "_";
    char letter[1] = {'p'};

    fill_arr(guessed_word, length, word);
    fill_arr(hidden_word, length - 1, underline);
    int no_match = check_match(
            guessed_word, hidden_word, length - 1, letter[0], &num_guess_ch);

    ASSERT_NOT_EQUAL(no_match, length - 1);
}

CTEST(Check_match, No_match)
{
    char* word = "panda";
    size_t length = strlen(word);
    int num_guess_ch = length - 1;
    char guessed_word[length];
    char hidden_word[length];
    char underline[] = "_";
    char letter[1] = {'c'};

    fill_arr(guessed_word, length, word);
    fill_arr(hidden_word, length - 1, underline);
    int no_match = check_match(
            guessed_word, hidden_word, length - 1, letter[0], &num_guess_ch);

    ASSERT_EQUAL(no_match, length - 1);
}

CTEST(Cut_ext, Cut_ext)
{
    char file_name[] = "trpo.txt";
    char exp[] = "trpo";
    cut_ext(file_name);
    ASSERT_STR(exp, file_name);
}

CTEST(Cut_name, Cut)
{
    char* d_name = "animals.txt";
    char exp[] = "animals";
    int count_dic = 0;
    char* dir_name[MAXLENGTH];
    int status = cut_name(d_name, dir_name, count_dic);
    int exp2 = WITHOUTERROR;
    ASSERT_EQUAL(exp2, status);
    ASSERT_STR(exp, dir_name[0]);
}
