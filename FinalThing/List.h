#ifndef LIST_H
#define LIST_H
#include "Node.h"
template <class T>
class List
{
private:
	Node<T>* m_head;
	Node<T>* m_tail;
public:
	List();
	List(T data);
	List(const List<T>& original);
	List(List<T>&& original) noexcept;
	List<T>& operator = (const List<T>& rhs);
	List<T>& operator = (List<T>&& rhs) noexcept;
	~List();
	void Clear();
	void Prepend(T data);
	void Append(T data);
	void Insert(int pos, T data);
	bool finditem(T target);
	void incrementQ(T target);
	void DeleteData(T target);
	void Display();
};

#endif


