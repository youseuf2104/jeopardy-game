/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, 
 *  Eric Whalls
 *  Yusuf Shaik
 *  Youseuf Molla
 *  Sarthak Sharma
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

// Colors:
#define COL_GRN "\x1B[32;1m" // Success colour
#define COL_RED "\x1B[31;1m" // Error colour
#define COL_DEF "\x1B[0m"    // Reset all attributes

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens);

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players);


int main(int argc, char *argv[])
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];
    int current_player = 0;
    
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    initialize_game();

    // setup a question counter
    int q_count = sizeof(questions);
    // setup a category and value of the category tracker

    // Prompt for players names
    printf(COL_GRN "Welcome to jeopardy!\n" COL_DEF); 

    // initialize each of the players in the array (as well)
    for(int i=0; i < NUM_PLAYERS; i++) { 
        printf("Enter player %d's name:\n", i+1);
        scanf("%s", players[i].name);
        players[i].score = 0;
    }

    //printf("Press any key to continue...");
    // Perform an infinite loop getting command input from users until game ends
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL) {
        // Call functions from the questions and players source files
        
        char *category = (char *) calloc(BUFFER_LEN, sizeof(char));
        // ensure we dont mismatch answer/tokenization data types 
        char *qanswer = (char *) calloc(BUFFER_LEN, sizeof(char));
        char **token[4][BUFFER_LEN] = {{0}};

        int value;
        // Execute the game until all questions are answered
        if(q_count > 0) {
            // check if we went above num players
            if(current_player > NUM_PLAYERS-1) {
                current_player = 0; 
            }

            // Show the players the question count
            display_categories();

            // Prompt Player
            printf(COL_GRN "It's %s's turn!\n" COL_DEF, players[current_player].name);
            printf("Choose your Category:\n");
            scanf("%s", category);
            printf("What amount are you playing for?\n");
            scanf("%d", &value);

            printf(COL_GRN "You have chosen %s for $%d!\n" COL_DEF, category, value);
            //

            if(already_answered(category, value)) {
                printf(COL_RED "The question was already answered :(\n" COL_DEF);
                // Give them another shot:
                current_player--;
            } else {
                display_question(category, value); 
                printf("What is your answer, %s?\n", players[current_player].name);
                // Get the answer
                getchar();
                scanf("%19[^\n]", qanswer);
                //
                printf("\n");
                printf("You said: %s\n", qanswer);
                //
                tokenize(qanswer, token);
                printf("Tokens: %s %s %s\n", &token[0], &token[1], &token[2]);
                // note you must enter who is or what is (requirement 7) in the answer
                if(valid_answer(category, value, token[2])) {
                    printf(COL_GRN "%s is correct!\n" COL_DEF "You've earned $%d!\n\n", players[current_player].name, value);
                    players[current_player].score += value;
                } else {
                    printf(COL_RED "Sorry, %s. You are incorrect :(\n\n" COL_DEF, players[current_player].name);
                }
            }
            // decrement the question count
            q_count--; 
            // next player
            current_player++; 
        } else {
            // End the game
            printf(COL_GRN "Thank you for playing! You have finished a round!\n" COL_DEF);
            // Display the final results and exit
            show_results(players, 4); 
            break; 
        }
    }
    return EXIT_SUCCESS;
}

// basically a string splitting method by spaces and stores to a pointer
// from http://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
void tokenize(char *input, char **tokens) {
	char *key1 = strtok(input, " ");

    for (int i = 0; key1 != NULL; i++) {
		strcpy(tokens[i], key1);
		key1 = strtok(NULL, " ");
	}
}

void show_results(player *players, int num_players) {
    printf(COL_RED "Congratulations!\n" COL_DEF);
	for(int i=0; i< num_players; i++) { 
		printf(COL_RED"Player: " COL_DEF " %s\t" COL_RED "Prize: " COL_GRN "$%d\n" COL_DEF, players[i].name, players[i].score);
	}
}