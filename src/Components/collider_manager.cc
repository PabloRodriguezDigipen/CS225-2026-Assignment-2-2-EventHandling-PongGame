#include "collider_manager.hh"

bool CheckCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
    if (x1 + (w1 / 2) < x2 - (w2 / 2))
        return false;

    if (x1 - (w1 / 2) > x2 + (w2 / 2))
        return false;

    if (y1 + (h1 / 2) < y2 - (h2 / 2))
        return false;

    if (y1 - (h1 / 2) > y2 + (h2 / 2))
        return false;

    return true;
}

CollisionManager::CollisionManager(Entity* player, Entity* ball, Entity* CPU) {
	mPlayer = player;
    mBall = ball;
	mCPU = CPU;
}

void CollisionManager::update() {
    PositionComponent* ballPos = static_cast<PositionComponent*>(mBall->getComponent("Position"));
    CollisionComponent* ballCol = static_cast<CollisionComponent*>(mBall->getComponent("Collision"));

    PositionComponent* playerPos = static_cast<PositionComponent*>(mPlayer->getComponent("Position"));
    CollisionComponent* playerCol = static_cast<CollisionComponent*>(mPlayer->getComponent("Collision"));

    PositionComponent* cpuPos = static_cast<PositionComponent*>(mCPU->getComponent("Position"));
    CollisionComponent* cpuCol = static_cast<CollisionComponent*>(mCPU->getComponent("Collision"));

    if (CheckCollision(ballPos->getX(), ballPos->getY(), ballCol->getWidth(), ballCol->getHeight(), playerPos->getX(), playerPos->getY(), playerCol->getWidth(), playerCol->getHeight())) {
        BallHitEvent event;
        notifyEvent(&event);

        CPUMoveEvent event2;
        notifyEvent(&event2);
    }

    else if (CheckCollision(ballPos->getX(), ballPos->getY(), ballCol->getWidth(), ballCol->getHeight(), cpuPos->getX(), cpuPos->getY(), cpuCol->getWidth(), cpuCol->getHeight())) {
        BallHitEvent event;
        notifyEvent(&event);

        CPUMoveEvent event2;
        notifyEvent(&event2);
    }

    if (ballPos->getX() > 375 || ballPos->getX() < -375) {
        Reset event;
        notifyEvent(&event);
    }
}

CollisionEvent::CollisionEvent(Entity* obj1, Entity* obj2) {
	object1 = obj1;
	object2 = obj2;
}
