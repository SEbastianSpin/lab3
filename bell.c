#include <stdlib.h>
#include <stddef.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAXLINE 4096
#define DEFAULT_THREADCOUNT 10
#define DEFAULT_N 1000
#define BIN_COUNT 11
#define NEXT_DOUBLE(seedptr) ((double) rand_r(seedptr) / (double) RAND_MAX)
#define ERR(source) (perror(source),\
		     fprintf(stderr,"%s:%d\n",__FILE__,__LINE__),\
		     exit(EXIT_FAILURE))

typedef unsigned int UINT;
typedef struct argsThrower{
        pthread_t tid;
        UINT seed;
        int *pBallsThrown;
        int *pBallsWaiting;
        int *bins;
        pthread_mutex_t *mxBins;
        pthread_mutex_t *pmxBallsThrown;
        pthread_mutex_t *pmxBallsWaiting;
} argsThrower_t;

void ReadArguments(int argc,char**  argv,int* balls,int* throwers);
int main(int argc, char** argv) {
  int balls, throwers;
  ReadArguments(argc,argv,&balls,&throwers);
  int balls throwns=0, bt=0;
  int ballsWaiting=balls;
  pthread_mutex_t mxBallsThrown = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_t mxBallsWaiting = PTHREAD_MUTEX_INITIALIZER;
  int bins[BIN_COUNT];
  pthread_mutex_t mxBins[BIN_COUNT];
  for(int i=0; i<BIN_COUNT;i++){
    bins[i]=0;
    if(pthread_mutex_init(&mxbins[i],NULL))ERR("MUTEX MXBINS FAILED");
}

argsThrower_t* args=(argsThrower_t*)malloc(sizeof(argsThrower_t*throwers);

args?NULL:ERR("MALLOC argsThrower_t");

for (int i = 0; i < throwers; i++) {
                args[i].seed = (UINT) rand();
                args[i].pBallsThrown = &ballsThrown;
                args[i].pBallsWaiting = &ballsWaiting;
                args[i].bins = bins;
                args[i].pmxBallsThrown = &mxBallsThrown;
                args[i].pmxBallsWaiting = &mxBallsWaiting;
                args[i].mxBins = mxBins;
        }
make_thowers(args,throwers);


}

void ReadArguments(int argc,char**  argv,int* balls,int* throwers){
  *balls=DEFAULT_N;
  *throwers=DEFAULT_THREADCOUNT;
  argc>=2?*balls=atoi(argv[1]):NULL;
  *ball<=0?ERR("INVALID AMMOUNT OF BALLS"):NULL;
  argc>=3?*throwers=atoi(argv[2]):NULL;
  *throwers<=0?ERR("INVALID AMMOUNT OF throwers"):NULL;
}

void* make_thowers(argsThrower_t *argsArray, int thrownsc){
pthread_attr_t threadAttr;
pthread_attr_init(&threadAttr)?ERR("Failed create attr threead");
pthread_attr_setdetached(&threadAttr,PTHREAD_CREATE_DETACHED)?ERR("PTHREAD_CREATE_DETACHED");
for (int i = 0; i < thrownsc; i++) {
	pthread_create(&argsArray[i].tid,&threadAttr,thowinffunc,&argsArray[i])?ERR("Creaation");
}
pthread_attr_destroy(&threadAttr);

}


void* thowinffunc(void* voidArgs){
	argsThrower_t* args= voidArgs;
	while (1) {
		pthread_mutex_lock(args->pmxBallsWaiting);
		if(*args->pBallsWaiting>0){
			(*args->pmxBallsWaiting)-=1;
			pthread_mutex_unlock(args->pmxBallsWaiting);
		}
	}
}
//	cp espins.tar.bz2 /home2/samba/karwowskij/unix
