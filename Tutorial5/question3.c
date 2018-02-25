#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUMSTUDENT 5
struct student {
  char name[256];
  int studentId;
  float grade;
};

void *bellCurve (void *arg){
  struct student *currentStudent = (struct student *) arg;
  printf("Student Name: %s\nStudent ID: %i\nGrade: %.2f\n\n", currentStudent->name, currentStudent->studentId, (currentStudent->grade * 1.5));
  return NULL;
}

int main(void){
  pthread_t tid[NUMSTUDENT];
  struct student *students = (struct student*) malloc(sizeof(struct student) * NUMSTUDENT);

  for (int i = 0; i < NUMSTUDENT; i++){
    printf("Student %i's name: ", i+1);
    scanf("%s", &students[i].name);
    printf("Student %i's student id: ", i+1);
    scanf("%i", &students[i].studentId);
    printf("Student %i's grade: ", i+1);
    scanf("%f", &students[i].grade);
  }

  pthread_attr_t attr[NUMSTUDENT];
  for (int i = 0; i < NUMSTUDENT; i++){
    pthread_attr_init(&attr[i]);
  }

  for (int i = 0; i < NUMSTUDENT; i++){
    pthread_create(&tid[i], &attr[i], bellCurve, &students[i]);
  }

  for (int i = 0; i < NUMSTUDENT; i++){
    pthread_join(tid[i], NULL);
  }

  return 0;
}
