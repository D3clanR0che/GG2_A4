#include "Framework.h"

#include "Survivors/SurvivorsGame.h"
#include "GameTypes.h"
#include "Pathfinder.h"
#include "PathfindingTestbedGame.h"
#include "Tilemap.h"

namespace fw
{
    PathfindingTestbedGame::PathfindingTestbedGame()
    {
        m_pBasicShader = new fw::ShaderProgram("Data/Basics/basic.vert", "Data/Basics/basic.frag");

        // Create meshes.
        m_meshes["tile"] = new fw::Mesh(GL_TRIANGLE_STRIP, { {{0,0}}, {{1,0}}, {{0,1}}, {{1,1}} });
        m_meshes["dot"] = new fw::Mesh(GL_POINTS, { {{0,0}} });

        // Create a camera.
        float aspectRatio = 1280.0f / 720.0f;
        m_pCamera = new fw::Camera(vec2(25, 25), aspectRatio, 30.0f);

        reset();
    }

    PathfindingTestbedGame::~PathfindingTestbedGame()
    {
        for (const auto& meshPair : m_meshes)
        {
            delete meshPair.second;
        }
    }

    void PathfindingTestbedGame::reset()
    {
        delete m_pTilemap;
        delete m_pPathfinder;

        // Create a tilemap.
        TileType* layout = new TileType[100];
        for (int y = 0; y < 10; y++)
        {
            for (int x = 0; x < 10; x++)
            {
                if (rand() % 3 == 0)
                {
                    layout[y * 10 + x] = TileType::Wall;
                }
                else
                {
                    layout[y * 10 + x] = TileType::Ground;
                }
            }
        }

        m_pTilemap = new Tilemap(m_meshes["tile"], m_pBasicShader, { 10,10 }, { 5.0f,5.0f }, layout);
        m_pPathfinder = new Pathfinder(m_pTilemap);
        delete[] layout;
    }

    void PathfindingTestbedGame::update(float deltaTime)
    {
        int startx = 3;
        int starty = 1;
        int endx = 0;
        int endy = 6;
        bool found = m_pPathfinder->findPath(startx, starty, endx, endy);

        m_pathFound = m_pPathfinder->getPath(endx, endy);
    }

    void PathfindingTestbedGame::draw()
    {
        glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glPointSize(10.0f);

        m_pTilemap->draw(m_pCamera);

        for (int i = 0; i < m_pathFound.size(); i++)
        {
            int tileIndex = m_pathFound[i];
            vec2 pos = m_pTilemap->getWorldPosForTileIndex(tileIndex);
            m_meshes["dot"]->draw(m_pCamera, m_pBasicShader, 1, 0, pos, Red());
        }
    }

    void PathfindingTestbedGame::onKey(int keyCode, fw::KeyState keyState)
    {
        if (keyState == fw::KeyState::Pressed && keyCode == 'R')
        {
            reset();
        }
    }
}
