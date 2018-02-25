#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *helloWorld(void *x){
    int seed = time(NULL);
    srand(seed);
    usleep((rand() % 201)*1000);
    printf("Hello World \n");
    return NULL;
}

void *goodBye(void *x){
    int seed = time(NULL);
    srand(seed);
    usleep((rand() % 201)*1000);
    printf("Goodbye\n");
    return NULL;
}

int main(void){
  pthread_t tid[2];
  pthread_create(&tid[0], NULL, helloWorld, NULL);
  pthread_create(&tid[1], NULL, goodBye, NULL);
  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);
  return 0;
}
