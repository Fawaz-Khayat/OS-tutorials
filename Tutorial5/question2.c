#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *bellCurve (void *grade){
  float *studentGrade = grade;
  float result = ((*studentGrade) * 1.50);
  printf("%.2f\n", result);
  return NULL;
}

int main(void){
  pthread_t tid[5];
  float *grades = malloc(sizeof(float) * 5);

  for (int i = 0; i < 5; i++){
    printf("Student %i's grade: ", i+1);
    scanf("%f", &grades[i]);
  }

  pthread_attr_t attr[5];
  for (int i = 0; i < 5; i++){
    pthread_attr_init(&attr[i]);
  }

  for (int i = 0; i < 5; i++){
    pthread_create(&tid[i], &attr[i], bellCurve, &grades[i]);
  }

  for (int i = 0; i < 5; i++){
    pthread_join(tid[i], NULL);
  }

  free(grades);
  return 0;
}
