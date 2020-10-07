//201935001 Kang Geonyoung
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	char buf[10000];

	int file_desc_son;
	int file_desc_dau;

	pid_t pid1, pid2;

	char* fifo_son = "/tmp/hw3_fifo_son";
	char* fifo_dau = "/tmp/hw3_fifo_dau";

	pid1 = fork();


	if (pid1 < 0)
	{
		printf("Fork failed!");
		return 1;
	}
	else if (pid1 == 0)
	{
		printf("process son create.\n");

		file_desc_son = open(fifo_son, O_RDONLY);
		while (read(file_desc_son, buf, sizeof(buf)) > 0)
		{
			if (buf[0] == '0')
			{
				close(file_desc_son);
			}
			else
			{
				printf("Son receives : %s", buf);
				printf("\n");
			}
		}
	}
	else
	{
		pid2 = fork();
		if (pid2 < 0)
		{
			printf("Fork failed!");
			return 1;
		}
		else if (pid2 == 0)
		{
			printf("process daughter create.\n");

			file_desc_dau = open(fifo_dau, O_RDONLY);
			while (read(file_desc_dau, buf, sizeof(buf)) > 0)
			{
				if (buf[0] == '0')
				{
					close(file_desc_dau);
				}
				else
				{
					printf("Daughter receives : %s", buf);
					printf("\n");
				}
			}
		}
		else
		{
			wait(NULL);
		}

		wait(NULL);
	}
	return 0;
}