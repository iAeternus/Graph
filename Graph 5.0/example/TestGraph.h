/*****************************************************************//**
 * \file   TestGraph.h
 * \brief  图算法测试用例
 *
 * \author lenovo
 * \date   July 2023
 *********************************************************************/
#pragma once
#include <string>

mylib::Graph<int>* TestIntGraph(const int index, bool isLGraph = true)
{
	mylib::Graph<int>* g = nullptr;
	if (isLGraph)
	{
		g = new mylib::LGraph<int>();
	}
	else
	{
		g = new mylib::AGraph<int>();
	}

	switch (index)
	{
	case 1: // 有向图
		g->AddNode(1);
		g->AddNode(2);
		g->AddNode(3);
		g->AddNode(4);
		g->AddNode(5);

		g->AddEdge(0, 1);
		g->AddEdge(0, 2);
		g->AddEdge(0, 3);
		g->AddEdge(0, 4);
		g->AddEdge(1, 3);
		g->AddEdge(4, 2);
		g->AddEdge(4, 0);
		break;
	case 2: // 有向图
		g->AddNode(1);
		g->AddNode(2);
		g->AddNode(3);
		g->AddNode(4);
		g->AddNode(5);

		g->AddEdge(0, 1);
		g->AddEdge(1, 2);
		g->AddEdge(2, 4);
		g->AddEdge(4, 3);
		g->AddEdge(4, 2);
		g->AddEdge(4, 1);
		break;
	case 3: // 无向图，五边形
		g->AddNode(1);
		g->AddNode(2);
		g->AddNode(3);
		g->AddNode(4);
		g->AddNode(5);
		g->AddNode(6);

		g->AddEdge(0, 1, false);
		g->AddEdge(0, 5, false);
		g->AddEdge(0, 4, false);
		g->AddEdge(1, 5, false);
		g->AddEdge(1, 2, false);
		g->AddEdge(2, 5, false);
		g->AddEdge(2, 3, false);
		g->AddEdge(3, 5, false);
		g->AddEdge(3, 4, false);
		g->AddEdge(4, 5, false);
		break;
	case 4: // 无向图，老师的8个结点的例子
		g->AddNode(1);
		g->AddNode(2);
		g->AddNode(3);
		g->AddNode(4);
		g->AddNode(5);
		g->AddNode(6);
		g->AddNode(7);
		g->AddNode(8);

		g->AddEdge(0, 1, false);
		g->AddEdge(0, 4, false);
		g->AddEdge(1, 5, false);
		g->AddEdge(5, 2, false);
		g->AddEdge(5, 6, false);
		g->AddEdge(2, 6, false);
		g->AddEdge(2, 3, false);
		g->AddEdge(6, 3, false);
		g->AddEdge(6, 7, false);
		g->AddEdge(3, 7, false);
		break;
	case 5: // 有向图，有回路
		g->AddNode(1);
		g->AddNode(2);
		g->AddNode(3);
		g->AddNode(4);

		g->AddEdge(0, 1);
		g->AddEdge(1, 2);
		g->AddEdge(2, 3);
		g->AddEdge(3, 0);
		break;
	case 6: // 有向图，无回路
		g->AddNode(1);
		g->AddNode(2);
		g->AddNode(3);
		g->AddNode(4);

		g->AddEdge(0, 1);
		g->AddEdge(1, 2);
		g->AddEdge(2, 3);
		g->AddEdge(1, 3);
		break;
	case 7: // 有向图，强连通分量测试用例
		g->AddNode(1);
		g->AddNode(2);
		g->AddNode(3);
		g->AddNode(4);
		g->AddNode(5);
		g->AddNode(6);
		g->AddNode(7);
		g->AddNode(8);
		g->AddNode(9);
		g->AddNode(10);

		g->AddEdge(1, 5);
		g->AddEdge(5, 4);
		g->AddEdge(4, 1);
		g->AddEdge(3, 5);
		g->AddEdge(3, 0);
		g->AddEdge(0, 2);
		g->AddEdge(0, 9);
		g->AddEdge(2, 3);
		g->AddEdge(2, 6);
		g->AddEdge(6, 6);
		g->AddEdge(9, 0);
		g->AddEdge(7, 9);
		g->AddEdge(7, 8);
		g->AddEdge(8, 7);
		g->AddEdge(8, 6);
	case 8: // 无向图，所有点对最短路径问题测试用例
		g->AddNode(1);
		g->AddNode(2);
		g->AddNode(3);
		g->AddNode(4);
		g->AddNode(5);

		g->AddEdge(0, 1, false, 200);
		g->AddEdge(0, 2, false, 100);
		g->AddEdge(0, 4, false, 500);
		g->AddEdge(0, 3, false, 500);
		g->AddEdge(1, 2, false, 200);
		g->AddEdge(2, 3, false, 200);
		g->AddEdge(1, 3, false, 1200);
		g->AddEdge(1, 4, false, 1000);
		g->AddEdge(2, 4, false, 600);
		g->AddEdge(3, 4, false, 100);
		break;
	default:
		break;
	}
	return g;
}

mylib::Graph<std::string>* TestStringGraph(const int index, bool isLGraph = true)
{
	mylib::Graph<std::string>* g = nullptr;
	if (isLGraph)
	{
		g = new mylib::LGraph<std::string>();
	}
	else
	{
		g = new mylib::AGraph<std::string>();
	}

	switch (index)
	{
	case 1: // 穿衣逻辑图
		g->AddNode("短裤");
		g->AddNode("袜子");
		g->AddNode("长裤");
		g->AddNode("鞋");
		g->AddNode("手表");
		g->AddNode("腰带");
		g->AddNode("衬衫");
		g->AddNode("领带");
		g->AddNode("外套");

		g->AddEdge(0, 2);
		g->AddEdge(0, 3);
		g->AddEdge(1, 3);
		g->AddEdge(2, 3);
		g->AddEdge(2, 5);
		g->AddEdge(6, 5);
		g->AddEdge(6, 7);
		g->AddEdge(7, 8);
		g->AddEdge(5, 8);
		break;
	case 2: // 无向图，单源最短路径测试用例
		g->AddNode("洪山广场");
		g->AddNode("珞珈山");
		g->AddNode("东湖");
		g->AddNode("江汉路");
		g->AddNode("万松园");
		g->AddNode("安贞门");
		g->AddNode("民族大道");
		g->AddNode("兰家石");
		g->AddNode("大智路");
		g->AddNode("舵落口");
		g->AddNode("蔡甸广场");
		g->AddNode("循礼门");
		g->AddNode("黄浦明珠");
		g->AddNode("阳逻");
		g->AddNode("汉口北");

		g->AddEdge(0, 1, false, 4);    // 洪山广场 - 珞珈山
		g->AddEdge(0, 4, false, 3);    // 洪山广场 - 万松园
		g->AddEdge(1, 2, false, 8);    // 珞珈山 - 东湖
		g->AddEdge(2, 3, false, 6);    // 东湖 - 江汉路
		g->AddEdge(2, 4, false, 5);    // 东湖 - 万松园
		g->AddEdge(3, 5, false, 7);    // 江汉路 - 安贞门
		g->AddEdge(3, 6, false, 6);    // 江汉路 - 民族大道
		g->AddEdge(4, 7, false, 2);    // 万松园 - 兰家石
		g->AddEdge(4, 8, false, 9);    // 万松园 - 大智路
		g->AddEdge(5, 7, false, 10);   // 安贞门 - 兰家石
		g->AddEdge(6, 8, false, 5);    // 民族大道 - 大智路
		g->AddEdge(7, 9, false, 4);    // 兰家石 - 舵落口
		g->AddEdge(8, 9, false, 6);    // 大智路 - 舵落口
		g->AddEdge(5, 10, false, 7);   // 安贞门 - 蔡甸广场   TODO 数组越界
		g->AddEdge(9, 11, false, 3);   // 舵落口 - 循礼门
		g->AddEdge(10, 11, false, 2);  // 蔡甸广场 - 循礼门
		g->AddEdge(11, 12, false, 5);  // 循礼门 - 黄浦明珠
		g->AddEdge(11, 13, false, 8);  // 循礼门 - 阳逻
		g->AddEdge(13, 14, false, 4);  // 阳逻 - 汉口北
		break;
	case 3: // 无向图，单源最短路径测试用例
		g->AddNode("北京");
		g->AddNode("上海");
		g->AddNode("广州");
		g->AddNode("深圳");
		g->AddNode("成都");
		g->AddNode("重庆");
		g->AddNode("天津");
		g->AddNode("杭州");
		g->AddNode("武汉");
		g->AddNode("南京");
		g->AddNode("西安");
		g->AddNode("合肥");
		g->AddNode("西宁");
		g->AddNode("青岛");
		g->AddNode("长春");
		g->AddNode("长沙");

		// 边
		g->AddEdge(0, 1, false, 1064);   // 北京 <-> 上海
		g->AddEdge(0, 2, false, 1888);   // 北京 <-> 广州
		g->AddEdge(1, 2, false, 1130);   // 上海 <-> 广州
		g->AddEdge(1, 3, false, 1452);   // 上海 <-> 深圳
		g->AddEdge(2, 3, false, 1350);   // 广州 <-> 深圳
		g->AddEdge(2, 4, false, 1786);   // 广州 <-> 成都
		g->AddEdge(3, 5, false, 1657);   // 深圳 <-> 重庆
		g->AddEdge(4, 5, false, 811);    // 成都 <-> 重庆
		g->AddEdge(1, 6, false, 1200);   // 上海 <-> 天津
		g->AddEdge(6, 7, false, 1268);   // 天津 <-> 杭州
		g->AddEdge(2, 8, false, 1052);   // 广州 <-> 武汉
		g->AddEdge(2, 9, false, 973);    // 广州 <-> 南京
		g->AddEdge(8, 9, false, 828);    // 武汉 <-> 南京
		g->AddEdge(3, 6, false, 1134);   // 深圳 <-> 天津
		g->AddEdge(5, 7, false, 1418);   // 重庆 <-> 杭州
		g->AddEdge(6, 8, false, 1067);   // 天津 <-> 武汉
		g->AddEdge(9, 10, false, 799);   // 南京 <-> 西安
		g->AddEdge(5, 11, false, 1123);  // 重庆 <-> 合肥
		g->AddEdge(6, 12, false, 924);   // 天津 <-> 西宁
		g->AddEdge(8, 13, false, 1020);  // 武汉 <-> 青岛
		g->AddEdge(10, 14, false, 668);  // 西安 <-> 长春
		g->AddEdge(9, 11, false, 1322);  // 南京 <-> 合肥
		g->AddEdge(7, 12, false, 636);   // 杭州 <-> 西宁
		g->AddEdge(10, 13, false, 1235); // 西安 <-> 青岛
		g->AddEdge(9, 14, false, 1098);  // 南京 <-> 长春
		g->AddEdge(11, 15, false, 1796); // 合肥 <-> 长沙
		g->AddEdge(13, 15, false, 783);  // 青岛 <-> 长沙
		break;
	case 4:
		
		break;
	default:
		break;
	}
	return g;
}

mylib::Graph<char>* TestCharGraph(const int index, bool isLGraph = true)
{
	mylib::Graph<char>* g = nullptr;
	if (isLGraph)
	{
		g = new mylib::LGraph<char>();
	}
	else
	{
		g = new mylib::AGraph<char>();
	}

	switch (index)
	{
	case 1: // 无向图，最小生成树测试用例
		g->AddNode('a');
		g->AddNode('b');
		g->AddNode('c');
		g->AddNode('d');
		g->AddNode('e');
		g->AddNode('f');
		g->AddNode('g');
		g->AddNode('h');
		g->AddNode('i');

		g->AddEdge(0, 1, false, 4);
		g->AddEdge(0, 7, false, 8);
		g->AddEdge(1, 7, false, 1);
		g->AddEdge(1, 2, false, 8);
		g->AddEdge(2, 8, false, 2);
		g->AddEdge(2, 5, false, 4);
		g->AddEdge(2, 3, false, 7);
		g->AddEdge(3, 5, false, 14);
		g->AddEdge(3, 4, false, 9);
		g->AddEdge(4, 5, false, 10);
		g->AddEdge(5, 6, false, 2);
		g->AddEdge(6, 7, false, 1);
		g->AddEdge(6, 8, false, 4);
		g->AddEdge(7, 8, false, 7);
		break;
	case 2: // 有向图，单源最短路径测试用例（某些点不可达）
		g->AddNode('s');
		g->AddNode('t');
		g->AddNode('x');
		g->AddNode('z');
		g->AddNode('y');

		g->AddEdge(0, 1, true, 8);
		g->AddEdge(1, 2, true, 1);
		g->AddEdge(0, 4, true, 5);
		g->AddEdge(1, 4, true, 2);
		g->AddEdge(4, 1, true, 3);
		g->AddEdge(4, 2, true, 9);
		g->AddEdge(2, 3, true, 4);
		g->AddEdge(3, 2, true, 6);
		g->AddEdge(4, 3, true, 2);
		break;
	case 3: // 有向图，带有负权，单源最短路径测试用例
		g->AddNode('s');
		g->AddNode('t');
		g->AddNode('x');
		g->AddNode('z');
		g->AddNode('y');

		g->AddEdge(0, 1, true, 6);
		g->AddEdge(1, 2, true, 5);
		g->AddEdge(2, 1, true, -2);
		g->AddEdge(0, 4, true, 7);
		g->AddEdge(1, 4, true, 8);
		g->AddEdge(1, 3, true, -4);
		g->AddEdge(4, 2, true, -3);
		g->AddEdge(2, 3, true, 7);
		g->AddEdge(4, 3, true, 2);
		break;
	case 4: // 带负环的有向图，单源最短路径测试用例
		g->AddNode('s');
		g->AddNode('a');
		g->AddNode('b');

		g->AddEdge(0, 1, true, 2);
		g->AddEdge(1, 2, true, 3);
		g->AddEdge(2, 0, true, -8);
		break;
	default:
		break;
	}
	return g;
}

// 最大流测试用例
mylib::Graph<std::string, Pipeline>* TestMaximumStreamGraph(const int index, bool isLGraph = true)
{
	mylib::Graph<std::string, Pipeline>* g = nullptr;
	if (isLGraph)
	{
		g = new mylib::LGraph<std::string, Pipeline>();
	}
	else
	{
		g = new mylib::AGraph<std::string, Pipeline>();
	}

	switch (index)
	{
	case 1:
		g->AddNode("s ");
		g->AddNode("v1");
		g->AddNode("v2");
		g->AddNode("v3");
		g->AddNode("v4");
		g->AddNode("t ");

		g->AddEdge(0, 1, true, Pipeline(0, 12));
		g->AddEdge(0, 2, true, Pipeline(0, 14));
		g->AddEdge(1, 3, true, Pipeline(0, 10));
		g->AddEdge(2, 1, true, Pipeline(0, 5));
		g->AddEdge(2, 3, true, Pipeline(0, 11));
		g->AddEdge(2, 4, true, Pipeline(0, 6));
		g->AddEdge(3, 4, true, Pipeline(0, 5));
		g->AddEdge(3, 5, true, Pipeline(0, 14));
		g->AddEdge(4, 5, true, Pipeline(0, 11));
		break;
	default:
		break;
	}
	return g;
}
