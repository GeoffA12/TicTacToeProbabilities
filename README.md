# TicTacToeProbabilities

This repository contains both implementations of a tic-tac-toe game program I developed in my free time. The Chp6 cpp file contains my original implementation of the tic-tac-toe game. In this source file, the user can either play a 1 or 2 player tic-tac-toe game. In the one-player mode, the user will play against the computer. 

The way in which I set up the computer in the Chp6 cpp file was to manually calculate all of the possible probabilities of the open spaces on the tic tac toe board. The computer would pick the space which gave it the best chance to win based on this logic. 

In the Chp7 cpp file, an implementation I borrowed from my C++ textbook was used. This approach takes a highly-similar approach based on functionality, but highly-different approach in methodology. For example, one big difference was that I used manual processing of probabilities to build the computer, while the textbook author suggested that readers use an array of probabilities, and always direct the computer to the highest probability. 
