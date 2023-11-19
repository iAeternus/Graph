#pragma once
#include "TestGraph.h"
#include "Timer.h"

void Test_BFS(bool isLGraph = true)
{
	mylib::Graph<int>* g = TestIntGraph(3, isLGraph);
	g->Output();
	std::cout << std::endl;

	int srcIndex;
	std::cout << "Enter the source point index [0, " << g->NumVertices() - 1 << "] > ";
	std::cin >> srcIndex;

	std::vector<int> visited;
	
	{
		mylib::Timer timer("广度优先搜索");
		visited = g->bfs(srcIndex);
	}	

	// 打印搜索到的结点值
	for (const int it : visited)
	{
		std::cout << g->GetNode(it).Value() << ' ';
	}
	std::cout << std::endl;

	delete g;
}

void Test_DFS(bool isLGraph = true)
{
	mylib::Graph<int>* g = TestIntGraph(3, isLGraph);
	g->Output();

	{
		mylib::Timer timer("深度优先搜索");
		g->dfs();
	}
	
	for (int i = 0; i < mylib::m_result.size(); i++)
	{
		std::cout << mylib::m_result[i] << ' ';
	}
	std::cout << std::endl;

	delete g;
}

void Test_Topological_Sort(bool isLGraph = true)
{
	mylib::Graph<std::string>* g = TestStringGraph(1, isLGraph);
	g->Output();

	std::cout << "广度优先搜索思路\n";

	std::vector<int> res;

	{
		mylib::Timer timer("拓扑排序");
		res	= g->Topological_Sort_BFS();
	}

	for (const auto& it : res)
	{
		std::cout << g->GetNode(it).Value() << ' ';
	}
	std::cout << '\n';

	delete g;
}

void Test_MST_Prim(bool isLGraph = true)
{
	int graphWeight = 0;
	mylib::Graph<char>* spanningTree = nullptr;
	if (isLGraph)
	{
		spanningTree = new mylib::LGraph<char>();
	}
	else
	{
		spanningTree = new mylib::AGraph<char>();
	}

	mylib::Graph<char>* g = TestCharGraph(1, isLGraph);
	g->Output();

	{
		mylib::Timer timer("最小生成树-Prim算法");
		g->MST_Prim(spanningTree, graphWeight);
	}
	
	std::cout << "The weight of the figure = " << graphWeight << std::endl;
	spanningTree->Output();

	delete g;
	delete spanningTree;
}

void Test_MST_Kruskal(bool isLGraph = true)
{
	int graphWeight = 0;
	mylib::Graph<char>* spanningTree = nullptr;
	if (isLGraph)
	{
		spanningTree = new mylib::LGraph<char>();
	}
	else
	{
		spanningTree = new mylib::AGraph<char>();
	}

	mylib::Graph<char>* g = TestCharGraph(1, isLGraph);
	g->Output();

	{
		mylib::Timer timer("最小生成树-Kruskal算法");
		g->MST_Kruskal(spanningTree, graphWeight);
	}

	std::cout << "The weight of the figure = " << graphWeight << std::endl;
	spanningTree->Output();

	delete g;
	delete spanningTree;
}

void Test_Dijkstra(bool isLGraph = true)
{
	mylib::Graph<std::string>* g = TestStringGraph(2, isLGraph);
	g->Output();

	int srcIndex;
	std::cout << "Enter the source point index > ";
	std::cin >> srcIndex;

	std::pair<std::vector<int>, std::vector<int>> res;
	
	{
		mylib::Timer timer("单源最短路径-Dijkstra算法");
		res = g->Dijkstra(srcIndex);
	}
	
	auto& [pred, dist] = res;

	std::cout << "pred = ";
	for (int i = 0; i < pred.size(); i++)
	{
		std::cout << pred[i] << ' ';
	}
	std::cout << std::endl;

	std::cout << "dist = ";
	for (int i = 0; i < dist.size(); i++)
	{
		std::cout << dist[i] << ' ';
	}
	std::cout << std::endl;

	mylib::Graph<std::string>::print_path(g, res, srcIndex);

	delete g;
}

void Test_Bellman_Ford(bool isLGraph = true)
{
	mylib::Graph<char>* g = TestCharGraph(3, isLGraph);
	g->Output();

	int srcIndex;
	std::cout << "Enter the source point index > ";
	std::cin >> srcIndex;
	std::tuple<std::vector<int>, std::vector<int>, bool> res;

	{
		mylib::Timer timer("单源最短路径-Bellman_Ford算法");
		res = g->Bellman_Ford(srcIndex);
	}

	auto& [pred, dist, hasNegativeLoop] = res;

	std::cout << "pred = ";
	for (int i = 0; i < pred.size(); i++)
	{
		std::cout << pred[i] << ' ';
	}
	std::cout << std::endl;

	std::cout << "dist = ";
	for (int i = 0; i < dist.size(); i++)
	{
		std::cout << dist[i] << ' ';
	}
	std::cout << std::endl;

	std::cout << (hasNegativeLoop ? "有负环" : "无负环") << std::endl;

	std::pair<std::vector<int>, std::vector<int>> temp = std::make_pair(pred, dist);
	mylib::Graph<char>::print_path(g, temp, srcIndex);

	delete g;
}

void Test_Floyd_Warshall(bool isLGraph = true)
{
	mylib::Graph<std::string>* g = TestStringGraph(3, isLGraph);
	g->Output();

	std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> res;

	{
		mylib::Timer timer("所有点对最短路径-Floyd_Warshall算法");
		res = g->Floyd_Warshall();
	}

	auto& [Rec, D] = res;

	std::cout << "dp = \n";
	for (int i = 0; i < D.size(); i++)
	{
		for (int j = 0; j < D[i].size(); j++)
		{
			std::cout << D[i][j] << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "rec = \n";
	for (int i = 0; i < Rec.size(); i++)
	{
		for (int j = 0; j < Rec[i].size(); j++)
		{
			std::cout << Rec[i][j] << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	for (int i = 0; i < g->NumVertices(); i++)
	{
		for (int j = 0; j < g->NumVertices(); j++)
		{
			if (i == j) continue;
			std::cout << "The shortest path from " << g->GetNode(i).Value() << " to " << g->GetNode(j).Value() << " is ";
			g->Find_path(Rec, i, j);
			std::cout << std::endl;
		}
	}

	delete g;
}

void Test_Ford_Fulkerson(bool isLGraph = true)
{
	mylib::Graph<std::string, Pipeline>* g = TestMaximumStreamGraph(1, isLGraph);
	g->Output();

	int maxFlow;

	{
		mylib::Timer timer("最大流-Ford_Fulkerson算法");
		maxFlow = g->Ford_Fulkerson(0, 5);
	}

	std::cout << "Maximum flow is " << maxFlow << std::endl;
	std::cout << "Residual network: \n";
	g->Output();

	delete g;
}
