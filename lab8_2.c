#include <pthread.h>
#include <stdio.h>
#include<semaphore.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

#define MAX 20
#define BUFLEN 24
#define MAX_COUNT 15
#define NUMTHREAD 3
#define LIMIT 50

void * depositor(int *id);
void * withdrawer(int *id);
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t belowLimit = PTHREAD_COND_INITIALIZER;
int thread_id[NUMTHREAD] = {0,1};
int i = 0, j = 0;
double balance = 0;
void main()
{
	int i;
	pthread_t thread[NUMTHREAD];
	pthread_create(&thread[1], NULL, (void *)withdrawer, &thread_id[1]);
	pthread_create(&thread[0], NULL, (void *)depositor, &thread_id[0]);
	for(i=0; i< NUMTHREAD ; i++)
		pthread_join(thread[i], NULL);
}

void * depositor(int *id)
{
	double deposit;
	while(j < MAX)
	{
		deposit = (double)(rand() % 100);
		balance += deposit;
		printf(" Deposited :%10.2f balance is %10.2f: by %d\n", deposit, balance, *id);
		fflush(stdout);
		j++;
		if (rand()%100 >= 50)
			sleep(rand()%2);
	}
}

void * withdrawer(int *id)
{
	double debt;
	while (i < MAX)
	{
		debt = (double)(rand() % 60);
		if (balance - debt < LIMIT)
			printf("Sorry can't withdraw!!!\n");
		else
		{
			balance -= debt;
			printf("%d Withdraw %10.2f : by :%d: balance %10.2f\n",i, debt, *id, balance);
		}
		fflush(stdout);
		i++;
		if (rand()%100 >= 50)
		sleep(rand()%2);
	}
}	
