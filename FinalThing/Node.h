#ifndef NODE_H
#define NODE_H
#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include "String.h"
using namespace std;
template <class T>

class Node
{
private:
	T item;
	Node<T>* m_next;
	Node<T>* m_prev;
public:
	Node();
	Node(T data);
	Node(T data, Node<T>* prev);
	Node(const Node<T>& original);
	Node<T>& operator =(const Node<T>& rhs);
	Node(Node<T>&& target) noexcept;
	Node<T>& operator = (Node<T>&& target) noexcept;
	~Node();
	void setData(T data);
	void getData();
	void setNext(Node<T>* next);
	Node<T>* getNext();
	void setPrev(Node<T>* prev);
	Node<T>* getPrev();
	template <class t>
	friend class List;
};
#endif



