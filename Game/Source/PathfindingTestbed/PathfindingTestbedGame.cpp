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
        m_pBasicShader = new fw::ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag");

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
                int randValue = rand() % 5;
                if (randValue == 0)
                {
                    layout[y * 10 + x] = TileType::Wall;
                }
                else if (randValue == 1)
                {
                    layout[y * 10 + x] = TileType::Void;
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
        
        // Initialize player position at a ground tile
        m_playerTilePos = {1, 1};
        m_isSliding = false;
        m_slideDirection = {0, 0};
    }

    void PathfindingTestbedGame::update(float deltaTime)
    {
        // Handle sliding on void tiles
        if (m_isSliding)
        {
            ivec2 nextPos = m_playerTilePos + m_slideDirection;
            TileType nextTileType = m_pTilemap->getTileTypeAtTilePos(nextPos);
            
            // Continue sliding on void tiles
            if (nextTileType == TileType::Void)
            {
                m_playerTilePos = nextPos;
            }
            else
            {
                // Stop sliding when we hit a non-void tile
                m_isSliding = false;
                
                // If we hit a wall, convert it to void
                if (nextTileType == TileType::Wall)
                {
                    m_pTilemap->setTileTypeAtTilePos(nextPos, TileType::Void);
                    m_playerTilePos = nextPos; // Move onto the converted tile
                }
                else if (nextTileType == TileType::Ground)
                {
                    m_playerTilePos = nextPos; // Move onto the ground tile
                }
                // If Air or out of bounds, stay at current position
            }
        }
    }

    void PathfindingTestbedGame::draw()
    {
        glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glPointSize(10.0f);

        m_pTilemap->draw(m_pCamera);

        // Draw the player
        vec2 playerWorldPos = vec2((float)m_playerTilePos.x, (float)m_playerTilePos.y) * m_pTilemap->getTileSize() + (m_pTilemap->getTileSize() * 0.5f);
        m_meshes["dot"]->draw(m_pCamera, m_pBasicShader, 1, 0, playerWorldPos, Yellow());
    }

    void PathfindingTestbedGame::onKey(int keyCode, fw::KeyState keyState)
    {
        if (keyState == fw::KeyState::Pressed)
        {
            if (keyCode == 'R')
            {
                reset();
            }
            else if (!m_isSliding) // Only allow movement if not currently sliding
            {
                ivec2 direction = {0, 0};
                
                if (keyCode == VK_UP)
                {
                    direction = {0, 1};
                }
                else if (keyCode == VK_DOWN)
                {
                    direction = {0, -1};
                }
                else if (keyCode == VK_LEFT)
                {
                    direction = {-1, 0};
                }
                else if (keyCode == VK_RIGHT)
                {
                    direction = {1, 0};
                }
                
                if (direction.x != 0 || direction.y != 0)
                {
                    movePlayer(direction);
                }
            }
        }
    }

    void PathfindingTestbedGame::movePlayer(ivec2 direction)
    {
        ivec2 targetPos = m_playerTilePos + direction;
        TileType targetTileType = m_pTilemap->getTileTypeAtTilePos(targetPos);
        
        if (targetTileType == TileType::Ground)
        {
            // Simply move to ground tile
            m_playerTilePos = targetPos;
        }
        else if (targetTileType == TileType::Wall)
        {
            // Convert wall to void and move onto it
            m_pTilemap->setTileTypeAtTilePos(targetPos, TileType::Void);
            m_playerTilePos = targetPos;
        }
        else if (targetTileType == TileType::Void)
        {
            // Start sliding on void tile
            m_playerTilePos = targetPos;
            m_isSliding = true;
            m_slideDirection = direction; // Continue in the same direction as the initial movement
        }
        // If Air or out of bounds, don't move
    }

    void PathfindingTestbedGame::handlePlayerMovement(ivec2 targetPos)
    {
        // This method is no longer needed, but keeping for now
    }
}
