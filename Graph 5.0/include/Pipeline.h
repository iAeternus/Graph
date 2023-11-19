#pragma once

// 最大流问题，这里以输气管道为例（还可以是活动的起始时间和结束时间）
struct Pipeline
{
    double flowRate; // 流量
    double capacity; // 容量
    double capacityRemaining; // 剩余容量

    Pipeline(double flowRate = 0, double capacity = 0) :
        flowRate(flowRate), capacity(capacity), capacityRemaining(capacity - flowRate)
    {}

    Pipeline(const Pipeline& other) :
        flowRate(other.flowRate), capacity(other.capacity), capacityRemaining(other.capacityRemaining)
    {}

    Pipeline& operator=(const Pipeline& other)
    {
        if (this != &other)
        {
            this->flowRate = other.flowRate;
            this->capacity = other.capacity;
            this->capacityRemaining = other.capacityRemaining;
        }
        return *this;
    }

    double residual() const { return capacity - flowRate; }

    bool operator==(const Pipeline& other) const
    {
        return this->flowRate == other.flowRate && this->capacity == other.capacity;
    }

    bool operator!=(const Pipeline& other) const
    {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& out, const Pipeline& pipeline)
    {
        out << '(' << pipeline.flowRate << '/' << pipeline.capacity << ')';
        return out;
    }
};

