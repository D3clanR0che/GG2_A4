#pragma once
#include "Survivors/SurvivorsGame.h"
#include "PathfindingTestbed/Tilemap.h"

namespace fw
{
	class Tilemap;

	class WorldMap
	{
	public:
		WorldMap(ShaderProgram* pBasicShader, ivec2 mapSize, vec2 tileSize, Mesh* pTileMesh);
		~WorldMap();

		void generateTilemap();

		void draw(Camera* camera);

		void proceduralGeneration(TileType* layout, TileType tile1, TileType tile2);

	private:

		Mesh* m_pTileMesh;
		ShaderProgram* m_pBasicShader;
		ivec2 m_mapSize;
		vec2 m_tileSize;
		Tilemap* tilemap1;
		Tilemap* tilemap2;
	};
}