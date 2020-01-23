/*--------- Multi-threaded "Hello World"-------*/

#include <pthread.h>
#include <stdio.h>
#include <sched.h>

// look up the sched_yield() system call

#define _REENTRANT
#define DCE_COMPAT

pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_cond  = PTHREAD_COND_INITIALIZER;

/*----------- Function Prototypes ------------------*/
void* producer(void*);
void* consumer(void*);

typedef struct {
	char c;
	int i;
	double d;
	int update;
	int done;
}ThreadInfo;
/*------------ Mutex Variables ---------------------*/
pthread_mutex_t threadLock = PTHREAD_MUTEX_INITIALIZER;


int main (void)
{
  // pthread_t thread1, thread2;
  // pthread_attr_t attr1, attr2;

  ThreadInfo info_ptr;
  info_ptr.c = 'a';
  info_ptr.i = 1;
  info_ptr.d = 10.5;
  info_ptr.update = 0;
  info_ptr.done = 0;

  // int high = 500, low = 100;
  // struct sched_param par;
  // struct sched_param par2;
  // pthread_attr_init(&attr1);
  // pthread_attr_init(&attr2);
  // pthread_setschedpolicy(&attr1, SCHED_RR);
  // pthread_setschedpolicy(&attr2, SCHED_RR);
  // Create and run the threads.
  pthread_create (&thread1, &attr1, producer, (ThreadInfo*)&info_ptr);
  pthread_create (&thread2, &attr2, consumer, (ThreadInfo*)&info_ptr);

  pthread_join (thread1, NULL);
  pthread_join (thread2, NULL);

  printf ("\n");
  return 0;
}


void* producer(void* arg){
  ThreadInfo* info = (ThreadInfo*)arg;

	char a = 'a';
	int i = 3;
	double d = 10.5;
	for (int i = 0;i < 3; i ++)
	{

    printf("Mut %d",info->update);
		if (info->update == 0) {
      printf("Mut");
			pthread_mutex_lock(&threadLock);
			info->c = a++;
			info->i = i++;
			info->d = d++;
			info->update = 1;
			if (i == 6)
				info->done = 1;
			pthread_mutex_unlock(&threadLock);
		}
		if (info->done)
			break;
	}
	return NULL;
}
void* consumer(void* arg){
  
  ThreadInfo* info = (ThreadInfo*)arg;

	for (int i = 0;i < 3; i ++)
	{
		if (info->update == 1) {
			pthread_mutex_lock(&threadLock);
      printf("Consumer");
      printf("Char: %s Int %d Double %d",info->c ,info->i, info->d);
			info->update = 0;
			pthread_mutex_unlock(&threadLock);
		}
		if (info->done)
			break;

	}
	return NULL;
}



