#pragma once

#include "core/scene.h"

class SceneTitle : public Scene
{
protected:
    SDL_FColor boundary_color_ = { 0.5, 0.5, 0.5, 1 };
    float color_timer_ = 0;

public:
    void init() override;
    void handleEvents(SDL_Event& event) override;
    void update(float dt) override;
    void render() override;
    void clean() override;

private:
    void renderTitleBackground();
    void updateColor();
};
