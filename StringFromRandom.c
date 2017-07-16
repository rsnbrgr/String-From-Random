/*
         1         2         3         4         5         6         7         8
12345678901234567890123456789012345678901234567890123456789012345678901234567890

CITATION: based on the work of Dr. Markku-Juhani O. Saarinen <mjos@iki.fi> and
his proof-of-concept C program published 5 Apr 17.

   USE: StringFromRandom  <SomeString  >SourceCode

GitHub repository:
   https://github.com/rsnbrgr/String-From-Random

This proof-of-concept reads a string from stdin up to 4095 characters and writes
to stdout the source code for a C program that will generate said string using
only calls to the stdlib.h random() function.

THE IMPORTANT CONCEPT: This program merely proves Dr. Saarinen's algorithm in a
different fashion.  It makes absolutely NO calls to random() -- rather, it uses
Dr. Saarinen's "magic value" to write a C program that itself ONLY makes calls
to random().  This proves random(3) is NOT non-linear, and IS predictable. As a
sidenote, I know Dr. Saarinen's algorithm works: I compared 3.653 trillion
consecutive iterations over a weekend just to see if it might fail.

REQUIREMENTS: a C compiler must include the POSIX non-ISO "random()" function in
the <stdlib.h> header.  Use TestForPosixRandom.c code at the GitHub repository
(see above) to test your compiler.  See these websites for more details:
   http://man7.org/linux/man-pages/man3/random.3.html
   http://www.gnu.org/software/libc/manual/html_node/BSD-Random.html
   https://en.wikibooks.org/wiki/C_Programming/stdlib.h
Some (but not all) GCC implementations carry it, e.g. GCC 6.3 as installed on
the http://ideone.com compiler website.

20170715 v1.03 by Rob Rosenberger <us@kumite.com>
   Removed unneeded "TempChar" variable from Construct1Char().  Used FOURSPACES
   in WriteIndents() (duh!).  Minor tweaks to comments.
20170714 v1.02 by Rob Rosenberger <us@kumite.com>
   Commit to GitHub https://github.com/rsnbrgr/String-From-Random.  Added a
   printf() to include this info in the output stream.
20170707 v1.01 by Rob Rosenberger <us@kumite.com>
   A minor code tweak.  Commit to GitHub.
20170706 v1.00 by Rob Rosenberger <us@kumite.com>
   Released to the PUBLIC DOMAIN with all due credit to Dr. Saarinen's work.
   I wanted to submit this to the IOCCC but, as of this date, the contest is
   still on hold.  Ah, well...

FYI: Rosenberger uses the "Whitesmiths" coding indent style and "PascalCase"
identifier naming style.  He doesn't always use braces for singular statements.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXINPUT 4096
#define FOURSPACES "    "
#define BLANKLINE "\n"


/* Forward declarations, aka prototypes. */
int EmulateRandomBit(void);
int WriteLn(int HowManyNewlines);
int WriteOpenCloseComments(int OpenBraces);
int WriteIndents(int Levels);
int Construct1Char(char c);
int WriteSourceCodeTemplate(int StartEnd);


/* Variables with file scope. */
char UserInput[MAXINPUT] = {0};   // Zeroizes IAW ISO 9899:C11 para 6.7.9.21
unsigned long long int RandomSlide = 0;
unsigned long long int Saarinen   = 0x29D3881D58517D9D;  // must be a variable!


int main(void)
    {
    /* Get a string from the user. */
    WriteOpenCloseComments(1);
    printf("This program writes obfuscated C code that, when compiled,\n");
    printf("spits out whatever you enter here via stdin:\n");
    fgets(&UserInput[0], sizeof(UserInput), stdin);
    WriteOpenCloseComments(0);


    /* Show the user what they entered. */
    WriteOpenCloseComments(1);
    printf("This C source code spits out the following string using only\n");
    printf("calls to the predictable (!) stdlib.h random() function:\n\"%s\"\n",
           UserInput);
    printf("See this GitHub repository for the program that wrote this code:\n");
    printf("   https://github.com/rsnbrgr/String-From-Random\n");
    WriteOpenCloseComments(0);

    /* Write source code that writes each character in UserInput. */
    WriteSourceCodeTemplate(1);
    for (int UserInputIndex = 0;
         UserInputIndex < strlen(UserInput);
         UserInputIndex++)
        if (UserInput[UserInputIndex])        // if it's not \0
            {
            Construct1Char(UserInput[UserInputIndex]);
            WriteLn(3);
            }

    /* Wrap up. */
    WriteSourceCodeTemplate(0);
    return 0;
    }



/*
 ** Function definitions start here
 ** Function definitions start here
 ** Function definitions start here
 ** Function definitions start here
 ** Function definitions start here
*/

int EmulateRandomBit(void)
    /*
     ** Returns 0 or 1 exactly as if you called "random() % 2".
     ** Again, all credit where due to Dr. Markku-Juhani O. Saarinen!
     ** NOTE: our file-scope variable "Saarinen" CHANGES with each call
     ** to this function.
    */
    {
    Saarinen = (Saarinen << 2) 
                | (((Saarinen >> 60) + (Saarinen >> 4)) & 3);

    return (int) ((Saarinen >> 1) & 1);
    }


int WriteLn(int HowManyNewlines)
    /*
     ** Writes newline escape sequence.  Returns the total printf() value.
     **
     ** Q: "Why not just do it inline, Rob?"
     ** I'm just a Pascal guru who prefers "WriteLn".  If you've got a problem
     ** with it, then use GCC optimization to unfold the loop.
     ** (On a serious note: I include this function in my template for C.  If
     ** I forget to use it in a program, then it means I should re-read Martin
     ** Fowler's book on "Refactoring.")
    */
    {
    int CharsWritten = 0;

    while (HowManyNewlines > 0)
        {
        CharsWritten += printf(BLANKLINE);
        HowManyNewlines--;
        }

    return CharsWritten;
    }


int WriteOpenCloseComments(int OpenComments)
    /* Writes opening or closing comments.  Returns the total printf() value. */
    {
    if (OpenComments)
        return WriteLn(1) + printf("/*") + WriteLn(1);
     else
        return WriteLn(1) + printf("*/") + WriteLn(1);
    }


int WriteIndents(int Levels)
    /* Writes FOURSPACES per level.  Returns the total printf() value. */
    {
    int CharsWritten = 0;
    
    for ( ; Levels > 0; Levels--)
        CharsWritten += printf(FOURSPACES);

    return CharsWritten;    
    }


int Construct1Char(char c)
    /* Constructs and prints a char "c". Returns the total printf() value. */
    {
    int CharsWritten = 0;
    
    CharsWritten += WriteIndents(1) + printf("using=0;")   + WriteLn(1);
    CharsWritten += WriteIndents(1) + printf("bitchar=0;") + WriteLn(1);
    for (int Xbit = 8; Xbit > 0; Xbit--)
        {
        /* Increment RandomSlide just to add obfuscation. */
        //RandomSlide += c;

        /* Here, we advance "random()" by RandomSlide calls. */
        for (int x = 0; x < RandomSlide; x++)
            EmulateRandomBit();       // ignore the return value

        /* Now we need to find a "random" bit: either 1 or 0. */
        do RandomSlide++;
         while ((c & 128) != (EmulateRandomBit() * 128));
        
        WriteIndents(1);
        /* RandomSlide == how many calls to random() gives our bit! */
        /* I use these C++/C# keywords as variable names out of pure spite. */
        CharsWritten += printf("for (new=0; new<%d; new++) using = (int)random() & 1;",
                               RandomSlide);
        CharsWritten += printf(" bitchar += using;");
        if (Xbit != 1)           // we don't want to bitshift the last time
            CharsWritten += printf(" bitchar <<= 1;");
        CharsWritten += WriteLn(1);

        /* Prep "c" for the next loop iteration. */
        c <<= 1;
        }
    CharsWritten += WriteIndents(1);
    CharsWritten += printf("printf(\"%%c\",bitchar);") + WriteLn(1);
    return CharsWritten;
    }


int WriteSourceCodeTemplate(int StartEnd)
    /* Writes a C source template.  Returns the total printf() value. */
    {
    int CharsWritten = 0;

    if (StartEnd)
        {
        CharsWritten += printf("#include <stdio.h>") + WriteLn(1);
        CharsWritten += printf("#include <stdlib.h>") + WriteLn(1);
        CharsWritten += printf("int main(void)") + WriteLn(1);
        CharsWritten += WriteIndents(1) + printf("{") + WriteLn(1);
        /* I use these C++/C# keywords as variable names out of pure spite. */
        CharsWritten += WriteIndents(1) + printf("int  bitchar = 0;") + WriteLn(1); // char assembler 
        CharsWritten += WriteIndents(1) + printf("char using   = 0;") + WriteLn(1); // random() loops
        CharsWritten += WriteIndents(1) + printf("int  new     = 0;") + WriteLn(2); // controls for()
        }
     else
        {
        CharsWritten += WriteIndents(1) + printf("return 0;"); + WriteLn(1);
        CharsWritten += WriteIndents(1) + printf("}")          + WriteLn(1);
        }

    return CharsWritten;
    }
