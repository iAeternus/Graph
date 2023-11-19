#pragma once
#include <string>
#include <tuple>
#include <functional>
#include <queue>
#include <vector>

#define MYLIB_BEGIN namespace mylib {
#define MYLIB_END }

const std::string RED_COLOR_CODE = "\033[1;31m"; // �����ı���ɫΪ��ɫ��ANSIת����
const std::string GREEN_COLOR_CODE = "\033[1;32m"; // �����ı���ɫΪ��ɫ��ANSIת����
const std::string YELLOW_COLOR_CODE = "\033[1;33m"; // �����ı���ɫΪ��ɫ��ANSIת����
const std::string DEFAULT_COLOR_CODE = "\033[0m";	// �ָ�Ĭ���ı���ɫ��ANSIת����

constexpr static int GRAPH_SIZE = 10; // Ĭ�Ͻ����
constexpr static int EXPANSION = 5; // ���ݽ����

const int threshold = 1e8; // ��Χ��ֵ
