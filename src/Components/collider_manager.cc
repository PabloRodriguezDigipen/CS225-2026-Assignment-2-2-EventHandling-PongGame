#include "collider_manager.hh"
#include <AEEngine.h>

//default constructor
CollisionManager::CollisionManager(Entity* player, Entity* ball, Entity* CPU, Entity* right, Entity* left) {
	mPlayer = player;
    mBall = ball;
	mCPU = CPU;
    mRight = right;
    mLeft = left;
}

void CollisionManager::update() {
    //get the ball data
    PositionComponent* ballPos = static_cast<PositionComponent*>(mBall->getComponent("Position"));
    CollisionComponent* ballCol = static_cast<CollisionComponent*>(mBall->getComponent("Collision"));

    //get the player data
    PositionComponent* playerPos = static_cast<PositionComponent*>(mPlayer->getComponent("Position"));
    CollisionComponent* playerCol = static_cast<CollisionComponent*>(mPlayer->getComponent("Collision"));

    //get the CPU data
    PositionComponent* cpuPos = static_cast<PositionComponent*>(mCPU->getComponent("Position"));
    CollisionComponent* cpuCol = static_cast<CollisionComponent*>(mCPU->getComponent("Collision"));

    //get all positions to vectors for AE
    AEVec2 ballPosition = AEVec2((float)ballPos->getX(), (float)ballPos->getY());
    AEVec2 playerPosition = AEVec2((float)playerPos->getX(), (float)playerPos->getY());
    AEVec2 cpuPosition = AEVec2((float)cpuPos->getX(), (float)cpuPos->getY());

    //check ball on player
    if (AEStaticRectToStaticCircle(&playerPosition, (float)playerCol->getWidth(), (float)playerCol->getHeight(), &ballPosition, (float)ballCol->getWidth()/2.f)) {
        //if they hit, change th balls direction and activate the CPU

        BallHitEvent event;
        notifyEvent(&event);

        CPUMoveEvent event2;
        notifyEvent(&event2);
    }

    //check ball on CPU
    else if (AEStaticRectToStaticCircle(&cpuPosition, (float)cpuCol->getWidth(), (float)cpuCol->getHeight(), &ballPosition, (float)ballCol->getWidth()/2.f)) {
        //if they hit, change th balls direction and deactivate the CPU

        BallHitEvent event;
        notifyEvent(&event);

        CPUMoveEvent event2;
        notifyEvent(&event2);
    }

    //get the right goal data
    PositionComponent* rightPos = static_cast<PositionComponent*>(mRight->getComponent("Position"));
    CollisionComponent* rightCol = static_cast<CollisionComponent*>(mRight->getComponent("Collision"));

    //get the left goal data
    PositionComponent* leftPos = static_cast<PositionComponent*>(mLeft->getComponent("Position"));
    CollisionComponent* leftCol = static_cast<CollisionComponent*>(mLeft->getComponent("Collision"));

    //get goal positions to vectors for AE
    AEVec2 rightPosition = AEVec2((float)rightPos->getX(), (float)rightPos->getY());
    AEVec2 leftPosition = AEVec2((float)leftPos->getX(), (float)leftPos->getY());

    //check if the ball hitas any goal
    if (AEStaticRectToStaticCircle(&rightPosition, (float)rightCol->getWidth(), (float)rightCol->getHeight(), &ballPosition, (float)ballCol->getWidth() / 2.f) ||
        AEStaticRectToStaticCircle(&leftPosition, (float)leftCol->getWidth(), (float)leftCol->getHeight(), &ballPosition, (float)ballCol->getWidth() / 2.f)) {
        //if it hits a goal, reset the game
        Reset event;
        notifyEvent(&event);
    }
}

//events constructor
CollisionEvent::CollisionEvent(Entity* obj1, Entity* obj2) {
	object1 = obj1;
	object2 = obj2;
}
