#include <AEEngine.h>
#include <imgui/imgui.h>
#include "Level 1.h"
#include "../Framework/entity.hh"
#include "../Framework/event.hh"
#include "../Framework/event_handlers.hh"
#include "../Components/render_component.hh"
#include "../Components/position_component.hh"
#include "../Components/game_components.hh"
#include "../Framework/game_events.hh"
#include "../Components/collider_manager.hh"

int mode = 0;

//create the player, cpu and ball
Entity* player;
Entity* CPU;
Entity* ball;

//add limits
Entity* right;
Entity* left;

//create the event managers
InputEventManager* inputManager;
CollisionManager* collisionManager;

bool ShowFrameworkMenu();

void Level_1_Load()
{
    //create the player
    player = new Entity;
    //create the ball
    ball = new Entity;
    //create the CPU
    CPU = new Entity;
    //create limits
    right = new Entity;
    left = new Entity;
}

void Level_1_Init()
{
    //add the components of the player
    RenderComponent* PlayerRender = new RenderComponent(false);
    player->attach(PlayerRender);
    PositionComponent* PlayerPosition = new PositionComponent(-375, 0);
    player->attach(PlayerPosition);
    CollisionComponent* PlayerColider = new CollisionComponent(20, 100);
    player->attach(PlayerColider);
    PlayerComponent* PlayerComp = new PlayerComponent();
    player->attach(PlayerComp);

    //add the components of the ball
    RenderComponent* BallRender = new RenderComponent(true);
    ball->attach(BallRender);
    PositionComponent* BallPosition = new PositionComponent(0, 0);
    ball->attach(BallPosition);
    CollisionComponent* BallColider = new CollisionComponent(25, 25);
    ball->attach(BallColider);
    BallComponent* BallComp = new BallComponent(-3, 3);
    ball->attach(BallComp);

    //add the components of the CPU
    RenderComponent* CPURender = new RenderComponent(false);
    CPU->attach(CPURender);
    PositionComponent* CPUPosition = new PositionComponent(375, 0);
    CPU->attach(CPUPosition);
    CollisionComponent* CPUColider = new CollisionComponent(20, 100);
    CPU->attach(CPUColider);
    CPUComponent* CPUComp = new CPUComponent(ball);
    CPU->attach(CPUComp);

    PositionComponent* rightPosition = new PositionComponent(400, 0);
    right->attach(rightPosition);
    CollisionComponent* rightColider = new CollisionComponent(1, 300);
    right->attach(rightColider);

    PositionComponent* leftPosition = new PositionComponent(-400, 0);
    left->attach(leftPosition);
    CollisionComponent* leftColider = new CollisionComponent(1, 300);
    left->attach(leftColider);

    //subscribe the objects to the collision events
    collisionManager = new CollisionManager(player, ball, CPU, right, left);
    //the ball collides with a racket
    collisionManager->registerEventHandler(new EventHandler<BallComponent, BallHitEvent>(BallComp, &BallComponent::OnRacket));
    //the cpu moves
    collisionManager->registerEventHandler(new EventHandler<CPUComponent, CPUMoveEvent>(CPUComp, &CPUComponent::OnMove));
    //the game is reset
    collisionManager->registerEventHandler(new EventHandler<PlayerComponent, Reset>(PlayerComp, &PlayerComponent::OnReset));
    collisionManager->registerEventHandler(new EventHandler<BallComponent, Reset>(BallComp, &BallComponent::OnReset));
    collisionManager->registerEventHandler(new EventHandler<CPUComponent, Reset>(CPUComp, &CPUComponent::OnReset));

    //subscribe the player and cpu to the input events
    inputManager = new InputEventManager;
    inputManager->registerEventHandler(new EventHandler<PlayerComponent, PlayerMoveEvent>(PlayerComp, &PlayerComponent::OnMove));
    inputManager->registerEventHandler(new EventHandler<CPUComponent, CPUMoveEvent>(CPUComp, &CPUComponent::OnMove));
}

void Level_1_Update()
{
    // core keyboard shortcuts and GUI, do not delete this code!
    KeyboardInput();
    bool guiActive = ShowFrameworkMenu();

    //update the ball
    BallComponent* ballUpdate = static_cast<BallComponent*>(ball->getComponent("Ball"));
    ballUpdate->Update();

    //update the CPU
    CPUComponent* CPUUpdate = static_cast<CPUComponent*>(CPU->getComponent("CPU"));
    CPUUpdate->Update();

    //update collisions (check them)
    collisionManager->update();
}

void Level_1_Render()
{
    // clear frame buffer, do not delete this code
    AEGfxSetClearColor(AEGfxColor(0, 0, 0));
    AEGfxClearBuffer();

    RenderComponent* PlayerRender = static_cast<RenderComponent*>(player->getComponent("Render"));
    PlayerRender->Draw();

    RenderComponent* CPURender = static_cast<RenderComponent*>(CPU->getComponent("Render"));
    CPURender->Draw();

    RenderComponent* BallRender = static_cast<RenderComponent*>(ball->getComponent("Render"));
    BallRender->Draw();
}

void Level_1_Free()
{

}

void Level_1_Unload()
{
}

void KeyboardInput()
{
    if (AEInputKeyTriggered('R'))
        AESetGameStateNext(AE_GS_RESTART);
    if (AEInputKeyTriggered('Q') && AEInputKeyPressed(AE_KEY_CTRL))
        AESetGameStateNext(AE_GS_QUIT);

    //move the player when pressing W or S
    if (AEInputKeyPressed('W')) {
        PlayerMoveEvent event;
        event.mDistance = 2;
        inputManager->notifyEvent(&event);
    }
    if (AEInputKeyPressed('S')) {
        PlayerMoveEvent event;
        event.mDistance = -2;
        inputManager->notifyEvent(&event);
    }
}

bool ShowFrameworkMenu()
{
    bool isGuiActive = false;
    mode = 0;

    // show File options 
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Mode")) {

            if (ImGui::MenuItem("Restart", "1"))
                mode = 1;

            ImGui::EndMenu();
        }

        auto mSize = ImGui::GetWindowHeight();
        AEVec2 mouseVP = AEGetMouseData().position + AEVec2((float)AEGetSysWindowWidth() / 2.0f, (float)AEGetSysWindowHeight() / 2.0f);
        auto inMenu = mouseVP.y >= (AEGetSysWindowHeight() - mSize);
        isGuiActive = ImGui::IsAnyItemActive() || ImGui::IsAnyItemHovered() || inMenu;

        ImGui::EndMainMenuBar();
    }

    if (mode == 1) {
        AESetGameStateNext(AE_GS_RESTART);
    }

    return isGuiActive;
}

