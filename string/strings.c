#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strings.h"

void removeSymbol(char str[], char symbol)
{
        size_t i = 0;

        for (i = 0; i < strlen(str); i++){
                if (str[i] == symbol){
                        memmove(&str[i], &str[i + 1], strlen(str) - i);
                        i--;
                }
        }
}

void infoCat(char *dst, char *src)
{
        strcat(src, ".");

        strcat(dst, src);
}