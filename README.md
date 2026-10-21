# OS_T1_V12_Qurbonmurodov# OS_T1_V12_Qurbonmurodov

Operatsion tizimlar, 1-topshiriq, variant 12.

## A qism (Hello World)
gcc -E hello.c -o hello.i
gcc -S hello.i -o hello.s
gcc -c hello.s -o hello.o
gcc hello.o -o hello
./hello

## B qism (talabalar baholari statistikasi)
gcc -Wall -Wextra main.c -o main
./main