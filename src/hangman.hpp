#ifndef HANGMAN_HPP
#define HANGMAN_HPP
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <SDL_main.h>  
#include <set>
#include "trie.h"


const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 1000;

class Hangman {
public:
    Hangman();
    ~Hangman();
    void run();

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    TTF_Font* font = nullptr;
    Trie wordsTrie;  // Using Trie to store words
    std::string selectedWord;
    std::string guessedWord;
    std::set<char> guessedLetters;
    int incorrectGuesses = 0;
    int maxGuesses = 6;
    bool gameOver = false;

    bool initSDL();
    void closeSDL();
    void gameLoop();
    void renderGame();
    void loadMedia();
    SDL_Texture* loadTexture(std::string path);
    void updateHangmanState();
    void checkGuess(char guess);
    bool handleInput(SDL_Event& e);
    void initializeGame();
    std::string selectRandomWordFromTrie(); 
};

#endif 