#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid1, tid2;
int call_agmal;
int call_iraj;
int agmal_status=0;
int iraj_status=100;
int count_agmal=0;
int count_iraj=0;
int flag=0;

void *cek_agmal(void *arg)
{
	while(1)
	{
		if(call_agmal==0)
		{
			sleep(10);
			call_agmal=1;
			count_agmal=0;
		}
	}
}

void *cek_iraj(void *arg)
{
	while(1)
	{
		if(call_iraj==0)
		{
			sleep(10);
			call_iraj=1;
			count_iraj=0;
		}
	}
}

void *agmal_tambah(void *arg)
{
	agmal_status+=15;
	if(agmal_status>=100)
	{
		printf("Agmal Terbangun,mereka bangun pagi dan berolahraga\n");
		flag=1;
	}
}
void *iraj_tambah(void *arg)
{
	iraj_status-=20;
	if(iraj_status<=0)
	{
		printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
		flag=1;
	}
}
int main(void)
{
	char pesan[50];
	int pesan_agmal;
	int pesan_iraj;
	char temp;
	call_agmal=1;
	call_iraj=1;
	pthread_t tid[4];
	pthread_create(&(tid[2]), NULL, cek_agmal, NULL);
	pthread_create(&(tid[3]), NULL, cek_iraj, NULL);

	while(1)
	{
		if(flag==1)break;
		printf("Agmal WakeUp_Status = %d\n", agmal_status);
		printf("Iraj Spirit_Status = %d\n", iraj_status);
		scanf("%[^\n]s", pesan);
		scanf("%c", &temp);
		pesan_agmal=strcmp(pesan, "Agmal Ayo Bangun");
		pesan_iraj=strcmp(pesan, "Iraj Ayo Tidur");
		if(pesan_agmal==0)
		{
			if(call_agmal==1)
			{
				pthread_create(&(tid[0]), NULL, agmal_tambah, NULL);
				count_agmal++;
				pthread_join( tid[0], NULL);
			}
			else
			{
				printf("Agmal Ayo Bangun disabled 10 s\n");
			}
			if(count_agmal==3)
			{
				call_agmal=0;
			}
		}
		if(pesan_iraj==0)
		{
			if(call_iraj==1)
			{
				pthread_create(&(tid[1]), NULL, iraj_tambah, NULL);
				count_iraj++;
				pthread_join( tid[1], NULL);
			}
			else
			{
				printf("Fitur Iraj Ayo Tidur disabled 10 s\n");
			}
			if(count_iraj==3)
			{
				call_iraj=0;
			}
		}
		pesan[0]='\0';
	}
	return 0;
}
