#pragma once

#include<assert.h>

template<class T>
class Vector
{
public:
	typedef T ValueType;
	typedef ValueType* Pointer;
	typedef ValueType& Reference;

	typedef ValueType* Iterator;

public:
	Vector()
		:_start(NULL)
		, _finish(NULL)
		, _endOfStorage(NULL)
	{}

	~Vector()
	{

	}

public:

	Iterator Begin()
	{
		return _start;
	}

	Iterator End()
	{
		return _finish;
	}

	size_t Size()
	{
		return _finish - _start;
	}

	size_t Capacity()
	{
		return _endOfStorage - _start;
	}

	void PushBack(const T& x)
	{
		_CheckCapacity();

		*_finish = x;
		_finish++;
	}

	void PopBack()
	{
		_finish--;
	}

	Iterator Erase(Iterator pos)
	{
		Iterator begin = pos + 1;
		while (begin != _finish)
		{
			*(begin - 1) = *begin;
			++begin;
		}
		--_finish;
		return pos;
	}

protected:
	void _CheckCapacity()
	{
		if (_finish == _endOfStorage)
		{
			size_t size = Size();
			size_t capacity = size * 2 + 3;
			T* tmp = new T[capacity];
			for (int i = 0; i < size; i++)
			{
				tmp[i] = _start[i];
			}
			delete[] _start;
			_start = tmp;
			_finish = _start + size;
			_endOfStorage = _start + capacity;
		}
	}

private:
	Iterator _start;
	Iterator _finish;
	Iterator _endOfStorage;
};

void Print(Vector<int>& v)
{
	Vector<int>::Iterator it = v.Begin();
	while (it != v.End())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}

void TestVector()
{
	Vector<int> v;
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);
	v.PushBack(4);
	v.PushBack(5);
	v.PushBack(6);
	Print(v);
}