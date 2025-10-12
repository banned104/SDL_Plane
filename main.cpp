#include <iostream>
#include "SDL.h"
#include <memory>
void RenderLoop(SDL_Renderer* render);

/*
* SDL2 Ҫ�� main ������ int main(int argc, char* argv[]) ����ǩ��
*/
int main(int argc, char* argv[]) {
	std::cout << "Hello plane" << std::endl;

	if ( SDL_Init( SDL_INIT_EVERYTHING ) != 0 ){
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	// ��������
	
	SDL_Window* window = SDL_CreateWindow("Game Window", 200, 200, 800, 600, SDL_WINDOW_SHOWN);
	// ������Ⱦ��
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	RenderLoop( renderer );

	// ����
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

void RenderLoop( SDL_Renderer* render ) {
	while (true) {
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) { std::cout<<"Quit!"<<std::endl; break; }
		}

		// ����
		SDL_RenderClear(render);
		// ��ͼ
		SDL_Rect rect = { 100, 100, 200, 200 };
		SDL_SetRenderDrawColor(render, 122, 20, 88, 255);
		SDL_RenderFillRect(render, &rect);
		SDL_SetRenderDrawColor(render, 255, 255, 255, 255);

		SDL_RenderPresent(render);
	}
	SDL_DestroyRenderer(render);
}