#include "stdafx.h"
#pragma once

#ifndef GENERIC_TREE_H
#define GENERIC_TREE_H

#include <iostream>
#include <iterator>
#include <queue>
#include <list>
#include "GenericTreeNode.h"
using namespace std;

template<class T>
class GenericTreeNode;

template<class T>
class GenericTree
{
public:
	GenericTree() = default;
	~GenericTree() = default;
	GenericTree(const GenericTree<T>& dataToCopy);
	GenericTree(GenericTree<T>&& dataToCopy);
public:
	GenericTree<T> & operator=(const GenericTree<T>& inRhs);
	GenericTree<T> & operator=(GenericTree<T>&& inRhs);
public:
	void SetFunction(void(*visit) (const GenericTreeNode<T>* const inNode)) noexcept { m_visit = visit; }
	void Breadthfirst() noexcept { m_Breadthfirst(m_root); }
	void SetRoot(GenericTreeNode<T>* inRoot) noexcept { m_root = inRoot; }
	GenericTreeNode<T> * GetRoot() const noexcept { return m_root; }
	void Purge();

private:
	GenericTreeNode<T>* m_root = nullptr;
	void(*m_visit) (const GenericTreeNode<T>* const inNode) = nullptr;
	void m_Breadthfirst(GenericTreeNode<T>* inNode) const;
	void m_PostOrder(GenericTreeNode<T>* inChild, std::list<GenericTreeNode<T>*>& traversal);
};

template<class T>
inline GenericTree<T>::GenericTree(const GenericTree<T>& dataToCopy)
{
	delete m_root;
	m_root = dataToCopy.m_root;
}

template<class T>
inline GenericTree<T>::GenericTree(GenericTree<T>&& dataToCopy)
{
	m_root = std::move(dataToCopy.m_root);
}

template<class T>
inline GenericTree<T>& GenericTree<T>::operator=(const GenericTree<T>& inRhs)
{
	if (this != &inRhs) {
		m_root = inRhs.m_root;
	}
	return *this;
}

template<class T>
inline GenericTree<T> & GenericTree<T>::operator=(GenericTree<T>&& inRhs)
{
	m_root = std::move(inRhs.m_root);
	return *this;
}

template<class T>
inline void GenericTree<T>::Purge()
{
	delete[] m_root;
	m_root = nullptr;
}

template<class T>
inline void GenericTree<T>::m_Breadthfirst(GenericTreeNode<T>* inNode) const
{
	list<GenericTreeNode<T>*> queueNode;
	queueNode.emplace_back(inNode);

	while (!queueNode.empty())
	{
		GenericTreeNode<T>* tempChildPtr = queueNode.front();
		list<GenericTreeNode<T>*> nodes = tempChildPtr->GetChildren();

		while (!nodes.empty())
		{
			queueNode.emplace_back(nodes.front());
			nodes.pop_front();
		}
		queueNode.pop_back();
	}
}

template<class T>
inline void GenericTree<T>::m_PostOrder(GenericTreeNode<T>* inChild, std::list<GenericTreeNode<T>*>& traversal)
{
	auto children = inChild->GetChildren();
	
	for (auto inChild: children) {
		m_PostOrder(inChild, traversal);
	}
	traversal.emplace_back(inChild);
}

#endif