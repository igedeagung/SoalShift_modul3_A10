#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

int mygetch(void)
{
	struct termios oldt,
	newt;
	int ch;
	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	return ch;
}


void main()
{
        key_t key = 1234;
        int *stok;
	char pilih;

        int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
        stok = shmat(shmid, NULL, 0);

        *stok = 10;
	while(1)
	{
		system("clear");
		printf("Shop\n");
		printf("Food stock : %d\n", *stok);
		printf("Choices\n");
		printf("1. Restock\n");
		printf("2. Exit\n");
		pilih=mygetch();
		if(pilih=='1')
		{
			*stok+=50;
		}
		if(pilih=='2')
		{
			break;
		}
	}
        shmdt(stok);
        shmctl(shmid, IPC_RMID, NULL);
}
