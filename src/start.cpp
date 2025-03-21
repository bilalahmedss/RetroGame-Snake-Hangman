#include "hangman.h"
#include "snake.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <SDL_mixer.h>
#include "start.hpp"

Main_Menu::Main_Menu() : window(nullptr), renderer(nullptr), backgroundTexture(nullptr), font(nullptr), backgroundMusic(nullptr) {
    int buttonWidth = BUTTON_WIDTH; // New width for buttons
    int buttonHeight = BUTTON_HEIGHT; // Keep your original button height
    int buttonYStartSnake = WINDOW_HEIGHT / 3;
    int buttonYStartHangman = WINDOW_HEIGHT / 2;
    int buttonXStart = 320; // Start buttons 340 pixels from the left

    buttonSnake = {buttonXStart, buttonYStartSnake, buttonWidth, buttonHeight};
    buttonHangman = {buttonXStart, buttonYStartHangman, buttonWidth, buttonHeight};
}

Main_Menu::~Main_Menu() {
    TTF_CloseFont(font);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

bool Main_Menu::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || IMG_Init(IMG_INIT_PNG) < 0 || TTF_Init() < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("DS2 Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    backgroundTexture = IMG_LoadTexture(renderer, "background.png");
    font = TTF_OpenFont("font.ttf", 24);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return false;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;//music implemented
            return false;
        }

        backgroundMusic = Mix_LoadMUS("game.mp3");
        if (!backgroundMusic) {
            std::cerr << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << std::endl;
            return false;
        }

        if (Mix_PlayMusic(backgroundMusic, -1) == -1) {
            std::cerr << "SDL_mixer could not play music! SDL_mixer Error: " << Mix_GetError() << std::endl;
            return false;
        }

        return true;
    }

void Main_Menu::run() {
    // Initialize and run the main menu loop
    if (!init()) {
        std::cerr << "Failed to initialize!" << std::endl;
        return;
    }

    quit = false;
    while (!quit) {
        handleEvents();
        render();
        }
    }   
void Main_Menu::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);

            if (isInside(x, y, buttonSnake)) {
                runSnakeGame();
                std::cout << "Returned from Snake Game" << std::endl;
            } else if (isInside(x, y, buttonHangman)) {
                runHangmanGame();
                std::cout << "Returned from Hangman Game" << std::endl;
            }
        }
    }
}

void Main_Menu::render() {
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Use black background
    SDL_RenderClear(renderer);

    // Draw background
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    // Draw buttons for Snake and Hangman
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red buttons
    SDL_RenderFillRect(renderer, &buttonSnake);
    SDL_RenderFillRect(renderer, &buttonHangman);

    // Text color
    SDL_Color textColor = {255, 255, 255, 255};

    // Draw text on buttons, adjusted to center the text on the buttons
    renderText("Snake", textColor, buttonSnake.x + BUTTON_WIDTH / 2 - strlen("Snake") * 6, buttonSnake.y + BUTTON_HEIGHT / 2 - 12);
    renderText("Hangman", textColor, buttonHangman.x + BUTTON_WIDTH / 2 - strlen("Hangman") * 6, buttonHangman.y + BUTTON_HEIGHT / 2 - 12);

    // Update screen
    SDL_RenderPresent(renderer);
}


bool Main_Menu::isInside(int x, int y, SDL_Rect rect) {
    return (x > rect.x) && (x < rect.x + rect.w) && (y > rect.y) && (y < rect.y + rect.h);
}

void Main_Menu::renderText(const char* text, SDL_Color color, int x, int y) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dstRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

int main(int argc, char* argv[]) {
    Main_Menu project;
    project.run();
    return 0;
}


// g++ -std=c++11 -o PROJECT start.cpp hangman.cpp snake.cpp doublylinkedlist.cpp trie.cpp -IC:/mingw_dev_lib/include/SDL2 -LC:/mingw_dev_lib/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer