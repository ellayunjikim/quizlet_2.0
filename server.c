#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>

#include "message.h"
#include "socket.h"
#include "import.h"

#define clients_num 10 // Maximum number of clients to accept
int client_array[clients_num]; // Array of clients
pthread_t client_threads[clients_num]; // Thread for clients running 
flashcard_set_t flashcard_sets[MAX_FLASHCARD_SETS]; // The server flashcard sets array

// Struct that holds information needed for thread 
typedef struct info
{
    int setnum;
    int client_fd;
    flashcard_set_t flashcard_sets[10];
    int server_fd;
    int score;
} info_t;

// Send from server to the client the flashcard definition and word pairs
// until we reach end of the flashcard set
void *sendFlashcards(void *arg)
{
    // Get the needed information from argument passed in
    info_t *info = (info_t *)arg;
    int set_num = info->setnum;
    int client_socket_fd = info->client_fd;

    printf("\e[1;34m"); // blue 
    printf("[Alert: Player requested to join this flashcard game. Accepting player now.]\n");
    int i = 0;
    printf("\e[0m");

    while (1)
    {
        // If the next pair is null (no more words/definition pairs)
        if (flashcard_sets[set_num - 1].flashcard_pairs[i].word == NULL)
        {
            // Send the message to the client socket that it's done
        //   send_message(client_socket_fd, "score");
            send_message(client_socket_fd, "done");
            break;
        }
        // Send the word and definition to the client
        send_message(client_socket_fd, flashcard_sets[set_num - 1].flashcard_pairs[i].definition);
        send_message(client_socket_fd, flashcard_sets[set_num - 1].flashcard_pairs[i].word);
        i++;
    }


    return NULL;
}

// Run in the background to read the word "stop" in standard input
void *readStop(void *arg) {
    info_t *info = (info_t *)arg;
    int server_socket_fd = info->server_fd;
    int set_num = info->setnum;
    
    char buffer[100]; // Buffer reading the word stop
    // Wait for a client to connect
    while (1)
    {   
        // Get stdin word if typed
        fgets(buffer, 100, stdin);
        // If the word is "stop"
        if (strcmp(buffer, "stop\n") == 0) {
            printf("\e[1;34m"); // blue
            // Stop accepting clients
            printf("Stopping to accept clients...\n");
            printf("\e[0m");
            break;
        }
    }

    // Begin playing game
    play_game(set_num,flashcard_sets);
    
    // create a thread here and look for points that is sent message of to the server and display it on the leaderboard
    
    close(server_socket_fd);
    printf("\e[0m");

    return NULL;
}

// Run in the background to see if the client has finished game and 
// receive score from client
void *getClientScore(void *arg) {
    info_t *info = (info_t *) arg;
    int client_socket_fd = info->server_fd;
    int score = info->setnum;

    while (1) {
        char* score = NULL;
        score = receive_message(client_socket_fd);
        if (strcmp(score, "done") == 0) {
        }
    }
}


int main()
{
    info_t info;
    int set_counter = 0;

    while (1) {
    printf("\e[1;32m");
    printf("Start Flashcard Game? Enter corresponding number:\n 1. Y\n 2. N\n");
     printf("\e[0m");
     char user_num[10];
    fgets(user_num, 10, stdin);
    int entry = atoi(user_num);

    if (entry == 2) {
        printf("Quitting game...\n");
        break;
     }
    
    // Call the function to import text file from user that will be input into the flashcard set pairs
    int c = read_file_program(flashcard_sets, set_counter);
    // set the set counter to the server's flashcard set updated set counter
    set_counter = c;
    // Call the function to select a specific flashcard set that the server user wants to play the game of.
    int set_num = select_flashcard_set(flashcard_sets);
    
    // store set_num selected by the user into the info struct (for thread)
    info.setnum = set_num;

    // Open a server socket
    unsigned short port = 0;
    int server_socket_fd = server_socket_open(&port);
    if (server_socket_fd == -1)
    {
        printf("\e[41m"); //red
        perror("Server socket was not opened");
        exit(EXIT_FAILURE);
        printf("\e[0m");
    }

    // Start listening for connections
    if (listen(server_socket_fd, 1))
    {
        printf("\e[41m"); //red
        perror("listen failed");
        exit(EXIT_FAILURE);
        printf("\e[0m");
    }

    printf("\e[1;34m"); // blue
    printf("Server listening on port %u\n", port);

    // Thread for server, to read 'stop' when user types it in
    pthread_t server_thread;
    // Store server fd in info struct
    info.server_fd = server_socket_fd;
    int idx = 0;

    printf("Type 'stop' if you would like to stop other clients from playing this game.\n");
    printf("\e[0m");
    // Create a thread running in the background to read the "stop" input from user
    pthread_create(&server_thread, NULL, readStop,(void *)&info);

    while (1) {
        // Accept new client connecting to the server
        int client_socket_fd = server_socket_accept(server_socket_fd);
        if (client_socket_fd == -1) // if server closed or is not valid
        {
            break; 
        }
        // Store the new client into the array
        client_array[idx] = client_socket_fd;
        info.client_fd = client_array[idx];
        // Create a thread running in the background to send to the client the flashcard set to play
        pthread_create(&client_threads[idx], NULL, sendFlashcards, (void *)&info);
        idx++;
    }

    printf("\e[0m");
    }

 
    return 0;
}
