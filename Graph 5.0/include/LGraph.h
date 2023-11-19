/*****************************************************************//**
 * \file   LGraph.h
 * \brief  使用邻接链表实现图
 * 
 * \author 吴子维
 * \date   September 2023
 *********************************************************************/
#pragma once
#include "Graph.h"

MYLIB_BEGIN
template<typename value_type, typename weight_type = int>
class LGraph : public Graph<value_type, weight_type>
{
public:
	LGraph();
    virtual ~LGraph();
	LGraph(const LGraph& other);
	LGraph& operator=(const LGraph& other);
	LGraph(LGraph&& other) noexcept;
	LGraph& operator=(LGraph&& other) noexcept;

    void AddNode(const value_type& value) override;
    void RemoveNode(int index) override;
    void AddEdge(int fromIndex, int toIndex, bool isDirEdge = true, const weight_type& weight = 0) override;
    void RemoveEdge(int fromIndex, int toIndex, bool isDirEdge = true) override;
    
    weight_type GetWeight(int fromIndex, int toIndex) const override;

    void Output(std::ostream& out = std::cout) const override;

protected:
    // 邻接链表的集合。邻接结点链表：存储与邻接结点连接的边
    std::vector<std::list<GraphEdge<weight_type>>> adjacencyLists;

    bool For_each_adjacency_vertices(int curNodeIndex, const std::function<bool(const GraphEdge<weight_type>&)>& func) const override;
    bool For_each_adjacency_vertices(int curNodeIndex, const std::function<bool(GraphEdge<weight_type>&)>& func) override;
};

// 偏特化 LGraph 类
template<typename value_type>
class LGraph<value_type, Pipeline> : public Graph<value_type, Pipeline>
{
public:
    void AddNode(const value_type& value) override;
    //void AddNode(const GraphNode<value_type>& node);
    void AddEdge(int fromIndex, int toIndex, bool isDirEdge = true, const Pipeline& weight = 0) override;
    Pipeline GetWeight(int fromIndex, int toIndex) const override;
    void Output(std::ostream& out = std::cout) const override;
protected:
    // 邻接链表的集合。邻接结点链表：存储与邻接结点连接的边
    std::vector<std::list<GraphEdge<Pipeline>>> adjacencyLists;

    bool For_each_adjacency_vertices(int curNodeIndex, const std::function<bool(const GraphEdge<Pipeline>&)>& func) const override;
    bool For_each_adjacency_vertices(int curNodeIndex, const std::function<bool(GraphEdge<Pipeline>&)>& func) override;
};

template<typename value_type, typename weight_type>
inline LGraph<value_type, weight_type>::LGraph() :
    Graph<value_type, weight_type>::Graph(), adjacencyLists(GRAPH_SIZE)
{}

template<typename value_type, typename weight_type>
inline LGraph<value_type, weight_type>::~LGraph()
{}

template<typename value_type, typename weight_type>
inline LGraph<value_type, weight_type>::LGraph(const LGraph& other) :
    Graph<value_type, weight_type>::Graph(other), adjacencyLists(other.adjacencyLists)
{}

template<typename value_type, typename weight_type>
inline LGraph<value_type, weight_type>& LGraph<value_type, weight_type>::operator=(const LGraph& other)
{
	if (this != &other)
	{
        this->operator=(other);
        this->adjacencyLists = other.adjacencyLists;
	}
	return *this;
}

template<typename value_type, typename weight_type>
inline LGraph<value_type, weight_type>::LGraph(LGraph&& other) noexcept :
    Graph<value_type, weight_type>::Graph(other), adjacencyLists(std::move(adjacencyLists))
{}

template<typename value_type, typename weight_type>
inline LGraph<value_type, weight_type>& LGraph<value_type, weight_type>::operator=(LGraph&& other) noexcept
{
	if (this != &other)
	{
        this->operator=(other);
        this->adjacencyLists = std::move(other.adjacencyLists);
	}
	return *this;
}

template<typename value_type, typename weight_type>
inline void LGraph<value_type, weight_type>::AddNode(const value_type& value)
{
    if (this->numVertices >= adjacencyLists.size()) // 装不下，扩容
    {
        adjacencyLists.resize(this->numVertices + EXPANSION);
    }
    Graph<value_type, weight_type>::AddNode(value);
}

template<typename value_type>
inline void LGraph<value_type, Pipeline>::AddNode(const value_type& value)
{
    if (this->numVertices >= adjacencyLists.size()) // 装不下，扩容
    {
        adjacencyLists.resize(this->numVertices + EXPANSION);
    }
    Graph<value_type, Pipeline>::AddNode(value);
}

template<typename value_type, typename weight_type>
inline void LGraph<value_type, weight_type>::RemoveNode(int index) // TODO
{
    if (index < 0 || index > this->numVertices) return;

    // 更新其他结点的邻接信息和边数
    for (int i = 0; i < this->numVertices; i++)
    {
        auto& neighbors = adjacencyLists[i];
        for (auto it = neighbors.begin(); it != neighbors.end(); )
        {
            if (it->NeighborIndex() == index)
            {
                it = neighbors.erase(it);
            }
            else if (it->NeighborIndex() > index)
            {
                --(it->NeighborIndex());
                ++it;
            }
            else
            {
                ++it;
            }
        }
        this->nodes[i].Out_degree(neighbors.size());
    }
    Graph<value_type, weight_type>::RemoveNode(index);
}

template<typename value_type, typename weight_type>
inline void LGraph<value_type, weight_type>::AddEdge(int fromIndex, int toIndex, bool isDirEdge, const weight_type& weight)
{
    if (fromIndex >= 0 && fromIndex < this->nodes.size() &&
        toIndex >= 0 && toIndex < this->nodes.size() &&
        !this->HasEdge(fromIndex, toIndex)) // 检查边是否存在
    {
        adjacencyLists[fromIndex].push_back(GraphEdge<weight_type>(fromIndex, toIndex, isDirEdge, weight));

        if (!isDirEdge)
        {
            adjacencyLists[toIndex].push_back(GraphEdge<weight_type>(toIndex, fromIndex, isDirEdge, weight));
        }
    }
    Graph<value_type, weight_type>::AddEdge(fromIndex, toIndex, isDirEdge, weight);
}

template<typename value_type>
inline void LGraph<value_type, Pipeline>::AddEdge(int fromIndex, int toIndex, bool isDirEdge, const Pipeline& weight)
{
    if (fromIndex >= 0 && fromIndex < this->nodes.size() &&
        toIndex >= 0 && toIndex < this->nodes.size() &&
        !this->HasEdge(fromIndex, toIndex)) // 检查边是否存在
    {
        adjacencyLists[fromIndex].push_back(GraphEdge<Pipeline>(fromIndex, toIndex, isDirEdge, weight));

        if (!isDirEdge)
        {
            adjacencyLists[toIndex].push_back(GraphEdge<Pipeline>(toIndex, fromIndex, isDirEdge, weight));
        }
    }
    Graph<value_type, Pipeline>::AddEdge(fromIndex, toIndex, isDirEdge, weight);
}

template<typename value_type, typename weight_type>
inline void LGraph<value_type, weight_type>::RemoveEdge(int fromIndex, int toIndex, bool isDirEdge)
{
    auto& neighbors = adjacencyLists[fromIndex];

    // 删除 fromIndex 结点的邻居列表中与 toIndex 相关的边
    neighbors.erase(std::remove_if(neighbors.begin(), neighbors.end(), [&](const auto& neighbor) {
        return neighbor.NeighborIndex() == toIndex;
    }), neighbors.end());

    // 如果是无向图，删除 toIndex 结点的邻居列表中与 fromIndex 相关的边
    if (!isDirEdge)
    {
        auto& neighborsTo = adjacencyLists[toIndex];
        neighborsTo.erase(std::remove_if(neighborsTo.begin(), neighborsTo.end(), [&](const auto& neighbor) {
            return neighbor.NeighborIndex() == fromIndex;
        }), neighborsTo.end());
    }

    Graph<value_type, weight_type>::RemoveEdge(fromIndex, toIndex, isDirEdge);
}

template<typename value_type, typename weight_type>
inline weight_type LGraph<value_type, weight_type>::GetWeight(int fromIndex, int toIndex) const
{
    weight_type res = std::numeric_limits<weight_type>::max();
    if (fromIndex >= 0 && fromIndex < this->nodes.size() &&
        toIndex >= 0 && toIndex < this->nodes.size())
    {
        const auto& neighbors = adjacencyLists[fromIndex];
        for (const auto& neighbor : neighbors)
        {
            if (neighbor.NeighborIndex() == toIndex)
            {
                res = neighbor.Weight();
                break;
            }
        }
    }

    return res;
}

template<typename value_type>
inline Pipeline LGraph<value_type, Pipeline>::GetWeight(int fromIndex, int toIndex) const
{
    Pipeline res = Pipeline(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    if (fromIndex >= 0 && fromIndex < this->nodes.size() &&
        toIndex >= 0 && toIndex < this->nodes.size())
    {
        const auto& neighbors = adjacencyLists[fromIndex];
        for (const auto& neighbor : neighbors)
        {
            if (neighbor.NeighborIndex() == toIndex)
            {
                res = neighbor.Weight();
                break;
            }
        }
    }

    return res;
}

template<typename value_type, typename weight_type>
inline void LGraph<value_type, weight_type>::Output(std::ostream& out) const
{
    for (int i = 0; i < this->nodes.size(); i++)
    {
        out << "Node " << i << ": ";
        out << RED_COLOR_CODE << this->nodes[i].Value() << DEFAULT_COLOR_CODE;
        out << " -> ";
        const auto& neighbors = adjacencyLists[i];
        for (const auto& neighbor : neighbors)
        {
            out << '(' << neighbor.NeighborIndex() << ": ";
            out << RED_COLOR_CODE << this->nodes[neighbor.NeighborIndex()].Value() << DEFAULT_COLOR_CODE;
            out << ", " << neighbor.Weight() << ") ";
        }
        out << '\n';
    }
}

template<typename value_type>
inline void LGraph<value_type, Pipeline>::Output(std::ostream& out) const
{
    for (int i = 0; i < this->nodes.size(); i++)
    {
        out << "Node " << i << ": ";
        out << RED_COLOR_CODE << this->nodes[i].Value() << DEFAULT_COLOR_CODE;
        out << " -> ";
        const auto& neighbors = adjacencyLists[i];
        for (const auto& neighbor : neighbors)
        {
            out << '(' << neighbor.NeighborIndex() << ": ";
            out << RED_COLOR_CODE << this->nodes[neighbor.NeighborIndex()].Value() << DEFAULT_COLOR_CODE;
            out << ", " << neighbor.Weight() << ") ";
        }
        out << '\n';
    }
}

template<typename value_type, typename weight_type>
inline bool LGraph<value_type, weight_type>::For_each_adjacency_vertices(int curNodeIndex, const std::function<bool(const GraphEdge<weight_type>&)>& func) const
{
    const auto& neighbors = adjacencyLists[curNodeIndex];
    for (const auto& neighbor : neighbors)
    {
        if (!func(neighbor)) // 回调函数返回 false，终止遍历
        {
            return false;
        }
    }
    return true;
}

template<typename value_type, typename weight_type>
inline bool LGraph<value_type, weight_type>::For_each_adjacency_vertices(int curNodeIndex, const std::function<bool(GraphEdge<weight_type>&)>& func)
{
    auto& neighbors = adjacencyLists[curNodeIndex];
    for (auto& neighbor : neighbors)
    {
        if (!func(neighbor)) // 回调函数返回 false，终止遍历
        {
            return false;
        }
    }
    return true;
}

template<typename value_type>
bool LGraph<value_type, Pipeline>::For_each_adjacency_vertices(int curNodeIndex, const std::function<bool(const GraphEdge<Pipeline>&)>& func) const
{
    const auto& neighbors = adjacencyLists[curNodeIndex];
    for (const auto& neighbor : neighbors)
    {
        if (!func(neighbor)) // 回调函数返回 false，终止遍历
        {
            return false;
        }
    }
    return true;
}

template<typename value_type>
bool LGraph<value_type, Pipeline>::For_each_adjacency_vertices(int curNodeIndex, const std::function<bool(GraphEdge<Pipeline>&)>& func)
{
    auto& neighbors = adjacencyLists[curNodeIndex];
    for (auto& neighbor : neighbors)
    {
        if (!func(neighbor)) // 回调函数返回 false，终止遍历
        {
            return false;
        }
    }
    return true;
}
MYLIB_END // mylib

// 尝试多线程，但是失败了
//template<typename value_type>
//bool LGraph<value_type, Pipeline>::For_each_adjacency_vertices(int curNodeIndex, const std::function<bool(GraphEdge<Pipeline>&)>& func)
//{
//    auto& neighbors = adjacencyLists[curNodeIndex];
//    std::vector<std::thread> threads;
//    std::atomic<bool> stop(false);
//
//    for (auto& neighbor : neighbors)
//    {
//        threads.emplace_back([&func, &neighbor, &stop]() {
//            if (!func(neighbor))
//            stop.store(true, std::memory_order_relaxed);
//            });
//    }
//
//    for (auto& thread : threads)
//    {
//        thread.join();
//    }
//
//    return !stop.load(std::memory_order_relaxed);
//}