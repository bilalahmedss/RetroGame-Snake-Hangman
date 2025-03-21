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
#include "hangman.hpp"
#include "hangman.h"


Hangman::Hangman() {
    if (!initSDL()) {
        std::cerr << "Failed to initialize SDL.\n";
        exit(-1);
    }
    initializeGame();
}

Hangman::~Hangman() {
    closeSDL();
}

void Hangman::run() {
    gameLoop();
}

bool Hangman::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << '\n';
        return false;
    }
    window = SDL_CreateWindow("Hangman Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << '\n';
        return false;
    }
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << '\n';
        return false;
    }
    font = TTF_OpenFont("font.ttf", 28);
    if (!font) {
        std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << '\n';
        return false;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Set background color to white
    return true;
}

void Hangman::closeSDL() {
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void Hangman::gameLoop() {
    SDL_Event e;
    bool guessMade = false;

    while (!gameOver && incorrectGuesses < maxGuesses) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                gameOver = true;
            } else {
                guessMade = handleInput(e);
                if (guessMade) {
                    renderGame();
                    std::cout << "Word to guess: " << guessedWord << std::endl;
                    std::cout << "Mistakes left: " << maxGuesses - incorrectGuesses << std::endl;
                    guessMade = false;  // Reset the flag after updating
                }
            }
        }
    }

    if (incorrectGuesses >= maxGuesses) {
        std::cout << "Game Over! The correct word was: " << selectedWord << std::endl;
        SDL_Texture* gameOverTexture = loadTexture("game_over.png");
        SDL_Rect renderQuad = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(renderer, gameOverTexture, nullptr, &renderQuad);
        SDL_RenderPresent(renderer);
        SDL_Delay(3000);  // Display the game over screen for 3 seconds
    }
}

void Hangman::renderGame() {
    SDL_RenderClear(renderer);
    updateHangmanState();
    SDL_RenderPresent(renderer);
}

SDL_Texture* Hangman::loadTexture(std::string path) {
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << '\n';
        return nullptr;
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

void Hangman::updateHangmanState() {
    SDL_Texture* currentTexture = nullptr;
    switch (incorrectGuesses) {
        case 0:
            currentTexture = loadTexture("start.png");
            break;
        case 1:
            currentTexture = loadTexture("wrong_1.png");
            break;
        case 2:
            currentTexture = loadTexture("wrong_2.png");
            break;
        case 3:
            currentTexture = loadTexture("wrong_3.png");
            break;
        case 4:
            currentTexture = loadTexture("wrong_4.png");
            break;
        case 5:
            currentTexture = loadTexture("wrong_5.png");
            break;
        case 6:
            currentTexture = loadTexture("wrong_6.png");
            break;
        default:
            currentTexture = loadTexture("game_over.png");
            gameOver = true;
            break;
    }
    if (currentTexture) {
        SDL_Rect renderQuad = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(renderer, currentTexture, nullptr, &renderQuad);
        SDL_DestroyTexture(currentTexture); // Free texture after use
    }
}
void Hangman::checkGuess(char guess) {
    if (guessedLetters.find(guess) != guessedLetters.end()) {
        std::cout << "You have already guessed the letter '" << guess << "'. Try a different one!" << std::endl;
        return;  // If the letter has already been guessed, do nothing further
    }

    guessedLetters.insert(guess);  // Add the guessed letter to the set

    bool found = false;
    for (size_t i = 0; i < selectedWord.length(); i++) {
        if (selectedWord[i] == guess && guessedWord[i] == '*') {
            guessedWord[i] = guess;
            found = true;
        }
    }

    if (!found && selectedWord.find(guess) == std::string::npos) {
        incorrectGuesses++;
    }

    if (guessedWord == selectedWord) {
        gameOver = true;
        std::cout << "Congratulations! You've won! The word was: " << selectedWord << std::endl;
        SDL_Texture* winTexture = loadTexture("won.png");
        SDL_Rect renderQuad = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(renderer, winTexture, nullptr, &renderQuad);
        SDL_RenderPresent(renderer);
        SDL_Delay(3000);  // Display the win screen for 3 seconds
    }
}
void Hangman::initializeGame() {
    wordsTrie.insert("ability");
    wordsTrie.insert("absurd");
    wordsTrie.insert("zombie");
    selectedWord = selectRandomWordFromTrie();  // Select a random word from the trie
    guessedWord = std::string(selectedWord.length(), '*');
    incorrectGuesses = 0;
    gameOver = false;
    std::cout << "Word to guess: " << guessedWord << std::endl;
    std::cout << "Mistakes left: " << maxGuesses - incorrectGuesses << std::endl;
    renderGame(); // Render initial game state
}

std::string Hangman::selectRandomWordFromTrie() {
    return wordsTrie.getRandomWord();
}

bool Hangman::handleInput(SDL_Event& e) {
    // Handle window close event
    if (e.type == SDL_QUIT) {
        gameOver = true;  // Use 'gameOver' to exit the game loop
        std::cout << "Window close requested. Exiting game loop." << std::endl;
        return true;
    }

    // Handle key press event
    if (e.type == SDL_KEYDOWN && !gameOver) {  
        char guess = static_cast<char>(tolower(e.key.keysym.sym));
        if (isalpha(guess)) {
            checkGuess(guess);
            return true;
        }
    }
    return false;
}


void runHangmanGame(){
    Hangman game;  // Create an instance of the Hangman game
    game.run();    // Run the game
}

//g++ -std=c++11 -o hangman hangman.cpp trie.cpp -IC:/mingw_dev_lib/include/SDL2 -LC:/mingw_dev_lib/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
