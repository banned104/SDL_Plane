#include <iostream>
#include <memory>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

void RenderLoop(SDL_Renderer* render);
void InitializeAxiliaries(SDL_Renderer* render);
void RenderImages(SDL_Renderer* render);
void DestroyAll(SDL_Renderer* render, SDL_Window* window);


SDL_Texture* texture;
Mix_Music* music;
TTF_Font* font;
SDL_Surface* textSurface;
SDL_Texture* textTexture;

enum GameState
{
	TITLE_SCREEN,
	PLAYING,
	PAUSED,
	GAME_OVER,
};

/*
* SDL2 要求 main 必须是 int main(int argc, char* argv[]) 这种签名
*/
int main(int argc, char* argv[]) {
	std::cout << "Hello plane" << std::endl;

	if ( SDL_Init( SDL_INIT_EVERYTHING ) != 0 ){
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	// 创建窗口
	SDL_Window* window = SDL_CreateWindow("Game Window", 200, 200, 800, 600, SDL_WINDOW_SHOWN);
	// 创建渲染器
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	// 加载其他库
	InitializeAxiliaries(renderer);

	RenderLoop( renderer );

	DestroyAll(renderer, window);
	return 0;
}


void InitializeAxiliaries(SDL_Renderer* render) {
	/*------------------------------------------------------------------------*/
	/* 初始化图像加载库 指定 JPG/PNG */
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) 
		!= (IMG_INIT_PNG | IMG_INIT_JPG)) 
	{
		std::cerr << "Img init failed" << IMG_GetError() << std::endl;
		return;
	}
	texture = IMG_LoadTexture(render, "assets/assets/image/bg.png");
	/*------------------------------------------------------------------------*/
	// 44100Hz CD音质; 音频格式默认; 声道数量 2 双声道立体声; 缓冲区大小 2048 Bytes;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cerr << "Mix_OpenAudio Init Error" << Mix_GetError() << std::endl;
		return;
	}
	music = Mix_LoadMUS("assets/assets/music/03_Racing_Through_Asteroids_Loop.ogg");
	// 第二个参数是循环次数 -1 表示无限循环
	Mix_PlayMusic(music, -1);
	/*------------------------------------------------------------------------*/
	if (TTF_Init() != 0) {
		std::cerr << "TTF Init Error" << TTF_GetError() << std::endl;
		return;
	}
	// F:\Codes\Games\SDL_Aircraft\assets\assets\font\VonwaonBitmap-16px.ttf
	font = TTF_OpenFont("assets/assets/font/VonwaonBitmap-16px.ttf", 24);
	SDL_Color color = { 0, 0, 255, 255 };
	textSurface = TTF_RenderUTF8_Solid(font, "Hello Niko, Hide, 高举双钳", color);
	textTexture = SDL_CreateTextureFromSurface(render, textSurface);
	/*------------------------------------------------------------------------*/
}

void DestroyAll( SDL_Renderer* render, SDL_Window* window ) {
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(render);
	// 结束
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}




void RenderLoop( SDL_Renderer* render ) {
	while (true) {
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) { std::cout<<"Quit!"<<std::endl; break; }
		}

		// 清屏
		SDL_RenderClear(render);
		// 绘图
		SDL_Rect rect = { 100, 100, 200, 200 };
		SDL_SetRenderDrawColor(render, 122, 20, 88, 255);
		SDL_RenderFillRect(render, &rect);
		SDL_SetRenderDrawColor(render, 255, 255, 255, 255);

		RenderImages(render);

		SDL_RenderPresent(render);
	}
	
}

void RenderImages( SDL_Renderer* render ) {
	//F:\Codes\Games\SDL_Aircraft\assets\assets\image\bg.png
	if( !texture ) { 
		std::cerr << "Load image failed " << std::endl;
	}
	SDL_Rect rect = { 200, 200, 200, 200 };
	SDL_RenderCopy(render, texture, NULL, &rect);
	SDL_Rect textRect = { 300, 300, textSurface->w, textSurface->h };
	SDL_RenderCopy(render, textTexture, NULL, &textRect);
}