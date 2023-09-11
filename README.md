<h1 align="center">Grinnell Quizlet 2.0:The Flashcard Game</h1>
<h3>Authors: Ella Kim, Caitlin Abreu</h3>
<h3>Date: May 16th, 2022</h3>
<h4>Acknowledgements: Code for `message.c` is from OS and Parallel Computing course Class Exercise: Networking</h4>

<br>
<p><h2>Getting Started</h2>
- Download all the files in this project, and put into the same directory. 
</p>
<p>
<h2>Text file Formatting</h2>
<h4>
- This flashcard game runs by importing your text file that contains words and definitions. <br>
- It should be formatted by each word and definition on separate new lines. Check the `test1.txt` file in this project for a sample of how these text files should be formatted. <br>
- Start with typing the word, then on a new line, type the corresponding definition. <br>
</p>
<p>
<h2>General Instructions</h2>

<h3>Server</h3>
<h4>
<b>This is how to run from the server side. Server is the host / user who can input text files and begin a multiplayer game. </b><br>
1. Open terminal and type `make`. <br>
2. Start the server by typing `./server`. <br>
3. Input path to the text file that you want to import to this game. <br>
4. Name the flashcard set when prompted. <br>
5. If you want to import another text file, repeat starting from #3. <br>
6. If you want to stop importing text file, type 'q' and enter. <br>
7. After you type 'q', you will be shown a list of your flashcard sets. Select the flashcard set you want to play a game of, by typing the corresponding number that is shown on the terminal. <br>
8. The server will open up to listen for connections from other users. <br>
9. Type "stop" and enter to stop accepting clients and begin to play game. <br>
10. You'll be shown a definition to enter the correct word for. <br>
11. Type in the word of your guess and the terminal will show if you got it correct or incorrect. <br>
12. #10 and #11 is repeated until the end of the flashcard set, and you will be shown the number of questions you got correct out of the total, and the program finishes. <br>
(Note that if you finish the game before 100 seconds, the program may not immediately exit.)
</h4>
</p>
<p>
<h3>Client</h3>
<h4>
<b>This is how to run from the client side. Client can connect to an open server to play a game.</b>
<br>
1. Start the client by typing `./client [name of machine to connnect to] [the port number of the server]` <br>
2. If the server is valid and you connect, you will be doing the same as the above #10-#12. </br>
</h4>
</p>

<h2>Specific Example</h2>
<p>
1. Follow the 'General Instructions' above up to #3. For #3, type `test1.txt` when prompted to input path name. <br>
2. Name the file "OS" and press enter. <br>
3. Type 'q' and press enter. <br>
4. You should be shown "1. OS" on the terminal. Type '1' and press enter. <br>
5. The server should open with a port number to listen to connections. <br>
6. Open a new terminal and type: "./client localhost [port number of the server]" and press enter. <br>
7. You should be shown "Starting game now..." on this new terminal of the client and be able to play the game. <br>
8. You should also be shown "Alert: Player requested to join this flashcard game. Accepting player now." on the server terminal when the client joins.  <br>
9. Back on the server terminal, type "stop" and press enter. <br>
10. This should now also show "Starting game now..." on the server side and be able to play the game. <br>
11. Type in your word guesses until you reach the end of the game. For the client side, after you reach the end of the game, it should immediately return. For the server terminal, it may not exit the terminal when you reach the end of the game. It may also quit during the game if you exceed 100 seconds after the game starts. If you want to exit the server terminal, you can do Ctrl+C to terminate. This will not affect the clients' ability to continue playing the game. <br>
</p>