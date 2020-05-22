/*
 ============================================================================
 Name        : Task_1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char**argv)
{
    int N,K;
    N = atoi(argv[1]);
    K = atoi(argv[2]);
    float J;
    J = (float) N / (float)(K+1);
    printf("%d\n",(int) ceil(J));
    return 0;
}
