#include "stdafx.h"
#pragma once

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <list>
using namespace std;

template<class T>
class Node
{
public:
	Node(T inData);
	~Node() {}
public: 
	T GetData() { return m_data; }

private:
	T m_data;
};

template<class T>
inline Node<T>::Node(T inData)
{
	m_data = inData;
}

#endif