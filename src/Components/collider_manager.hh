#pragma once
#include "../Framework/event.hh"
#include "../Framework/event_handlers.hh"
#include "../Framework/entity.hh"
#include "../Framework/component.hh"
#include "../Components/position_component.hh"
#include "../Components/game_components.hh"

class CollisionManager : public EventManager {
    //pointers to the game elements
    Entity* mBall;
    Entity* mPlayer;
    Entity* mCPU;

    //pointers to the goals
    Entity* mRight;
    Entity* mLeft;

public:
    //default constructos
    CollisionManager(Entity* player, Entity* ball, Entity* CPU, Entity* right, Entity* left);
    //update
    void update() override;
};

//event for a collision
class CollisionEvent : public Event {
    //colliding objects
    Entity* object1;
    Entity* object2;
public:
    //constructor
    CollisionEvent(Entity* obj1, Entity* obj2);
};