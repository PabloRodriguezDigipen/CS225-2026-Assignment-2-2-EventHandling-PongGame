#include "game_components.hh"

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


PlayerComponent::PlayerComponent() : Component("Player") {}

PlayerComponent::~PlayerComponent() {}


CPUComponent::CPUComponent() : Component("CPU") {}

void CPUComponent::Update() {

}

CPUComponent::~CPUComponent() {}


BallComponent::BallComponent() : Component("Ball") {}

void BallComponent::Update() {

}

BallComponent::~BallComponent() {}