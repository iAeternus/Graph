/*****************************************************************//**
 * \file   Graph.h
 * \brief  ͼ������
 * 
 * \author ����ά
 * \date   September 2023
 * \version 1.0 ����˻�����ڽ�����������Ĺ�����ʹ�� lambda ���ʽʵ�ֱ����ڽӽ��
 * \version 2.0 ����˽��ļ̳й�ϵ����������������ʵ������С�������㷨
 * \version 3.0 ����㼯�ͱ߼���������У����Ƴ��˽��ļ̳й�ϵ
 * \version 4.0 �������㷨���ڻ�����ʵ�֣��Ż�������ʵ��ϸ��
 * \version 5.0 ���ڽ�����ӽ�����Ƴ������뵽�������У��Ż��˼̳нṹ��
 *              �Ż��˲������ͱߵĺ���
 *              Ϊʵ��������㷨������ػ���
 *********************************************************************/
#pragma once
#include "Config.h"
#include "GraphNode.h"
#include "GraphEdge.h"
#include "DisjointSet.h"

MYLIB_BEGIN
int m_time; // �����������αʱ���
std::vector<int> m_result; // �����������������飬�洢�������

// �������������Ľ����ɫ״̬ö��
enum Color 
{
    WHITE, // δ����
    GRAY, // ������
    BLACK // �ѷ���
};

// ͼ����
// ģ��������붨��������������߼��������������������
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

    // ��ȡ�����
    int NumVertices() const noexcept;
    // ��ȡ����
    int NumEdges() const noexcept;
    // ��ȡ��㼯
    std::vector<GraphNode<value_type>>& Nodes() const;
    // ��ȡ�߼�
    std::vector<GraphEdge<weight_type>>& Edges() const;

    /**
     * \brief ��ӽ��.
     * \param value Ҫ��ӵĽ���ֵ
     */
    virtual void AddNode(const value_type& value);
    virtual void AddNode(const GraphNode<value_type>& node);

    /**
     * \brief ɾ�����.
     * \param index Ҫɾ���Ľ�������
     */
    virtual void RemoveNode(int index);

    /**
     * \brief ��ӱ�.
     * \param fromIndex �ߵ���ʼ�������
     * \param toIndex �ߵ���ֹ�������
     * \param isDirEdge ���Ƿ�������� true-����� false-�����
     * \param weight ��Ȩ
     */
    virtual void AddEdge(int fromIndex, int toIndex, bool isDirEdge = true, const weight_type& weight = weight_type(0));
    virtual void AddEdge(const GraphEdge<weight_type>& edge);

    /**
     * \brief ɾ����.
     * \param fromIndex �ߵ���ʼ�������
     * \param toIndex �ߵ���ֹ�������
     * \param isDirEdge Ҫɾ���ı��Ƿ�������� true-����� false-�����
     */
    virtual void RemoveEdge(int fromIndex, int toIndex, bool isDirEdge = true);

    /**
     * \brief �ж��������֮���Ƿ��б�. 
     * \param fromIndex �ߵ���ʼ�������
     * \param toIndex �ߵ���ֹ�������
     * \return ���ڱ߾ͷ��� true�����򷵻� false
     */
    virtual bool HasEdge(int fromIndex, int toIndex) const;

    /**
     * \brief ���ͼ�е����н��ͱ�.
     */
    virtual void Clear();

    /**
     * \brief ��ȡ�ߵ�Ȩ��.
     * \param fromIndex �ߵ���ʼ�������
     * \param toIndex �ߵ���ֹ�������
     * \return ���رߵ�Ȩ��
     */
    virtual weight_type GetWeight(int fromIndex, int toIndex) const = 0;

    /**
     * \brief ��ȡ���.
     * \param index �������
     * \return ���ؽ�������
     */
    virtual GraphNode<value_type>& GetNode(int index);
    virtual GraphNode<value_type>& GetNode(int index) const;

    static weight_type GetInitialWeight();

    // �������
    virtual void Input(std::istream& in = std::cin);
    virtual void Output(std::ostream& out = std::cout) const = 0;

    template<typename value_type, typename weight_type>
    friend std::istream& operator>>(std::istream& in, Graph<value_type, weight_type>& graph);
    template<typename value_type, typename weight_type>
    friend std::ostream& operator<<(std::ostream& out, const Graph<value_type, weight_type>& graph);

    /**
     * \brief �����Ǿ����ͼ�㷨.
     */
    
    // ����������� ʱ�临�Ӷ� O(V + E)
    virtual std::vector<int> bfs(int srcIndex) const;
    // ����������� ʱ�临�Ӷ� O(V + E)
    virtual void dfs() const;

    // �������� ---- �����������˼· ʱ�临�Ӷ� O(V + E)
    virtual std::vector<int> Topological_Sort_BFS() const;

    // Prim�㷨����С������ ʱ�临�Ӷ� O(ElgV)
    virtual void MST_Prim(Graph<value_type, weight_type>*& minSpanningTree, weight_type& graphWeight) const;
    // Kruskal�㷨����С������ ʱ�临�Ӷ� O(ElgV)
    virtual void MST_Kruskal(Graph<value_type, weight_type>*& minSpanningTree, weight_type& graphWeight) const;

    // ��Դ���·�����⣨��ȨΪ����Dijkstra�㷨 ʱ�临�Ӷ� O((E + V)lgV)�������н����ɴ�Դ��㵽����ʱ��Ϊ O(ElgV)
    virtual std::pair<std::vector<int>, std::vector<weight_type>> Dijkstra(int srcIndex) const;
    // ��ӡ���·����Ϣ
    static void print_path(Graph<value_type, weight_type>* const graph, const std::pair<std::vector<int>, std::vector<int>>& res, int srcIndex);
    // ��Դ���·�����⣨��Ȩ��Ϊ����Bellman_Ford�㷨 ʱ�临�Ӷ� O(VE)
    virtual std::tuple<std::vector<int>, std::vector<weight_type>, bool> Bellman_Ford(int srcIndex) const;
    // ���е�����·������ Floyd_Warshall�㷨 ʱ�临�ӶȦ�(V^3)
    virtual std::pair<std::vector<std::vector<int>>, std::vector<std::vector<weight_type>>> Floyd_Warshall() const;
    // ��ȡ���Ž�
    void Find_path(const std::vector<std::vector<int>>& rec, int u, int v);

protected:
    int numVertices; // �����
    int numEdges; // ����
    mutable std::vector<GraphNode<value_type>> nodes; // ��㼯
    mutable std::vector<GraphEdge<weight_type>> edges; // �߼�

    /**
     * \brief ����ͼ�н����ڽӽ��.
     * \param curNodeIndex ԭ�������
     * \param func(GraphEdge<weight_type>) ���ڽӽ��Ĳ�������
     * 
     * \brief func(GraphEdge<weight_type>)
     *      \param GraphEdge<weight_type> �����ڽӶ���ı�
     */
    virtual bool For_each_adjacency_vertices(int curNodeIndex, const std::function<bool(const GraphEdge<weight_type>&)>& func) const = 0;
    virtual bool For_each_adjacency_vertices(int curNodeIndex, const std::function<bool(GraphEdge<weight_type>&)>& func) = 0;

    // ��������������ʺ���
    void dfs_Visit(
        std::vector<Color>& color,
        std::vector<int>& pred,
        std::vector<int>& d,
        std::vector<int>& f,
        int srcIndex
    ) const;
};

// ƫ�ػ� Graph ��
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

    // ��������� Ford_Fulkerson�㷨 ʱ�临�Ӷ� O(E|f*|)��f*��ʾת���������е�һ������������߱�ʾ����ֵ��
    double Ford_Fulkerson(int srcIndex, int dstIndex);

protected:
    int numVertices; // �����
    int numEdges; // ����
    mutable std::vector<GraphNode<value_type>> nodes; // ��㼯
    mutable std::vector<GraphEdge<Pipeline>> edges; // �߼�

    virtual bool For_each_adjacency_vertices(int curNodeIndex, const std::function<bool(const GraphEdge<Pipeline>&)>& func) const = 0;
    virtual bool For_each_adjacency_vertices(int curNodeIndex, const std::function<bool(GraphEdge<Pipeline>&)>& func) = 0;

    // ʹ�ù�����������ҵ�����·���������Ƿ���Դ� srcIndex ���� dstIndex
    bool BFS(int srcIndex, int dstIndex, std::vector<int>& parent, double& pathFlow) const;
    // �ڲд�����������·��
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
    // ɾ��������صı�
    edges.erase(
        // �жϱ��Ƿ��뱻ɾ��������
        std::remove_if(edges.begin(), edges.end(), [index](const GraphEdge<weight_type>& edge)->bool {
            return edge.FromIndex() == index || edge.ToIndex() == index;
        }),
        edges.end()
    );
    // ���±���
    numEdges = edges.size();

    nodes.erase(nodes.begin() + index);
    --numVertices;
}

template<typename value_type, typename weight_type>
inline void Graph<value_type, weight_type>::AddEdge(int fromIndex, int toIndex, bool isDirEdge, const weight_type& weight)
{
    edges.push_back(GraphEdge(fromIndex, toIndex, isDirEdge, weight));
    ++numEdges;

    // ���½�����Ⱥͳ���
    nodes[toIndex].In_degree_plus_one();
    nodes[fromIndex].Out_degree_plus_one();

    if (!isDirEdge)
    {
        edges.push_back(GraphEdge(toIndex, fromIndex, isDirEdge, weight));
        ++numEdges;

        // ���½�����Ⱥͳ���
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

    // ���½�����Ⱥͳ���
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
    // �ӱ߼����Ƴ���Ӧ�ı�
    auto it = std::find_if(edges.begin(), edges.end(), [&](const GraphEdge<weight_type>& edge) {
        return edge.FromIndex() == fromIndex && edge.ToIndex() == toIndex && edge.IsDirEdge() == isDirEdge;
    });

    if (it != edges.end())
    {
        edges.erase(it);
        --numEdges;

        // ���½�����Ⱥͳ���
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
    bool tag = true; // �Ƿ���������ı�־

    std::cout << "������ > \n";
    value_type value = value_type();
    while (tag)
    {
        while (!(in >> value))
        {
            std::cout << "����ȷ�����룡���������� > ";
            in.clear(); // �������״̬
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���Ե�ǰ��
        }
        if (in.peek() == '\n')
        {
            tag = false;
        }
        AddNode(value);
    }

    Output(); // �鿴����
    tag = true;
    int maxEdgeCnt = numVertices * numVertices;
    std::cout << "������� " << maxEdgeCnt << " ���ߣ���ʽΪ�ߵ� ��Դ��ȥ���Ƿ�Ϊ����ߡ�Ȩ�أ���Ȩд 0�������롮#��ֹͣ > \n";

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
    // ��ʼ��
    std::vector<Color> color(numVertices, WHITE); // ��ɫ
    std::vector<int> pred(numVertices, -1); // ǰ��
    std::vector<int> dist(numVertices, std::numeric_limits<int>::max()); // ����
    std::vector<int> visited; // �������Ľ����������
    std::queue<int> Q; // �ȴ�����

    if (srcIndex < 0 || srcIndex > numVertices)
    {
        std::cout << "Incorrect srcIndex!\n";
        return visited;
    }

    color[srcIndex] = GRAY;
    dist[srcIndex] = 0;
    Q.push(srcIndex);

    // �����������
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
    // ��ʼ��
    std::vector<Color> color(numVertices + 1, WHITE);
    std::vector<int> pred(numVertices, -1);
    std::vector<int> d(numVertices, 0); // ��¼��� i �ķ���ʱ��
    std::vector<int> f(numVertices, 0); // ��¼��� i �Ľ���ʱ��
    m_time = 0; // ʱ��� 0 ��ʼ

    // �����������
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
    std::queue<int> Q; // ��¼���Ϊ 0 �Ľ������

    for (int i = 0; i < numVertices; i++)
    {
        if (GetNode(i).In_degree() == 0) // ���Ϊ 0���������
        {
            Q.push(i);
        }
    }

    int item;
    while (!Q.empty())
    {
        // ����¼�
        item = Q.front();
        Q.pop();
        res.push_back(item);

        // ɾ���¼����������
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
    graphWeight = 0; // ͼ��Ȩ��

    // ��ʼ����С������
    for (int i = 0; i < numVertices; i++)
    {
        minSpanningTree->AddNode(GetNode(i).Value());
    }
    // ��ʼ����������
    std::vector<bool> visited(numVertices, false);
    std::vector<weight_type> dist(numVertices, std::numeric_limits<weight_type>::max());
    std::vector<int> pred(numVertices, -1);
    // ʹ�����ȶ����Ż��㷨
    using pq_element = std::pair<weight_type, int>; // �ڽӽ��Ȩ�غ�����
    std::priority_queue<pq_element, std::vector<pq_element>, std::greater<pq_element>> priorityQueue;

    dist[0] = 0; // ѡ����������Ϊ���

    priorityQueue.push(std::make_pair(0, 0)); // ��ʼ����Ȩ��Ϊ0
    while (!priorityQueue.empty())
    {
        int cur = priorityQueue.top().second; // ��ǰ��������
        weight_type curDist = priorityQueue.top().first; // �������ȶ��п��ٷ������
        priorityQueue.pop();

        if (visited[cur]) continue;

        visited[cur] = true; // ��ǽ��Ϊ�ѷ���
        graphWeight += curDist; // ά��ͼ��Ȩ��

        // ����Ӧ�ı߼�����С������
        if (pred[cur] != -1)
        {
            weight_type weight = GetWeight(pred[cur], cur);
            minSpanningTree->AddEdge(pred[cur], cur, false, weight); // ��ӱ�
        }

        // ��ÿ���� cur �ڽӵ�ȴ�������еĽ�� v �ľ����ǰ�����и���
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
    graphWeight = 0; // ͼ��Ȩ��

    // ��ʼ����С������
    for (int i = 0; i < this->numVertices; i++)
    {
        minSpanningTree->AddNode(GetNode(i).Value());
    }

    // �������ཻ������ʼ��ÿ��Ԫ��Ϊһ�������ļ���
    DisjointSet ds(numVertices);

    // �Ա߰���Ȩ����������
    std::vector<GraphEdge<weight_type>> sortedEdges = edges;
    std::sort(sortedEdges.begin(), sortedEdges.end(), [](const GraphEdge<weight_type>& a, const GraphEdge<weight_type>& b) {
        return a.Weight() < b.Weight();
    });

    for (const auto& edge : sortedEdges)
    {
        int fromIndex = edge.FromIndex();
        int toIndex = edge.ToIndex();

        // ������Ƿ����ڲ�ͬ�ļ���
        if (ds.find_set(fromIndex) != ds.find_set(toIndex))
        {
            // ������ӵ���С��������
            minSpanningTree->AddEdge(edge);
            // �����ϲ���ͬһ������
            ds.union_set(fromIndex, toIndex);
            // �ۼӱߵ�Ȩ�ص�ͼ��Ȩ��
            graphWeight += edge.Weight();
        }
    }
}

template<typename value_type, typename weight_type>
inline std::pair<std::vector<int>, std::vector<weight_type>> Graph<value_type, weight_type>::Dijkstra(int srcIndex) const
{
    // ��ʼ��
    std::vector<bool> color(numVertices, false);
    std::vector<int> pred(numVertices, -1);
    std::vector<weight_type> dist(numVertices, std::numeric_limits<weight_type>::max());

    if (srcIndex < 0 || srcIndex > numVertices - 1)
    {
        std::cout << "Incorrect srcIndex!\n";
        return std::make_pair(pred, dist);
    }

    // ʹ�����ȶ����Ż��㷨
    using pq_element = std::pair<weight_type, int>; // Ȩ�غ��ڽӽ������
    std::priority_queue<pq_element, std::vector<pq_element>, std::greater<pq_element>> priorityQueue;
    dist[srcIndex] = 0;

    // ִ�е�Դ���·���㷨
    priorityQueue.push(std::make_pair(0, srcIndex)); // ��ʼ����Ȩ��Ϊ0
    while (!priorityQueue.empty())
    {
        pq_element top = priorityQueue.top();
        priorityQueue.pop();
        weight_type minDist = top.first;
        int rec = top.second;

        if (color[rec]) continue; // �Ѿ����ʹ��ý��

        // �� rec �����ı߽����ɳ�
        For_each_adjacency_vertices(rec, [&](const GraphEdge<weight_type>& neighbor)->bool {
            weight_type weight = GetWeight(rec, neighbor.NeighborIndex());
            if (dist[rec] + weight < dist[neighbor.NeighborIndex()]) // �ɳ�
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
        if (dist[srcIndex] && dist[i] != 1e8) // �жϿɴ��� TODO 1e8 to xxx::max()
        {
            std::cout << "The shortest path from " << graph->GetNode(srcIndex).Value() << " to " << graph->GetNode(i).Value() << ": ";
            // ���·�����ƣ�����pred�е�˳��
            std::cout << graph->GetNode(srcIndex).Value(); // ������
            int current = i;
            std::vector<int> temp; // ��ʱ�洢·������
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
    // ��ʼ�����������ǰ������
    std::vector<int> pred(numVertices, -1);
    std::vector<weight_type> dist(numVertices, 1e8); // TODO
    bool hasNegativeLoop = false;

    if (srcIndex < 0 || srcIndex > numVertices - 1)
    {
        std::cout << "Incorrect srcIndex!\n";
        return std::make_tuple(pred, dist, hasNegativeLoop);
    }

    dist[srcIndex] = 0;

    // ���� |V|-1 ���ɳڲ���
    for (int i = 0; i < numVertices - 1; i++)
    {
        // ����ͼ�е�ÿ����
        for (const auto& edge : edges)
        {
            int fromIndex = edge.FromIndex();
            int toIndex = edge.ToIndex();
            weight_type weight = GetWeight(fromIndex, toIndex);

            // �ж��Ƿ����ͨ����ǰ������·������
            if (dist[fromIndex] + weight < dist[toIndex])
            {
                dist[toIndex] = dist[fromIndex] + weight;
                pred[toIndex] = fromIndex;
            }
        }
    }

    // ����Ƿ���ڸ���
    for (const auto& edge : edges)
    {
        int fromIndex = edge.FromIndex();
        int toIndex = edge.ToIndex();
        // ����|V|-1���ɳڲ�������Ȼ����·���������̵����������ڸ�������ֹ����
        if (dist[fromIndex] + GetWeight(fromIndex, toIndex) < dist[toIndex])
        {
            hasNegativeLoop = true;
            break;
        }
    }

    // �������·���������顢ǰ��������Ƿ���ڸ����ı�־
    return std::make_tuple(pred, dist, hasNegativeLoop);
}

template<typename value_type, typename weight_type>
inline std::pair<std::vector<std::vector<int>>, std::vector<std::vector<weight_type>>> Graph<value_type, weight_type>::Floyd_Warshall() const
{
    // ���ڼ�¼·���ľ���
    std::vector<std::vector<int>> rec(numVertices, std::vector<int>(numVertices, -1)); 
    // ���ó�ʼ����Ϊ������
    std::vector<std::vector<weight_type>> dp(numVertices, std::vector<weight_type>(numVertices, std::numeric_limits<weight_type>::max())); 

    // base case
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            if (i == j)
            {
                dp[i][j] = 0; // �������յ���ͬ�ľ���Ϊ0
            }
            else
            {
                weight_type weight = GetWeight(i, j);
                if (weight != weight_type{}) // ����Ƿ���ڱ�
                {
                    dp[i][j] = weight; // ���յ㲻ͬ������Ϊ��Ȩ
                }
            }
        }
    }

    // dp
    // dp[i][j]: ��� i �ͽ�� j �����·��Ϊ dp[i][j]
    // dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j])
    for (int k = 0; k < numVertices; k++)
    {
        for (int i = 0; i < numVertices; i++)
        {
            if (dp[i][k] == std::numeric_limits<weight_type>::max()) continue; // �������ɴ�����

            for (int j = 0; j < numVertices; j++)
            {
                // ����Ƿ��и��̵�·��
                if (dp[k][j] != std::numeric_limits<weight_type>::max() && dp[i][j] > dp[i][k] + dp[k][j])
                {
                    dp[i][j] = dp[i][k] + dp[k][j]; // ����·������
                    rec[i][j] = k; // ��¼·���Ͼ����Ľ��
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
        std::cout << GetNode(u).Value() << " "; // ��ӡ·���еĽ��ֵ�������յ���ͬ��
    }
    else if (rec[u][v] == -1)
    {
        std::cout << GetNode(u).Value() << "->" << GetNode(v).Value() << " "; // ��ӡ·���еĽ��ֵ�������յ㲻ͬ��
    }
    else
    {
        int k = rec[u][v];
        Find_path(rec, u, k); // �ݹ��ӡ����㵽������� k �Ĳ���·��
        Find_path(rec, k, v); // �ݹ��ӡ�Ӿ������ k ���յ�Ĳ���·��
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
    d[srcIndex] = m_time; // ��¼��ʼʱ��

    For_each_adjacency_vertices(srcIndex, [&](const GraphEdge<weight_type>& neighbor)->bool {
        if (color[neighbor.NeighborIndex()] == WHITE)
        {
            pred[neighbor.NeighborIndex()] = srcIndex;
            dfs_Visit(color, pred, d, f, neighbor.NeighborIndex()); // ����
        }
        return true;
    });

    color[srcIndex] = BLACK;
    m_time++;
    f[srcIndex] = m_time; // ��¼����ʱ��

    // ��������˳��
    m_result.push_back(srcIndex);
}

// ʹ�ù�������������Ҵ�Դ���(srcIndex)��Ŀ����(dstIndex)������·��
template<typename value_type>
inline bool Graph<value_type, Pipeline>::BFS(int srcIndex, int dstIndex, std::vector<int>& parent, double& pathFlow) const
{
    // ��ʼ����������飬���ڼ�¼���·����
    parent[srcIndex] = srcIndex;

    std::queue<std::pair<int, double>> q;
    q.push({ srcIndex, std::numeric_limits<double>::max() }); // ��ʼʱ��·����������Ϊ�����

    bool isReachable = false; // ��ʼ���ɴ��Ա�־

    while (!isReachable && !q.empty())
    {
        int u = q.front().first; // ��ǰ���
        double capacity = q.front().second; // ��ǰ·���ϵ���Сʣ������
        q.pop();

        // ����u���ڽӽ��
        For_each_adjacency_vertices(u, [&](const GraphEdge<Pipeline>& neighbor) -> bool {
            int v = neighbor.NeighborIndex();
            double residualCapacity = neighbor.Weight().residual();

            // ���vδ��������·���ϻ���ʣ������
            if (parent[v] == -1 && residualCapacity > 0)
            {
                parent[v] = u; // ��¼v�ĸ����Ϊu���������·����
                double minCapacity = std::min(capacity, residualCapacity); // ������Сʣ������

                // ���v��Ŀ���㣬���ҵ�������·��
                if (v == dstIndex)
                {
                    pathFlow = minCapacity; // ����·������
                    isReachable = true; // �ҵ�������·��
                    return false; // ֹͣ����
                }

                // ��v����Сʣ������������У�����BFS����
                q.push({ v, minCapacity });
            }
            return true; // ��������
        });
    }

    // �����Ƿ��ҵ��ɴ�·��
    return isReachable;
}

template<typename value_type>
inline void Graph<value_type, Pipeline>::Augment(int srcIndex, int dstIndex, double pathFlow)
{
    // �����������������
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
        // �ڷ�����ϼ�������
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