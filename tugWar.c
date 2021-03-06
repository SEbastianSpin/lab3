#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#define DEFAULT_FORPARAM1 1
#define DEFAULT_FORPARAM2 1
#define MAXLINE 4096 //PUT HERE to avoid MAGIC NUMBERS

#define ERR(source) (perror(source),\
		     fprintf(stderr,"%s:%d\n",__FILE__,__LINE__),\
		     exit(EXIT_FAILURE))


typedef unsigned int UINT;
typedef struct timespec timespec_t;


typedef struct argsThread{ // STRUCTS FOR ARGS
	pthread_t tid;
	int counter;
    int timer;
	//pthread_mutex_t *mxBins;
} argsThread_t;


typedef struct argsplayer{ // STRUCTS FOR players
	pthread_t tid;
	 int playerid;
     int* counter;
    UINT seed;
    int *timer;
	//pthread_mutex_t *mxBins;
} argsplayer_t;


void* thread_func(void* args);
void* player_func(void* args);
void ReadArguments(int argc, char** argv, int *param1);

int main(int argc, char** argv) {
int matchTime;
ReadArguments(argc, argv, &matchTime);

argsThread_t judge;
judge.counter=0;
judge.timer=matchTime;
int errr = pthread_create(&(judge.tid), NULL, thread_func, &judge);
if (errr != 0) ERR("Couldn't create thread");



// JOIN

		int err = pthread_join(judge.tid,NULL);
		if (err != 0) ERR("Can't join with a thread");
	



exit(EXIT_SUCCESS);
}

void ReadArguments(int argc, char** argv, int *param1){
	*param1 = DEFAULT_FORPARAM1;
	if (argc >= 2) {
		*param1 = atoi(argv[1]);
		if (*param1 <= 2 || *param1>=128) {
			printf("Invalid value for 'PLAY TIME count'");
			exit(EXIT_FAILURE);
		}
	}
	
}


void* thread_func(void* args){
	argsThread_t* fargs = args;

    argsplayer_t* argsP = (argsplayer_t*) malloc(sizeof(argsplayer_t) * 2);
    if (argsP == NULL) ERR("Malloc error for players arguments!");
    

    for(int i=0;i<2;i++){
    argsP[i].playerid=i+1;
    argsP[i].counter=&(fargs->counter);
    argsP[i].timer=&(fargs->timer);
    int err = pthread_create(&(argsP[i].tid), NULL, player_func, &argsP[i]);
     if (err != 0) ERR("Couldn't create thread");


    }

   while(fargs->timer){
        printf("score %d \n", fargs->counter);
       sleep(1);

       fargs->timer-=1;
   }
   


    for (int i = 0; i < 2; i++) {
		int err = pthread_join(argsP[i].tid,NULL);
		if (err != 0) ERR("Can't join with a judge");
	}

   	printf("EXIT FROM MAIN \n");

    free(argsP);

	
}


void* player_func(void* args){
    argsplayer_t* pargs = args;
  
    struct timespec tv;
   int msec = (int)(((double)rand_r(pthread_self()) / INT_MAX) * 1000);
   tv.tv_sec = 0;
   tv.tv_nsec = 1000000 * msec;
   
   while(*pargs->timer){
       int  goal=rand_r(pthread_self())%6;
      if(nanosleep(&tv, NULL) == -1) {
      perror("nanosleep");
   }

    if(pargs->playerid==1){
      *pargs->counter= *pargs->counter-goal;
     
     }
     else{
      *pargs->counter= *pargs->counter+goal;
     
     }


   }
    
  

//
     
    
}