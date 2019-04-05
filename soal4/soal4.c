#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

pthread_t tid[3]; //inisialisasi array untuk menampung thread dalam kasus ini ada 2 thread

int length=5; //inisialisasi jumlah untuk looping

void* mkdir()
{
	system("mkdir /home/edgar/Documents/FolderProses1");
	system("mkdir /home/edgar/Documents/FolderProses2");
}

void* touch()
{
	system("touch /home/edgar/Documents/FolderProses1/SimpanProses1.txt");
	system("touch /home/edgar/Documents/FolderProses2/SimpanProses2.txt");
}

void* aux()
{
	system("ps aux | head -11 | tail -10 >> /home/edgar/Documents/FolderProses1/SimpanProses1.txt");
	system("ps aux | head -11 | tail -10 >> /home/edgar/Documents/FolderProses2/SimpanProses2.txt");
}

void* zip()
{
	system("zip -j /home/edgar/Documents/FolderProses1/KompresProses1.zip /home/edgar/Documents/FolderProses1/SimpanProses1.txt");
	system("zip -j /home/edgar/Documents/FolderProses2/KompresProses2.zip /home/edgar/Documents/FolderProses2/SimpanProses2.txt");
}

void* rm()
{
	system("rm /home/edgar/Documents/FolderProses1/SimpanProses1.txt");
	system("rm /home/edgar/Documents/FolderProses2/SimpanProses2.txt");
}


void* unzip()
{
	system("unzip /home/edgar/Documents/FolderProses1/KompresProses1.zip -d /home/edgar/Documents/FolderProses1/");
	system("unzip /home/edgar/Documents/FolderProses2/KompresProses2.zip -d /home/edgar/Documents/FolderProses2/");
}

int main(void)
{
	int i=0;
	int err;
	pthread_t thread1, thread2, thread3, thread4, thread5, thread6;
	int  iret1, iret2, iret3, iret4, iret5, iret6;
		iret1 = pthread_create( &thread1, NULL, mkdir, NULL); //membuat thread pertama
    		if(iret1) //jika eror
    		{
        		fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
        		exit(EXIT_FAILURE);
    		}
		pthread_join( thread1, NULL);

		iret2 = pthread_create( &thread2, NULL,touch , NULL); //membuat thread pertama
    		if(iret2) //jika eror
    		{
        		fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
        		exit(EXIT_FAILURE);
    		}
    		 pthread_join( thread2, NULL); 

		iret3 = pthread_create( &thread3, NULL,aux , NULL); //membuat thread pertama
                if(iret3) //jika eror
                {
                        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret3);
                        exit(EXIT_FAILURE);
                }
                 pthread_join( thread3, NULL);

		iret4 = pthread_create( &thread4, NULL,zip , NULL); //membuat thread pertama
                if(iret4) //jika eror
                {
                        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret4);
                        exit(EXIT_FAILURE);
                }
                 pthread_join( thread4, NULL);

		iret6 = pthread_create( &thread6, NULL,rm , NULL); //membuat thread pertama
               	if(iret6) //jika eror
               	{
                       	fprintf(stderr,"Error - pthread_create() return code: %d\n",iret6);
                       	exit(EXIT_FAILURE);
               	}
               	pthread_join( thread6, NULL);

		printf("Menunggu 15 detik untuk mengekstrak kembali\n");
		sleep(15);

		iret5 = pthread_create( &thread5, NULL,unzip , NULL); //membuat thread pertama
               	if(iret5) //jika eror
               	{
                       	fprintf(stderr,"Error - pthread_create() return code: %d\n",iret5);
                       	exit(EXIT_FAILURE);
               	}
               	pthread_join( thread5, NULL);

	return 0;
}
