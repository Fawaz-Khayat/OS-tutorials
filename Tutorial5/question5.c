#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_STUDENT 2
#define NUM_THREADS 10

void *read_grades(void *this_thread);
void *save_bellcurve(void *grades_struct);

pthread_barrier_t barr;
pthread_mutex_t mutex;
float total_grade = 0.0;
float total_bellcurve = 0.0;

struct grades{
  int number;
  float value;
};

struct grades grades_array[NUM_THREADS];

void *read_grades(void *this_thread){
  pthread_t thread[NUM_THREADS];
  pthread_attr_t attr;
  
  // variables for current thread
  int i;
  long tid;
  tid = (long)this_thread;
  float grade;
  // variables for creating threads
  int rc;
  long bellcurve_thread;
  void *status;

  FILE *fp;
  fp = fopen("grades.txt", "r");

  for(bellcurve_thread=0; bellcurve_thread<NUM_THREADS; bellcurve_thread++) {
    fscanf(fp, "%f\n",&grade);
    grades_array[bellcurve_thread].number = bellcurve_thread;
    grades_array[bellcurve_thread].value =  grade;
    printf("Main: creating thread %ld\n", bellcurve_thread);
    rc = pthread_create(&thread[bellcurve_thread], &attr, save_bellcurve, (void *)&grades_array[bellcurve_thread]);  
    if (rc) {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
      }
    }

  fclose(fp);

  /* Free attribute and wait for the other threads */
  pthread_attr_destroy(&attr);
  for(bellcurve_thread=0; bellcurve_thread<NUM_THREADS; bellcurve_thread++) {
    rc = pthread_join(thread[bellcurve_thread], &status);
    if (rc) {
      printf("ERROR; return code from pthread_join() is %d\n", rc);
      exit(-1);
      }
    printf("Main: completed join with thread %ld having a status of %ld\n",bellcurve_thread,(long)status);
    }

  pthread_exit((void*) this_thread);
}

void *save_bellcurve(void *grades_struct){
  // variables for current thread
  struct grades *grades_data;
  grades_data = (struct grades *) grades_struct;
  int i;
  long tid = grades_data->number;
  float grade = grades_data->value;

  total_grade += grade;
  float grade_bellcurve = grade * 1.50;
  total_bellcurve += grade_bellcurve;
  
  FILE *fp;
  fp = fopen("bellcurve.txt", "a");
  fprintf(fp, "%f\n",grade_bellcurve);

  fclose(fp);

  pthread_exit((void*) tid);

}

int main(void){
  pthread_t tid;
  pthread_t read_grades_thread;
  pthread_attr_t attr;
  int rc;
  //long read_grades_thread = 0;
  void *status;

  /* Initialize and set thread detached attribute */
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  //creating thread to read_grades
  printf("Reading grades from grades.txt\n");
  rc = pthread_create(&read_grades_thread, &attr, read_grades, (void *)read_grades_thread);
  if (rc) {
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
        }

  /* Free attribute and wait for the other threads */
    pthread_attr_destroy(&attr);
    
    rc = pthread_join(read_grades_thread, &status);
    if (rc) {
      printf("ERROR; return code from pthread_join() is %d\n", rc);
      exit(-1);
      }
    printf("Main: completed join with thread %ld having a status of %ld\n",read_grades_thread,(long)status);
    
 
 // print total grade and the class average before bellcurve
 // print total grade and the class average after bellcurve
 printf("Before bellcurve:\n");
 printf("Total Grade = %f\n",total_grade);
 printf("Class average = %f\n", total_grade/10.0);
 printf("After bellcurve:\n");
 printf("Total Grade = %f\n",total_bellcurve);
 printf("Class average = %f\n", total_bellcurve/10.0);

 printf("Main: program completed. Exiting.\n");
 pthread_exit(NULL);

  return 0;
}
