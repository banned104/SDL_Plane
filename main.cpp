#include <iostream>
#include <memory>
#include "Game.hpp"

/*
* SDL2 要求 main 必须是 int main(int argc, char* argv[]) 这种签名
*/
int main(int argc, char* argv[]) {
    std::unique_ptr<Game> GameInstance = std::make_unique<Game>();
    GameInstance.get()->init();
    GameInstance.get()->RenderLoop();
    GameInstance->clean();
	return 0;
}

