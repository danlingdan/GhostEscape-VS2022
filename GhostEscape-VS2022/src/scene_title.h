#pragma once

#include "core/scene.h"

class HUDButton;
class HUDText;
class SceneTitle : public Scene
{
protected:
    SDL_FColor boundary_color_ = { 0.5, 0.5, 0.5, 1 };
    float color_timer_ = 0;

    HUDButton* button_start_ = nullptr;    // start
    HUDButton* button_credits_ = nullptr;  // credit
    HUDButton* button_quit_ = nullptr;     // quit

    HUDText* credits_text_ = nullptr;

public:
    void init() override;
    bool handleEvents(SDL_Event& event) override;
    void update(float dt) override;
    void render() override;
    void clean() override;

private:
    void renderTitleBackground();
    void updateColor();

    void checkButtonQuit();
    void checkButtonStart();
    void checkButtonCredits();
};
