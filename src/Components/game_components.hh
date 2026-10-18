#pragma once

#include "../Framework/component.hh"
#include "../Framework/game_events.hh"

class CollisionComponent : public Component {
protected:
    int mWidth;
    int mHeight;
public:
    CollisionComponent(int width, int height);
    int getWidth() const;
    int getHeight() const;
    ~CollisionComponent();
};

class PlayerComponent : public Component {
protected:
public:
    PlayerComponent();
    void OnMove(PlayerMoveEvent* event);
    ~PlayerComponent();
};

class CPUComponent : public Component {
protected:
    Entity* mBall;
    bool mFollowBall = false;
    int mSpeed = 2;
public:
    CPUComponent(Entity* ball);
    void Update();
    void OnMove(CPUMoveEvent* event);
    ~CPUComponent();
};

class BallComponent : public Component {
protected:
    float mSpeedX = 0;
    float mSpeedY = 0;
public:
    BallComponent(int speedX, int speedY);
    void Update();
    ~BallComponent();
};