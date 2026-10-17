#pragma once
#include "../Framework/event.hh"
#include "../Framework/event_handlers.hh"

class CollisionManager : public EventManager {

public:
    void update() override;
};


class CollisionEvent : public Event
{
public:
    CollisionEvent();
};


bool CheckCollision(int x1, int y1, int w1, int h1,
                    int x2, int y2, int w2, int h2) {
    if (x1 + (w1 / 2) < x2 - (w2 / 2))
        return false;

    if (x1 - (w1 / 2) > x2 + (w2 / 2))
        return false;

    if (y1 + (h1 / 2) < y2 - (h2 / 2))
        return false;

    if (y1 - (h1 / 2) > y2 + (h2 / 2))
        return false;

    return true;
}