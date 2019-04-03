#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>
#include <ncurses.h>
#include <termios.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int sehat=300;
int lapar=200;//berkurang 5 setiap 10 dtk
int bersih=100;//berkurang 10 setiap 30 dtk
int makan=10;
int standby=1;
int counter=0;
char nama[50];
void battle();
void shop();

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

void *laper(void *arg)
{
	while(1)
	{
		if(standby==1)
		{
			sleep(10);
			lapar-=5;
		}
	}
}

void *kotor(void *arg)
{
	while(1)
	{
		if(standby==1)
		{
			sleep(30);
			bersih-=10;
		}
	}
}

void *up_health(void *arg)
{
	while(1)
	{
		if(standby==1)
		{
			sleep(10);
			sehat+=5;
		}
	}
}

void *timer(void *arg)
{
	while(1)
	{
		if(standby==1)
		{
			if(counter >0)
			{
				sleep(1);
				counter--;
			}
		}
	}
}

void stand()
{
	char pilih;
	while(1)
	{
		if(lapar<=0 || bersih<=0)
		{
			printf("OH NO %s is DEAD !!!\n", nama);
			break;
		}
		printf("Standby Mode\n");
		printf("Health : %d\n", sehat);
		printf("Hunger : %d\n", lapar);
		printf("Hygiene : %d\n", bersih);
		printf("Food left : %d\n", makan);
		if(counter > 0)
		{
			printf("Bath will be ready in %ds\n", counter);
		}
		else
		{
			printf("Bath is ready\n");
		}
		printf("Choices\n");
		printf("1. Eat\n");
		printf("2. Bath\n");
		printf("3. Battle\n");
		printf("4. Shop\n");
		printf("5. Exit\n");

		pilih=mygetch();
		if(pilih=='1')
		{
			if(lapar<200)
			{
				if(makan>0)
				{
					system("clear");
					lapar+=15;
					makan-=1;
					printf("NOM NOM... %s EATS THE FOOD\n", nama);
					sleep(2);
					system("clear");
					if(lapar>200) lapar=200;
				}
			}
			else
			{
				system("clear");
				printf("%s TUMMY IS FULL \n", nama);
				sleep(2);
			}
		}
		if(pilih=='2')
		{
			if(bersih<100)
			{
				if(counter==0)
				{
					system("clear");
					printf("%s IS CLEAN NOW\n", nama);
					sleep(2);
					system("clear");
					bersih+=30;
					counter=20;
					if(bersih>100) bersih=100;
				}
				else
				{
					system("clear");
					printf("BATH IS NOT READY\n");
					sleep(2);
				}
			}
			else
			{
				system("clear");
				printf("%s IS CLEAN AND FRESH\n", nama);
				sleep(2);
			}
		}
		if(pilih=='3')
		{
			standby=0;
			system("clear");
			battle();
		}
		if(pilih=='4')
		{
			system("clear");
			shop();
		}
		if(pilih=='5')
		{
			break;
		}
		system("clear");
	}
}

void battle()
{
	char pilih_b;
	int enemy_health=100;
	while(1)
	{
		if(enemy_health<=0)
		{
			printf("%s DEFEATED ENEMY \n", nama);
			printf("-----------VICTORY--------- \n");
			standby=1;
			sleep(2);
			system("clear");
			break;
		}
		if(sehat<=0)
		{
			printf("%s DEFEATED \n", nama);
			printf("GO HOME, %s HEALTH IS EMPTY\n", nama);
			standby=1;
			sehat=0;
			sleep(2);
			system("clear");
			break;
		}
		printf("Battle Mode\n");
		printf("%s Health : %d\n", nama, sehat);
		printf("Enemy’s Health : %d\n", enemy_health);
		printf("Choices\n");
		printf("1. Attack\n");
		printf("2. Run\n");
		pilih_b=mygetch();
		if(pilih_b=='1')
		{
			system("clear");
			sehat-=20;
			enemy_health-=20;
			printf("%s Attacks the Enemy !!!\n", nama);
			printf("Enemy Health -20 ! \n");
			printf("Enemy Attacks %s !!!\n", nama);
			printf("%s Health -20 ! \n", nama);
			sleep(5);
			system("clear");
		}
		if(pilih_b=='2')
		{
			system("clear");
			printf("%s is Running \n", nama);
			printf("%s escaped the battle\n", nama);
			standby=1;
			sleep(3);
			system("clear");
			break;
		}
	}
}

void shop()
{
        key_t key = 1234;
        int *stok;
	int pil_s;
        int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
        stok = shmat(shmid, NULL, 0);

	while(1)
	{
		printf("Shop Mode\n");
		printf("Shop food stock : %d\n", *stok);
		printf("Your food stock : %d\n", makan);
		printf("Choices\n");
		printf("1. Buy\n");
		printf("2. Back\n");
		pil_s=mygetch();
		if(pil_s=='1')
		{
			if(*stok >=5)
			{
				makan+=5;
				*stok-=5;
			}
			else
			{
				system("clear");
				printf("Insufficient Food stock \n");
				sleep(2);
				system("clear");
			}
		}
		if(pil_s=='2')
		{
			break;
		}
		system("clear");
	}
        shmdt(stok);
        shmctl(shmid, IPC_RMID, NULL);
}
int main()
{
	system("clear");
	printf("-------------WELCOME TO PET MONSTER LUCU------------\n");
	printf("Give Your Monster Name: ");
	scanf("%s", nama);
	printf("------------NOW YOUR MONSTER NAME IS %s!------------\n", nama);
	sleep(2);
	system("clear");
	pthread_t tid[5];
	pthread_create(&(tid[0]), NULL, laper, NULL);
	pthread_create(&(tid[1]), NULL, kotor, NULL);
	pthread_create(&(tid[2]), NULL, up_health, NULL);
	pthread_create(&(tid[3]), NULL, timer, NULL);
	stand();
}
