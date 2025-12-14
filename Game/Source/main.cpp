#include "Framework.h"
#include "Game.h"
#include "Survivors/SurvivorsGame.h"
#include "PathfindingTestbed/PathfindingTestbedGame.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    fw::vec2::test();

    fw::FWWindows framework(1280, 720);

    //Game game;

    //fw::SurvivorsGame survivorsGame;

    fw::PathfindingTestbedGame pathfinderGame;

    framework.run(&pathfinderGame);
}