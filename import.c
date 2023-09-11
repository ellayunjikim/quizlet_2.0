#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include "import.h"

// int ui_welcome(flashcard_set_t flashcard_sets[10], int set_counter) {
//    while (1) {
//     printf("Select an option by selecting the corresponding number:\n");
//     printf("1. Import a new flashcard text file\n");
//     printf("2. Select another flashcard set to play game\n");

// // Get the user entry number
//     char user_num[10];
//     fgets(user_num, 10, stdin);
//     int entry = atoi(user_num);

//     if (entry == 1) {
//         read_file_program(flashcard_sets, set_counter);
//     }
//     else if (entry == 2) {
//         select_flashcard_set(flashcard_sets);
//     }
//     else {
//         printf("You did not select a proper number. Try again.\n");
//     }
//    }
// }

// Function to select a flashcard set to play game of
int select_flashcard_set(flashcard_set_t flashcard_sets[10]) {
    printf("\e[1;34m"); // blue
    printf("Select the flashcard set you want to play from below by typing the corresponding number of the set:\n");
    printf("\e[0m");
    
    int i = 0;
    // Printing out the names of the flashcard sets available to play
    while (flashcard_sets[i].name != NULL) {
        printf("%d. %s\n", i+1, flashcard_sets[i].name);
        i++;
    }
    // Get the user entry number
    char user_entry[100];
    fgets(user_entry, 100, stdin);
    int entry = atoi(user_entry);
    return entry;
}

// This is the function to play game
int play_game(int set, flashcard_set_t flashcard_sets[10]) {
    int set_num = set;
    int point = 0;  
    char buffer[1000];
    char* entry = buffer;
    size_t entrysize = 100000;
    
    printf("\e[1;32m"); // Green
    printf("Starting game now!\n");
    printf("\e[0m");

    int i = 0;
   // int idx = 0;
    // int rand_range = 100;
    // int idxs[100];
    // int* idxs = malloc(100*sizeof(int));
    // bool signal = false;
    while (1) {
        // Random numbrr generator
      //  i =  1 + rand()/((RAND_MAX + 1u)/rand_range);
        // check if this random value already exists in array
        // int cou = 0;
        // while (idxs[cou] != NULL) {
        //     if (i == idxs[cou]) {
        //         // if this value already exists
        //         signal = true;
        //         break;
        //     }
        //     cou++;
        // }
        // idxs[cou] = i;
        
        // if (signal == true) {
        //     signal = false;
        //     continue;
      //  }
        // set i = randomvalue
           // Stop running when we reach the end of the flashcard pairs
        if (flashcard_sets[set_num-1].flashcard_pairs[i].word == NULL) {
            break;
        } 

        // if (flashcard_sets[set_num-1].flashcard_pairs[i].word == NULL) {
        //     // random num generator is too far oof so continue
        //     rand_range = i;
        //     continue;
        // }

        else {
            // store this index value in array
        }
        // if the number of eleemnts in array equals to ?
        printf("\e[1;34m");
        printf("Enter the correct word for the following definition:\n");
        printf("\e[0m");
        printf("\e[1;35m");
        // Print the definition of the word to guess
        printf("%s\n", flashcard_sets[set_num-1].flashcard_pairs[i].definition);
        printf("\e[0m");
        // Get the user input (and exclude newline by strtok)
        getline(&entry, &entrysize, stdin);
        strtok(entry, "\n");
        // If the entry is same as the word in the flashcard set
        if (strcmp(entry, flashcard_sets[set_num-1].flashcard_pairs[i].word) == 0) {
            printf("\e[1;32m");
            printf("Correct! You earned a point.\n");
            printf("\e[0m");
            // Add a point
            point++;
        }
        else {
            // If not same
            printf("\e[1;31m");
            // Incorrect and let them know what the correct word was
            printf("Incorrect! You typed in %s. The correct word is %s.\n", entry, flashcard_sets[set_num-1].flashcard_pairs[i].word);
            printf("\e[0m");
        }
        i++;
    }

    printf("\e[1;32m");
    // Print the number of words they got correct.
    printf("Game over. You got %d out of %d correct.\n", point, i);
    printf("\e[0m");
    
    // Return the number of questions you got correct
    return point;
}

// This function reads the file imported by user and adds them to the flashcard set
int read_file_program(flashcard_set_t flashcard_sets[10], int set_counter)
{
    int prev = 0;
    int choice_num = 0;
    // In a loop to accept file texts to import, unless user selects q
    while (1) {
    // Create a string to put path string in
    char path[200];
    int i = 0;
    
    printf("\e[1;32m");
    printf("----Welcome to the Flashcard Game!----\n");
    printf("\e[0m");
    printf("\e[1;34m");
    printf("Enter an absolute path to the text file. Type 'q' to quit: \n");
    printf("\e[0m");
   
    // Get input path
    fgets(path,200,stdin);

    // If the user quits, break out of loop
    if (strcmp(path, "q\n") == 0) {
        break;
    }

    // If user enters nothing
    if (strcmp(path, "\n") == 0) {
        printf("\033[0;31m");
        printf("You did not enter any path. Try again.\n");
        printf("\033[0m");
        continue;
    }

    // Remove newline from user input
    char* token = strtok(path, "\n");

    // If the length of the read path is less than 4 
    int len = strlen(token);
    if (len < 4) {
         printf("\033[0;31m");
        printf("Check your typing and file input. Try again. \n");
         printf("\033[0m");
        continue;
    }
    // If the last four characters of path read is not .txt
    const char *last_four = &token[len-4];
    if (strcmp(last_four,".txt") != 0) {
        printf("\033[0;31m");
        printf("You did not put in a txt file. Try again. \n");
        printf("\033[0m");
        continue;
    } 

    // Open this file to read
    FILE *fp = fopen(token, "r");
    if (fp == NULL){
        printf("\033[0;31m");
        printf("Error opening file. Try again. \n");
        printf("\033[0m");
        continue;
    }

    // If there was no error
    char* line = NULL;
    size_t line_size = 0;
    // Counter to delegate into word of pair or definition of pair
    int counter = 0;

    pair_t pairs[100];

    if (fp != NULL) {
        // Until we reach end of file
        while (getline(&line, &line_size, fp) != -1) {
            // If counter is at even number
            if (counter%2 == 0) {
                // Store into the word of pair
                line = strtok(line, "\n");
                pairs[i].word = strdup(line);
             //   printf("Adding word: ");
             //  puts(pairs[i].word);
            }
            else {
                // If counter is at odd number
                line = strtok(line, "\n");
                // Store into the definition of pair
                pairs[i].definition = strdup(line);
            //    printf("Adding definition: ");
             //   puts(pairs[i].definition);
                // Increment pair counter
                i++;
            }
            // Increment counter of word-def
            counter++;
        }
    }

    // If previous flashcard set was larger
    if (prev > counter) {
        // Get rid of the pairs from previous flashcard set
        int remove = (prev/2)- (counter/2);
        printf("remove %d\n", remove);
        for (int i = 0 ; i < remove; i++) {
            pairs[(counter/2)].definition = NULL;
            pairs[(counter/2)].word = NULL;
        }
    }

    prev = counter;
    printf("\e[1;34m");
    printf("Finished adding flashcard set!\n");
    
    // Add these pairs to the flashcard set
    memcpy(flashcard_sets[set_counter].flashcard_pairs, pairs, sizeof(pairs));
    // Ask the user to name the flashcard set
    printf("Name this flashcard set: \n");
    printf("\e[0m");
    char* name = NULL;
    size_t namesize;
    // Get the user name from stdin excluding newline
    getline(&name, &namesize, stdin);
    char* token2 = NULL;
    token2 = strtok(name, "\n");
    // Store the name into the name of the flashcard_sets struct
    flashcard_sets[set_counter].name = strdup(token2); 
    
    printf("\e[1;34m");
    printf("You successfully named and stored your flashcard set '%s'\n", flashcard_sets[set_counter].name);
    printf("\e[0m");
    // Increment set counter for next flashcard set place in array
    set_counter++;

    fclose(fp);
   }

   return set_counter;
}

