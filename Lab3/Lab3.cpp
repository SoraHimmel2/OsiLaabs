#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <string.h>
#include <stdio.h>


int fd[2];



void *inputDigit(void *arg)
{
    int *someVariable = (int*)arg;
    int buf = 1;
    
    
    while (*someVariable != 27)
    {
       
        write(fd[1], &buf, 100);
        buf++;
     
        
    }
     pthread_exit(NULL);
}

void *getDigit(void *arg)
{
    int *Variable = (int*)arg;
    int buf ;
    errno = 0;
    while (*Variable != 27)
    {
        if (read(fd[0], &buf, 100))
        {
            std::cout << buf << std::endl;
        }
        else
        {
            std::cout << strerror(errno) << std::endl;
        }
        sleep(2);
    }
     pthread_exit(NULL);
}

int main()
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
    
    pipe(fd);
    fcntl(fd[0], F_SETFL, O_NONBLOCK);
    //pipe2(fd, O_NONBLOCK);

    
     pthread_create(&thread_1,&attr_1,inputDigit,(void*)pFlag1);
    pthread_create(&thread_2,&attr_2,getDigit,(void*)pFlag2);
    
    
    sleep(5);
    *pFlag1 = 27;
    *pFlag2 = 27;
    std::cout << "end" <<std::endl;
   

    close(fd[0]);
    close(fd[1]);
    return 0;
}