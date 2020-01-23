/*--------- Multi-threaded "Hello World"-------*/

#include <pthread.h>
#include <stdio.h>
#include <sched.h>

// look up the sched_yield() system call

#define _REENTRANT
#define DCE_COMPAT

/*----------- Function Prototypes ------------------*/
void* producer(void*);
void* consumer(void*);

typedef struct {
	char *c;
	int i;
	double d;
	int update;
	int done;
}ThreadInfo;
/*------------ Mutex Variables ---------------------*/
pthread_mutex_t threadLock = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t condition_mutex = PTHREAD_COND_INITIALIZER;

int main (void)
{
  pthread_t thread1, thread2;

  ThreadInfo info_ptr;
  info_ptr.c = "Hi";
  info_ptr.i = 1;
  info_ptr.d = 10.5;
  info_ptr.update = 0;
  pthread_create (&thread1, 0, producer, (ThreadInfo*)&info_ptr);
  pthread_create (&thread2, 0, consumer, (ThreadInfo*)&info_ptr);

  pthread_join (thread1, NULL);
  pthread_join (thread2, NULL);

  printf ("\n");
  return 0;
}


void* producer(void* arg){
  ThreadInfo* info = (ThreadInfo*)arg;

	int i = 0;
	for (;i < 3;i++)
	{
	 		pthread_mutex_lock(&threadLock);
      printf("Enter in String: ");
      char a[100];
      fgets(a,100,stdin);
      info->c = a;
      info->i = i;
      info->d++;
	    pthread_cond_wait(&condition_mutex,&threadLock);
      pthread_cond_signal(&condition_mutex);
			pthread_mutex_unlock(&threadLock);

	}
	return NULL;
}
void* consumer(void* arg){
  
  ThreadInfo* info = (ThreadInfo*)arg;

	int i = 0;
	for (;i < 3;i++)
	{
			pthread_mutex_lock(&threadLock);
      
      pthread_cond_signal(&condition_mutex);
      printf("String:%sInt:%d\r\nDouble:%f\r\n", info->c,info->i,info->d);

	    pthread_cond_wait(&condition_mutex,&threadLock);
	 		pthread_mutex_unlock(&threadLock);


		

	}
	return NULL;
}



