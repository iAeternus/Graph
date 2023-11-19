/*****************************************************************//**
 * \file   Graph.h
 * \brief  图抽象类
 * 
 * \author 吴子维
 * \date   September 2023
 * \version 1.0 完成了基类和邻接链表派生类的构建，使用 lambda 表达式实现遍历邻接结点
 * \version 2.0 添加了结点的继承关系，在两个派生类里实现了最小生成树算法
 * \version 3.0 将结点集和边集提入基类中，并移除了结点的继承关系
 * \version 4.0 将所有算法均在基类中实现，优化了其他实现细节
 * \version 5.0 将邻接链表从结点类移除，加入到派生类中，优化了继承结构。
 *              优化了操作结点和边的函数
 *              为实现最大流算法添加了特化类
 *********************************************************************/
#pragma once
#include "Config.h"
#include "GraphNode.h"
#include "GraphEdge.h"
#include "DisjointSet.h"

MYLIB_BEGIN
int m_time; // 深度优先搜索伪时间戳
std::vector<int> m_result; // 深度优先搜索结果数组，存储结点索引

// 用于搜索函数的结点颜色状态枚举
enum Color 
{
    WHITE, // 未访问
    GRAY, // 访问中
    BLACK // 已访问
};

// 图类型
// 模板参数必须定义算术运算符、逻辑运算符、输入输出运算符
template<typename value_type, typename weight_type = int>
class Graph
{
public:
    Graph();
    virtual ~Graph();
    Graph(const Graph& other);
    Graph& operator=(const Graph& other);
    Graph(Graph&& other) noexcept;
    Graph& operator=(Graph&& other) noexcept;

    // 获取结点数
    int NumVertices() const noexcept;
    // 获取边数
    int NumEdges() const noexcept;
    // 获取结点集
    std::vector<GraphNode<value_type>>& Nodes() const;
    // 获取边集
    std::vector<GraphEdge<weight_type>>& Edges() const;

    /**
     * \brief 添加结点.
     * \param value 要添加的结点的值
     */
    virtual void AddNode(const value_type& value);
    virtual void AddNode(const GraphNode<value_type>& node);

    /**
     * \brief 删除结点.
     * \param index 要删除的结点的索引
     */
    virtual void RemoveNode(int index);

    /**
     * \brief 添加边.
     * \param fromIndex 边的起始结点索引
     * \param toIndex 边的终止结点索引
     * \param isDirEdge 边是否是有向边 true-有向边 false-无向边
     * \param weight 边权
     */
    virtual void AddEdge(int fromIndex, int toIndex, bool isDirEdge = true, const weight_type& weight = weight_type(0));
    virtual void AddEdge(const GraphEdge<weight_type>& edge);

    /**
     * \brief 删除边.
     * \param fromIndex 边的起始结点索引
     * \param toIndex 边的终止结点索引
     * \param isDirEdge 要删除的边是否是有向边 true-有向边 false-无向边
     */
    virtual void RemoveEdge(int fromIndex, int toIndex, bool isDirEdge = true);

    /**
     * \brief 判断两个结点之间是否有边. 
     * \param fromIndex 边的起始结点索引
     * \param toIndex 边的终止结点索引
     * \return 存在边就返回 true，否则返回 false
     */
    virtual bool HasEdge(int fromIndex, int toIndex) const;

    /**
     * \brief 清空图中的所有结点和边.
     */
    virtual void Clear();

    /**
     * \brief 获取边的权重.
     * \param fromIndex 边的起始结点索引
     * \param toIndex 边的终止结点索引
     * \return 返回边的权重
     */
    virtual weight_type GetWeight(int fromIndex, int toIndex) const = 0;

    /**
     * \brief 获取结点.
     * \param index 结点索引
     * \return 返回结点的引用
     */
    virtual GraphNode<value_type>& GetNode(int index);
    virtual GraphNode<value_type>& GetNode(int index) const;

    static weight_type GetInitialWeight();

    // 输入输出
    virtual void Input(std::istream& in = std::cin);
    virtual void Output(std::ostream& out = std::cout) const = 0;

    template<typename value_type, typename weight_type>
    friend std::istream& operator>>(std::istream& in, Graph<value_type, weight_type>& graph);
    template<typename value_type, typename weight_type>
    friend std::ostream& operator<<(std::ostream& out, const Graph<value_type, weight_type>& graph);

    /**
     * \brief 以下是具体的图算法.
     */
    
    // 广度优先搜索 时间复杂度 O(V + E)
    virtual std::vector<int> bfs(int srcIndex) const;
    // 深度优先搜索 时间复杂度 O(V + E)
    virtual void dfs() const;

    // 拓扑排序 ---- 广度优先搜索思路 时间复杂度 O(V + E)
    virtual std::vector<int> Topological_Sort_BFS() const;

    // Prim算法求最小生成树 时间复杂度 O(ElgV)
    virtual void MST_Prim(Graph<value_type, weight_type>*& minSpanningTree, weight_type& graphWeight) const;
    // Kruskal算法求最小生成树 时间复杂度 O(ElgV)
    virtual void MST_Kruskal(Graph<value_type, weight_type>*& minSpanningTree, weight_type& graphWeight) const;

    // 单源最短路径问题（边权为正）Dijkstra算法 时间复杂度 O((E + V)lgV)，若所有结点均可从源结点到达，则该时间为 O(ElgV)
    virtual std::pair<std::vector<int>, std::vector<weight_type>> Dijkstra(int srcIndex) const;
    // 打印最短路径信息
    static void print_path(Graph<value_type, weight_type>* const graph, const std::pair<std::vector<int>, std::vector<int>>& res, int srcIndex);
    // 单源最短路径问题（边权可为负）Bellman_Ford算法 时间复杂度 O(VE)
    virtual std::tuple<std::vector<int>, std::vector<weight_type>, bool> Bellman_Ford(int srcIndex) const;
    // 所有点对最短路径问题 Floyd_Warshall算法 时间复杂度Θ(V^3)
    virtual std::pair<std::vector<std::vector<int>>, std::vector<std::vector<weight_type>>> Floyd_Warshall() const;
    // 获取最优解
    void Find_path(const std::vector<std::vector<int>>& rec, int u, int v);

protected:
    int numVertices; // 结点数
    int numEdges; // 边数
    mutable std::vector<GraphNode<value_type>> nodes; // 结点集
    mutable std::vector<GraphEdge<weight_type>> edges; // 边集

    /**
     * \brief 遍历图中结点的邻接结点.
     * \param curNodeIndex 原结点索引
     * \param func(GraphEdge<weight_type>) 对邻接结点的操作函数
     * 
     * \brief func(GraphEdge<weight_type>)
     *      \param GraphEdge<weight_type> 链接邻接定点的边
     */
    virtual bool For_each_adjacency_vertices(int curNodeIndex, const std::function<bool(const GraphEdge<weight_type>&)>& func) const = 0;
    virtual bool For_each_adjacency_vertices(int curNodeIndex, const std::function<bool(GraphEdge<weight_type>&)>& func) = 0;

    // 深度优先搜索访问函数
    void dfs_Visit(
        std::vector<Color>& color,
        std::vector<int>& pred,
        std::vector<int>& d,
        std::vector<int>& f,
        int srcIndex
    ) const;
};

// 偏特化 Graph 类
template<typename value_type>
class Graph<value_type, Pipeline>
{
public:
    virtual void AddNode(const value_type& value);
    virtual void AddNode(const GraphNode<value_type>& node);
    virtual void AddEdge(int fromIndex, int toIndex, bool isDirEdge = true, const Pipeline& weight = 0);
    virtual Pipeline GetWeight(int fromIndex, int toIndex) const = 0;
    virtual void Output(std::ostream& out = std::cout) const = 0;

    virtual bool HasEdge(int fromIndex, int toIndex) const;
    static Pipeline GetInitialWeight();

    // 最大流问题 Ford_Fulkerson算法 时间复杂度 O(E|f*|)（f*表示转换后网络中的一个最大流，竖线表示绝对值）
    double Ford_Fulkerson(int srcIndex, int dstIndex);

protected:
    int numVertices; // 结点数
    int numEdges; // 边数
    mutable std::vector<GraphNode<value_type>> nodes; // 结点集
    mutable std::vector<GraphEdge<Pipeline>> edges; // 边集

    virtual bool For_each_adjacency_vertices(int curNodeIndex, const std::function<bool(const GraphEdge<Pipeline>&)>& func) const = 0;
    virtual bool For_each_adjacency_vertices(int curNodeIndex, const std::function<bool(GraphEdge<Pipeline>&)>& func) = 0;

    // 使用广度优先搜索找到增广路径，返回是否可以从 srcIndex 到达 dstIndex
    bool BFS(int srcIndex, int dstIndex, std::vector<int>& parent, double& pathFlow) const;
    // 在残存网络上增广路径
    void Augment(int srcIndex, int dstIndex, double pathFlow);
};

template<typename value_type, typename weight_type>
inline Graph<value_type, weight_type>::Graph() :
    numVertices(0), numEdges(0), nodes(), edges()
{}

template<typename value_type, typename weight_type>
inline Graph<value_type, weight_type>::~Graph()
{}

template<typename value_type, typename weight_type>
inline Graph<value_type, weight_type>::Graph(const Graph& other) :
    numVertices(other.numVertices), numEdges(other.numEdges), nodes(other.nodes), edges(other.edges)
{}

template<typename value_type, typename weight_type>
inline Graph<value_type, weight_type>& Graph<value_type, weight_type>::operator=(const Graph& other)
{
    if (this != &other)
    {
        this->numVertices = other.numVertices;
        this->numEdges = other.numEdges;
        this->nodes = other.nodes;
        this->edges = other.edges;
    }
    return *this;
}

template<typename value_type, typename weight_type>
inline Graph<value_type, weight_type>::Graph(Graph&& other) noexcept :
    numVertices(other.numVertices), numEdges(other.numEdges), nodes(std::move(other.nodes)), edges(std::move(other.edges))
{}

template<typename value_type, typename weight_type>
inline Graph<value_type, weight_type>& Graph<value_type, weight_type>::operator=(Graph&& other) noexcept
{
    if (this != &other)
    {
        this->numVertices = other.numVertices;
        this->numEdges = other.numEdges;
        this->nodes = std::move(other.nodes);
        this->edges = std::move(other.edges);
    }
    return *this;
}

template<typename value_type, typename weight_type>
inline int Graph<value_type, weight_type>::NumVertices() const noexcept
{
    return this->numVertices;
}

template<typename value_type, typename weight_type>
inline int Graph<value_type, weight_type>::NumEdges() const noexcept
{
    return this->numEdges;
}

template<typename value_type, typename weight_type>
inline std::vector<GraphNode<value_type>>& Graph<value_type, weight_type>::Nodes() const
{
    return this->nodes;
}

template<typename value_type, typename weight_type>
inline std::vector<GraphEdge<weight_type>>& Graph<value_type, weight_type>::Edges() const
{
    return this->edges;
}

template<typename value_type, typename weight_type>
inline void Graph<value_type, weight_type>::AddNode(const value_type& value)
{
    nodes.push_back(GraphNode<value_type>(value));
    ++numVertices;
}

template<typename value_type, typename weight_type>
inline void Graph<value_type, weight_type>::AddNode(const GraphNode<value_type>& node)
{
    nodes.push_back(node);
    ++numVertices;
}

template<typename value_type>
inline void Graph<value_type, Pipeline>::AddNode(const value_type& value)
{
    nodes.push_back(GraphNode<value_type>(value));
    ++numVertices;
}

template<typename value_type>
inline void Graph<value_type, Pipeline>::AddNode(const GraphNode<value_type>& node)
{
    nodes.push_back(node);
    ++numVertices;
}

template<typename value_type, typename weight_type>
inline void Graph<value_type, weight_type>::RemoveNode(int index)
{
    // 删除与结点相关的边
    edges.erase(
        // 判断边是否与被删除结点相关
        std::remove_if(edges.begin(), edges.end(), [index](const GraphEdge<weight_type>& edge)->bool {
            return edge.FromIndex() == index || edge.ToIndex() == index;
        }),
        edges.end()
    );
    // 更新边数
    numEdges = edges.size();

    nodes.erase(nodes.begin() + index);
    --numVertices;
}

template<typename value_type, typename weight_type>
inline void Graph<value_type, weight_type>::AddEdge(int fromIndex, int toIndex, bool isDirEdge, const weight_type& weight)
{
    edges.push_back(GraphEdge(fromIndex, toIndex, isDirEdge, weight));
    ++numEdges;

    // 更新结点的入度和出度
    nodes[toIndex].In_degree_plus_one();
    nodes[fromIndex].Out_degree_plus_one();

    if (!isDirEdge)
    {
        edges.push_back(GraphEdge(toIndex, fromIndex, isDirEdge, weight));
        ++numEdges;

        // 更新结点的入度和出度
        nodes[fromIndex].In_degree_plus_one();
        nodes[toIndex].Out_degree_plus_one();
    }
}

template<typename value_type, typename weight_type>
inline void Graph<value_type, weight_type>::AddEdge(const GraphEdge<weight_type>& edge) // TODO
{
    AddEdge(edge.FromIndex(), edge.ToIndex(), edge.IsDirEdge(), edge.Weight());
}

template<typename value_type>
void Graph<value_type, Pipeline>::AddEdge(int fromIndex, int toIndex, bool isDirEdge, const Pipeline& weight)
{
    edges.push_back(GraphEdge(fromIndex, toIndex, isDirEdge, weight));
    ++numEdges;

    // 更新结点的入度和出度
    nodes[toIndex].In_degree_plus_one();
    nodes[fromIndex].Out_degree_plus_one();

    if (!isDirEdge)
    {
        AddEdge(toIndex, fromIndex, !isDirEdge, weight);
    }
}

template<typename value_type, typename weight_type>
inline void Graph<value_type, weight_type>::RemoveEdge(int fromIndex, int toIndex, bool isDirEdge)
{
    // 从边集中移除对应的边
    auto it = std::find_if(edges.begin(), edges.end(), [&](const GraphEdge<weight_type>& edge) {
        return edge.FromIndex() == fromIndex && edge.ToIndex() == toIndex && edge.IsDirEdge() == isDirEdge;
    });

    if (it != edges.end())
    {
        edges.erase(it);
        --numEdges;

        // 更新结点的入度和出度
        nodes[toIndex].In_degree_minus_one();
        nodes[fromIndex].Out_degree_minus_one();
    }
}

template<typename value_type, typename weight_type>
inline bool Graph<value_type, weight_type>::HasEdge(int fromIndex, int toIndex) const
{
    return GetWeight(fromIndex, toIndex) != std::numeric_limits<weight_type>::max();
}

template<typename value_type>
bool Graph<value_type, Pipeline>::HasEdge(int fromIndex, int toIndex) const
{
    return GetWeight(fromIndex, toIndex) != Pipeline(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
}

template<typename value_type, typename weight_type>
inline void Graph<value_type, weight_type>::Clear()
{
    nodes.clear();
    edges.clear();
    numVertices = 0;
    numEdges = 0;
}

template<typename value_type, typename weight_type>
weight_type Graph<value_type, weight_type>::GetInitialWeight()
{
    return std::numeric_limits<weight_type>::max();
}

template<typename value_type>
Pipeline Graph<value_type, Pipeline>::GetInitialWeight()
{
    return Pipeline(0, std::numeric_limits<double>::max());
}

template<typename value_type, typename weight_type>
inline GraphNode<value_type>& Graph<value_type, weight_type>::GetNode(int index)
{
    return nodes[index];
}

template<typename value_type, typename weight_type>
inline GraphNode<value_type>& Graph<value_type, weight_type>::GetNode(int index) const
{
    return nodes[index];
}

template<typename value_type, typename weight_type>
inline void Graph<value_type, weight_type>::Input(std::istream& in)
{
    bool tag = true; // 是否允许输入的标志

    std::cout << "输入结点 > \n";
    value_type value = value_type();
    while (tag)
    {
        while (!(in >> value))
        {
            std::cout << "不正确的输入！请重新输入 > ";
            in.clear(); // 清除错误状态
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略当前行
        }
        if (in.peek() == '\n')
        {
            tag = false;
        }
        AddNode(value);
    }

    Output(); // 查看索引
    tag = true;
    int maxEdgeCnt = numVertices * numVertices;
    std::cout << "输入最多 " << maxEdgeCnt << " 条边，格式为边的 来源、去向、是否为有向边、权重（无权写 0），输入‘#’停止 > \n";

    char ch = 0;
    GraphEdge<weight_type> edge;
    for (int i = 0; tag && i < maxEdgeCnt; i++)
    {
        in >> ch;
        if (ch != '#')
        {
            in.putback(ch);
            in >> edge;
            AddEdge(edge);
        }
        else
        {
            tag = false;
        }
    }
}

template<typename value_type, typename weight_type>
std::istream& operator>>(std::istream& in, Graph<value_type, weight_type>& graph)
{
    graph.Input();
    return in;
}

template<typename value_type, typename weight_type>
std::ostream& operator<<(std::ostream& out, const Graph<value_type, weight_type>& graph)
{
    graph.Output();
    return out;
}

template<typename value_type, typename weight_type>
inline std::vector<int> Graph<value_type, weight_type>::bfs(int srcIndex) const
{
    // 初始化
    std::vector<Color> color(numVertices, WHITE); // 颜色
    std::vector<int> pred(numVertices, -1); // 前驱
    std::vector<int> dist(numVertices, std::numeric_limits<int>::max()); // 距离
    std::vector<int> visited; // 搜索到的结点索引数组
    std::queue<int> Q; // 等待队列

    if (srcIndex < 0 || srcIndex > numVertices)
    {
        std::cout << "Incorrect srcIndex!\n";
        return visited;
    }

    color[srcIndex] = GRAY;
    dist[srcIndex] = 0;
    Q.push(srcIndex);

    // 广度优先搜索
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();

        For_each_adjacency_vertices(u, [&](const GraphEdge<weight_type>& neighbor)->bool {
            if (color[neighbor.NeighborIndex()] == WHITE)
            {
                color[neighbor.NeighborIndex()] = GRAY;
                dist[neighbor.NeighborIndex()] = dist[u] + 1;
                pred[neighbor.NeighborIndex()] = u;
                Q.push(neighbor.NeighborIndex());
            }
            return true;
        });

        visited.push_back(u);
        color[u] = BLACK;
    }

    return visited;
}

template<typename value_type, typename weight_type>
inline void Graph<value_type, weight_type>::dfs() const
{
    // 初始化
    std::vector<Color> color(numVertices + 1, WHITE);
    std::vector<int> pred(numVertices, -1);
    std::vector<int> d(numVertices, 0); // 记录结点 i 的发现时刻
    std::vector<int> f(numVertices, 0); // 记录结点 i 的结束时刻
    m_time = 0; // 时间从 0 开始

    // 深度优先搜索
    m_result.clear();

    for (int i = 0; i < numVertices; i++)
    {
        if (color[i] == WHITE)
        {
            dfs_Visit(color, pred, d, f, i);
        }
    }
}

template<typename value_type, typename weight_type>
inline std::vector<int> Graph<value_type, weight_type>::Topological_Sort_BFS() const
{
    std::vector<int> res;
    std::queue<int> Q; // 记录入度为 0 的结点索引

    for (int i = 0; i < numVertices; i++)
    {
        if (GetNode(i).In_degree() == 0) // 入度为 0，加入队列
        {
            Q.push(i);
        }
    }

    int item;
    while (!Q.empty())
    {
        // 完成事件
        item = Q.front();
        Q.pop();
        res.push_back(item);

        // 删除事件，更新入度
        For_each_adjacency_vertices(item, [&](const GraphEdge<weight_type>& neighbor)->bool {
            GetNode(neighbor.NeighborIndex()).In_degree_minus_one(); // --node.in_degree;  TODO constant???
            if (GetNode(neighbor.NeighborIndex()).In_degree() == 0)
            {
                Q.push(neighbor.NeighborIndex());
            }
            return true;
        });
    }
    return res;
}

template<typename value_type, typename weight_type>
inline void Graph<value_type, weight_type>::MST_Prim(Graph<value_type, weight_type>*& minSpanningTree, weight_type& graphWeight) const
{
    minSpanningTree->Clear();
    graphWeight = 0; // 图的权重

    // 初始化最小生成树
    for (int i = 0; i < numVertices; i++)
    {
        minSpanningTree->AddNode(GetNode(i).Value());
    }
    // 初始化辅助数组
    std::vector<bool> visited(numVertices, false);
    std::vector<weight_type> dist(numVertices, std::numeric_limits<weight_type>::max());
    std::vector<int> pred(numVertices, -1);
    // 使用优先队列优化算法
    using pq_element = std::pair<weight_type, int>; // 邻接结点权重和索引
    std::priority_queue<pq_element, std::vector<pq_element>, std::greater<pq_element>> priorityQueue;

    dist[0] = 0; // 选择任意结点作为起点

    priorityQueue.push(std::make_pair(0, 0)); // 初始结点的权重为0
    while (!priorityQueue.empty())
    {
        int cur = priorityQueue.top().second; // 当前结点的索引
        weight_type curDist = priorityQueue.top().first; // 依赖优先队列快速发现轻边
        priorityQueue.pop();

        if (visited[cur]) continue;

        visited[cur] = true; // 标记结点为已访问
        graphWeight += curDist; // 维护图的权重

        // 将对应的边加入最小生成树
        if (pred[cur] != -1)
        {
            weight_type weight = GetWeight(pred[cur], cur);
            minSpanningTree->AddEdge(pred[cur], cur, false, weight); // 添加边
        }

        // 对每个与 cur 邻接但却不在树中的结点 v 的距离和前驱进行更新
        For_each_adjacency_vertices(cur, [&](const GraphEdge<weight_type>& neighbor)->bool {
            int neighborIdx = neighbor.NeighborIndex();
            weight_type weight = neighbor.Weight();

            if (!visited[neighborIdx] && weight < dist[neighborIdx])
            {
                dist[neighborIdx] = weight;
                pred[neighborIdx] = cur;
                priorityQueue.push(std::make_pair(weight, neighborIdx));
            }
            return true;
        });
    }
}

template<typename value_type, typename weight_type>
inline void Graph<value_type, weight_type>::MST_Kruskal(Graph<value_type, weight_type>*& minSpanningTree, weight_type& graphWeight) const
{
    minSpanningTree->Clear();
    graphWeight = 0; // 图的权重

    // 初始化最小生成树
    for (int i = 0; i < this->numVertices; i++)
    {
        minSpanningTree->AddNode(GetNode(i).Value());
    }

    // 创建不相交集并初始化每个元素为一个独立的集合
    DisjointSet ds(numVertices);

    // 对边按照权重升序排序
    std::vector<GraphEdge<weight_type>> sortedEdges = edges;
    std::sort(sortedEdges.begin(), sortedEdges.end(), [](const GraphEdge<weight_type>& a, const GraphEdge<weight_type>& b) {
        return a.Weight() < b.Weight();
    });

    for (const auto& edge : sortedEdges)
    {
        int fromIndex = edge.FromIndex();
        int toIndex = edge.ToIndex();

        // 检查结点是否属于不同的集合
        if (ds.find_set(fromIndex) != ds.find_set(toIndex))
        {
            // 将边添加到最小生成树中
            minSpanningTree->AddEdge(edge);
            // 将结点合并到同一个集合
            ds.union_set(fromIndex, toIndex);
            // 累加边的权重到图的权重
            graphWeight += edge.Weight();
        }
    }
}

template<typename value_type, typename weight_type>
inline std::pair<std::vector<int>, std::vector<weight_type>> Graph<value_type, weight_type>::Dijkstra(int srcIndex) const
{
    // 初始化
    std::vector<bool> color(numVertices, false);
    std::vector<int> pred(numVertices, -1);
    std::vector<weight_type> dist(numVertices, std::numeric_limits<weight_type>::max());

    if (srcIndex < 0 || srcIndex > numVertices - 1)
    {
        std::cout << "Incorrect srcIndex!\n";
        return std::make_pair(pred, dist);
    }

    // 使用优先队列优化算法
    using pq_element = std::pair<weight_type, int>; // 权重和邻接结点索引
    std::priority_queue<pq_element, std::vector<pq_element>, std::greater<pq_element>> priorityQueue;
    dist[srcIndex] = 0;

    // 执行单源最短路径算法
    priorityQueue.push(std::make_pair(0, srcIndex)); // 初始结点的权重为0
    while (!priorityQueue.empty())
    {
        pq_element top = priorityQueue.top();
        priorityQueue.pop();
        weight_type minDist = top.first;
        int rec = top.second;

        if (color[rec]) continue; // 已经访问过该结点

        // 对 rec 出发的边进行松弛
        For_each_adjacency_vertices(rec, [&](const GraphEdge<weight_type>& neighbor)->bool {
            weight_type weight = GetWeight(rec, neighbor.NeighborIndex());
            if (dist[rec] + weight < dist[neighbor.NeighborIndex()]) // 松弛
            {
                dist[neighbor.NeighborIndex()] = dist[rec] + weight;
                pred[neighbor.NeighborIndex()] = rec;
                priorityQueue.push(std::make_pair(dist[neighbor.NeighborIndex()], neighbor.NeighborIndex()));
            }
            return true;
        });

        color[rec] = true;
    }

    return std::make_pair(pred, dist);
}

template<typename value_type, typename weight_type>
inline void Graph<value_type, weight_type>::print_path(Graph<value_type, weight_type>* const graph, const std::pair<std::vector<int>, std::vector<int>>& res, int srcIndex)
{
    if (srcIndex < 0 || srcIndex > graph->numVertices - 1)
    {
        std::cout << "Incorrect srcIndex!\n";
        return;
    }

    auto& [pred, dist] = res;

    for (int i = 0; i < graph->NumVertices(); i++)
    {
        if (dist[srcIndex] && dist[i] != 1e8) // 判断可达性 TODO 1e8 to xxx::max()
        {
            std::cout << "The shortest path from " << graph->GetNode(srcIndex).Value() << " to " << graph->GetNode(i).Value() << ": ";
            // 输出路径名称，按照pred中的顺序
            std::cout << graph->GetNode(srcIndex).Value(); // 输出起点
            int current = i;
            std::vector<int> temp; // 临时存储路径索引
            while (current != srcIndex)
            {
                temp.push_back(current);
                current = pred[current];
            }
            std::reverse(temp.begin(), temp.end());
            for (int j = 0; j < temp.size(); j++)
            {
                std::cout << " -> " << graph->GetNode(temp[j]).Value();
            }

            std::cout << '\n';
            std::cout << "Path weight = " << dist[i] << std::endl;
        }
        else
        {
            std::cout << "The shortest path from " << graph->GetNode(srcIndex).Value() 
                << " to " << graph->GetNode(i).Value() << " is not reachable\n";
        }
    }
}

template<typename value_type, typename weight_type>
inline std::tuple<std::vector<int>, std::vector<weight_type>, bool> Graph<value_type, weight_type>::Bellman_Ford(int srcIndex) const
{
    // 初始化距离数组和前驱数组
    std::vector<int> pred(numVertices, -1);
    std::vector<weight_type> dist(numVertices, 1e8); // TODO
    bool hasNegativeLoop = false;

    if (srcIndex < 0 || srcIndex > numVertices - 1)
    {
        std::cout << "Incorrect srcIndex!\n";
        return std::make_tuple(pred, dist, hasNegativeLoop);
    }

    dist[srcIndex] = 0;

    // 进行 |V|-1 轮松弛操作
    for (int i = 0; i < numVertices - 1; i++)
    {
        // 遍历图中的每条边
        for (const auto& edge : edges)
        {
            int fromIndex = edge.FromIndex();
            int toIndex = edge.ToIndex();
            weight_type weight = GetWeight(fromIndex, toIndex);

            // 判断是否可以通过当前边缩短路径长度
            if (dist[fromIndex] + weight < dist[toIndex])
            {
                dist[toIndex] = dist[fromIndex] + weight;
                pred[toIndex] = fromIndex;
            }
        }
    }

    // 检查是否存在负环
    for (const auto& edge : edges)
    {
        int fromIndex = edge.FromIndex();
        int toIndex = edge.ToIndex();
        // 若在|V|-1次松弛操作后，依然存在路径长度缩短的情况，则存在负环，终止遍历
        if (dist[fromIndex] + GetWeight(fromIndex, toIndex) < dist[toIndex])
        {
            hasNegativeLoop = true;
            break;
        }
    }

    // 返回最短路径长度数组、前驱数组和是否存在负环的标志
    return std::make_tuple(pred, dist, hasNegativeLoop);
}

template<typename value_type, typename weight_type>
inline std::pair<std::vector<std::vector<int>>, std::vector<std::vector<weight_type>>> Graph<value_type, weight_type>::Floyd_Warshall() const
{
    // 用于记录路径的矩阵
    std::vector<std::vector<int>> rec(numVertices, std::vector<int>(numVertices, -1)); 
    // 设置初始距离为正无穷
    std::vector<std::vector<weight_type>> dp(numVertices, std::vector<weight_type>(numVertices, std::numeric_limits<weight_type>::max())); 

    // base case
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            if (i == j)
            {
                dp[i][j] = 0; // 设置起终点相同的距离为0
            }
            else
            {
                weight_type weight = GetWeight(i, j);
                if (weight != weight_type{}) // 检查是否存在边
                {
                    dp[i][j] = weight; // 起终点不同，距离为边权
                }
            }
        }
    }

    // dp
    // dp[i][j]: 结点 i 和结点 j 的最短路径为 dp[i][j]
    // dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j])
    for (int k = 0; k < numVertices; k++)
    {
        for (int i = 0; i < numVertices; i++)
        {
            if (dp[i][k] == std::numeric_limits<weight_type>::max()) continue; // 跳过不可达的情况

            for (int j = 0; j < numVertices; j++)
            {
                // 检查是否有更短的路径
                if (dp[k][j] != std::numeric_limits<weight_type>::max() && dp[i][j] > dp[i][k] + dp[k][j])
                {
                    dp[i][j] = dp[i][k] + dp[k][j]; // 更新路径长度
                    rec[i][j] = k; // 记录路径上经过的结点
                }
            }
        }
    }

    return std::make_pair(rec, dp);
}

template<typename value_type, typename weight_type>
inline void Graph<value_type, weight_type>::Find_path(const std::vector<std::vector<int>>& rec, int u, int v)
{
    if (u == v)
    {
        std::cout << GetNode(u).Value() << " "; // 打印路径中的结点值（起点和终点相同）
    }
    else if (rec[u][v] == -1)
    {
        std::cout << GetNode(u).Value() << "->" << GetNode(v).Value() << " "; // 打印路径中的结点值（起点和终点不同）
    }
    else
    {
        int k = rec[u][v];
        Find_path(rec, u, k); // 递归打印从起点到经过结点 k 的部分路径
        Find_path(rec, k, v); // 递归打印从经过结点 k 到终点的部分路径
    }
}

template<typename value_type>
inline double Graph<value_type, Pipeline>::Ford_Fulkerson(int srcIndex, int dstIndex)
{
    for (int i = 0; i < numEdges; ++i)
    {
        edges[i].Weight().flowRate = 0;
    }

    double pathFlow = 0, maxFlow = 0;
    std::vector<int> parent(numVertices, -1);
    while (BFS(srcIndex, dstIndex, parent, pathFlow)) 
    {
        maxFlow += pathFlow;
        int v = dstIndex;
        while (v != srcIndex)
        {
            int u = parent[v];
            Augment(u, v, pathFlow);
            v = u;
        }
    }

    return maxFlow;
}

template<typename value_type, typename weight_type>
inline void Graph<value_type, weight_type>::dfs_Visit(
    std::vector<Color>& color, 
    std::vector<int>& pred, 
    std::vector<int>& d, 
    std::vector<int>& f, 
    int srcIndex
) const
{
    color[srcIndex] = GRAY;
    m_time++;
    d[srcIndex] = m_time; // 记录开始时间

    For_each_adjacency_vertices(srcIndex, [&](const GraphEdge<weight_type>& neighbor)->bool {
        if (color[neighbor.NeighborIndex()] == WHITE)
        {
            pred[neighbor.NeighborIndex()] = srcIndex;
            dfs_Visit(color, pred, d, f, neighbor.NeighborIndex()); // 深挖
        }
        return true;
    });

    color[srcIndex] = BLACK;
    m_time++;
    f[srcIndex] = m_time; // 记录结束时间

    // 遍历结点的顺序
    m_result.push_back(srcIndex);
}

// 使用广度优先搜索查找从源结点(srcIndex)到目标结点(dstIndex)的增广路径
template<typename value_type>
inline bool Graph<value_type, Pipeline>::BFS(int srcIndex, int dstIndex, std::vector<int>& parent, double& pathFlow) const
{
    // 初始化父结点数组，用于记录最短路径树
    parent[srcIndex] = srcIndex;

    std::queue<std::pair<int, double>> q;
    q.push({ srcIndex, std::numeric_limits<double>::max() }); // 初始时，路径流量设置为无穷大

    bool isReachable = false; // 初始化可达性标志

    while (!isReachable && !q.empty())
    {
        int u = q.front().first; // 当前结点
        double capacity = q.front().second; // 当前路径上的最小剩余容量
        q.pop();

        // 遍历u的邻接结点
        For_each_adjacency_vertices(u, [&](const GraphEdge<Pipeline>& neighbor) -> bool {
            int v = neighbor.NeighborIndex();
            double residualCapacity = neighbor.Weight().residual();

            // 如果v未被访问且路径上还有剩余容量
            if (parent[v] == -1 && residualCapacity > 0)
            {
                parent[v] = u; // 记录v的父结点为u，构建最短路径树
                double minCapacity = std::min(capacity, residualCapacity); // 计算最小剩余容量

                // 如果v是目标结点，就找到了增广路径
                if (v == dstIndex)
                {
                    pathFlow = minCapacity; // 设置路径流量
                    isReachable = true; // 找到了增广路径
                    return false; // 停止迭代
                }

                // 将v和最小剩余容量加入队列，继续BFS遍历
                q.push({ v, minCapacity });
            }
            return true; // 继续迭代
        });
    }

    // 返回是否找到可达路径
    return isReachable;
}

template<typename value_type>
inline void Graph<value_type, Pipeline>::Augment(int srcIndex, int dstIndex, double pathFlow)
{
    // 在正向边上增加流量
    bool tag = For_each_adjacency_vertices(srcIndex, [&](GraphEdge<Pipeline>& neighbor)->bool {
        if (neighbor.NeighborIndex() == dstIndex)
        {
            neighbor.Weight().flowRate += pathFlow;
            return false; // return;
        }
        return true;
    });

    if (tag)
    {
        // 在反向边上减少流量
        For_each_adjacency_vertices(dstIndex, [&](GraphEdge<Pipeline>& neighbor)->bool {
            if (neighbor.NeighborIndex() == srcIndex)
            {
                neighbor.Weight().flowRate -= pathFlow;
                return false; // return;
            }
            return true;
        });
    }
}
MYLIB_END // mylib