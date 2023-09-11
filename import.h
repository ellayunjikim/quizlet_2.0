#pragma once

#define MAX_FLASHCARD_SETS 10

// Struct defining one word-def pair
typedef struct pair {
    char* word;
    char* definition;
} pair_t;

// Struct defining an individual flashcard set
typedef struct flashcard_set {
    pair_t flashcard_pairs[100];
    char* name;
} flashcard_set_t; 

// int ui_weclome(flashcard_set_t flashcard_sets[10], int set_counter);

int select_flashcard_set(flashcard_set_t flashcard_sets[10]);

int play_game(int set, flashcard_set_t flashcard_sets[10]);

int read_file_program(flashcard_set_t flashcard_sets[10], int set_counter);