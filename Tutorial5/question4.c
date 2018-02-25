#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

#define NUMSTUDENT 10
float totalGrade = 0.0;
pthread_mutex_t mutex;

void *classTotal (void *grade){
  float *studentGrade = grade;
  //lock mutex
  pthread_mutex_lock(&mutex);
  totalGrade += (*studentGrade);
  //unlock mutex
  pthread_mutex_unlock(&mutex);
  return NULL;
}

int main(void){
  pthread_t tid[NUMSTUDENT];
  float *grades = malloc(sizeof(float) * NUMSTUDENT);

  for (int i = 0; i < NUMSTUDENT; i++){
    printf("Student %i's grade: ", i+1);
    scanf("%f", &grades[i]);
  }

  pthread_attr_t attr[NUMSTUDENT];
  for (int i = 0; i < NUMSTUDENT; i++){
    pthread_attr_init(&attr[i]);
  }

  for (int i = 0; i < NUMSTUDENT; i++){
    pthread_create(&tid[i], &attr[i], classTotal, &grades[i]);
  }

  for (int i = 0; i < NUMSTUDENT; i++){
    pthread_join(tid[i], NULL);
  }

  printf("Total Grade: %.2f\n", totalGrade);

  return 0;
}
