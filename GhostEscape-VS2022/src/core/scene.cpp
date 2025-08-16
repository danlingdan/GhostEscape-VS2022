#include "scene.h"

bool Scene::handleEvents(SDL_Event &event)
{

    for (auto &child : children__screen_)
    {
        if (child->getActive())
        {
            if (child->handleEvents(event))
            {
                return true;
            }
        }
    }

    if (!is_pause_)
    {
        Object::handleEvents(event);

        for (auto& child : children_world_)
        {
            if (child->getActive())
            {
                if (child->handleEvents(event))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

void Scene::update(float dt)
{
    if (!is_pause_)
    {
        Object::update(dt);

        for (auto it = children_world_.begin(); it != children_world_.end();)
        {
            auto child = *it;
            if (child->getNeedRemove())
            {
                it = children_world_.erase(it);
                child->clean();
                delete child;
                child = nullptr;
                // SDL_Log("DEL!\n");
            }
            else
            {
                if (child->getActive())
                {
                    child->update(dt);
                }
                ++it;
            }
        }
    }

    for (auto it = children__screen_.begin(); it != children__screen_.end();)
    {
        auto child = *it;
        if (child->getNeedRemove())
        {
            it = children__screen_.erase(it);
            child->clean();
            delete child;
            child = nullptr;
        }
        else
        {
            if (child->getActive())
            {
                child->update(dt);
            }
            ++it;
        }
    }
}

void Scene::render()
{
    Object::render();
    for (auto &child : children_world_)
    {
        if (child->getActive())
        {
            child->render();
        }
    }
    for (auto &child : children__screen_)
    {
        if (child->getActive())
        {
            child->render();
        }
    }
}

void Scene::clean()
{
    Object::clean();
    for (auto &child : children__screen_)
    {
        child->clean();
        delete child;
    }
    children__screen_.clear();
    for (auto &child : children_world_)
    {
        child->clean();
        delete child;
    }
    children_world_.clear();
}

void Scene::setCameraPosition(const glm::vec2 &camera_position)
{
    camera_position_ = camera_position;
    camera_position_ = glm::clamp(camera_position_, glm::vec2(-30), world_size_ - game_.getScreenSize() + glm::vec2(30));
}

void Scene::addChild(Object *child)
{
    switch (child->getType())
    {
    case ObjectType::OBJECT_WORLD:
    case ObjectType::ENEMY:
        children_world_.push_back(dynamic_cast<ObjectWorld *>(child));
        break;
    case ObjectType::OBJECT_SCREEN:
        children__screen_.push_back(dynamic_cast<ObjectScreen *>(child));
        break;
    case ObjectType::NONE:
        children_.push_back(child);
        break;
    default:
        break;
    }
}

void Scene::removeChild(Object *child)
{
    switch (child->getType())
    {
    case ObjectType::OBJECT_WORLD:
    case ObjectType::ENEMY:
        children_world_.erase(std::remove(children_world_.begin(), children_world_.end(), dynamic_cast<ObjectWorld *>(child)), children_world_.end());
        break;
    case ObjectType::OBJECT_SCREEN:
        children__screen_.erase(std::remove(children__screen_.begin(), children__screen_.end(), dynamic_cast<ObjectScreen *>(child)), children__screen_.end());
        break;
    case ObjectType::NONE:
        children_.erase(std::remove(children_.begin(), children_.end(), child), children_.end());
        break;
    default:
        break;
    }
}