/*****************************************************************//**
 * \file   TestGraph.h
 * \brief  ͼ�㷨��������
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
	case 1: // ����ͼ
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
	case 2: // ����ͼ
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
	case 3: // ����ͼ�������
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
	case 4: // ����ͼ����ʦ��8����������
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
	case 5: // ����ͼ���л�·
		g->AddNode(1);
		g->AddNode(2);
		g->AddNode(3);
		g->AddNode(4);

		g->AddEdge(0, 1);
		g->AddEdge(1, 2);
		g->AddEdge(2, 3);
		g->AddEdge(3, 0);
		break;
	case 6: // ����ͼ���޻�·
		g->AddNode(1);
		g->AddNode(2);
		g->AddNode(3);
		g->AddNode(4);

		g->AddEdge(0, 1);
		g->AddEdge(1, 2);
		g->AddEdge(2, 3);
		g->AddEdge(1, 3);
		break;
	case 7: // ����ͼ��ǿ��ͨ������������
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
	case 8: // ����ͼ�����е�����·�������������
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
	case 1: // �����߼�ͼ
		g->AddNode("�̿�");
		g->AddNode("����");
		g->AddNode("����");
		g->AddNode("Ь");
		g->AddNode("�ֱ�");
		g->AddNode("����");
		g->AddNode("����");
		g->AddNode("���");
		g->AddNode("����");

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
	case 2: // ����ͼ����Դ���·����������
		g->AddNode("��ɽ�㳡");
		g->AddNode("����ɽ");
		g->AddNode("����");
		g->AddNode("����·");
		g->AddNode("����԰");
		g->AddNode("������");
		g->AddNode("������");
		g->AddNode("����ʯ");
		g->AddNode("����·");
		g->AddNode("�����");
		g->AddNode("�̵�㳡");
		g->AddNode("ѭ����");
		g->AddNode("��������");
		g->AddNode("����");
		g->AddNode("���ڱ�");

		g->AddEdge(0, 1, false, 4);    // ��ɽ�㳡 - ����ɽ
		g->AddEdge(0, 4, false, 3);    // ��ɽ�㳡 - ����԰
		g->AddEdge(1, 2, false, 8);    // ����ɽ - ����
		g->AddEdge(2, 3, false, 6);    // ���� - ����·
		g->AddEdge(2, 4, false, 5);    // ���� - ����԰
		g->AddEdge(3, 5, false, 7);    // ����· - ������
		g->AddEdge(3, 6, false, 6);    // ����· - ������
		g->AddEdge(4, 7, false, 2);    // ����԰ - ����ʯ
		g->AddEdge(4, 8, false, 9);    // ����԰ - ����·
		g->AddEdge(5, 7, false, 10);   // ������ - ����ʯ
		g->AddEdge(6, 8, false, 5);    // ������ - ����·
		g->AddEdge(7, 9, false, 4);    // ����ʯ - �����
		g->AddEdge(8, 9, false, 6);    // ����· - �����
		g->AddEdge(5, 10, false, 7);   // ������ - �̵�㳡   TODO ����Խ��
		g->AddEdge(9, 11, false, 3);   // ����� - ѭ����
		g->AddEdge(10, 11, false, 2);  // �̵�㳡 - ѭ����
		g->AddEdge(11, 12, false, 5);  // ѭ���� - ��������
		g->AddEdge(11, 13, false, 8);  // ѭ���� - ����
		g->AddEdge(13, 14, false, 4);  // ���� - ���ڱ�
		break;
	case 3: // ����ͼ����Դ���·����������
		g->AddNode("����");
		g->AddNode("�Ϻ�");
		g->AddNode("����");
		g->AddNode("����");
		g->AddNode("�ɶ�");
		g->AddNode("����");
		g->AddNode("���");
		g->AddNode("����");
		g->AddNode("�人");
		g->AddNode("�Ͼ�");
		g->AddNode("����");
		g->AddNode("�Ϸ�");
		g->AddNode("����");
		g->AddNode("�ൺ");
		g->AddNode("����");
		g->AddNode("��ɳ");

		// ��
		g->AddEdge(0, 1, false, 1064);   // ���� <-> �Ϻ�
		g->AddEdge(0, 2, false, 1888);   // ���� <-> ����
		g->AddEdge(1, 2, false, 1130);   // �Ϻ� <-> ����
		g->AddEdge(1, 3, false, 1452);   // �Ϻ� <-> ����
		g->AddEdge(2, 3, false, 1350);   // ���� <-> ����
		g->AddEdge(2, 4, false, 1786);   // ���� <-> �ɶ�
		g->AddEdge(3, 5, false, 1657);   // ���� <-> ����
		g->AddEdge(4, 5, false, 811);    // �ɶ� <-> ����
		g->AddEdge(1, 6, false, 1200);   // �Ϻ� <-> ���
		g->AddEdge(6, 7, false, 1268);   // ��� <-> ����
		g->AddEdge(2, 8, false, 1052);   // ���� <-> �人
		g->AddEdge(2, 9, false, 973);    // ���� <-> �Ͼ�
		g->AddEdge(8, 9, false, 828);    // �人 <-> �Ͼ�
		g->AddEdge(3, 6, false, 1134);   // ���� <-> ���
		g->AddEdge(5, 7, false, 1418);   // ���� <-> ����
		g->AddEdge(6, 8, false, 1067);   // ��� <-> �人
		g->AddEdge(9, 10, false, 799);   // �Ͼ� <-> ����
		g->AddEdge(5, 11, false, 1123);  // ���� <-> �Ϸ�
		g->AddEdge(6, 12, false, 924);   // ��� <-> ����
		g->AddEdge(8, 13, false, 1020);  // �人 <-> �ൺ
		g->AddEdge(10, 14, false, 668);  // ���� <-> ����
		g->AddEdge(9, 11, false, 1322);  // �Ͼ� <-> �Ϸ�
		g->AddEdge(7, 12, false, 636);   // ���� <-> ����
		g->AddEdge(10, 13, false, 1235); // ���� <-> �ൺ
		g->AddEdge(9, 14, false, 1098);  // �Ͼ� <-> ����
		g->AddEdge(11, 15, false, 1796); // �Ϸ� <-> ��ɳ
		g->AddEdge(13, 15, false, 783);  // �ൺ <-> ��ɳ
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
	case 1: // ����ͼ����С��������������
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
	case 2: // ����ͼ����Դ���·������������ĳЩ�㲻�ɴ
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
	case 3: // ����ͼ�����и�Ȩ����Դ���·����������
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
	case 4: // ������������ͼ����Դ���·����������
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

// �������������
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
