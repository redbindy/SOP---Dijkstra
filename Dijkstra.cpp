#include <iostream>
#include <list>
#include <queue>
#include <vector>

typedef struct
{
    size_t id;
    std::list<std::pair<size_t, size_t>> neighbors;
} node_t;

struct compare
{
    bool operator()(std::pair<node_t, size_t>& p1, std::pair<node_t, size_t>& p2)
    {
        return p1.second > p2.second;
    }
};

int main()
{
    size_t nodeCount;
    std::cin >> nodeCount;

    std::vector<node_t> nodes;
    nodes.reserve(nodeCount);

    for (size_t fromIndex = 0; fromIndex < nodeCount; ++fromIndex)
    {
        node_t node;
        node.id = fromIndex;

        size_t distance = 0;

        size_t toIndex;
        for (toIndex = 0; toIndex < nodeCount; ++toIndex)
        {
            std::cin >> distance;

            if (toIndex == fromIndex || distance == 99)
            {
                continue;
            }

            node.neighbors.push_front({ toIndex, distance });
        }

        nodes.push_back(node);
    }

    std::vector<size_t> minDists;
    minDists.assign(nodeCount, (size_t)-1);
    minDists[0] = 0;

    std::priority_queue<std::pair<node_t, size_t>, std::vector<std::pair<node_t, size_t>>, compare> open;
    open.push({ nodes[0], 0 });

    while (!open.empty())
    {
        node_t node = open.top().first;
        size_t totalDistance = open.top().second;
        open.pop();

        if (minDists[node.id] < totalDistance)
        {
            continue;
        }

        for (std::pair<size_t, size_t>& pair : node.neighbors)
        {
            size_t newDist = totalDistance + pair.second;

            if (newDist >= minDists[pair.first])
            {
                continue;
            }

            minDists[pair.first] = newDist;
            open.push({ nodes[pair.first], newDist });
        }
    }

    for (size_t minDist : minDists)
    {
        std::cout << minDist << " ";
    }
    std::cout << std::endl;
}
