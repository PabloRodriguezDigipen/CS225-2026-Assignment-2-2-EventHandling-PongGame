#pragma once
#include "event.hh"
#include "event_handlers.hh"

//event fot players input
class InputEventManager : public EventManager {
public:
    void update() override {}
};

//event to move player
class PlayerMoveEvent : public Event {
public:
    int mDistance = 0;
};

//event for ball colliding
class BallHitEvent : public Event {};

//event for cpu to start/ending movement
class CPUMoveEvent : public Event {};

//event for game reset
class Reset : public Event {};