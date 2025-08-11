#pragma once
#include "core/scene.h"

class Player;
class Spawer;
class UIMouse;
class HUDStats;
class HUDText;
class SceneMain : public Scene
{

    Player *player_ = nullptr;
    Spawer *spawer_ = nullptr;
    UIMouse *ui_mouse_ = nullptr;
    HUDStats* hud_stats_ = nullptr;
    HUDText* hud_text_score_ = nullptr;

public:
    SceneMain() = default;
    virtual ~SceneMain() = default;

    virtual void init() override;
    virtual void handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

private:
    void renderBackground();

    void updateScore();
};