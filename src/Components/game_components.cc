#include "game_components.hh"
#include "../Framework/entity.hh"
#include "position_component.hh"

CollisionComponent::CollisionComponent(int width, int height) : Component("Collision") {
	mWidth = width;
	mHeight = height;
}

int CollisionComponent::getWidth() const {
	return mWidth;
}

int CollisionComponent::getHeight() const {
	return mHeight;
}

CollisionComponent::~CollisionComponent() {}

//-------------------------------------------------------------------------------------------------------------------

PlayerComponent::PlayerComponent() : Component("Player") {}

void PlayerComponent::OnMove(PlayerMoveEvent* event)
{
	PositionComponent* position = static_cast<PositionComponent*>(mOwner->getComponent("Position"));

	position->setPosition(position->getX(), position->getY() + event->mDistance);

	if (position->getY() > 250)
		position->setPosition(position->getX(), 250);
	else if (position->getY() < -250)
		position->setPosition(position->getX(), -250);
}

void PlayerComponent::OnReset(Reset* event) {
	PositionComponent* position = static_cast<PositionComponent*>(mOwner->getComponent("Position"));
	position->setPosition(-375, 0);
}

PlayerComponent::~PlayerComponent() {}

//-------------------------------------------------------------------------------------------------------------------

CPUComponent::CPUComponent(Entity* ball) : Component("CPU") {
	mBall = ball;
}

void CPUComponent::Update() {
	if (mFollowBall) {
		PositionComponent* ballPosition = static_cast<PositionComponent*>(mBall->getComponent("Position"));

		PositionComponent* position = static_cast<PositionComponent*>(mOwner->getComponent("Position"));


		if (ballPosition->getY() > position->getY() && position->getY() < 250)
			position->setPosition(position->getX(), position->getY() + mSpeed);

		else if (ballPosition->getY() < position->getY() && position->getY() > -250)
			position->setPosition(position->getX(), position->getY() - mSpeed);
	}
}

void CPUComponent::OnReset(Reset* event) {
	PositionComponent* position = static_cast<PositionComponent*>(mOwner->getComponent("Position"));
	position->setPosition(375, 0);

	mFollowBall = !mFollowBall;
}

void CPUComponent::OnMove(CPUMoveEvent* event) {
	mFollowBall = !mFollowBall;
}

CPUComponent::~CPUComponent() {}

//-------------------------------------------------------------------------------------------------------------------

BallComponent::BallComponent(int speedX, int speedY) : Component("Ball") {
	mSpeedX = (float)speedX;
	mSpeedY = (float)speedY;
}

void BallComponent::Update() {
	PositionComponent* position = static_cast<PositionComponent*>(mOwner->getComponent("Position"));
	if (position->getY() > 275 || position->getY() < -275)
		mSpeedY = -mSpeedY;

	position->setPosition((int)position->getX() + (int)mSpeedX, (int)position->getY() + (int)mSpeedY);
}

void BallComponent::OnRacket(BallHitEvent* event) {
	mSpeedX = -mSpeedX;
}

void BallComponent::OnReset(Reset* event) {
	PositionComponent* position = static_cast<PositionComponent*>(mOwner->getComponent("Position"));
	position->setPosition(0,0);

	mSpeedX = -mSpeedX;
}

BallComponent::~BallComponent() {}