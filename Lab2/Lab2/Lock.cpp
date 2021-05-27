#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <time.h>



using namespace std;

pthread_mutex_t mutex;

void* firstThread(void *arg){
    int *someVariable = (int*)arg;
   struct timespec time;
  // clock_gettime(CLOCK_REALTIME,&time);
   time.tv_sec +=10;
   cout << time.tv_sec << endl;

          pthread_mutex_timedlock(&mutex,&time);
    while (*someVariable != 0) {
        sleep(2);
        cout << "1" << endl;

    }
   pthread_mutex_unlock(&mutex);
      int* threadinfo = new int (50);
      pthread_exit(threadinfo);


}

void* secondThread(void *arg){

    if(pthread_mutex_trylock(&mutex))
          pthread_mutex_lock(&mutex);
    int *someVariable = (int*)arg;
    while (*someVariable != 0) {
        sleep(2);
        cout << "2" <<endl;

    }
     pthread_mutex_unlock(&mutex);
      int* threadinfo = new int (234);
      pthread_exit(threadinfo);


}

int main ()
{
    int flag1 = 1;
    int flag2 = 1;
    int *pFlag1 = &flag1;
    int *pFlag2 = &flag2;
    pthread_t thread_1;
    pthread_attr_t attr_1;
    pthread_attr_init(&attr_1);

    pthread_t thread_2;
    pthread_attr_t attr_2;
    pthread_attr_init(&attr_2);

    pthread_mutex_init(&mutex,NULL);

    pthread_create(&thread_1,&attr_1,firstThread,(void*)pFlag1);

    pthread_create(&thread_2,&attr_2,secondThread,(void*)pFlag2);

    getchar();

    *pFlag1 = 0;
    *pFlag2 = 0;

    int* thread_1_Info;
    int* thread_2_Info;

    pthread_join(thread_1,(void**)&thread_1_Info);
    pthread_join(thread_2,(void**)&thread_2_Info);

    pthread_mutex_destroy(&mutex);

    cout << *thread_1_Info << endl;
    cout << *thread_2_Info << endl;

    sleep(6);



}
