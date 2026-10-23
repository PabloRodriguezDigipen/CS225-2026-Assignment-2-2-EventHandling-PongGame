#include "game_components.hh"
#include "../Framework/entity.hh"
#include "position_component.hh"

//default constructor
CollisionComponent::CollisionComponent(int width, int height) : Component("Collision") {
	mWidth = width;
	mHeight = height;
}

//getters
int CollisionComponent::getWidth() const {
	return mWidth;
}
int CollisionComponent::getHeight() const {
	return mHeight;
}


//-------------------------------------------------------------------------------------------------------------------

//default constructor
PlayerComponent::PlayerComponent() : Component("Player") {}

//on move envent handler
void PlayerComponent::OnMove(PlayerMoveEvent* event) {
	//get the position component
	PositionComponent* position = static_cast<PositionComponent*>(mOwner->getComponent("Position"));

	//change the position
	position->setPosition(position->getX(), position->getY() + event->mDistance);

	//dont surpass the limits
	if (position->getY() > 250)
		position->setPosition(position->getX(), 250);
	else if (position->getY() < -250)
		position->setPosition(position->getX(), -250);
}

//when a goal is scored
void PlayerComponent::OnReset(Reset* event) {
	//retstart the racket
	PositionComponent* position = static_cast<PositionComponent*>(mOwner->getComponent("Position"));
	position->setPosition(-375, 0);
}


//-------------------------------------------------------------------------------------------------------------------

//default constructor
CPUComponent::CPUComponent(Entity* ball) : Component("CPU") {
	mBall = ball;
}

//update
void CPUComponent::Update() {
	//if it is following the ball
	if (mFollowBall) {
		//get the balls position component
		PositionComponent* ballPosition = static_cast<PositionComponent*>(mBall->getComponent("Position"));

		//get its own position component
		PositionComponent* position = static_cast<PositionComponent*>(mOwner->getComponent("Position"));

		//move on the direction of the ball
		if (ballPosition->getY() > position->getY() && position->getY() < 250)
			position->setPosition(position->getX(), position->getY() + mSpeed);

		else if (ballPosition->getY() < position->getY() && position->getY() > -250)
			position->setPosition(position->getX(), position->getY() - mSpeed);
	}
}

//when a goal is scored
void CPUComponent::OnReset(Reset* event) {
	//retstart the racket
	PositionComponent* position = static_cast<PositionComponent*>(mOwner->getComponent("Position"));
	position->setPosition(375, 0);

	mFollowBall = !mFollowBall;
}

//on move envent handler
void CPUComponent::OnMove(CPUMoveEvent* event) {
	//make it follow or unfollow the ball
	mFollowBall = !mFollowBall;
}


//-------------------------------------------------------------------------------------------------------------------

//default constructor
BallComponent::BallComponent(int speedX, int speedY) : Component("Ball") {
	mSpeedX = (float)speedX;
	mSpeedY = (float)speedY;
}

//update
void BallComponent::Update() {
	//get the position component
	PositionComponent* position = static_cast<PositionComponent*>(mOwner->getComponent("Position"));
	//check ceiling and floor bounds
	if (position->getY() > 275 || position->getY() < -275)
		mSpeedY = -mSpeedY;

	//move the ball
	position->setPosition((int)position->getX() + (int)mSpeedX, (int)position->getY() + (int)mSpeedY);
}

//when hitting racket envent handler
void BallComponent::OnRacket(BallHitEvent* event) {
	mSpeedX = -mSpeedX;
}

//when a goal is scored
void BallComponent::OnReset(Reset* event) {
	//retstart the ball
	PositionComponent* position = static_cast<PositionComponent*>(mOwner->getComponent("Position"));
	position->setPosition(0,0);

	mSpeedX = -mSpeedX;
}
