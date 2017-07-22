/*
This PUBLIC DOMAIN program tests a C compiler for a predictable POSIX-compliant
non-ISO random() function.  See github.com/rsnbrgr/String-From-Random for full
details.
*/

#include <stdio.h>
#include <stdlib.h>

#define POSIXRANDOMFIRSTVALUE 1804289383

int main(void)
    {
    if ((int)random() == POSIXRANDOMFIRSTVALUE)
        printf("HURRAY!  Your C compiler appears to use the predictable POSIX-compliant non-ISO random() function!\n");
     else
        printf("UH-OH!  Your C compiler appears to use a different PRNG for its random() function.  Sorry.\n");

    printf("See https://github.com/rsnbrgr/String-From-Random for full details.\n");
    return 0;
    }
