#pragma once
#include "../Framework/event.hh"
#include "../Framework/event_handlers.hh"
#include "../Framework/entity.hh"
#include "../Framework/component.hh"
#include "../Components/position_component.hh"
#include "../Components/game_components.hh"

class CollisionManager : public EventManager {
    Entity* mBall;
    Entity* mPlayer;
    Entity* mCPU;

    Entity* mRight;
    Entity* mLeft;

public:
    CollisionManager(Entity* player, Entity* ball, Entity* CPU, Entity* right, Entity* left);
    void update() override;
};


class CollisionEvent : public Event {
    Entity* object1;
    Entity* object2;
public:
    CollisionEvent(Entity* obj1, Entity* obj2);
};