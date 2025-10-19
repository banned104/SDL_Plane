#ifndef SCENE_H
#define SCENE_H

#include "SDL.h"

class Scene {
    public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void init()     = 0;            // 初始化场景
    virtual void update()   = 0;            // 更新场景状态
    virtual void render()   = 0;            // 渲染场景
    virtual void clean()    = 0;            // 清理场景
    virtual void handleEvent( SDL_Event* event ) = 0;       // 处理输入事件
};

#endif
