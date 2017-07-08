# String-From-Random
CITATION: based on the work of Dr. Markku-Juhani O. Saarinen <mjos@iki.fi> and his proof-of-concept C program published 5 Apr 17.

   USE: StringFromRandom  \<SomeString  \>SourceCode

This PUBLIC DOMAIN proof-of-concept reads a string from stdin up to 4095 characters and writes to stdout the source code for a C program that will generate said string using only calls to the \<stdlib.h\> random() function.

THE IMPORTANT CONCEPT: This program merely proves Dr. Saarinen's algorithm in a different fashion.  It makes absolutely NO calls to random() -- rather, it uses Dr. Saarinen's "magic value" to write a C program that itself ONLY makes calls to random().  Yes yes yes, I know Dr. Saarinen's algorithm works: I compared 3.653 trillion iterations over a weekend just to see if it might fail.

REQUIREMENTS: a C compiler must include the POSIX non-ISO "random()" function in the <stdlib.h> header.  See these websites for details:

http://man7.org/linux/man-pages/man3/random.3.html

http://www.gnu.org/software/libc/manual/html_node/BSD-Random.html

https://en.wikibooks.org/wiki/C_Programming/stdlib.h

Some GCC implementations carry it, e.g. GCC as installed on the http://ideone.com compiler website.  You can see this code in action at http://ideone.com/NJO94H and you can see its output in action at http://ideone.com/ddgP3q.

ODD BEHAVIOR NOTICED ON THESE PLATFORMS: OpenBSD 5.9 with GCC 4.2.1 appears to use a different PRNG algorithm; and it throws a "deterministic values" warning when you call random().

FYI: Rosenberger uses the "Whitesmiths" coding indent style and "PascalCase" identifier naming style.  He doesn't always use braces for singular statements.

Q: "Why didn't you use getchar() in the main() function?"

A: I wanted to include the string it will print, in a comment at the top of the generated C source code.  Yes, I might fork the code someday to allow unlimited binary input.  But in the meantime, you can fork it yourself.
