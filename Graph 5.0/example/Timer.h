#pragma once
#include <iostream>
#include <chrono>

#include "../include/Config.h"

// 微秒计时器（理论上适用于 release 模式）
MYLIB_BEGIN
class Timer
{
public:
	Timer(const char* name = nullptr)
		: name(name), m_startTimePoint(std::chrono::high_resolution_clock::now()), is_Stopped(false) 
	{}

	~Timer()
	{
		if (!is_Stopped)
		{
			Stop();
		}
	}

	void Stop()
	{
		auto endTimePoint = std::chrono::high_resolution_clock::now();
		// 转成微秒，更精确
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimePoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

		auto duration = end - start;
		double ms = duration * 0.001; // 如果要毫秒的话

		if (name)
		{
			std::cout << YELLOW_COLOR_CODE << '[' << name << "] " << DEFAULT_COLOR_CODE;
		}
		std::cout << GREEN_COLOR_CODE << duration << DEFAULT_COLOR_CODE << "us ( ";
		std::cout << GREEN_COLOR_CODE << ms << DEFAULT_COLOR_CODE << "ms )\n";
		is_Stopped = true;
	}
private:
	const char* name; // 计时器名字
	std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimePoint; // 开始时刻
	bool is_Stopped; // 计时器是否停止
};
MYLIB_END
