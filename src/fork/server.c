#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_BUF	1024

int main(int argc, char *argv[])
{
	// init global variable
	char ch, tch;
	int terminate = 0;

	// init named pipe
	char message[MAX_BUF];
	int file_desc_son;
	int file_desc_dau;
	int cnt;

	// open named fifo
	char *fifo_son = "/tmp/hw3_fifo_son";
	char *fifo_dau = "/tmp/hw3_fifo_dau";
	mkfifo(fifo_son, 0666);
	mkfifo(fifo_dau, 0666);
	file_desc_son = open(fifo_son, O_WRONLY);
	file_desc_dau = open(fifo_dau, O_WRONLY);

	while(!terminate)
	{
		printf("Who do you want to send a message? (1:son/2:daughter/0:end)");
		ch = getchar();

		if (ch == '0') {
			terminate = 1;
			write(file_desc_son, "0", sizeof(MAX_BUF));
			write(file_desc_dau, "0", sizeof(MAX_BUF));
			continue;
		}
		else if (ch == '1' || ch == '2') {
			scanf("%c", &tch);
			printf("What is a message?\n");
			scanf("%[^\n]", message);

			// send message
			if (ch == '1') {
				write(file_desc_son, message, sizeof(message));
			}
			else {
				write(file_desc_dau, message, sizeof(message));
			}

			// flush remaining new line command
			scanf("%c", &ch);
		}
		else if (ch == '\n') continue;
	}

	// unlink fifo
	unlink(fifo_son);
	unlink(fifo_dau);

	return 1;
}
