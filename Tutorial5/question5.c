#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUMSTUDENT 2

pthread_barrier_t barr;
pthread_mutex_t mutex;
float totalGrade = 0.0;
float totalBellCurve = 0.0;

void *bellCurve(void *arg){

  return NULL;
}

void *readGrades(void *arg){

}

void *saveBellCurve(void *grade){

}

int main(void){
  pthread_t tid;
  pthread_barrier_init(&barr, NULL, 1);


  for (int i = 0; i < NUMSTUDENT; i++){

  }

  for (int i = 0; i < NUMSTUDENT; i++){
    pthread_join(tid[i], NULL);
  }

  return 0;
}
