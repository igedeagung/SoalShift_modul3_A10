#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

pthread_t tid[100];
long long int A[100];
int total;
long long int sementara;

void *fact(void *argv){
        long long int hasil[100];
        int i;
        int n;
	sementara= *((long long*) argv);
	hasil[sementara]=1;
        for(i=1;i<=sementara;i++)
        {
                hasil[sementara] = hasil[sementara] * i;
	}
	printf("%lld! = %lld\n",sementara,hasil[sementara]);
}


int main(int argc,char *argv[])
{
        int i,n,j,k,a,t,fak[100];
	long long int *angka;
	long long int tmp;
	total=argc-1;
        for(i=1;i<argc;i++)
        {
                A[i] = strtol(argv[i],NULL,10);
        }

        for(i=1;i<(argc-1);i++){
                for(j=argc-1;j>=(i+1);j--){
                        if(A[j-1]>A[j]){
                                t = A[j-1];
                                A[j-1] = A[j];
                                A[j] = t;}}}
	for(i=1; i<argc; i++)
	{
		angka = &A[i];
	        pthread_create(&(tid[i]), NULL, fact, angka);
	}
	for(n=1; n<argc; n++)
	{
        	pthread_join(tid[n], NULL);
	}
        return 1;
}

