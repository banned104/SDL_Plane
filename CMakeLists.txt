cmake_minimum_required(VERSION 3.5.0)
project( SDL_Plane VERSION 1.0.0 LANGUAGES C CXX )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 指定 SDL2 SDL2Config.cmake 所在目录
set( SDL2_DIR "${CMAKE_SOURCE_DIR}/libs/SDL2/cmake" )
# 查找并导入SDL2
find_package( SDL2 CONFIG REQUIRED )


add_executable( SDL_Plane 
	main.cpp 

)

# 链接SDL2 库到主程序中
target_link_libraries( SDL_Plane
	SDL2::SDL2
	SDL2::SDL2main
)