#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

pthread_t tid[100];
long long int A[100];
int total;

void *fact(void *arg){
        long long int hasil[100];
        int i;
        int n;
	long long int sementara;
	for(int j=1; j<=total; j++)
	{
		sementara=A[j];
		hasil[sementara]=1;
        	for(i=1;i<=sementara;i++)
        	{
                	hasil[sementara] = hasil[sementara] * i;
		}
		printf("%lld! = %lld\n",sementara,hasil[sementara]);
	}
}


int main(int argc,char *argv[])
{
        int i,n,j,k,a,t,fak[100];
        void *fa = A;
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
        pthread_create(&(tid[0]), NULL, fact, NULL);
        pthread_join(tid[0], NULL);
        return 1;
}

