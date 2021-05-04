#include "hangman.h"
#include <string.h>

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
