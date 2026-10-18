#pragma once
#include "event.hh"
#include "event_handlers.hh"

class InputEventManager : public EventManager {
public:
    void update() override {}
};

class PlayerMoveEvent : public Event {
public:
    int mDistance;
};

class BallHitEvent : public Event {};

class CPUMoveEvent : public Event {};

class Reset : public Event {};