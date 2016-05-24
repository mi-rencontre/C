#pragma once

#include<assert.h>

template<class T>
struct __ListNode
{
	T _data;
	__ListNode<T>* _prev;
	__ListNode<T>* _next;

	__ListNode()
		:_prev(NULL)
		, _next(NULL)
	{}

	__ListNode(const T& x)
		:_data(x)
		, _prev(NULL)
		, _next(NULL)
	{}
};

template<class T>
struct __ListIterator
{
	typedef __ListIterator<T> Iterator;
	typedef T ValueType;
	typedef __ListNode<T>* LinkType;
	typedef T& Reference;
	typedef T* Pointer;

	LinkType _node;

	__ListIterator(LinkType node = NULL)
		:_node(node)
	{}

	bool operator==(const Iterator& x) const
	{
		return _node == x._node;
	}

	bool operator!=(const Iterator& x) const
	{
		return _node != x._node;
	}

	Reference operator*() const
	{
		return _node->_data;
	}

	Pointer operator->() const
	{
		return &(operator*());
	}

	Iterator& operator++()
	{
		_node = _node->_next;
		return *this;
	}

	Iterator operator++(int)
	{
		Iterator tmp(_node);
		_node = _node->_next;
		return tmp;
	}

	Iterator& operator--()
	{
		_node = _node->_prev;
		return *this;
	}

	Iterator operator--(int)
	{
		Iterator tmp(_node);
		_node = _node->_prev;
		return tmp;
	}

};

template<class T>
class List
{
public:
	typedef __ListIterator<T> Iterator;
	typedef T ValueType;
	typedef __ListNode<T>* LinkType;

	List()
	{
		_head._prev = &_head;
		_head._next = &_head;
	}

	~List()
	{
		Clear();
	}

public:
	void Insert(Iterator pos, const ValueType& x)
	{
		LinkType tmp = new __ListNode<T>(x);
		LinkType prev = pos._node->_prev;
		LinkType cur = pos._node;

		prev->_next = tmp;
		tmp->_prev = prev;

		tmp->_next = cur;
		cur->_prev = tmp;
	}

	void PushBack(const T& x)
	{
		Insert(End(), x);
	}

	void PushFront(const T& x)
	{
		Insert(Begin(), x);
	}

	//删除pos指向的结点，返回pos之后的一个结点
	Iterator Erase(Iterator pos)
	{
		LinkType prev = pos._node->_prev;
		LinkType next = pos._node->_next;

		prev->_next = next;
		next->_prev = prev;

		delete pos._node;

		return Iterator(next);
	}

	void PopBack()
	{
		Erase(--end());
	}

	void PopFront()
	{
		Erase(begin());
	}

	Iterator Begin()
	{
		return _head._next;
	}

	Iterator End()
	{
		return &_head;
	}

protected:

	void Clear()
	{
		Iterator begin = Begin();
		while (begin != End())
		{
			LinkType tmp = begin._node;
			++begin;
			delete tmp;
		}
	}

private:
	__ListNode<T>  _head;
};

void PrintList(List<int>& l)
{
	List<int>::Iterator it = l.Begin();
	while (it != l.End())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

void TestList()
{
	List<int> l;
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.PushBack(5);
	l.PushBack(6);
	PrintList(l);
}