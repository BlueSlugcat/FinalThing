#ifndef LIST_H
#define LIST_H
#include "Node.cpp"
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
	void Append(T data);
	bool finditem(T target);
	void incrementQ(T target);
	void DeleteData(T target);
	friend class Player;
};

#endif


