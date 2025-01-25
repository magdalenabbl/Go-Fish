# 🎴 Go Fish Card Game Program

A simple C++ program simulating a card game between a player and the computer using a standard 52-card deck. Features include randomized deck shuffling, scoring, and winner declaration.



## Table of Contents

- [Features](#features)
- [How It Works](#how-it-works)
- [Example Gameplay](#example-gameplay)
- [How to Run](#how-to-run)
- [License](#license)

## Features

- Simulates a card game between a player and a computer.
- Randomized deck shuffling ensures varied gameplay.
- Compares card ranks and tracks scores.
- Declares the winner at the end of the game.
- Every time the Player has to confirm something he types '*'.
## How It Works

The game alternates between the Player's and Computer's turns:

1. Both draw cards from a shuffled deck.
2. They start asking each other for a card and if the other has he gives all of the cards of that kind.
3. The first phase of the game ends when the deck is empty, and the Players have collected all of their cards so that their hands are empty.
4. The second phase starts and the Player is first asking the Computer for a collection (he can't see his own cards).
5. When the Computer asks for a collection the Player can see his own cards and if he has that collection, he has to give it to the Computer.
6. The winner is the one who collect all of the cards if the other - 13 collections of 4 cards.

## Example Gameplay

### First phase 
Every time the Player gives a card to the Computer; collects 4 cards of one kind (collection); confirms end of the game, he types '*'.
- **Player asks the computer for A**: A
- **Computer has an A and gives the  A cards to the Player**
- **Player asks the computer for 10**: 10
- **Computer doesn't have a 10 and the Player draws a card from the deck (if it's not empty)**
- **Computer's turn starts and he asks for 4**: 4
- **Player has 4 cards and he confirms he is giving them to the Computer**: *
- ....

  
  After collecting all of their cards an the deck is empty they go to the second phase of the game.

### Second phase 
- **Player is first and asks the Computer for J without seeing his own cards**: J
- **Computer has an A and gives the  J cards to the Player**
- **When Computer doesn't have a card of the kind the Player asked for, The Computer's turn starts**
- 
  *The winner is who collect all of the other's collections .*
### Final Scores

- **Player**: 0
- **Computer**: 13 collections (max)
- 
  *Computer wins the game!*

## How to Run

1. Clone the repository:
   ```bash
   https://github.com/magdalenabbl/Go-Fish.git
   ```
   
---

# License

This project is licensed under the MIT License.

---

Copyright (c) [2025] [Magdalena Dicheva]

Permission is granted to use, copy, modify, and distribute this software for any purpose, with or without modification, provided the above copyright notice appears in all copies.




