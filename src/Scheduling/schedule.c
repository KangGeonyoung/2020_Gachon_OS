//201935001 Kang Geonyoung
#include <stdio.h>
#include <stdlib.h>

struct PCB {
	int pid;
	int begin_tick;
	int finish_tick;
	int burst_tick;
	int state;
	int first_tick;
};
struct PCB* list[10];
int choice;
int small = 0;
int order = 0;
int j;

void read_proc_list(const char* file_name)
{
	int i;
	int pid, begin, burst;
	FILE* fp;

	fp = fopen(file_name, "r");
	fscanf(fp, "%d", &j);

	for (i = 0; i < j; i++)
	{
		fscanf(fp, "%d %d %d", &pid, &begin, &burst);
		list[i] = malloc(sizeof(struct PCB));
		list[i]->pid = pid;
		list[i]->begin_tick = begin;
		list[i]->burst_tick = burst;
		list[i]->finish_tick = 0;
		list[i]->state = 0;
	}
	fclose(fp);
}

void set_schedule(int method)
{
	choice = method;
}

int do_schedule(int tick)
{
	if (choice == 1)  //FCFS
	{
		int statement = 0;

		for (int i = 0; i < j; i++)  //check whether all process is end. 
		{
			if (list[i]->state == 1)
			{
				statement = 1;
			}
			else
			{
				statement = 0;
				break;
			}
		}
		if (statement == 1)
		{
			return -1;
		}

		if (list[order]->begin_tick <= tick && list[order]->state != 1)
		{
			list[order]->finish_tick += 1;
		}
		if (list[order]->finish_tick == 1)
		{
			list[order]->first_tick = tick;
		}
		if (list[order]->finish_tick == list[order]->burst_tick)
		{
			list[order]->state = 1;
			list[order]->finish_tick = tick + 1;
			order++;
			return list[order - 1]->pid;
		}
		else
		{
			return list[order]->pid;
		}
		return 0;
	}
	else if (choice == 2)  //SJF
	{
		int statement = 0;

		for (int i = 0; i < j; i++)  //check whether all process is end. 
		{
			if (list[i]->state == 1)
			{
				statement = 1;
			}
			else
			{
				statement = 0;
				break;
			}
		}
		if (statement == 1)
		{
			return -1;
		}

		order = small;
		if (list[order]->begin_tick <= tick && list[order]->state != 1)
		{
			list[order]->finish_tick += 1;
		}
		if (list[order]->finish_tick == 1)
		{
			list[order]->first_tick = tick;
		}
		if (list[order]->finish_tick == list[order]->burst_tick)
		{
			list[order]->state = 1;
			list[order]->finish_tick = tick + 1;
			small = list[0]->pid - 1;
			for (int i = 1; i < j; i++)
			{
				if (list[i]->state == 0)
				{
					if (list[small]->burst_tick > list[i]->burst_tick)
					{
						small = i;
					}
				}

			}
			return list[order]->pid;
		}
		else
		{
			return list[order]->pid;
		}
		return 0;
	}
	else if (choice == 3)  //SRTF
	{
		int statement = 0;

		for (int i = 0; i < j; i++)  //check whether all process is end. 
		{
			if (list[i]->state == 1)
			{
				statement = 1;
			}
			else
			{
				statement = 0;
				break;
			}
		}
		if (statement == 1)
		{
			return -1;
		}

		order = small;
		if (order + 1 >= j)
		{
			order--;
		}
		if (list[order + 1]->begin_tick > tick && list[order]->state != 1)
		{
			list[order]->finish_tick += 1;
			if (list[order]->finish_tick == 1)
			{
				list[order]->first_tick = tick;
			}
			if (list[order]->finish_tick == list[order]->burst_tick)
			{
				list[order]->state = 1;
				list[order]->finish_tick = tick + 1;
			}
			return list[order]->pid;
		}
		else if (list[order + 1]->begin_tick <= tick)
		{
			small = list[0]->pid - 1;
			for (int i = 0; i < j; i++)  //find small value index
			{
				if (list[i]->begin_tick <= tick)
				{
					if (list[i]->state == 0)
					{
						if (list[small]->state == 1)
						{
							small = i;
						}
						if (list[small]->burst_tick - list[small]->finish_tick > list[i]->burst_tick - list[i]->finish_tick)
						{
							small = i;
						}
					}
				}
			}
			if (list[small]->begin_tick <= tick && list[small]->state != 1)
			{
				list[small]->finish_tick += 1;
			}
			if (list[small]->finish_tick == 1)
			{
				list[small]->first_tick = tick;
			}
			if (list[small]->finish_tick == list[small]->burst_tick && list[small]->state != 1)
			{
				list[small]->state = 1;
				list[small]->finish_tick = tick + 1;
			}
			return list[small]->pid;
		}
		return 0;
	}
}

void print_performance()
{
	int turnaround = 0, waiting = 0, response = 0;

	printf("===============================================================================\n");
	printf("  PID    begin    finish    Turn around time    Wating time    Response time\n");
	printf("===============================================================================\n");
	for (int i = 0; i < j; i++)
	{
		printf("%4d    %4d     %4d           %4d               %4d           %4d",
			list[i]->pid, list[i]->begin_tick, list[i]->finish_tick, list[i]->finish_tick - list[i]->begin_tick,
			list[i]->finish_tick - list[i]->begin_tick - list[i]->burst_tick, list[i]->first_tick - list[i]->begin_tick);
		printf("\n");
		turnaround += list[i]->finish_tick - list[i]->begin_tick;
		waiting += list[i]->finish_tick - list[i]->begin_tick - list[i]->burst_tick;
		response += list[i]->first_tick - list[i]->begin_tick;
	}
	printf("-------------------------------------------------------------------------------\n");
	printf("  average:                        %.2f              %.2f            %.2f\n", (float)turnaround / j, (float)waiting / j, (float)response / j);
	printf("===============================================================================\n");
}