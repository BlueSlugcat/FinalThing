#include "Node.h"

template <class T>
Node<T>::Node() : m_next(nullptr), m_prev(nullptr)
{}

template <class T>
Node<T>::Node(T data) : m_next(nullptr), m_prev(nullptr)
{
	item = data;
}

template <class T>
Node<T>::Node(T data, Node<T>* prev) : m_next(nullptr), m_prev(prev)
{
	item = data;
}

template <class T>
Node<T>::Node(const Node<T>& original)
{
	if (original != nullptr)
	{
		setData(original.item);
		setNext(original.m_next);
		setPrev(original.m_prev);
	}
	else
	{
		this = new Node<T>;
	}

}

template <class T>
Node<T>& Node<T>::operator=(const Node<T>& rhs)
{
	if (rhs != nullptr)
	{
		setData(rhs.item);
		setNext(rhs.m_next);
		setPrev(rhs.m_prev);
		return *this;
	}
	else
	{
		return nullptr;
	}
}

template <class T>
Node<T>::Node(Node<T>&& target) noexcept
{
	if (target != nullptr)
	{
		item = move(target.item);
		m_next = move(target.m_next);
		m_prev = move(target.m_next);
		delete target;
	}
	else
	{
		this = move(new Node<T>);
	}

}

template <class T>
Node<T>& Node<T>::operator=(Node<T>&& target) noexcept
{
	item = move(target.item);
	m_next = move(target.m_next);
	m_prev = move(target.m_next);
	delete target;
	return *this;
}


template <class T>
Node<T>::~Node<T>()
{}

template <class T>
void Node<T>::setData(T data)
{
	item = data;
}

template <class T>
void Node<T>::getData()
{
	item.Display();
}

template <class T>
void Node<T>::setNext(Node<T>* next)
{
	m_next = next;
}

template <class T>
Node<T>* Node<T>::getNext()
{
	return m_next;
}

template <class T>
void Node<T>::setPrev(Node<T>* prev)
{
	m_prev = prev;
}

template <class T>
Node<T>* Node<T>::getPrev()
{
	return m_prev;
}