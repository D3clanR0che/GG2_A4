#pragma once
#include "Framework.h"
#include "GameCore.h"
#include "GameTypes.h"
#include "Mesh.h"
#include "Types.h"
#include "Math/vec2.h"
#include "Types/KeyStates.h"
#include "MathFuncs.h"
#include "ProgressBar.h"

namespace fw
{
    class Enemy;
    class Pickup;
    class Player;
    class SurvivorsCamera;
    class Tilemap;
    class Pathfinder;
    class WorldMap;
    class ResourceManager;

    class SurvivorsGame : public fw::GameCore
    {
    private:
        static const int c_numEnemies;
        static const int c_numPickups;
        static const int c_initialXPRequiredToLevelUp;
        static const float c_XPMultiplierPerLevel;
        static const float c_initialEnemySpawnTime;
        static const int c_numSides;
        static const ivec2 c_mapSize;
        static const vec2 c_tileSize;
        static const float c_spriteDuration;

    public:
        SurvivorsGame();
        virtual ~SurvivorsGame();

        void reset();
        void update(float deltaTime);
        void draw();

        // Input event methods.
        void onKey(int keyCode, fw::KeyState keyState);
        //void OnMouseButtonEvent(MouseButton button, MouseButtonState state, float mouseX, float mouseY);
        //void OnMouseMovedEvent(float mouseX, float mouseY);

        void spawnEnemies();
        void spawnEnemy(vec2 pos);
        void spawnPickup(vec2 pos);

        void handleCollisions();

        ResourceManager* GetManager() { return m_pResourceManager; }

        void onEnemyKilled(vec2 location);
        Enemy* getClosestEnemy(vec2 pos);

        // Getters.
        Player* getPlayer() { return m_pPlayer; }
        bool isGameOver() { return m_gameOver; }

        ivec2 getMapSize() { return c_mapSize; }
        vec2 getTileSize() { return c_tileSize; }


    private:
        bool m_gameOver = false;
        int m_enemiesKilled = 0;
        float m_timePlayed = 0.0f;

        float m_enemySpawnTimer = 0.0f;

        bool m_drawDebugData = false;

        Player* m_pPlayer = nullptr;
        EnemyList m_enemies;
        std::vector<Pickup*> m_pickups;
        Mesh* m_pBG = nullptr;

        std::unordered_map<std::string, Mesh*> m_meshes;

        SurvivorsCamera* m_pCamera = nullptr;
        Camera* m_pHudCamera = nullptr;

        ProgressBar* m_pHealthBar = nullptr;

        WorldMap* m_pWorldMap = nullptr;

        ResourceManager* m_pResourceManager;
    };
}
