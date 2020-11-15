//201935001 Kang Geonyoung
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

void* cntPrime(void* var);

int count = 0;
int unit;

int main(int argc, char* argv[])
{
	clock_t begin_time = clock();

	pthread_t p_thread[10];
	int i, j;
	int num = atoi(argv[1]);
	int temp;
	int num_arr[10];

	temp = num / 10;
	unit = temp;
	for (j = 0; j < 10; j++)
	{
		num_arr[j] = temp;
		temp += unit;
	}

	for (i = 0; i < 10; i++)
	{
		pthread_create(&p_thread[i], NULL, cntPrime, &num_arr[i]);
		pthread_join(p_thread[i], NULL);
	}

	clock_t end_time = clock();

	double elapsed_time = (double)(end_time - begin_time) / CLOCKS_PER_SEC;

	printf("elapsed time : % f sec \n", elapsed_time);
	printf("The number of prime numbers between 1~%d is %d\n", num, count);

	return 0;
}

void* cntPrime(void* var)
{
	int num = *(int*)var;
	int add = 0;
	int cnt;
	int i, j;

	if (num > unit)
	{
		add += num - unit;
	}

	for (j = 1 + add; j <= num; j++)
	{
		cnt = 0;
		if (j >= 2)
		{
			for (i = 1; i * i < j; i++) {
				if (j % i == 0) cnt++;
			}
			if (i * i == j) cnt++;
			if (cnt == 1) count++;
		}
	}

}