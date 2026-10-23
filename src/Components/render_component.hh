#pragma once

#include "../Framework/component.hh"

/// <summary>
/// Exampe of a Render component class that draw an Entity
/// </summary>
class RenderComponent : public Component
{
    //render depends on if its the ball or a racket
    bool mIsBall;
public:
    RenderComponent(bool isBall);
    
    virtual void Draw();
    
    ~RenderComponent();
};
