#pragma once
#include <iostream>
#include <chrono>

#include "../include/Config.h"

// ΢���ʱ���������������� release ģʽ��
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
		// ת��΢�룬����ȷ
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimePoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

		auto duration = end - start;
		double ms = duration * 0.001; // ���Ҫ����Ļ�

		if (name)
		{
			std::cout << YELLOW_COLOR_CODE << '[' << name << "] " << DEFAULT_COLOR_CODE;
		}
		std::cout << GREEN_COLOR_CODE << duration << DEFAULT_COLOR_CODE << "us ( ";
		std::cout << GREEN_COLOR_CODE << ms << DEFAULT_COLOR_CODE << "ms )\n";
		is_Stopped = true;
	}
private:
	const char* name; // ��ʱ������
	std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimePoint; // ��ʼʱ��
	bool is_Stopped; // ��ʱ���Ƿ�ֹͣ
};
MYLIB_END
