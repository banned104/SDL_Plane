#include <iostream>
#include <memory>

#include "SDL.h"
#include "SDL_image.h"

void RenderLoop(SDL_Renderer* render);
void InitializeAxiliaries(SDL_Renderer* render);
void RenderImages(SDL_Renderer* render);
void DestroyAll(SDL_Renderer* render, SDL_Window* window);


SDL_Texture* texture;


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
	/* 初始化图像加载库 指定 JPG/PNG */
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) 
		!= (IMG_INIT_PNG | IMG_INIT_JPG)) 
	{
		std::cerr << "Img init failed" << IMG_GetError() << std::endl;
		return;
	}

	texture = IMG_LoadTexture(render, "assets/assets/image/bg.png");

}

void DestroyAll( SDL_Renderer* render, SDL_Window* window ) {
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(render);
	// 结束
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
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
	
}