#include "WorldMap.h"
#include "PathfindingTestbed/Tilemap.h"

fw::WorldMap::WorldMap(ShaderProgram* pBasicShader, ivec2 mapSize, vec2 tileSize, Mesh* pTileMesh) :
    m_pBasicShader(pBasicShader),
    m_mapSize(mapSize),
    m_tileSize(tileSize),
    m_pTileMesh(pTileMesh)
{
    generateTilemap();
}

fw::WorldMap::~WorldMap()
{
    delete tilemap1;
    delete tilemap2;
}

void fw::WorldMap::generateTilemap()
{
    delete tilemap1;
    delete tilemap2;

    TileType* layout1 = new TileType[m_mapSize.x * m_mapSize.y];
    TileType* layout2 = new TileType[m_mapSize.x * m_mapSize.y];

    int randNum = randInt(3, 5);

    for (int y = 0; y < m_mapSize.y; y++)
    {
        for (int x = 0; x < m_mapSize.x; x++)
        {
            if (rand() % 100 < 45)
            {
                layout1[y * m_mapSize.x + x] = TileType::Wall;
            }
            else
            {
                layout1[y * m_mapSize.x + x] = TileType::Air;
            }
            if (rand() % 100 < 45)
            {
                layout2[y * m_mapSize.x + x] = TileType::Void;
            }
            else
            {
                layout2[y * m_mapSize.x + x] = TileType::Ground;
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        proceduralGeneration(layout1, TileType::Wall, TileType::Air);
        proceduralGeneration(layout2, TileType::Void, TileType::Ground);
    }

    for (int i = 0; i < m_mapSize.x * m_mapSize.y; i++)
    {
        if (layout2[i] == TileType::Void)
        {
            layout1[i] = TileType::Air;
        }
    }


    tilemap1 = new Tilemap(m_pTileMesh, m_pBasicShader, { m_mapSize.x, m_mapSize.y }, { m_tileSize.x,m_tileSize.y }, layout1);
    tilemap2 = new Tilemap(m_pTileMesh, m_pBasicShader, { m_mapSize.x, m_mapSize.y }, { m_tileSize.x,m_tileSize.y }, layout2);

    delete[] layout1;
    delete[] layout2;
}

void fw::WorldMap::draw(Camera* camera)
{
    tilemap2->draw(camera);
    tilemap1->draw(camera);
}

void fw::WorldMap::proceduralGeneration(TileType* layout, TileType tile1, TileType tile2)
{
    TileType* tempLayout = new TileType[m_mapSize.x * m_mapSize.y];

    for (int y = 0; y < m_mapSize.y; y++)
    {
        for (int x = 0; x < m_mapSize.x; x++)
        {
            int solid = 0;

            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    if (x + j < 0 || x + j > m_mapSize.x + 1 || y + i < 0 || y + i > m_mapSize.y + 1)
                    {
                        solid++;
                    }
                    else if (layout[(y + i) * m_mapSize.x + (x + j)] == tile1)
                    {
                        solid++;
                    }
                }
            }

            if (solid >= 5)
            {
                tempLayout[y * m_mapSize.x + x] = tile1;
            }
            else
            {
                tempLayout[y * m_mapSize.x + x] = tile2;
            }
        }
    }

    for (int i = 0; i < m_mapSize.x * m_mapSize.y; i++)
    {
        layout[i] = tempLayout[i];
    }

    delete[] tempLayout;
}
