/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
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
void tokenize(char *input, char **tokens) {
	char *first = strtok(input, " ");
	first = strtok(input, " ");
	for (index = 0; first != NULL; index++) {
		strcpy(tokens[index], first);
		first = strtok(NULL, " ");
	}
}

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players);
	


int main(int argc, char *argv[])
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];
    
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    initialize_game();

    // Prompt for players names AND initialize each of the players in the array
	printf("JEOPARDY GAME!\n");
	printf("Enter Player 1 Name: ");
	scanf("%s", players[0].name);
	printf("Enter Player 2 Name: ");
	scanf("%s", players[1].name);
	printf("Enter Player 3 Name: ");
	scanf("%s", players[2].name);
	printf("Enter Player 4 Name: ");
	scanf("%s", players[3].name);
    

    // Perform an infinite loop getting command input from users until game ends
    //while (fgets(buffer, BUFFER_LEN, stdin) != NULL)

	//Start with 0 for player 0 in the players array
	int play = 0;
	//Holds true or false depending on if question was answered right
	bool checker;
	//Checks the global variable NUM_QUESTIONS to see if there are still more unanswered questions
	while (NUM_QUESTIONS > 0)
    {
		//Goes back to the first player after all players have a turn, loops
		if (play == 3) {
			play = 0
		}
		//Will show the categories to the player to chose from (global function)
		display_categories();


		printf(("%s's Turn. Chose a Category: \n", players[play].name);)
		scanf("%s", category);

		printf(("Chose a value: \n")
		scanf("%d", value);

		//Check globalfunction to see if that specific question was already chosen before
		if (already_answered(category, value)) {
			printf("That question has been answered. Please chose a different question. ");
			play--;
		}
		printf("\n");

		else {
			//Use global function to show the corresponding question
			display_question(category, value);
			printf("Enter your Answer: \n ");
			scanf("%s", response);
			//Takes out the phrasing from the answer taken
			tokenize(response, token);
			//use function to check if the player's answer is right
			checker = valid_answer(category, value, token[2]);

			if (checker) {
				printf("Your answer is correct. \n");
				//Add the questions's value to that player object's score variable
				players[play].score += value;
			}
			else {
				printf("Your answer is wrong. \n");
			}
			
			//Decrease number of questions left
			NUM_QUESTIONS--;
		}
			//Increment to go the next player's turn
			play++;

        // Execute the game until all questions are answered

        
    }
	// Display the final results and exit
	show_results(players,4);

    return EXIT_SUCCESS;
}
