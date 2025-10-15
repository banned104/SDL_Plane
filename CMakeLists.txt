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
    # target_link_options(${TARGET} PRIVATE "/SUBSYSTEM:WINDOWS")
endif()

# 获取 SDL2 库目录
get_target_property(SDL2_DLL_PATH SDL2::SDL2 IMPORTED_LOCATION)
get_filename_component(SDL2_LIB_DIR ${SDL2_DLL_PATH} DIRECTORY)
    
# 输出时复制dll
    # 复制 SDL2 相关 DLL
    add_custom_command(TARGET ${TARGET} POST_BUILD
        # CMake命令 当文件不同时才复制
        # copy_if_different 用于复制单个文件
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_LIB_DIR}/SDL2.dll"
        "${SDL2_LIB_DIR}/SDL2_image.dll"
        "${SDL2_LIB_DIR}/SDL2_mixer.dll"
        "${SDL2_LIB_DIR}/SDL2_ttf.dll"
        # 目标目录：$<TARGET_FILE_DIR:${TARGET}>，表示可执行文件所在的输出目录（如 out/build/x64-Debug/）。
        $<TARGET_FILE_DIR:${TARGET}>
    )

    # TARGET ${TARGET} POST_BUILD 意思是 在目标 {TARGET} 构建完成后执行命令
    add_custom_command(TARGET ${TARGET} POST_BUILD
        # CMake命令 复制整个目录
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        # 源目录
        "${CMAKE_SOURCE_DIR}/assets"
        # 目标目录（复制到输出目录下的 assets 子目录）
        "$<TARGET_FILE_DIR:${TARGET}>/assets"
    )
