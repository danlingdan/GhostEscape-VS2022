#pragma once

#define DEBUG_MODE

enum class ObjectType
{
    NONE,
    OBJECT_WORLD,
    OBJECT_SCREEN,
    ENEMY
};

enum class Anchor
{
    NONE,
    TOP_LEFT,
    TOP_CENTER,
    TOP_RIGHT,
    CENTER_LEFT,
    CENTER,
    CENTER_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_CENTER,
    BOTTOM_RIGHT,
};