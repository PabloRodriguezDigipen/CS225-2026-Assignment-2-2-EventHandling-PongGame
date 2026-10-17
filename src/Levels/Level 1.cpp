#include <AEEngine.h>
#include <imgui/imgui.h>
#include "Level 1.h"
#include "../Framework/entity.hh"
#include "../Framework/event.hh"
#include "../Framework/event_handlers.hh"
#include "../Components/render_component.hh"
#include "../Components/position_component.hh"

int mode = 0;

Entity* player;
Entity* CPU;
Entity* ball;

EventManager* manager;

bool ShowFrameworkMenu();

void Level_1_Load()
{
    player = new Entity;
    RenderComponent* PlayerRender = new RenderComponent(false);
    player->attach(PlayerRender);
    PositionComponent* PlayerPosition = new PositionComponent(-375, 0);
    player->attach(PlayerPosition);

    CPU = new Entity;
    RenderComponent* CPURender = new RenderComponent(false);
    CPU->attach(CPURender);
    PositionComponent* CPUPosition = new PositionComponent(375, 0);
    CPU->attach(CPUPosition);

    ball = new Entity;
    RenderComponent* BallRender = new RenderComponent(true);
    ball->attach(BallRender);
    PositionComponent* BallPosition = new PositionComponent(0, 0);
    ball->attach(BallPosition);


}

void Level_1_Init()
{
}

void Level_1_Update()
{
    // core keyboard shortcuts and GUI, do not delete this code!
    KeyboardInput();
    bool guiActive = ShowFrameworkMenu();


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

    if (AEInputKeyTriggered('W'))
        AESetGameStateNext(AE_GS_RESTART);
    if (AEInputKeyTriggered('S') && AEInputKeyPressed(AE_KEY_CTRL))
        AESetGameStateNext(AE_GS_QUIT);
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

