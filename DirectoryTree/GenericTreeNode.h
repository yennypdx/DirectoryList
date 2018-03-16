#include "stdafx.h"
#pragma once

#ifndef GTNODE_H
#define GTNODE_H

#include <iostream>
#include <list>
#include "Node.h"
using namespace std;

template<class T>
class Node;

template<class T>
class GenericTreeNode: public Node<T>
{
public:
	explicit GenericTreeNode( T inData, GenericTreeNode<T>* inParent = nullptr)	:Node<T>(inData), m_parent(inParent) {}
	~GenericTreeNode() { m_children.clear(); m_parent = nullptr; }
	GenericTreeNode(const GenericTreeNode<T>& dataToCopy);
	GenericTreeNode(GenericTreeNode<T>&& dataToCopy);
public:
	GenericTreeNode<T>* GetParent() const noexcept { return m_parent; }
	void SetParent(GenericTreeNode<T>*  inParent) noexcept { m_parent = inParent; }
public:
	std::list<GenericTreeNode<T>*> GetChildren() const noexcept { return m_children; }
	void AddChild(GenericTreeNode<T>* const inChild) noexcept { m_children.emplace_back(inChild); }

private:
	GenericTreeNode<T>* m_parent = nullptr;
	std::list<GenericTreeNode<T>*> m_children;
};

template<class T>
inline GenericTreeNode<T>::GenericTreeNode(const GenericTreeNode<T>& dataToCopy)
{
	delete m_parent;
	m_parent = dataToCopy.m_parent;
	for (auto listNode : m_children) {
		m_children = dataToCopy.m_children;
	}
}

template<class T>
inline GenericTreeNode<T>::GenericTreeNode(GenericTreeNode<T>&& dataToCopy)
{
	m_parent = std::move(dataToCopy.m_parent);
}

#endif