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
#include "questions.h"

// Initializes the array of questions for the game
void initialize_game(void){
    // TODO: eventually could build this into a dynamic file parser or cli 
    char **qs[NUM_QUESTIONS][4] = {
        {"programming", "The Best Programming Language is ", "HTML", "100"},
        {"programming", "The best operating system is", "Mac OS"," 250"},
        {"programming", "CUDA is a software library offered by", "Nvidia","500"},
        {"programming", "The AMD Zen 4 processor line is called ", "Ryzen", "1000"},
        // 
        {"uoit", "The building that can replicate climate conditions is called", "ACE", "250"},
        {"uoit", "The building with the tim hortons is ", "UA", "500"},        
        {"uoit", "The best professor is ", "Khalid Hafeez", "750"},
        {"uoit", "The best program is ", "Software Engineering", "1000"},
        //
        {"python", "A powerful library in python used mainly to manipulate data structures", "numpy", "1000"},
        {"python", "A library used to communicate with serial devices", "pyserial", "1500"},
        {"python", "A library used for digital signal processing/fast forier transforms", "scipy", "2500"},
        {"python", "This library can be used for training and understanding large datasets", "Tensorflow", "4000"},
    };

    // initialize categories, questions, and values into the struct from the array above
    // TODO: future implement into file 
    for(int i=0; i < NUM_QUESTIONS; i++) {
        strcpy(questions[i].category, qs[i][0]); 
        strcpy(questions[i].question, qs[i][1]);
        strcpy(questions[i].answer, qs[i][2]);
        questions[i].value = atoi(qs[i][3]);
        questions[i].answered = false;

    }

}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
    
    // make it dynamic
    for(int i=0; i<NUM_CATEGORIES; i++) { 
        printf("\t%s\t|", categories[i]);
    }
    //
    int ratio = (int) NUM_QUESTIONS/NUM_CATEGORIES; 
    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    for (int i=0; i<ratio; i++) {
        for(int j=i; j<NUM_QUESTIONS; j+=4) {
            if(questions[j].answered == false) {
                printf("\t%i\t|",questions[j].value);
            } else {
                printf("\t%s\t","----");
            }
        }
        printf("\n");   
    }
    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");

}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
    for(int i=0; i < NUM_QUESTIONS; i++) {
        if(questions[i].category == category) {
            if(questions[i].value == value) {
                printf("Question: %s for $%d\n", questions[i].question, questions[i].value);
                break;
            }
        }
    }
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer) {
    for (int i=0; i < NUM_QUESTIONS; i++) {
        if(questions[i].category == category && questions[i].value == value) {
            if(strcmp(questions[i].answer, answer) == 0) { 
                return true;
            } else {
                // exit the loop, we found the question and they got it wrong
                break; 
            }
        }
    }
    // Look into string comparison functions
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value) {
    // lookup the question and see if it's already been marked as answered
    for(int i=0; i<NUM_QUESTIONS; i++) {
        if(questions[i].category == category && questions[i].value == value) {
            return questions[i].answered;
        }
    }
    return false;
}
