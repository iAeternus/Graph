#include "../include/Config.h"
#include "../include/DisjointSet.h"

MYLIB_BEGIN
DisjointSet::DisjointSet(int n) :
    parent(n), rank(n, 0), groupSize(n, 1)
{
    for (int i = 0; i < n; i++)
    {
        parent[i] = i; // ��ʼ��ÿ��Ԫ�صĸ����Ϊ����
    }
}

DisjointSet::~DisjointSet()
{}

DisjointSet::DisjointSet(const DisjointSet& other) :
    parent(other.parent), rank(other.rank), groupSize(other.groupSize)
{}

DisjointSet& DisjointSet::operator=(const DisjointSet& other)
{
    if (this != &other)
    {
        this->parent = other.parent;
        this->rank = other.rank;
        this->groupSize = other.groupSize;
    }
    return *this;
}

DisjointSet::DisjointSet(DisjointSet&& other) noexcept :
    parent(std::move(other.parent)), rank(std::move(other.rank)), groupSize(std::move(other.rank))
{}

DisjointSet& DisjointSet::operator=(DisjointSet&& other) noexcept
{
    if (this != &other)
    {
        this->parent = std::move(other.parent);
        this->rank = std::move(other.rank);
        this->groupSize = std::move(other.groupSize);
    }
    return *this;
}

void DisjointSet::make_set(int x)
{
    parent[x] = x;
    rank[x] = 0;
    groupSize[x] = 1;
}

int DisjointSet::find_set(int x) const
{
    while (x != parent[x])
    {
        x = parent[x]; // ·��ѹ���������ĸ��������Ϊ������
    }
    return x;
}

void DisjointSet::union_set(int x, int y)
{
    link(find_set(x), find_set(y));
}

void DisjointSet::link(int x, int y)
{
    // ���Ⱥϲ�������С���и����ϲ����ȴ������ȥ
    if (rank[x] > rank[y])
    {
        parent[y] = x;
    }
    else
    {
        parent[x] = y;
        if (rank[x] == rank[y])
        {
            ++rank[y];
        }
    }
}

int DisjointSet::getGroupSize(int x)
{
    int root = find_set(x); // �ҵ�Ԫ�����ڼ��ϵĸ����
    return groupSize[root]; // ���ظ�������ڼ��ϵĴ�С
}
MYLIB_END // mylib