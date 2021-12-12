#include <stdlib.h>
#include <stddef.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAXLINE 4096
#define DEFAULT_THREADCOUNT 10
#define DEFAULT_SAMPLESIZE 100

#define ERR(source) (perror(source),\
		     fprintf(stderr,"%s:%d\n",__FILE__,__LINE__),\
		     exit(EXIT_FAILURE))




void* threadWork(void *voidPtr) {
  int *arr= voidPtr;
	int place=(rand()%3);

	printf("[%d]  place %d \n",arr[place],place);

}

int main(int argc, char** argv) {
argc<=3?ERR("NOT ENOUGH PARAMS"):NULL;
int n=atoi(argv[1]);
int k=atoi(argv[1]);
n<=0?ERR("NOT ENOUGH threads"):NULL;
k<=0?ERR("NOT ENOUGH array size"):NULL;


int randomArr[k];
srand(time(NULL));
for (size_t i = 0; i < k; i++) {
	randomArr[i]=(rand()%60)+1;
}

for (size_t i = 0; i < k; i++) {
	printf("[%d]",	randomArr[i]);
}

printf("\n");
pthread_t* tids = (pthread_t*) malloc(sizeof(pthread_t) * n);
tids?NULL:ERR("MALLOC TIDS FIALED");


for(int i=0;i<k;i++){
	pthread_create(&tids[i],NULL,&threadWork,&randomArr);
}

printf("Arr %d",randomArr);
printf("Arr %d",&randomArr);

for (int i = 0; i < k; i++) {
		int err = pthread_join(tids[i],NULL);
		if (err != 0) ERR("Can't join with a thread");
	}

free(tids);


}
