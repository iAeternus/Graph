#pragma once
#include <string>
#include <tuple>
#include <functional>
#include <queue>
#include <vector>

#define MYLIB_BEGIN namespace mylib {
#define MYLIB_END }

const std::string RED_COLOR_CODE = "\033[1;31m"; // 设置文本颜色为红色的ANSI转义码
const std::string GREEN_COLOR_CODE = "\033[1;32m"; // 设置文本颜色为绿色的ANSI转义码
const std::string YELLOW_COLOR_CODE = "\033[1;33m"; // 设置文本颜色为黄色的ANSI转义码
const std::string DEFAULT_COLOR_CODE = "\033[0m";	// 恢复默认文本颜色的ANSI转义码

constexpr static int GRAPH_SIZE = 10; // 默认结点数
constexpr static int EXPANSION = 5; // 扩容结点数

const int threshold = 1e8; // 范围阈值
