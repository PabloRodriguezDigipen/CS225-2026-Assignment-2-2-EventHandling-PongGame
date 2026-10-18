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
	PositionComponent* position = static_cast<PositionComponent*>(mOwner->getComponent("Position"));
	if (mIsBall)
		AEGfxCircle(position->getX(), position->getY(), 12, AEGfxColor(255, 0, 0), 20);
	else
		AEGfxRect(position->getX(), position->getY(), 0, 20, 100, AEGfxColor(255, 255, 255));
}

RenderComponent::~RenderComponent() {

}