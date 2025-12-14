#pragma once

#include <unordered_map>

namespace fw
{
    class Tilemap;
    class Pathfinder;

    class PathfindingTestbedGame : public fw::GameCore
    {
    public:
        PathfindingTestbedGame();
        virtual ~PathfindingTestbedGame();

        void reset();
        virtual void update(float deltaTime) override;
        virtual void draw() override;
        virtual void onKey(int keyCode, fw::KeyState keyState) override;

    private:
        fw::Camera* m_pCamera = nullptr;

        std::unordered_map<std::string, fw::Mesh*> m_meshes;
        fw::ShaderProgram* m_pBasicShader = nullptr;

        Tilemap* m_pTilemap;
        Pathfinder* m_pPathfinder;

        std::vector<int> m_pathFound;
    };
}
