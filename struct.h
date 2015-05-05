#pragma once
#include "CollisionRectangle.h"

struct coordinates
{
    int x;
    int y;
};

struct AnimationInfo
{
    int BeginFrame;
    int EndFrame;
    int Row;
    int Speed;
};

enum ObjectType
{
    TypeNone,
    TypeGround,
    TypeWater,
    TypeItem,
    TypeAbilityItem,
    TypeFood
};

enum EffectType
{
    EffectTypeNone,
    EffectTypeChamp
};
