#pragma once

#include "../framework/component.hh"

class CollisionComponent : public Component
{
protected:
    int mWidth;
    int mHeight;
public:
    CollisionComponent(int width, int height);
    int getWidth() const;
    int getHeight() const;
    ~CollisionComponent();
};

class PlayerComponent : public Component
{
protected:
public:
    PlayerComponent();
    ~PlayerComponent();
};

class CPUComponent : public Component
{
protected:
    bool mFollowBall = false;
public:
    CPUComponent();
    void Update();
    ~CPUComponent();
};

class BallComponent : public Component
{
protected:
    float mSpeedX = 0;
    float mSpeedY = 0;
public:
    BallComponent();
    void Update();
    ~BallComponent();
};