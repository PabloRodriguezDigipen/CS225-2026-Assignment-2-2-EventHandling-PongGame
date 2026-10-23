#pragma once

#include "../Framework/component.hh"
#include "../Framework/game_events.hh"

//component to check collisions
class CollisionComponent : public Component {
protected:
    //data for collision (position will be taken from its own component)
    int mWidth;
    int mHeight;
public:
    //default constructor
    CollisionComponent(int width, int height);
    //getters
    int getWidth() const;
    int getHeight() const;
    //default destructor
    ~CollisionComponent() = default;
};

//players racket
class PlayerComponent : public Component {
protected:
public:
    //default constructor
    PlayerComponent();
    //functions to handle events
    void OnMove(PlayerMoveEvent* event);
    void OnReset(Reset* event);
};

//CPUs racket
class CPUComponent : public Component {
protected:
    //pointer to the ball, to know its position
    Entity* mBall;
    //bool to know if it should be following the ball
    bool mFollowBall = false;
    //speed of the CPU
    int mSpeed = 2;
public:
    //default constructor
    CPUComponent(Entity* ball);
    //update function
    void Update();
    //functions to handle events
    void OnMove(CPUMoveEvent* event);
    void OnReset(Reset* event);
};

//the ball
class BallComponent : public Component {
protected:
    //speeds on x and y
    float mSpeedX = 0;
    float mSpeedY = 0;
public:
    //default constructor
    BallComponent(int speedX, int speedY);
    //update function
    void Update();
    //functions to handle events
    void OnRacket(BallHitEvent* event);
    void OnReset(Reset* event);
};