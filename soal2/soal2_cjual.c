#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT1 8090

int main(int argc, char const *argv[]) {
	struct sockaddr_in address;
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char buffer[1024] = {0};
	//penjual
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        	printf("\n Socket creation error \n");
	        return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT1);

	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        	printf("\nInvalid address/ Address not supported \n");
	        return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        	printf("\nConnection Failed \n");
	        return -1;
	}

	char pesan[20];
	char output[50];
	int banding_jual;
	while(1)
	{
		scanf("%s", pesan);
		banding_jual=strcmp(pesan, "tambah");
		if(banding_jual==0)
		{
			send(sock, pesan, strlen(pesan), 0);
		}
	}
	return 0;
}
