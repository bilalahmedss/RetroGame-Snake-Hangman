

# **Retro Gaming Reinvented**

## **Contributors**
- **Bilal Ahmed**
- **Ayesha Aimen**
- **Qazi Mustafa**
- **Simra Shamim**


## **Overview**
This repository contains the implementation of two classic games, **Snake** and **Hangman**, developed as part of the **Data Structures** course. The project incorporates key data structures like a **Doubly Linked List** for Snake and a **Trie** for Hangman. These data structures enhance the gameplay experience by ensuring efficient and dynamic game management.

## **Features**
- **Snake Game**: Utilizes a **Doubly Linked List** to manage the snake’s body dynamically, enabling constant-time movement and growth.
- **Hangman Game**: Implements a **Trie** data structure for fast word lookups and efficient guessing.
- **Graphics and Sound**: Uses **SDL** for handling images, sound files, and fonts to provide a rich user experience.
- **Interactive Console**: The games run in the console, providing a simple yet engaging gaming experience.

---

## **1. Snake**

### **Gameplay:**
- **Objective**: In **Snake**, control the snake to eat apples, grow longer, and avoid colliding with the walls or itself.
- **Player Controls**: Use **arrow keys** to move the snake in the desired direction.
- **Growth**: Each apple eaten causes the snake to grow in length, and the speed increases over time.

### **Data Structure:**
- **Doubly Linked List**: The snake’s body is represented using a **Doubly Linked List**, where each segment is a node. This allows efficient insertion, removal, and traversal of the snake’s body.
  
---

## **2. Hangman**

### **Gameplay:**
- **Objective**: In **Hangman**, guess the word by selecting letters. The game ends when the player guesses all letters correctly or the **hangman** is fully drawn.
- **Player Controls**: The player selects a letter to guess, and the game updates with correct or incorrect guesses.
- **Word Progress**: The word is displayed with underscores, showing the correctly guessed letters as they are revealed.

### **Data Structure:**
- **Trie**: A **Trie** is used to store and quickly retrieve words. This data structure enables fast searching and efficient word management, making the word-guessing process smooth and responsive.

---

## **Technologies Used:**
- **C++** for game logic and development.
- **SDL (Simple DirectMedia Layer)** for graphics rendering and user input handling.
- **Trie** for managing the word list in Hangman.
- **Doubly Linked List** for efficiently managing the snake's body in Snake.

---


## **Contributions:**
If you wish to contribute to this project, feel free to fork the repository and submit a pull request. Contributions are welcome, whether it’s by improving the code, adding new features, or suggesting improvements. 
