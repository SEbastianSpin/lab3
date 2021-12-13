#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#define DEFAULT_FORPARAM1 1
#define DEFAULT_FORPARAM2 1
#define MAXLINE 4096 //PUT HERE to avoid MAGIC NUMBERS

#define ERR(source) (perror(source),\
		     fprintf(stderr,"%s:%d\n",__FILE__,__LINE__),\
		     exit(EXIT_FAILURE))


typedef struct argsSignalHandler {
	pthread_t tid;

	//pthread_mutex_t *pmxArray;
	sigset_t *pMask;

} argsSignalHandler_t;

typedef struct argsThread{ // STRUCTS FOR ARGS
	//pthread_t tid;
	// int *pBallsThrown;
	//pthread_mutex_t *mxBins;
} argsThread_t;

void ReadArguments(int argc, char** argv, int *param1 /*, int* param2 */);

void* thread_func(void* args);
void* signal_handling(void*);

int main(int argc, char** argv) {
int param1, param2;
ReadArguments(argc, argv, &param1);

//NORMAL MUTEX
// pthread_mutex_t MUTEXNAME = PTHREAD_MUTEX_INITIALIZER;

// int ARRAY[ARRSIZE];
// Mutex ARR
// pthread_mutex_t mxARRAY[ARRSIZE];

// for (int i =0; i < ARRSIZE; i++) {
// 		ARRAY[i] = 0;
// 		if(pthread_mutex_init(&mxARRAY[i], NULL))ERR("Couldn't initialize mutex!");
//   //MUTEX FOR ARR
// }

// IN case you need to alocate memory for STRUCT array
//argsThread_t* args = (argsThread_t*) malloc(sizeof(argsThread_t) * ?*NUM OF THREADS*/);
//if (args == NULL) ERR("Malloc error for throwers arguments!");

//// threads NORMAL
// for (int i = 0; i < threadCount; i++) {
//    	int err = pthread_create(&(argsThread.tid), NULL, thread_func, &argsThread);  // warning HERE
// 		int err = pthread_create(&(argsThread[i].tid), NULL, thread_func, &argsThread[i]);
// 		if (err != 0) ERR("Couldn't create thread");
// 	}

//// threads DETACHED
// pthread_attr_t threadAttr;
// if(pthread_attr_init(&threadAttr)) ERR("Couldn't create pthread_attr_t");
// if(pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED)) ERR("Couldn't setdetachsatate on pthread_attr_t");
// for (int i = 0; i < threadCount; i++) {
// 		if(pthread_create(&argsArray.tid, &threadAttr, thread_func, &argsArray)) ERR("Couldn't create thread"); //WARNING
// 		if(pthread_create(&argsArray[i].tid, &threadAttr, thread_func, &argsArray[i])) ERR("Couldn't create thread");
// 	}
// 	pthread_attr_destroy(&threadAttr);



// //SIGNALS
// sigset_t oldMask, newMask;
// 	sigemptyset(&newMask);
// 	sigaddset(&newMask, SIGINT);
// 	sigaddset(&newMask, SIGQUIT);
// 	if (pthread_sigmask(SIG_BLOCK, &newMask, &oldMask)) ERR("SIG_BLOCK error");

// //SET  signal_handling
// argsSignalHandler_t args;
// args.pMask = &newMask;
//if(pthread_create(&args.tid, NULL, signal_handling, &args))ERR("Couldn't create signal handling thread!");



//// JOIN
// for (int i = 0; i < k; i++) {
// 		int err = pthread_join(tids[i],NULL);
// 		if (err != 0) ERR("Can't join with a thread");
// 	}


///FREE ALOCATED IF THERE IS SOME

exit(EXIT_SUCCESS);
}

void ReadArguments(int argc, char** argv, int *param1 /*, int *param2 */){
	*param1 = DEFAULT_FORPARAM1;
	//*param2 = DEFAULT_FORPARAM2;
	if (argc >= 2) {
		*param1 = atoi(argv[1]);
		if (*param1 <= 0) {
			printf("Invalid value for 'param1 count'");
			exit(EXIT_FAILURE);
		}
	}
	// if (argc >= 3) {
	// 	*param2 = atoi(argv[2]);
	// 	if (*param2 <= 0) {
	// 		printf("Invalid value for 'param2 count'");
	// 		exit(EXIT_FAILURE);
	// 	}
	// }
}


void* thread_func(void* args){
	argsThread_t* args = voidArgs;
	// pthread_mutex_lock(/*args->MUTEXNAME*/);
	// DO SOMETHING
	//pthread_mutex_unlock(a/*args->MUTEXNAME*/);
}


void* signal_handling(void* voidArgs) {
	argsSignalHandler_t* args = voidArgs;
  int signo;
	for (;;) {
		if(sigwait(args->pMask, &signo)) ERR("sigwait failed.");
		switch (signo) {
			case SIGINT:


			case SIGQUIT:

			default:
				printf("unexpected signal %d\n", signo);
				exit(1);
		}
	}

}
