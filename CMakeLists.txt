cmake_minimum_required(VERSION 3.5.0)
project( SDL_Plane VERSION 1.0.0 LANGUAGES C CXX )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TARGET SDL_Plane)
set( SDL2_LIBRARIES SDL2::SDL2 SDL2::SDL2::SDL2main )

# 指定 SDL2 SDL2Config.cmake 所在目录
set( SDL2_DIR "${CMAKE_SOURCE_DIR}/libs/SDL2/cmake" )
# 查找并导入SDL2
find_package( SDL2 CONFIG REQUIRED )


add_executable( ${TARGET}
	main.cpp 

)

# 指定 SDL2_image 配置文件所在目录
set(SDL2_image_DIR "${CMAKE_SOURCE_DIR}/libs/SDL2/cmake")
set(SDL2_mixer_DIR "${CMAKE_SOURCE_DIR}/libs/SDL2/cmake")
set(SDL2_ttf_DIR "${CMAKE_SOURCE_DIR}/libs/SDL2/cmake")

# 查找并载入Cmake预设
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

# 链接SDL2 库到主程序中
target_link_libraries( ${TARGET}
	${SDL2_LIBRARIES}
	SDL2_image::SDL2_image
	SDL2_mixer::SDL2_mixer
	SDL2_ttf::SDL2_ttf
)

# 不要弹出控制台窗口
if (MSVC)
    target_link_options(${TARGET} PRIVATE "/SUBSYSTEM:WINDOWS")
endif()