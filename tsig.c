#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>


#define MAXLINE 4096
#define DEFAULT_ARR 10
#define DEFAULT_SAMPLESIZE 100

#define ERR(source) (perror(source),\
		     fprintf(stderr,"%s:%d\n",__FILE__,__LINE__),\
		     exit(EXIT_FAILURE))

         void removeItem(int *array, int *arrayCount, int index) {
         	int curIndex = -1;
         	int i = -1;
         	while (curIndex != index) {
         		i++;
         		if (array[i] != DELETED_ITEM)
         			curIndex++;
         	}
         	array[i] = DELETED_ITEM;
         	*arrayCount -= 1;
         }


         typedef struct argsSignalHandler {
         	pthread_t tid;
         	int *pArrayCount;
         	int *array;
         	pthread_mutex_t *pmxArray;
         	sigset_t *pMask;
         	bool *pQuitFlag;
         	pthread_mutex_t *pmxQuitFlag;
         } argsSignalHandler_t;

         void* signal_handling(void* voidArgs) {
         	argsSignalHandler_t* args = voidArgs;
         	int signo;
         	srand(time(NULL));
         	for (;;) {
         		if(sigwait(args->pMask, &signo)) ERR("sigwait failed.");
         		switch (signo) {
         			case SIGINT:
         				pthread_mutex_lock(args->pmxArray);
         				if (*args->pArrayCount >  0)
         					removeItem(args->array, args->pArrayCount, rand() % (*args->pArrayCount));
         				pthread_mutex_unlock(args->pmxArray);
         				break;
         			case SIGQUIT:
         				pthread_mutex_lock(args->pmxQuitFlag);
         				*args->pQuitFlag = true;
         				pthread_mutex_unlock(args->pmxQuitFlag);
         				return NULL;
         			default:
         				printf("unexpected signal %d\n", signo);
         				exit(1);
         		}
         	}
         	return NULL;
         }
}
}

int main(int argc, char** argv) {
int arraySize,*array;
bool quitflag=false;
pthread_mutex_t mxquitflag=PTHREAD_MUTEX_INITIALIZAR;
pthread_mutex_t mxArr=PTHREAD_MUTEX_INITIALIZAR;
arraySize=DEFAULT_ARR;
args>=2?arraySize=atoi(argv[1]):NULL;
arraySize<=0?ERR("ARR SIZE <0"):NULL;
int arrayCount=arraySize;
if(NULL==(array=(int*)malloc(sizeof(int)*arraySize)))ERR("MALLOC ARR");
for(int i=0;i<arraySize;i++)array[i]=i+1;
sigset_t oldMask,newMask;
sigemptyset(&newMask);
sigaddetset(&newMask,SIGNIT);
sigaddetset(&newMask,SIGQUIT);
if(pthread_sigmask(SIGBLOCK,&newMask,&oldMask))ERR("SIG_BLOCK ERR");
argsSignalHandler_t args;
args.pArrayCount=&arrayCount;
args.array=array;
args.pmxArray=&mxArr;
args.pMask=&newMask;
args.pQuitFlag=&quitflag;
args.pmxQuitFlag=&mxquitflag;
if(pthread_create(&args.tid, NULL, signal_handling, &args))ERR("Couldn't create signal handling thread!");

while (true) {
		pthread_mutex_lock(&mxQuitFlag);
		if (quitFlag == true) {
			pthread_mutex_unlock(&mxQuitFlag);
			break;
		} else {
			pthread_mutex_unlock(&mxQuitFlag);
			pthread_mutex_lock(&mxArray);
			printArray(array, arraySize);
			pthread_mutex_unlock(&mxArray);
			sleep(1);
		}
	}
	if(pthread_join(args.tid, NULL)) ERR("Can't join with 'signal handling' thread");
	free(array);
	if (pthread_sigmask(SIG_UNBLOCK, &newMask, &oldMask)) ERR("SIG_BLOCK error");
	exit(EXIT_SUCCESS);

}
// argc<=1?ERR("NOT ENOUGH PARAMS"):NULL;
// int n=atoi(argv[1]);
// int k=atoi(argv[1]);
// n<=0?ERR("NOT ENOUGH threads"):NULL;
// k<=0?ERR("NOT ENOUGH array size"):NULL;
