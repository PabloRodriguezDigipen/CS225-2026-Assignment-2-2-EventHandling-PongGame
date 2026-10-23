#pragma once

#include "AECore/inc/AEEngine.h"
#include "../Framework/entity.hh"

#include "render_component.hh"
#include "position_component.hh"

RenderComponent::RenderComponent(bool isBall) : Component("Render")
{
	mIsBall = isBall;
}

void RenderComponent::Draw()
{
	//get the position
	PositionComponent* position = static_cast<PositionComponent*>(mOwner->getComponent("Position"));
	//if its the ball, draw a red circle
	if (mIsBall)
		AEGfxCircle(position->getX(), position->getY(), 12, AEGfxColor(255, 0, 0), 20);
	//if its a racket, draw a white rectangle
	else
		AEGfxRect(position->getX(), position->getY(), 0, 20, 100, AEGfxColor(255, 255, 255));
}

RenderComponent::~RenderComponent() {

}