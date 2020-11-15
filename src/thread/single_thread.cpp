//201935001 Kang Geonyoung
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

int main(int argc, char* argv[])
{
    clock_t begin_time = clock();

    int cntPrime(int num);
    int count = 0;
    int num = atoi(argv[1]);
    int i;

    for (i = 1; i <= num; i++)
    {
        if (cntPrime(i))
        {
            count++;
        }
    }

    clock_t end_time = clock();

    double elapsed_time = (double)(end_time - begin_time) / CLOCKS_PER_SEC;

    printf("elapsed time : % f sec \n", elapsed_time);
    printf("The number of prime numbers between 1~%d is %d\n", num, count);

    return 0;
}

int cntPrime(int num)
{
    int cnt = 0;
    int i;
    if (num < 2) return 0;

    for (i = 1; i * i < num; i++) {
        if (num % i == 0) cnt++;
    }
    if (i * i == num) cnt++;
    if (cnt == 1) return 1;
    else return 0;
}
