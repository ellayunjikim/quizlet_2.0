#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "message.h"
#include "socket.h"
#include "import.h"


// global flshcard set for client
flashcard_set_t client_flashcard_sets[MAX_FLASHCARD_SETS];
int client_set_counter = 0;

// Here on the client side, it will call the receive_message functions (twice each iteration for word-def pairs)
// which will then store into its corresponding flashcard set 

int main(int argc, char** argv) {
  if (argc != 3) {
    printf("\e[1;31m");
    fprintf(stderr, "Usage: %s <server name> <port>\n", argv[0]);
    exit(EXIT_FAILURE);
    printf("\e[0m");
  }

  // Read command line arguments
  char* server_name = argv[1];
  unsigned short port = atoi(argv[2]);

  // Connect to the server
  int socket_fd = socket_connect(server_name, port);
  if (socket_fd == -1) {
    printf("\e[1;31m");
    perror("Failed to connect");
    printf("\e[0m");
    exit(EXIT_FAILURE);
  }

size_t size = 0;
int i = 0;
pair_t pairs[100];

while(true){
  char* definition = NULL;
  char* word = NULL;
  // Receive definition from the server
  definition = receive_message(socket_fd);
  // If the message is "done"
  if (strcmp(definition, "done") == 0) {
    // Stop receiving messages
    break;
  }
  // Receive word from the server
  word = receive_message(socket_fd);

  // Store the word and definitions into the flashcard set
  pairs[i].word = strdup(word);
  pairs[i].definition = strdup(definition);
  i++; // increment pairs counter

 // Free the message
  free(definition);
  free(word);
}

  // Copy the pairs that we just received and stored messages of into the client_flashcard_sets global array
  memcpy(client_flashcard_sets[client_set_counter].flashcard_pairs, pairs, 100);
  // Begin playing that game of that flashcard set
  int points = play_game(client_set_counter+1, client_flashcard_sets);
 //  send_message(socket_fd, points);
  client_set_counter++;
  // Close socket
  close(socket_fd);

  return 0;
}
