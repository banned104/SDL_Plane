#ifndef GAME_H
#define GAME_H
#include <memory>
#include <iostream>
#include "SDL.h"
#include "Scene.hpp"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

enum GameState
{
	TITLE_SCREEN,
	PLAYING,
	PAUSED,
	GAME_OVER,
};

class Game {
public:
    Game();
    ~Game();
    void run();
    void init();
    void clean();
    void changeScreen(Scene* scene);
    void RenderLoop();
    void InitializeAxiliaries(SDL_Renderer* render);
    void RenderImages(SDL_Renderer* render);
    void DestroyAll(SDL_Renderer* render, SDL_Window* window);


private:
    bool isRunning = true;
     Scene* currentScene = nullptr; 
    //std::unique_ptr<Scene> currentScene;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    Mix_Music* music;
    TTF_Font* font;
    SDL_Surface* textSurface;
    SDL_Texture* textTexture;
};

#endif