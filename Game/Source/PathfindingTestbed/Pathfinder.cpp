#include "Framework.h"

#include "Pathfinder.h"
#include "Tilemap.h"

namespace fw
{
    Pathfinder::Pathfinder(Tilemap* pTilemap)
    {
        m_pTilemap = pTilemap;

        m_mapSize = pTilemap->getMapSize();

        m_numNodes = m_mapSize.x * m_mapSize.y;

        m_nodes = new PathNode[m_numNodes];
        m_openNodes = new int[m_numNodes];

        reset();
    }

    Pathfinder::~Pathfinder()
    {
        delete[] m_nodes;
        delete[] m_openNodes;
    }

    void Pathfinder::reset()
    {
        m_numOpen = 0;

        for (int i = 0; i < m_numNodes; i++)
        {
            m_nodes[i].parentNodeIndex = -1;
            m_nodes[i].status = PathNode::Unchecked;

            m_nodes[i].f = 0;
            m_nodes[i].g = FLT_MAX; // Set g to be highest cost possible, so any comparison will be better.
            m_nodes[i].h = -1; // -1 indicates the heuristic hasn't been calculated yet.
        }
    }

    bool Pathfinder::findPath(int sx, int sy, int ex, int ey)
    {
        if (sx < 0 || sx >= m_mapSize.x ||
            sy < 0 || sy >= m_mapSize.y ||
            ex < 0 || ex >= m_mapSize.x ||
            ey < 0 || ey >= m_mapSize.y)
        {
            // Start or end position is out of bounds.
            return false;
        }

        // reset the pathfinder.
        reset();

        // Get the starting tile index and the destination tile index.
        int currentNodeIndex = calculateNodeIndex(sx, sy);
        int endNodeIndex = calculateNodeIndex(ex, ey);

        // Set starting node cost to zero, then add it to the open list to start the process.
        m_nodes[currentNodeIndex].g = 0;
        addToOpen(currentNodeIndex);

        while (true)
        {
            // Find the lowest F and remove it from the open list.
            currentNodeIndex = findNodeIndexForNodeWithLowestFInOpenList();
            removeFromOpen(currentNodeIndex);

            // If we found the end node, we're done.
            if (currentNodeIndex == endNodeIndex)
                return true;

            // Mark it as closed.
            m_nodes[currentNodeIndex].status = PathNode::Closed;

            // Add neighbours to open list.
            addNeighboursToOpenList(currentNodeIndex, endNodeIndex);

            // If we're out of nodes to check, then we're done without finding the end node.
            if (m_numOpen == 0)
                return false;
        }

        // This shouldn't happen, we should either find the destination or run out of nodes in the open list.
        assert(false);
        return false;
    }

    std::vector<int> Pathfinder::getPath(int ex, int ey)
    {
        std::vector<int> path;
        int nodeIndex = calculateNodeIndex(ex, ey);
        while (true)
        {
            path.push_back(nodeIndex);
            nodeIndex = m_nodes[nodeIndex].parentNodeIndex;
            if (nodeIndex == -1)
                break;
        }
        return path;
    }

    void Pathfinder::addToOpen(int nodeindex)
    {
        assert(m_nodes[nodeindex].status != PathNode::Closed);

        // If the node isn't already open, then add it to the list.
        if (m_nodes[nodeindex].status != PathNode::Open)
        {
            m_openNodes[m_numOpen] = nodeindex;
            m_numOpen++;
            m_nodes[nodeindex].status = PathNode::Open;
        }
    }

    void Pathfinder::removeFromOpen(int nodeindex)
    {
        // Remove the node from the open list, since we don't care about order, replace the node we're removing with the last node in list.
        for (int i = 0; i < m_numOpen; i++)
        {
            if (m_openNodes[i] == nodeindex)
            {
                m_numOpen--;
                m_openNodes[i] = m_openNodes[m_numOpen];
                return;
            }
        }
    }

    int Pathfinder::findNodeIndexForNodeWithLowestFInOpenList()
    {
        // Loop through the nodes in the open list, then find and return the node with the lowest f score
        float lowest = FLT_MAX;
        int lownode = -1;

        for (int i = 0; i < m_numOpen; i++)
        {
            if (m_nodes[m_openNodes[i]].f < lowest)
            {
                lowest = m_nodes[m_openNodes[i]].f;
                lownode = m_openNodes[i];
            }
        }

        return lownode;
    }

    int Pathfinder::calculateNodeIndex(int tx, int ty)
    {
        assert(tx >= 0 && tx < m_mapSize.x && ty >= 0 && ty < m_mapSize.y);

        // Calculate the node index based on the tiles x/y.
        return ty * m_mapSize.x + tx;
    }

    int Pathfinder::checkIfNodeIsClearAndReturnNodeIndex(int tx, int ty)
    {
        // If the node is out of bounds, return -1 (an invalid tile index).
        if (tx < 0 || tx >= m_mapSize.x || ty < 0 || ty >= m_mapSize.y)
            return -1;

        int nodeIndex = calculateNodeIndex(tx, ty);

        // If the node is already closed, return -1 (an invalid tile index).
        if (m_nodes[nodeIndex].status == PathNode::Closed)
            return -1;

        // If the node can't be walked on, return -1 (an invalid tile index).
        int layer = -1;
        if (m_pTilemap->isTileWalkableForTilePos({ tx, ty }) == false)
            return -1;

        // Return a valid tile index.
        return nodeIndex;
    }

    void Pathfinder::addNeighboursToOpenList(int nodeIndex, int endNodeIndex)
    {
        // Calculate the tile x/y based on the nodeIndex.
        int tx = nodeIndex % m_mapSize.x;
        int ty = nodeIndex / m_mapSize.x;

        // Create an array of the four neighbour tiles.
        int nodestoadd[4];
        nodestoadd[0] = -1;
        nodestoadd[1] = -1;
        nodestoadd[2] = -1;
        nodestoadd[3] = -1;
        nodestoadd[0] = checkIfNodeIsClearAndReturnNodeIndex(tx, ty - 1);
        nodestoadd[1] = checkIfNodeIsClearAndReturnNodeIndex(tx, ty + 1);
        nodestoadd[2] = checkIfNodeIsClearAndReturnNodeIndex(tx + 1, ty);
        nodestoadd[3] = checkIfNodeIsClearAndReturnNodeIndex(tx - 1, ty);

        // Loop through the array.
        for (int i = 0; i < 4; i++)
        {
            int nodetoadd;
            nodetoadd = nodestoadd[i];

            // Check if the node to add has a valid node index.
            if (nodetoadd != -1)
            {
                int cost = 1;

                // Add the node to the open list.
                addToOpen(nodetoadd);

                // If the cost to get there from here is less than the previous cost to get there, then overwrite the values.
                if (m_nodes[nodeIndex].g + cost < m_nodes[nodetoadd].g)
                {
                    // Set the parent node.
                    m_nodes[nodetoadd].parentNodeIndex = nodeIndex;

                    // Calculate the cost to travel to that node.
                    m_nodes[nodetoadd].g = m_nodes[nodeIndex].g + cost;

                    // If we haven't already calculated the heuristic, calculate it.
                    if (m_nodes[nodetoadd].h == -1)
                        m_nodes[nodetoadd].h = calculateH(nodetoadd, endNodeIndex);

                    // Calculate the final value.
                    m_nodes[nodetoadd].f = m_nodes[nodetoadd].g + m_nodes[nodetoadd].h;
                }
            }
        }
    }

    float Pathfinder::calculateH(int nodeIndex1, int nodeIndex2)
    {
        // Calculate the h score using the manhatten distance (absolute diff in x + absolute diff in y).
        int tx1 = nodeIndex1 % m_mapSize.x;
        int ty1 = nodeIndex1 / m_mapSize.x;

        int tx2 = nodeIndex2 % m_mapSize.x;
        int ty2 = nodeIndex2 / m_mapSize.x;

        return (float)abs(tx1 - tx2) + abs(ty1 - ty2);
    }
}
