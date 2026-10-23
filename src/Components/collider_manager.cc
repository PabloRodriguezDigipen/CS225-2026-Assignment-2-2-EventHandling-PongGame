#include "collider_manager.hh"
#include <AEEngine.h>

CollisionManager::CollisionManager(Entity* player, Entity* ball, Entity* CPU, Entity* right, Entity* left) {
	mPlayer = player;
    mBall = ball;
	mCPU = CPU;
    mRight = right;
    mLeft = left;
}

void CollisionManager::update() {
    PositionComponent* ballPos = static_cast<PositionComponent*>(mBall->getComponent("Position"));
    CollisionComponent* ballCol = static_cast<CollisionComponent*>(mBall->getComponent("Collision"));

    PositionComponent* playerPos = static_cast<PositionComponent*>(mPlayer->getComponent("Position"));
    CollisionComponent* playerCol = static_cast<CollisionComponent*>(mPlayer->getComponent("Collision"));

    PositionComponent* cpuPos = static_cast<PositionComponent*>(mCPU->getComponent("Position"));
    CollisionComponent* cpuCol = static_cast<CollisionComponent*>(mCPU->getComponent("Collision"));

    AEVec2 ballPosition = AEVec2((float)ballPos->getX(), (float)ballPos->getY());
    AEVec2 playerPosition = AEVec2((float)playerPos->getX(), (float)playerPos->getY());
    AEVec2 cpuPosition = AEVec2((float)cpuPos->getX(), (float)cpuPos->getY());

    if (AEStaticRectToStaticCircle(&playerPosition, (float)playerCol->getWidth(), (float)playerCol->getHeight(), &ballPosition, (float)ballCol->getWidth()/2.f)) {
        BallHitEvent event;
        notifyEvent(&event);

        CPUMoveEvent event2;
        notifyEvent(&event2);
    }

    else if (AEStaticRectToStaticCircle(&cpuPosition, (float)cpuCol->getWidth(), (float)cpuCol->getHeight(), &ballPosition, (float)ballCol->getWidth()/2.f)) {
        BallHitEvent event;
        notifyEvent(&event);

        CPUMoveEvent event2;
        notifyEvent(&event2);
    }

    PositionComponent* rightPos = static_cast<PositionComponent*>(mRight->getComponent("Position"));
    CollisionComponent* rightCol = static_cast<CollisionComponent*>(mRight->getComponent("Collision"));

    PositionComponent* leftPos = static_cast<PositionComponent*>(mLeft->getComponent("Position"));
    CollisionComponent* leftCol = static_cast<CollisionComponent*>(mLeft->getComponent("Collision"));

    AEVec2 rightPosition = AEVec2((float)rightPos->getX(), (float)rightPos->getY());
    AEVec2 leftPosition = AEVec2((float)leftPos->getX(), (float)leftPos->getY());

    if (AEStaticRectToStaticCircle(&rightPosition, (float)rightCol->getWidth(), (float)rightCol->getHeight(), &ballPosition, (float)ballCol->getWidth() / 2.f) ||
        AEStaticRectToStaticCircle(&leftPosition, (float)leftCol->getWidth(), (float)leftCol->getHeight(), &ballPosition, (float)ballCol->getWidth() / 2.f)) {
        Reset event;
        notifyEvent(&event);
    }
}

CollisionEvent::CollisionEvent(Entity* obj1, Entity* obj2) {
	object1 = obj1;
	object2 = obj2;
}
