/*****************************************************************//**
 * \file    DisjointSet.h
 * \brief   简介
 *              不相交集，也称为并查集（Disjoint Set Union），
 *              是一种用于解决集合合并与查询问题的数据结构。
 *
 *          基本操作
 *              MakeSet(x): 创建一个只包含元素 x 的新集合。
 *              find_set(x): 返回元素 x 所属的集合的代表元素（也称为根结点）。
 *              union_set(x, y): 将元素 x 所属的集合和元素 y 所属的集合合并成一个集合。
 *
 *          实现方式
 *              不相交集可以通过数组和树两种方式进行实现。
 *                  数组实现
 *                      使用一个数组 parent[] 来存储每个元素的父结点，
 *                      初始状态下每个元素的父结点都是它自身。
 *                      合并操作通过修改两个元素的父结点来实现。
 *                  树实现
 *                      初始状态下，每个元素都是一个独立的树，
 *                      合并操作将两个树的根结点连接在一起。
 *                      可以使用一个数组 parent[] 来存储每个元素的父结点，
 *                      其中父结点为自身时表示该元素为根结点。
 *
 *          基本操作的实现
 *              make_set(x)
 *                  创建一个新的结点，并将其 parent[x] 设置为 x。
 *              find_set(x)
 *                  如果 parent[x] 等于 x，则 x 为根结点，直接返回 x。
 *                  否则，递归调用 find_set(parent[x])，找到 x 所属的集合的根结点。
 *              union_set(x, y)
 *                  调用 find_set(x) 和 find_set(y) 分别找到 x 和 y 所属的集合的根结点。
 *                  如果两个根结点不相等，将其中一个根结点的 parent 设为另一个根结点，实现合并操作。
 *
 *          优化
 *              按秩合并（Rank Union）
 *                  基于树的高度（也称为秩或秩值）进行合并。
 *                  将树高度小的根结点作为新的根结点，以减小树的高度，提高查询效率。
 *              路径压缩（Path Compression）
 *                  在 find_set 操作时，将沿着路径的每个结点的 parent 直接设为根结点，
 *                  以减小树的高度，进一步提高查询效率。
 *
 *          应用场景
 *              连通性问题
 *                  判断图中两个结点是否连通或者找到连通分量。
 *              最小生成树算法
 *                  如 Kruskal 算法。
 *              朋友圈问题
 *                  判断社交网络中两个人是否在同一个朋友圈内等。
 *
 *          注意事项
 *              在使用数组实现时，需要注意数组的大小，至少需要包含所有可能出现的元素。
 *              需要谨慎处理合并操作的顺序，避免形成过深的树。
 *              优化技巧可以提高算法的效率，但也增加了代码的复杂性，需要根据具体情况评估优化的必要性和收益。
 *
 * \author  吴子维
 * \date    July 2023
 *********************************************************************/
#pragma once

 // 不相交集类型定义
MYLIB_BEGIN
class DisjointSet
{
public:
    // 构造函数，创建一个可容纳 n 个元素的并查集
    DisjointSet(int n = 0);
    virtual ~DisjointSet();
    DisjointSet(const DisjointSet& other);
    DisjointSet& operator=(const DisjointSet& other);
    DisjointSet(DisjointSet&& other) noexcept;
    DisjointSet& operator=(DisjointSet&& other) noexcept;

    // 创建一个只包含元素 x 的新集合。
    void make_set(int x);
    // 查：返回元素 x 所属的集合的代表元素（也称为根结点）。时间复杂度 O(logV)
    int find_set(int x) const;
    // 并：将元素 x 所属的集合和元素 y 所属的集合合并成一个集合。时间复杂度 O(logV)
    void union_set(int x, int y);
    void link(int x, int y);
    // 获取元素 x 所在集合的大小
    int getGroupSize(int x);

private:
    std::vector<int> parent;        // 存储每个元素的父结点
    std::vector<int> rank;          // 存储每个结点的秩
    std::vector<int> groupSize;     // 存储每个集合的大小
};
MYLIB_END // mylib