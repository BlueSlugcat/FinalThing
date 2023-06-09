#include "List.h"

template <class T>
List<T>::List() : m_head(nullptr), m_tail(nullptr)
{}

template <class T>
List<T>::List(T data)
{
	m_head = new Node<T>(data);
	m_tail = m_head;
	m_tail->setPrev(m_head);

}

template <class T>
List<T>::List(const List<T>& original)
{
	m_head = new Node<T>(*(original.m_head));
	m_tail = new Node<T>(*(original.m_tail));
}

template <class T>
List<T>::List(List<T>&& original) noexcept
{
	m_head = new Node<T>(*(move(original.m_head)));
	m_tail = new Node<T>(*(move(original.m_tail)));
	delete original;
}

template <class T>
List<T>& List<T>::operator=(const List<T>& rhs)
{
	m_head = rhs->m_head;
	m_tail = rhs->m_tail;
	return *this;
}

template <class T>
List<T>& List<T>::operator=(List<T>&& rhs) noexcept
{
	m_head = new Node<T>(*(move(rhs.m_head)));
	m_tail = new Node<T>(*(move(rhs.m_tail)));
	delete rhs;
	return *this;
}

template <class T>
List<T>::~List<T>()
{}

template <class T>
void List<T>::Clear()
{
	Node<T>* temp;
	Node<T>* deltemp;
	int done{};
	if (m_head != nullptr)
	{
		temp = m_head;
		while (done == 0)
		{
			if (temp->getNext() != nullptr)
			{
				deltemp = temp;
				temp = temp->getNext();
				delete deltemp;
			}
			else
			{
				delete temp;
				m_head = nullptr;
				done = 1;
			}
		}
		
	}
	else
	{
		
	}

}

template <class T>
void List<T>::Prepend(T data)
{
	Node<T>* temp;
	if (m_head != nullptr)
	{

		temp = m_head;
		m_head = new Node<T>(data);
		m_head->m_next = temp;
		m_head->m_next->m_prev = m_head;
	}
	else if (m_head == m_tail && m_head != nullptr)
	{
		m_head = new Node<T>(data);
		m_head->m_next = m_tail;
		m_tail->m_prev = m_head;
	}
	else
	{
		m_head = new Node<T>(data);
		m_tail = m_head;
		m_head->m_next = m_tail;
		m_tail->m_next = nullptr;
	}
}

template <class T>
void List<T>::Append(T data)
{
	Node<T>* temp;
	if (m_head != nullptr && m_tail != nullptr)
	{
		m_tail->m_prev = (new Node<T>(data));
	}
	else
	{
		m_head = new Node<T>(data);
		m_tail = m_head;
		m_tail->setPrev(m_head);
	}
}

template <class T>
void List<T>::Insert(int pos, T data)
{
	Node<T>* temp;
	Node<T>* nexttemp;

	if (pos == 0)
	{
		Prepend(data);
	}
	else if (pos < 0)
	{
		
	}
	else if (m_head != nullptr)
	{
		temp = m_head;
		for (int i{}; i < pos; i++)
		{
			if (temp->getNext() == nullptr)
			{
				if (i < pos - 1)
				{
					
					temp->setNext(new Node<T>(data, temp));
					m_tail = temp->getNext();
					break;
				}
				else if (i == pos - 1)
				{
					temp->setNext(new Node<T>(data, temp));
					
				}
			}
			else if (i == pos - 1)
			{
				nexttemp = temp->getNext();
				temp->setNext(new Node<T>(data, temp));
				temp = temp->getNext();
				temp->setNext(nexttemp);
			
			}
			else
			{
				temp = temp->m_next;
			}
		}
	}
	else
	{
		
		m_head = new Node<T>(data);
		m_tail = m_head;
		m_tail->setPrev(m_head);

	}
}

template <class T>
bool List<T>::finditem(T target)
{
	bool foundflag = false;
	Node<T>* temp = m_head;
	if (m_head == nullptr)
	{
		return foundflag;
	}

	while (temp != nullptr && foundflag == false)
	{
		if (temp->item == target)
		{
			foundflag = true;
		}
		else
		{
			temp = temp->m_next;
		}
	}
	return foundflag;
}

template <class T>
void List<T>::incrementQ(T target)
{
	int flag{};
	Node<T>* temp = m_head;
	while (flag != 1)
	{
		if (temp->item == target)
		{
			flag = 1;
			temp->item.setQ(temp->item.getQ() + 1);
		}
		else
		{
			temp = temp->m_next;
		}
	}
}




template <class T>
void List<T>::DeleteData(T target)
{
	Node<T>* temp = m_head;
	Node<T>* nexttemp = nullptr;
	Node<T>* prevtemp = nullptr;
	int completeflag{};
	if (m_head == nullptr)
	{
		
	}
	else if (m_head->item == target)
	{
		nexttemp = m_head->m_next;
		if (nexttemp != nullptr)
		{
			nexttemp->m_prev = nullptr;
		}
		m_head = nexttemp;
		delete temp;
	
	}
	else if (m_tail->item == target)
	{
		prevtemp = m_tail->m_prev;
		if (prevtemp != nullptr)
		{
			prevtemp->m_next = nullptr;
		}
		m_tail = prevtemp;
		delete temp;
		
	else
	{
		while (temp != nullptr && completeflag != 1)
		{
			nexttemp = temp->m_next;
			if (temp->item == target)
			{
				prevtemp->m_next = nexttemp;
				nexttemp->m_prev = prevtemp;
				delete temp;
				completeflag = 1;
				
			}
			else
			{
				prevtemp = temp;
				temp = temp->m_next;
			}
		}
		if (completeflag == 0)
		{
			
	}
}

template <class T>
void List<T>::Display()
{
	Node<T>* temp;
	temp = m_head;
	if (m_head == nullptr)
	{
		
	}
	while (temp != nullptr)
	{
		temp->getData();
		temp = temp->getNext();

	}
}