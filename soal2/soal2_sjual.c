#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#define PORT 8090

int *seok;

void *cek_stok(void *arg)
{
	while(1)
	{
		sleep(3);
		printf("%d\n", *seok);
	}
}

int main(int argc, char const *argv[]) {
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};

	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("socket failed");
	        exit(EXIT_FAILURE);
	}

	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        	perror("setsockopt");
	        exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );

	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        	perror("bind failed");
	        exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 3) < 0) {
        	perror("listen");
	        exit(EXIT_FAILURE);
	}
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
       		perror("accept");
        	exit(EXIT_FAILURE);
	}

	key_t key = 1234;
        int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
        seok = shmat(shmid, NULL, 0);

        *seok = 0;
	int banding_read;
	char pesan[50]="BERHASIL";
	pthread_t tid[3];
	pthread_create(&(tid[0]), NULL, cek_stok, NULL);
	while(1)
	{
		valread=read(new_socket, buffer, 1024);
		banding_read=strcmp(buffer, "tambah");
		if(banding_read==0)
		{
			*seok= *seok+1;
		}
	}
	shmdt(seok);
        shmctl(shmid, IPC_RMID, NULL);
	return 0;
}
