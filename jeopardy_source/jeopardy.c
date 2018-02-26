/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2018, Clyve Widjaya 100590208
 *                     Fawwaz Khayyat 100568635
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens);

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(struct player *players);

bool game_state;

int main(int argc, char *argv[]){
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    struct player players[NUM_PLAYERS];
    int playerIndex = 0;
    int dollarValue;
    char *category = (char *) calloc(BUFFER_LEN, sizeof(char));
    char *playerName = (char *) calloc(BUFFER_LEN, sizeof(char));

    // Buffer for user input
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    initialize_game();

    // Prompt for players names
    for (int i = 0; i < NUM_PLAYERS; i++){
      printf("Player %i name: ", i+1);
      scanf("%s", playerName);
      if (!player_exists(players, NUM_PLAYERS, playerName)){
        strcpy(players[i].name, playerName);
      } else {
        printf("Name exists, enter new name!\n");
        i--;
      }
    }

    // initialize each of the players in the array
    for (int i = 0; i < NUM_PLAYERS; i++){
      players[i].score = 0;
    }

    // Perform an infinite loop getting command input from users until game ends
    game_state = true;
    int notAnswered = NUM_QUESTIONS;
    while (game_state){
      int count = 0;
      printf("\n");
      display_categories();

      printf("\n%s's turn to play!\n", players[playerIndex].name);
      printf("Enter category you want to answer > ");
      scanf("%s", category);
      printf("Enter dollar value you want > ");
      scanf("%i", &dollarValue);
      int c;
      while ((c = getchar()) != EOF && c != '\n');
      if (already_answered(category, dollarValue)){
        playerIndex--;
      } else {
        display_question(category, dollarValue);

        printf("Answer > ");
        fgets(buffer, BUFFER_LEN, stdin);

        char *token;

        tokenize(buffer, &token);

        if (valid_answer(category, dollarValue, token)){
          notAnswered--;
          update_score(players, NUM_PLAYERS, players[playerIndex].name, dollarValue);
          playerIndex--;
        } else {
          printf("Wrong answer, you suck\n");
        }
      }

      if (notAnswered == 0){
        show_results(players);
        game_state = false;
      }

      if (playerIndex != 4){
        playerIndex++;
      } else {
        playerIndex = 0;
      }

      //game_state = false;
    }
    return EXIT_SUCCESS;
}

void show_results(struct player *players){
  for (int i = 0; i < NUM_PLAYERS; i++){
    printf("Player %d, %s\n", i+1, players[i].name);
    printf("Score: %d\n\n", players[i].score);
  }
}

void tokenize(char *input, char **tokens){
  printf("|%s|\n", input);

  //printf("|%s,%s,%s|\n", &tokens[0], &tokens[1], &tokens[2]);
  const char delims[2] = " \n";
  char *tok;

  /* get the first token */
  tok = strtok(input, delims);
  int num_tokens = 1;

  /* Assuming the third word is the start of the answer */
  while(tok != NULL && num_tokens <=2){
    tok = strtok(NULL,delims);
    num_tokens++;
  }
  *tokens = tok;
}
