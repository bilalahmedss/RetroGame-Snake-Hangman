#ifndef START_HPP
#define START_HPP
#include "hangman.h"
#include "snake.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <SDL_mixer.h>
#include "start.hpp"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int BUTTON_WIDTH = 133;
const int BUTTON_HEIGHT = 50;

class Main_Menu {
public:
    Main_Menu();
    ~Main_Menu();
    void run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;
    TTF_Font* font;
    SDL_Rect buttonSnake, buttonHangman;
    bool quit;
    Mix_Music* backgroundMusic;
    bool init();
    void handleEvents();
    void render();
    bool isInside(int x, int y, SDL_Rect rect);
    void renderText(const char* text, SDL_Color color, int x, int y);
};


#endif