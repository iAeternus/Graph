#pragma once

// ��������⣬�����������ܵ�Ϊ�����������ǻ����ʼʱ��ͽ���ʱ�䣩
struct Pipeline
{
    double flowRate; // ����
    double capacity; // ����
    double capacityRemaining; // ʣ������

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

