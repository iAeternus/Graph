/*****************************************************************//**
 * \file   AGraph.h
 * \brief  使用邻接矩阵实现图
 * 
 * \author 吴子维
 * \date   September 2023
 *********************************************************************/
#pragma once
#include "Graph.h"

MYLIB_BEGIN
template<typename value_type, typename weight_type = int>
class AGraph : public Graph<value_type, weight_type>
{
public:
	AGraph();
	virtual ~AGraph();
	AGraph(const AGraph& other);
	AGraph& operator=(const AGraph& other);
	AGraph(AGraph&& other) noexcept;
	AGraph& operator=(AGraph&& other) noexcept;

	void AddNode(const value_type& value) override;
	void RemoveNode(int index) override;
	void AddEdge(int fromIndex, int toIndex, bool isDirEdge = true, const weight_type& weight = 0) override;
	void RemoveEdge(int fromIndex, int toIndex, bool isDirEdge = true) override;
	void Clear() override;

	weight_type GetWeight(int fromIndex, int toIndex) const override;

	void Output(std::ostream& out = std::cout) const override;

protected:
	// 邻接矩阵，存储边
	std::vector<std::vector<GraphEdge<weight_type>>> adjacencyMatrix;
	
	bool For_each_adjacency_vertices(int curNodeIndex, const std::function<bool(const mylib::GraphEdge<weight_type>&)>& func) const override;
	bool For_each_adjacency_vertices(int curNodeIndex, const std::function<bool(mylib::GraphEdge<weight_type>&)>& func) override;
};

// 偏特化 AGraph 类
template<typename value_type>
class AGraph<value_type, Pipeline> : public Graph<value_type, Pipeline>
{
public:
	void AddNode(const value_type& value) override;
	void AddEdge(int fromIndex, int toIndex, bool isDirEdge = true, const Pipeline& weight = 0) override;
	Pipeline GetWeight(int fromIndex, int toIndex) const override;
	void Output(std::ostream& out = std::cout) const override;
protected:
	// 邻接矩阵，存储边
	std::vector<std::vector<mylib::GraphEdge<Pipeline>>> adjacencyMatrix;

	bool For_each_adjacency_vertices(int curNodeIndex, const std::function<bool(const mylib::GraphEdge<Pipeline>&)>& func) const override;
	bool For_each_adjacency_vertices(int curNodeIndex, const std::function<bool(mylib::GraphEdge<Pipeline>&)>& func) override;
};

template<typename value_type, typename weight_type>
inline AGraph<value_type, weight_type>::AGraph() :
	adjacencyMatrix(GRAPH_SIZE, std::vector<GraphEdge<weight_type>>(GRAPH_SIZE, GraphEdge<weight_type>(Graph<value_type, weight_type>::GetInitialWeight())))
{}

template<typename value_type, typename weight_type>
inline AGraph<value_type, weight_type>::~AGraph()
{}

template<typename value_type, typename weight_type>
inline AGraph<value_type, weight_type>::AGraph(const AGraph& other) :
	Graph<value_type, weight_type>::Graph(other), adjacencyMatrix(other.adjacencyMatrix)
{}

template<typename value_type, typename weight_type>
inline AGraph<value_type, weight_type>& AGraph<value_type, weight_type>::operator=(const AGraph& other)
{
	if (this != &other)
	{
		this->operator=(other);
		this->adjacencyMatrix = other.adjacencyMatrix;
	}
	return *this;
}

template<typename value_type, typename weight_type>
inline AGraph<value_type, weight_type>::AGraph(AGraph&& other) noexcept :
	Graph<value_type, weight_type>::Graph(other), adjacencyMatrix(std::move(other.adjacencyMatrix))
{}

template<typename value_type, typename weight_type>
inline AGraph<value_type, weight_type>& AGraph<value_type, weight_type>::operator=(AGraph&& other) noexcept
{
	if (this != &other)
	{
		this->operator=(other);
		this->adjacencyMatrix = std::move(other.adjacencyMatrix);
	}
	return *this;
}

template<typename value_type, typename weight_type>
inline void AGraph<value_type, weight_type>::AddNode(const value_type& value)
{
	if (this->numVertices >= adjacencyMatrix.size()) // 装不下，扩容
	{
		int newMatrixSize = this->numVertices + EXPANSION;

		// 创建新的扩容矩阵
		std::vector<std::vector<GraphEdge<weight_type>>> newMatrix(newMatrixSize,
			std::vector<GraphEdge<weight_type>>(newMatrixSize, GraphEdge<weight_type>(Graph<value_type, weight_type>::GetInitialWeight())));

		// 复制原始矩阵的元素到新矩阵
		for (int i = 0; i < this->numVertices; i++)
		{
			for (int j = 0; j < this->numVertices; j++)
			{
				newMatrix[i][j] = adjacencyMatrix[i][j];
			}
		}

		// 更新邻接矩阵和结点数
		adjacencyMatrix = std::move(newMatrix);
	}

	Graph<value_type, weight_type>::AddNode(value);
}

template<typename value_type>
void AGraph<value_type, Pipeline>::AddNode(const value_type& value)
{
	if (this->numVertices >= adjacencyMatrix.size()) // 装不下，扩容
	{
		int newMatrixSize = this->numVertices + EXPANSION;

		// 创建新的扩容矩阵
		std::vector<std::vector<GraphEdge<Pipeline>>> newMatrix (
			newMatrixSize,
			std::vector<GraphEdge<Pipeline>> (
				newMatrixSize, 
				GraphEdge<Pipeline>(Graph<value_type, Pipeline>::GetInitialWeight())
			)
		);

		// 复制原始矩阵的元素到新矩阵
		for (int i = 0; i < this->numVertices; i++)
		{
			for (int j = 0; j < this->numVertices; j++)
			{
				newMatrix[i][j] = adjacencyMatrix[i][j];
			}
		}

		// 更新邻接矩阵和结点数
		adjacencyMatrix = std::move(newMatrix);
	}

	Graph<value_type, Pipeline>::AddNode(value);
}

template<typename value_type, typename weight_type>
inline void AGraph<value_type, weight_type>::RemoveNode(int index)
{
	if (index < 0 || index > this->numVertices) return;

	// 删除行
	auto i = adjacencyMatrix.begin() + index;
	adjacencyMatrix.erase(i);

	// 删除列
	for (auto& v : adjacencyMatrix)
	{
		auto j = v.begin() + index;
		v.erase(j);
	}
	Graph<value_type, weight_type>::RemoveNode(index);
}

template<typename value_type, typename weight_type>
inline void AGraph<value_type, weight_type>::AddEdge(int fromIndex, int toIndex, bool isDirEdge, const weight_type& weight)
{
	if (fromIndex >= 0 && fromIndex < this->nodes.size() &&
		toIndex >= 0 && toIndex < this->nodes.size())
	{
		adjacencyMatrix[fromIndex][toIndex] = GraphEdge<weight_type>(fromIndex, toIndex, isDirEdge, weight);

		if (!isDirEdge)
		{
			adjacencyMatrix[toIndex][fromIndex] = GraphEdge<weight_type>(toIndex, fromIndex, isDirEdge, weight);
		}
	}
	Graph<value_type, weight_type>::AddEdge(fromIndex, toIndex, isDirEdge, weight);
}

template<typename value_type>
inline void AGraph<value_type, Pipeline>::AddEdge(int fromIndex, int toIndex, bool isDirEdge, const Pipeline& weight)
{
	if (fromIndex >= 0 && fromIndex < this->nodes.size() &&
		toIndex >= 0 && toIndex < this->nodes.size())
	{
		adjacencyMatrix[fromIndex][toIndex] = GraphEdge<Pipeline>(fromIndex, toIndex, isDirEdge, weight);

		if (!isDirEdge)
		{
			adjacencyMatrix[toIndex][fromIndex] = GraphEdge<Pipeline>(toIndex, fromIndex, isDirEdge, weight);
		}
	}
	Graph<value_type, Pipeline>::AddEdge(fromIndex, toIndex, isDirEdge, weight);
}

template<typename value_type, typename weight_type>
inline void AGraph<value_type, weight_type>::RemoveEdge(int fromIndex, int toIndex, bool isDirEdge)
{
	adjacencyMatrix[fromIndex][toIndex] = GraphEdge<weight_type>(Graph<value_type, weight_type>::GetInitialWeight());

	if (!isDirEdge)
	{
		adjacencyMatrix[toIndex][fromIndex] = GraphEdge<weight_type>(Graph<value_type, weight_type>::GetInitialWeight());
	}
	Graph<value_type, weight_type>::RemoveEdge(fromIndex, toIndex, isDirEdge);
}

template<typename value_type, typename weight_type>
inline void AGraph<value_type, weight_type>::Clear()
{
	Graph<value_type, weight_type>::Clear();
	for (int i = 0; i < adjacencyMatrix.size(); i++)
	{
		for (int j = 0; j < adjacencyMatrix[i].size(); j++)
		{
			if (GetWeight(i, j) != Graph<value_type, weight_type>::GetInitialWeight())
			{
				adjacencyMatrix[i][j] = GraphEdge<weight_type>(Graph<value_type, weight_type>::GetInitialWeight());
			}
		}
	}
}

template<typename value_type, typename weight_type>
inline weight_type AGraph<value_type, weight_type>::GetWeight(int fromIndex, int toIndex) const
{
	return this->adjacencyMatrix[fromIndex][toIndex].Weight(); // 权重
}

template<typename value_type>
inline Pipeline AGraph<value_type, Pipeline>::GetWeight(int fromIndex, int toIndex) const
{
	return this->adjacencyMatrix[fromIndex][toIndex].Weight(); // 权重
}

template<typename value_type, typename weight_type>
inline void AGraph<value_type, weight_type>::Output(std::ostream& out) const
{
	out << " \t";
	for (int i = 0; i < this->numVertices; i++)
	{
		out << i << '\t';
	}
	out << '\n';

	for (int i = 0; i < this->numVertices; i++)
	{
		out << i << '\t';
		for (int j = 0; j < this->numVertices; j++)
		{
			weight_type weight = GetWeight(i, j);
			if (weight != Graph<value_type, weight_type>::GetInitialWeight())
			{
				out << RED_COLOR_CODE << weight << DEFAULT_COLOR_CODE << '\t';
			}
			else
			{
				out << ' ' << '\t';
			}
		}
		out << '\n';
	}
}

template<typename value_type>
inline void AGraph<value_type, Pipeline>::Output(std::ostream& out) const
{
	out << " \t";
	for (int i = 0; i < this->numVertices; i++)
	{
		out << i << '\t';
	}
	out << '\n';

	for (int i = 0; i < this->numVertices; i++)
	{
		out << i << '\t';
		for (int j = 0; j < this->numVertices; j++)
		{
			Pipeline weight = GetWeight(i, j);
			if (weight != Graph<value_type, Pipeline>::GetInitialWeight())
			{
				out << RED_COLOR_CODE << weight << DEFAULT_COLOR_CODE << '\t';
			}
			else
			{
				out << ' ' << '\t';
			}
		}
		out << '\n';
	}
}

template<typename value_type, typename weight_type>
inline bool AGraph<value_type, weight_type>::For_each_adjacency_vertices(int curNodeIndex, const std::function<bool(const GraphEdge<weight_type>&)>& func) const
{
	for (int i = 0; i < adjacencyMatrix[curNodeIndex].size(); i++)
	{
		if (GetWeight(curNodeIndex, i) != Graph<value_type, weight_type>::GetInitialWeight())
		{
			if (!func(adjacencyMatrix[curNodeIndex][i]))
			{
				return false;
			}
		}
	}
	return true;
}

template<typename value_type, typename weight_type>
inline bool AGraph<value_type, weight_type>::For_each_adjacency_vertices(int curNodeIndex, const std::function<bool(GraphEdge<weight_type>&)>& func)
{
	for (int i = 0; i < adjacencyMatrix[curNodeIndex].size(); i++)
	{
		if (GetWeight(curNodeIndex, i) != Graph<value_type, weight_type>::GetInitialWeight())
		{
			if (!func(adjacencyMatrix[curNodeIndex][i]))
			{
				return false;
			}
		}
	}
	return true;
}

template<typename value_type>
bool AGraph<value_type, Pipeline>::For_each_adjacency_vertices(int curNodeIndex, const std::function<bool(const mylib::GraphEdge<Pipeline>&)>& func) const
{
	for (int i = 0; i < adjacencyMatrix[curNodeIndex].size(); i++)
	{
		if (GetWeight(curNodeIndex, i) != Graph<value_type, Pipeline>::GetInitialWeight())
		{
			if (!func(adjacencyMatrix[curNodeIndex][i]))
			{
				return false;
			}
		}
	}
	return true;
}

template<typename value_type>
bool AGraph<value_type, Pipeline>::For_each_adjacency_vertices(int curNodeIndex, const std::function<bool(mylib::GraphEdge<Pipeline>&)>& func)
{
	for (int i = 0; i < adjacencyMatrix[curNodeIndex].size(); i++)
	{
		if (GetWeight(curNodeIndex, i) != Graph<value_type, Pipeline>::GetInitialWeight())
		{
			if (!func(adjacencyMatrix[curNodeIndex][i]))
			{
				return false;
			}
		}
	}
	return true;
}
MYLIB_END // mylib