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
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens, int count);

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(struct player *players);

bool game_state;

int main(int argc, char *argv[]){
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    struct player players[NUM_PLAYERS];
    int playerIndex = 0;
    int dollarValue;
    char *category = (char *) calloc(BUFFER_LEN, sizeof(char));
    // // EXAMPLE: player 1 is named Fred
    // strcpy(players[0].name, "Fred");
    // printf("%s\n", players[0].name);

    // Buffer for user input
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    initialize_game();

    // Prompt for players names
    for (int i = 0; i < NUM_PLAYERS; i++){
      printf("Player %i name: ", i+1);
      scanf("%s", players[i].name);
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
        // EXAMPLE: This line gets a line of input from the user
    //     fgets(buffer, BUFFER_LEN, stdin);
    //     printf("[before]%s[after]", buffer);
    //
		// if (strcmp(buffer, "hello\n") == 0) printf(":)\n");
		// if (strcmp(buffer, "world\n") == 0) printf(":)\n");
      display_categories();

      printf("\n%s's turn to play!\n", players[playerIndex].name);
      printf("Enter category you want to answer > ");
      scanf("%s", category);
      printf("Enter dollar value you want > ");
      scanf("%i", &dollarValue);
      int c;
      while ((c = getchar()) != EOF && c != '\n');
      // printf("|%s|\n",category);
      // printf("|%i|\n", dollarValue);
      if (already_answered(category, dollarValue)){
        playerIndex--;
      } else {
        display_question(category, dollarValue);

        printf("Answer > ");
        fgets(buffer, BUFFER_LEN, stdin);
        for(int i = 0; i < BUFFER_LEN; i++){
            if (buffer[i] == '\n'){
                buffer[i] = ' ';
            }
            else if (buffer[i] == ' ' && buffer[i+1] != ' '){
                count++;
            }
        }
        count++;
        /*
        char *token[count][BUFFER_LEN];
        token[0] = "coba";
        token[1] = "coba2";
        token[2] = "coba3";
        */
        char *token;
        
        //printf("passd\n");
        tokenize(buffer, &token, count);

        //printf("Check token: |%s,%s,%s|\n", *token[0], *token[1], *token[2]);

        //printf("count: %i token2: |%s|\n",count, *token[0]);
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

void tokenize(char *input, char **tokens, int count){
  printf("|%s|\n", input);

  //printf("|%s,%s,%s|\n", &tokens[0], &tokens[1], &tokens[2]);
  const char delims[2] = " ";
  char *tok;

  /* get the first token */
  tok = strtok(input, delims);
  int num_tokens = 1;

  /* Assuming the third word is the start of the answer */
  while(tok != NULL && num_tokens <=2){
    //strcpy(tokens[index], tok);
    //printf("index:%i |%s|\n", tok);
    tok = strtok(NULL,delims);
    num_tokens++;
  }
  *tokens = tok;
  //printf("|%s,%s,%s|\n", tokens[0], tokens[1], tokens[2]);
}
