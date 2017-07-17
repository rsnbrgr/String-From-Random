# String-From-Random
CITATION: based on the work of Dr. Markku-Juhani O. Saarinen <mjos@iki.fi> and his proof-of-concept C program published 5 Apr 17.

   USE: gcc TestForPosixRandom.c  &&  ./a.out
   
   USE: gcc StringFromRandom.c  &&  ./a.out  \<SomeString  \>SourceCode

This PUBLIC DOMAIN proof-of-concept reads a string from stdin up to 4095 characters and writes to stdout the source code for a C program that will generate said string using only calls to the \<stdlib.h\> random() function.

THE IMPORTANT CONCEPT: This program merely proves Dr. Saarinen's algorithm in a different fashion.  It makes absolutely NO calls to random() -- rather, it uses Dr. Saarinen's "magic value" to write a C program that itself ONLY makes calls to random().

THE PROBLEM: FreeBSD's delusional man page for random(3) describes it as "a non-linear additive feedback random number generator."  Dr. Saarinen's research proved it to be linear by definition.  It goes on to say "all the bits generated by random() are usable.  For example, 'random()&01' will produce a random binary value."  Dr. Saarinen's research proved this wrong, too.  This program uses Dr. Saarinen's research to predict random()'s output.  As a sidenote, I compared Dr. Saarinen's algorithm to random() in 3.653 trillion consecutive iterations over a weekend just to see if it might fail.

EXPLOITABLE USES: You might predict / hijack a TLS session if a programming team coded it to use random().  You can easily tweak this proof-of-concept to accept binary input (e.g. "netcat.exe") vice a string.  The resulting C source code will contain ONLY calls to random(); you then rebuild the binary in memory and set the EIP register to run it.

REQUIREMENTS: a C compiler must include the POSIX-compliant non-ISO "random()" function in the <stdlib.h> header.  See these websites for further details:

http://man7.org/linux/man-pages/man3/random.3.html

http://www.gnu.org/software/libc/manual/html_node/BSD-Random.html

https://en.wikibooks.org/wiki/C_Programming/stdlib.h

Many (not all) GCC implementations include the exploitable random(3).  Use the included "TestForPosixRandom.c" program to test your C compiler.

WORKS ON THESE PLATFORMS: Kali Linux 3.14-kali1-amd64.  NetWars Linux 3.2.0-58-generic.  CentOS 7 Linux 3.10.0-514.2.2.el7.x86_64.  You can compile & run this program's code online at http://ideone.com/NJO94H and see its output in action at http://ideone.com/ddgP3q. 

ODD BEHAVIOR NOTICED ON THESE PLATFORMS: OpenBSD 5.9 with GCC 4.2.1 appears to use a different PRNG; and it throws a "deterministic values" warning when you call random().  Windows MinGW-64 with GCC 5.3.0 doesn't include random() in <stdlib.h>.

FYI: Rosenberger uses the "Whitesmiths" coding indent style and "PascalCase" identifier naming style.  He doesn't always use braces for singular statements.

Q1: "Why didn't you use getchar() in the main() function?"  I wanted to include the string it will print, in a comment at the top of the generated C source code.  Yes, I might fork the code someday to allow unlimited binary input.  But in the meantime, you can fork it yourself.

Q2: "Why did you label '\n' as BLANKLINE?"  The string literally defines a blank line.

Q3: "Why do you use C++/C# keywords as variables?"  Honestly, it's just an inside joke for Anders Hejlsberg.  I mourn the halcyon days of object-oriented Pascal.

Q4: "Why don't you always use braces?"  It's an old Pascal discipline.
