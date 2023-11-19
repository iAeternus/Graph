/*****************************************************************//**
 * \file   GraphNode.h
 * \brief  结点基类
 * 
 * \author 吴子维
 * \date   September 2023
 *********************************************************************/
#pragma once

MYLIB_BEGIN
template<typename value_type>
class GraphNode
{
public:
    GraphNode(const value_type& value = value_type(0));
    GraphNode(const value_type&& value);
    virtual ~GraphNode();
    GraphNode(const GraphNode& other);
    GraphNode& operator=(const GraphNode& other);
    GraphNode(GraphNode&& other) noexcept;
    GraphNode& operator=(GraphNode&& other) noexcept;

    int In_degree() const;
    int Out_degree() const;
    value_type Value() const;
    
    void In_degree(int in_degree);
    void Out_degree(int out_degree);

    void In_degree_plus_one();
    void Out_degree_plus_one();

    void In_degree_minus_one();
    void Out_degree_minus_one();

    template<typename value_type>
    friend std::istream& operator>>(std::istream& in, GraphNode<value_type>& node);

protected:
    int in_degree; // 入度
    int out_degree; // 出度
    value_type value; // 结点值
};

template<typename value_type>
inline GraphNode<value_type>::GraphNode(const value_type& value) :
    in_degree(0), out_degree(0), value(value)
{}

template<typename value_type>
inline GraphNode<value_type>::GraphNode(const value_type&& value) :
    in_degree(0), out_degree(0), value(std::move(value))
{}

template<typename value_type>
inline GraphNode<value_type>::~GraphNode()
{}

template<typename value_type>
inline GraphNode<value_type>::GraphNode(const GraphNode& other) :
    in_degree(other.in_degree), out_degree(other.out_degree), value(other.value)
{}

template<typename value_type>
inline GraphNode<value_type>& GraphNode<value_type>::operator=(const GraphNode& other)
{
    if (this != &other)
    {
        this->in_degree = other.in_degree;
        this->out_degree = other.out_degree;
        this->value = other.value;
    }
    return *this;
}

template<typename value_type>
inline GraphNode<value_type>::GraphNode(GraphNode&& other) noexcept :
    in_degree(other.in_degree), out_degree(other.out_degree), value(std::move(other.value))
{}

template<typename value_type>
inline GraphNode<value_type>& GraphNode<value_type>::operator=(GraphNode&& other) noexcept
{
    if (this != &other)
    {
        this->in_degree = other.in_degree;
        this->out_degree = other.out_degree;
        this->value = std::move(other.value);
    }
    return *this;
}

template<typename value_type>
inline int GraphNode<value_type>::In_degree() const
{
    return this->in_degree;
}

template<typename value_type>
inline int GraphNode<value_type>::Out_degree() const
{
    return out_degree;
}

template<typename value_type>
inline value_type GraphNode<value_type>::Value() const
{
    return this->value;
}

template<typename value_type>
inline void GraphNode<value_type>::In_degree(int in_degree)
{
    this->in_degree = in_degree;
}

template<typename value_type>
inline void GraphNode<value_type>::Out_degree(int out_degree)
{
    this->out_degree = out_degree;
}

template<typename value_type>
inline void GraphNode<value_type>::In_degree_plus_one()
{
    ++this->in_degree;
}

template<typename value_type>
inline void GraphNode<value_type>::Out_degree_plus_one()
{
    ++this->out_degree;
}

template<typename value_type>
inline void GraphNode<value_type>::In_degree_minus_one()
{
    --this->in_degree;
}

template<typename value_type>
inline void GraphNode<value_type>::Out_degree_minus_one()
{
    --this->out_degree;
}

template<typename value_type>
std::istream& operator>>(std::istream& in, GraphNode<value_type>& node)
{
    in >> node.value;
    return in;
}
MYLIB_END