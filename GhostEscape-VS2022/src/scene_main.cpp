#include "scene_main.h"
#include "player.h"
#include "enemy.h"
#include "world/effect.h"
#include "spawer.h"
#include "screen/ui_mouse.h"
#include "world/spell.h"
#include "screen/hud_stats.h"
#include "screen/hud_text.h"
#include "screen/hud_button.h"
#include "scene_title.h"

void SceneMain::init()
{
    SDL_HideCursor();

    game_.playMusic("assets/bgm/OhMyGhost.ogg");

    world_size_ = game_.getScreenSize() * 3.0f;
    camera_position_ = world_size_ / 2.0f - game_.getScreenSize() / 2.0f;

    player_ = new Player();
    player_->init();
    player_->setPosition(world_size_ / 2.0f);
    addChild(player_);

    spawer_ = new Spawer();
    spawer_->init();
    spawer_->setTarget(player_);
    addChild(spawer_);


    // control button
    button_pause_ = HUDButton::addHUDButtonChild(this,
        game_.getScreenSize() - glm::vec2(230.f, 30.f),
        "assets/UI/A_Pause1.png", "assets/UI/A_Pause2.png", "assets/UI/A_Pause3.png");
    button_restart_ = HUDButton::addHUDButtonChild(this,
        game_.getScreenSize() - glm::vec2(140.f, 30.f),
        "assets/UI/A_Restart1.png", "assets/UI/A_Restart2.png", "assets/UI/A_Restart3.png");
    button_back_ = HUDButton::addHUDButtonChild(this,
        game_.getScreenSize() - glm::vec2(50.f, 30.f),
        "assets/UI/A_Back1.png", "assets/UI/A_Back2.png", "assets/UI/A_Back3.png");
    
    hud_stats_ = HUDStats::addHUDStatsChild(this, player_, glm::vec2(30.f));
    hud_text_score_ = HUDText::addHUDTextChild(this, "Score: 0", glm::vec2(game_.getScreenSize().x - 120.f, 30.f), glm::vec2(200, 50));
    ui_mouse_ = UIMouse::addUIMouseChild(this, "assets/UI/29.png", "assets/UI/30.png", 1.0f, Anchor::CENTER);
}

bool SceneMain::handleEvents(SDL_Event &event)
{
    if (Scene::handleEvents(event))
    {
        return true;
    }

    return false;
}

void SceneMain::update(float dt)
{
    Scene::update(dt);
    updateScore();
    checkButtonPause();
    checkButtonRestart();
    checkButtonBack();
}

void SceneMain::render()
{
    renderBackground();
    Scene::render();
}

void SceneMain::clean()
{
    Scene::clean();
}

void SceneMain::renderBackground()
{
    auto start = -camera_position_;
    auto end = world_size_ - camera_position_;
    game_.drawGrid(start, end, 80.0f, {0.5, 0.5, 0.5, 1.0});
    game_.drawBoundary(start, end, 5.0f, {1.0, 1.0, 1.0, 1.0});
}

void SceneMain::updateScore()
{
    hud_text_score_->setText("Score: " + std::to_string(game_.getScore()));
}

void SceneMain::checkButtonPause()
{
    if (!button_pause_->getIsTrigger())
    {
        return;
    }

    if (is_pause_)
    {
        resume();
    }
    else
    {
        pasue();
    }
}

void SceneMain::checkButtonRestart()
{
    if (!button_restart_->getIsTrigger())
    {
        return;
    }

    auto scene = new SceneMain();
    game_.safeChangeScene(scene);
}

void SceneMain::checkButtonBack()
{
    if (!button_back_->getIsTrigger())
    {
        return;
    }

    auto scene = new SceneTitle();
    game_.safeChangeScene(scene);
}
