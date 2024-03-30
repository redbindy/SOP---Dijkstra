#include <iostream>
#include <list>
#include <queue>
#include <vector>

struct compare
{
    bool operator()(const std::pair<size_t, size_t>& p1, const std::pair<size_t, size_t>& p2)
    {
        return p1.second > p2.second;
    }
};

enum
{
    INF = 99
};

int main()
{
    /*
    * �Է� ����
    * 
    * ù �Է�: ����� ����
    * ���� �Է�: �������
    * 
    * �Է¿��� 99�� ���Ѵ� ����ġ(INF)�� �����ϰ� �ۼ�
    * 
    * �Է� ����
    * 6
    * 0 2 1 99 99 99
    * 2 0 3 99 1 99
    * 1 3 0 3 1 99
    * 99 99 3 0 1 4
    * 99 1 1 1 0 2
    * 99 99 99  4 2 99
    * 
    * ����� (0�� ���)->(�ٸ� ���) �ִܺ��
    * 
    * �Է� ���ÿ� ���� ���
    * 0 2 1 3 2 4
    */

    size_t nodeCount;
    std::cin >> nodeCount;

    // std::pair<��� ��ȣ, ����ġ> ����Ʈ�� �迭
    std::vector<std::list<std::pair<size_t, size_t>>> adjacencyLists;
    adjacencyLists.reserve(nodeCount);

    // from -> to ����
    for (size_t fromIndex = 0; fromIndex < nodeCount; ++fromIndex)
    {
        adjacencyLists.push_back(std::list<std::pair<size_t, size_t>>());

        size_t distance = 0;

        for (size_t toIndex = 0; toIndex < nodeCount; ++toIndex)
        {
            std::cin >> distance;

            if (toIndex == fromIndex || distance == INF)
            {
                continue;
            }

            adjacencyLists[fromIndex].push_front({ toIndex, distance });
        }
    }

    std::vector<size_t> minDists;
    minDists.assign(nodeCount, (size_t)-1);
    minDists[0] = 0;

    std::priority_queue<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>, compare> open;
    open.push({ 0, 0 });

    while (!open.empty())
    {
        size_t nodeIndex = open.top().first;
        size_t currDist = open.top().second;
        open.pop();

        if (minDists[nodeIndex] < currDist)
        {
            continue;
        }

        for (std::pair<size_t, size_t>& pair : adjacencyLists[nodeIndex])
        {
            size_t newDist = currDist + pair.second;

            if (newDist >= minDists[pair.first])
            {
                continue;
            }

            minDists[pair.first] = newDist;
            open.push({ pair.first, newDist });
        }
    }

    for (size_t minDist : minDists)
    {
        std::cout << minDist << " ";
    }
    std::cout << std::endl;
}
