/*
 ============================================================================
 Name        : Task_2.c
 Author      : Anton Kotsiubailo
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char**argv)
{
    int N,D,S;
    int i;
    N = atoi(argv[1]);
    D = atoi(argv[2]);

    S = 0;
    for(i=1;i<=N;i++)
      S += i;

      S *= D;
    printf("%d\n",S);
    return 0;
}
