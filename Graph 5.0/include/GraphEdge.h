/*****************************************************************//**
 * \file   GraphEdge.h
 * \brief  ����
 * 
 * \author ����ά
 * \date   September 2023
 *********************************************************************/
#pragma once
#include "Pipeline.h"

MYLIB_BEGIN
template<typename weight_type = int>
class GraphEdge
{
public:
    GraphEdge(const weight_type& weight = weight_type(0));
    GraphEdge(const weight_type&& weight);
    GraphEdge(int fromIndex, int toIndex, bool isDirEdge = true, const weight_type& weight = weight_type(0));
    virtual ~GraphEdge();
    GraphEdge(const GraphEdge& other);
    GraphEdge& operator=(const GraphEdge& other);
    GraphEdge(GraphEdge&& other) noexcept;
    GraphEdge& operator=(GraphEdge&& other) noexcept;

    int FromIndex() const;
    int ToIndex() const;
    bool IsDirEdge() const;
    weight_type Weight() const;
    weight_type& Weight();
    int NeighborIndex() const;
    int& NeighborIndex();

    bool operator==(const GraphEdge& other) const;
    bool operator!=(const GraphEdge& other) const;

    template<typename weight_type = int>
    friend std::istream& operator>>(std::istream& in, GraphEdge<weight_type>& edge);

protected:
    int fromIndex; // �ߵ���Դ
    int toIndex; // �ߵ�ȥ��
    bool isDirEdge; // �Ƿ�������� true-����� false-�����
    weight_type weight; // �ߵ�Ȩ��
};

// ȫ�ػ� GraphEdge ��
template<>
class GraphEdge<Pipeline>
{
public:
    GraphEdge(const Pipeline& weight = Pipeline()) :
        fromIndex(-1), toIndex(-1), isDirEdge(true), weight(weight)
    {}

    GraphEdge(int fromIndex, int toIndex, bool isDirEdge = true, const Pipeline& weight = Pipeline()) :
        fromIndex(fromIndex), toIndex(toIndex), isDirEdge(isDirEdge), weight(weight)
    {}

    int FromIndex() const { return fromIndex; }
    int ToIndex() const { return toIndex; }
    Pipeline Weight() const { return weight; }
    Pipeline& Weight() { return weight; }
    int NeighborIndex() const { return toIndex; }
    int& NeighborIndex() { return toIndex; }

protected:
    int fromIndex; // �ߵ���Դ
    int toIndex; // �ߵ�ȥ��
    bool isDirEdge; // �Ƿ�������� true-����� false-�����
    Pipeline weight; // �ߵ�Ȩ��
};

template<typename weight_type>
inline GraphEdge<weight_type>::GraphEdge(const weight_type& weight) :
    fromIndex(-1), toIndex(-1), isDirEdge(true), weight(weight)
{}

template<typename weight_type>
inline GraphEdge<weight_type>::GraphEdge(const weight_type && weight) :
    fromIndex(-1), toIndex(-1), isDirEdge(true), weight(std::move(weight))
{}

template<typename weight_type>
inline GraphEdge<weight_type>::GraphEdge(int fromIndex, int toIndex, bool isDirEdge, const weight_type& weight) :
    fromIndex(fromIndex), toIndex(toIndex), isDirEdge(isDirEdge), weight(weight)
{}

//inline GraphEdge<Pipeline>::GraphEdge(int fromIndex, int toIndex, bool isDirEdge, const Pipeline& weight) :
//    fromIndex(fromIndex), toIndex(toIndex), isDirEdge(isDirEdge), weight(weight)
//{}

template<typename weight_type>
inline GraphEdge<weight_type>::~GraphEdge()
{}

template<typename weight_type>
inline GraphEdge<weight_type>::GraphEdge(const GraphEdge& other) :
    fromIndex(other.fromIndex), toIndex(other.toIndex), isDirEdge(other.isDirEdge), weight(other.weight)
{}

template<typename weight_type>
inline GraphEdge<weight_type>& GraphEdge<weight_type>::operator=(const GraphEdge& other)
{
    if (this != &other)
    {
        this->fromIndex = other.fromIndex;
        this->toIndex = other.toIndex;
        this->isDirEdge = other.isDirEdge;
        this->weight = other.weight;
    }
    return *this;
}

template<typename weight_type>
inline GraphEdge<weight_type>::GraphEdge(GraphEdge&& other) noexcept :
    fromIndex(other.fromIndex), toIndex(other.toIndex), isDirEdge(other.isDirEdge), weight(std::move(other.weight))
{}

template<typename weight_type>
inline GraphEdge<weight_type>& GraphEdge<weight_type>::operator=(GraphEdge&& other) noexcept
{
    if (this != &other)
    {
        this->fromIndex = other.fromIndex;
        this->toIndex = other.toIndex;
        this->isDirEdge = other.isDirEdge;
        this->weight = std::move(other.weight);
    }
    return *this;
}

template<typename weight_type>
inline int GraphEdge<weight_type>::FromIndex() const
{
    return this->fromIndex;
}

//template<>
//inline int GraphEdge<Pipeline>::FromIndex() const
//{
//    return this->fromIndex;
//}

template<typename weight_type>
inline int GraphEdge<weight_type>::ToIndex() const
{
    return this->toIndex;
}

//template<>
//inline int GraphEdge<Pipeline>::ToIndex() const
//{
//    return this->toIndex;
//}

template<typename weight_type>
inline bool GraphEdge<weight_type>::IsDirEdge() const
{
    return this->isDirEdge;
}

template<typename weight_type>
inline weight_type GraphEdge<weight_type>::Weight() const
{
    return this->weight;
}

template<typename weight_type>
inline weight_type& GraphEdge<weight_type>::Weight()
{
    return this->weight;
}

//template<>
//inline Pipeline GraphEdge<Pipeline>::Weight() const
//{
//    return this->weight;
//}
//
//template<>
//inline Pipeline& GraphEdge<Pipeline>::Weight()
//{
//    return this->weight;
//}

template<typename weight_type>
inline int GraphEdge<weight_type>::NeighborIndex() const
{
    return this->toIndex;
}

template<typename weight_type>
inline int& GraphEdge<weight_type>::NeighborIndex()
{
    return this->toIndex;
}

//template<>
//inline int GraphEdge<Pipeline>::NeighborIndex() const
//{
//    return this->toIndex;
//}
//
//template<>
//inline int& GraphEdge<Pipeline>::NeighborIndex()
//{
//    return this->toIndex;
//}

template<typename weight_type>
inline bool GraphEdge<weight_type>::operator==(const GraphEdge& other) const
{
    return fromIndex == other.fromIndex && toIndex == other.toIndex && isDirEdge == other.isDirEdge && weight == other.weight;
}

template<typename weight_type>
inline bool GraphEdge<weight_type>::operator!=(const GraphEdge& other) const
{
    return !(*this == other);
}

template<typename weight_type>
std::istream& operator>>(std::istream& in, GraphEdge<weight_type>& edge)
{
    in >> edge.fromIndex >> edge.toIndex >> edge.isDirEdge >> edge.weight;
    return in;
}
MYLIB_END // mylib