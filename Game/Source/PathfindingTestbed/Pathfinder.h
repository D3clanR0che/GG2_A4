#pragma once

#include "GameTypes.h"

namespace fw
{
    class Tilemap;

    struct PathNode
    {
        enum PathNodeStatus
        {
            Unchecked,
            Open,
            Closed,
        };

        int parentNodeIndex;
        PathNodeStatus status;

        float f; // Current sum.
        float g; // Cost to get to current node.
        float h; // Heuristic: Manhatten distance to destination.
    };

    class Pathfinder
    {
    public:
        Pathfinder(Tilemap* pTilemap);
        virtual ~Pathfinder();

        void reset();

        // Start a search, supply the starting tile x,y and ending tile x,y.
        // Returns true if path found, false otherwise.
        bool findPath(int sx, int sy, int ex, int ey);

        // Retrieve the final path.
        std::vector<int> getPath(int ex, int ey);

    protected:
        // Internal methods.
        void addToOpen(int nodeindex);
        void removeFromOpen(int nodeindex);
        int findNodeIndexForNodeWithLowestFInOpenList();

        int calculateNodeIndex(int tx, int ty);
        int checkIfNodeIsClearAndReturnNodeIndex(int tx, int ty);
        void addNeighboursToOpenList(int nodeIndex, int endNodeIndex);

        float calculateH(int nodeIndex1, int nodeIndex2);

    protected:
        Tilemap* m_pTilemap;
        ivec2 m_mapSize;

        PathNode* m_nodes;
        int m_numNodes;

        int* m_openNodes;
        int m_numOpen;
    };
}
