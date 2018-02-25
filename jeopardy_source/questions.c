/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2018, Clyve Widjaya 100590208
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "questions.h"
#define MAXCHAR 1000
// Initializes the array of questions for the game
void initialize_game(void){
    // initialize each question struct and assign it to the questions array
    printf("\nWelcome to Jeopardy, players!\n");
    FILE *fp;
    char str[MAXCHAR];
    int questionIndex = 0;

    fp = fopen("question.txt", "r");

    while (fgets(str, MAXCHAR, fp) != NULL){
      char *line = NULL;
      char delims[] = ",";
      line = strtok(str, delims);
      //while (line != NULL){
      strcpy(questions[questionIndex].category, line);
      line = strtok(NULL, delims);
      strcpy(questions[questionIndex].question, line);
      line = strtok(NULL, delims);
      strcpy(questions[questionIndex].answer, line);
      line = strtok(NULL, delims);
      questions[questionIndex].value = atoi(line);
      line = strtok(NULL, delims);
      questions[questionIndex].answered = false;

      //}
      questionIndex++;
    }

    fclose(fp);
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void){
  // print categories and dollar values for each unanswered question in questions array
  char qBoard[NUM_QUESTIONS][20];
	for (int i = 0; i < NUM_QUESTIONS; i++) {
		if (questions[i].answered == false) {
			snprintf(qBoard[i], 20, "%d", questions[i].value);
		} else {
			strcpy(qBoard[i], "   ");
		}
	}
  printf("|------------------------------------------------------------|\n");
  printf("|    %s     |    %s     |     %s     |\n", categories[0], categories[1], categories[2]);
  printf("|------------------------------------------------------------|\n");
  for (int i = 0; i <= NUM_CATEGORIES; i++){
    printf("|        %s         |        %s        |        %s        |\n", &qBoard[i], &qBoard[i+4], &qBoard[i+8]);
  	printf("|------------------------------------------------------------|\n");
  }
}

// Displays the question for the category and dollar value
void display_question(char *category, int value){
  for (int i = 0; i < NUM_QUESTIONS; i++){
    if ((strcmp(questions[i].category, category) == 0) && (questions[i].value == value)){
      printf("\nAnswer this question:\n%s\n",questions[i].question);
    }
  }

}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer){
  // Look into string comparison functions
  for (int i = 0; i < NUM_QUESTIONS; i++){
    if ((strcmp(questions[i].category, category) == 0) && (questions[i].value == value)){
      if (strcmp(questions[i].answer, answer) == 0) {
        questions[i].answered = true;
        return true;
      } else {
        return false;
      }
    }
  }
  return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value){
  // lookup the question and see if it's already been marked as answered
  for (int i = 0; i < NUM_QUESTIONS; i++){
    if ((strcmp(questions[i].category, category) == 0) && (questions[i].value == value)){
      if (questions[i].answered == true){
        return true;
      } else {
        return false;
      }
    }
  }

  printf("Question does not exists\n");
  return true;
}
