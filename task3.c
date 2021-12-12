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


typedef struct argsT {
				         int* arr;
								 float* resArr;
								 pthread_mutex_t* mxresArr;
								 int size;
} argsT;

void* threadWork(void* voidPtr) {
	argsT* arg=voidPtr;
	int place=(rand()%arg->size);
	//arg->arr[place]+=1;
	printf("[%d]  place %d  SIZE %d \n",arg->arr[place],place, arg->size);
	pthread_mutex_lock(arg->mxresArr);
	arg->resArr[place]=sqrt(arg->arr[place]);
	printf("sqrt(%d)=%f \n",arg->arr[place], arg->resArr[place]);
	sleep(1);
  pthread_mutex_unlock(arg->mxresArr);
}

int main(int argc, char** argv) {
argc<=3?ERR("NOT ENOUGH PARAMS"):NULL;
int n=atoi(argv[1]);
int k=atoi(argv[1]);
n<=0?ERR("NOT ENOUGH threads"):NULL;
k<=0?ERR("NOT ENOUGH array size"):NULL;


int randomArr[k];
float resultArray[n];
srand(time(NULL));
for (size_t i = 0; i < k; i++) {
	randomArr[i]=(rand()%60)+1;
}


for (size_t i = 0; i < n; i++) {
	resultArray[i]=0;
}

for (size_t i = 0; i < k; i++) {
	printf("[%d]",	randomArr[i]);
}


pthread_mutex_t mxResultArray = PTHREAD_MUTEX_INITIALIZER;

printf("\n");
pthread_t* tids = (pthread_t*) malloc(sizeof(pthread_t) * n);
tids?NULL:ERR("MALLOC TIDS FIALED");

argsT* arryArg = (argsT*) malloc(sizeof(argsT));
tids?NULL:ERR("MALLOC arryArg FIALED");


arryArg->arr=randomArr;
arryArg->size=k;
arryArg->resArr=resultArray;
arryArg->mxresArr=&mxResultArray;

//printf("Hello [%d]",	arryArg->arr[0]); //print VAL STORES IN ADDRESS
//printf("Hello [%d] \n",	&arryArg->arr[0]); // print addres

for(int i=0;i<k;i++){
	pthread_create(&tids[i],NULL,&threadWork,arryArg);
}


for (int i = 0; i < k; i++) {
		int err = pthread_join(tids[i],NULL);
		if (err != 0) ERR("Can't join with a thread");
	}

	for (size_t i = 0; i < k; i++) {
		printf("[%d]",	randomArr[i]);

	}

		printf("\n");
	for (size_t i = 0; i < k; i++) {
		printf("[%f]",	resultArray[i]);

	}
	printf("\n");

free(tids);
free(arryArg);

}
