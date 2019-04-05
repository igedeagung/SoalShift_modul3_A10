#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT2 8080

int main(int argc, char const *argv[]) {
	struct sockaddr_in address2;
	int sock2 = 0, valread;
	struct sockaddr_in serv_addr2;
	char buffer[1024] = {0};
	//pembeli
	if ((sock2 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        	printf("\n Socket creation error \n");
        	return -1;
	}

	memset(&serv_addr2, '0', sizeof(serv_addr2));

	serv_addr2.sin_family = AF_INET;
	serv_addr2.sin_port = htons(PORT2);

	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr2.sin_addr)<=0) {
        	printf("\nInvalid address/ Address not supported \n");
	        return -1;
	}

	if (connect(sock2, (struct sockaddr *)&serv_addr2, sizeof(serv_addr2)) < 0) {
        	printf("\nConnection Failed \n");
	        return -1;
	}
	char pesan[20];
	char output[50];
	int banding_beli;
	while(1)
	{
		scanf("%s", pesan);
		banding_beli=strcmp(pesan, "beli");
		if(banding_beli==0)
		{
			send(sock2, pesan, strlen(pesan), 0);
			valread=read(sock2, output, 50);
			printf("%s\n", output);
		}
	}
	return 0;
}
