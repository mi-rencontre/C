#include <iostream>
using namespace std;


//auto_ptr
template<typename T>
class AutoPtr
{
public:
    AutoPtr(T *ptr)
		:_ptr(ptr)
	{}

	AutoPtr(AutoPtr<T>& ap)
		:_ptr(ap._ptr)
	{
		ap._ptr = NULL;
	}

	AutoPtr<T>& operator=(AutoPtr<T>& ap)
	{
		if(_ptr != ap._ptr)
		{
			delete _ptr;
			_ptr = ap._ptr;
			ap._ptr = NULL;
		}
		return *this;
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

	~AutoPtr()
	{
		delete _ptr;
	}
private:
	T *_ptr;
};


//scoped_ptr
template<typename T>
class ScopedPtr
{
public:
    ScopedPtr(T *ptr)
		:_ptr(ptr)
	{}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

	~ScopedPtr()
	{
		delete _ptr;
	}
protected:
	ScopedPtr(ScopedPtr<T>& sp);
	ScopedPtr<T>& operator=(ScopedPtr<T>& sp);
private:
	T *_ptr;
};


//shared_ptr
template<typename T>
class SharedPtr
{
public:
    SharedPtr(T *ptr)
		:_ptr(ptr)
		,_pcount(new int(1))
	{
	}

	SharedPtr(SharedPtr<T>& sp)
		:_ptr(sp._ptr)
		,_pcount(sp._pcount)
	{
		(*_pcount)++;
	}

	SharedPtr<T>& operator=(SharedPtr<T>& sp)
	{
		if(_ptr != sp._ptr)
		{
			if(--(*_pcount) == 0)
			{
				delete _pcount;
				delete _ptr;
			}
			_ptr = sp._ptr;
			_pcount = sp._pcount;
			(*_pcount)++;
		}
		return *this;
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

	~SharedPtr()
	{
		if(--(*_pcount) == 0)
		{
			delete _ptr;
			delete _pcount;
		}
	}

private:
	T *_ptr;
	int *_pcount;
};

void Test1()
{
	int *p1 = new int(1);
	int *p2 = new int(2);
	AutoPtr<int> ap1(p1);
	AutoPtr<int> ap2(ap1);
	ap2 = ap1;
}

void Test2()
{
	int *p1 = new int(1);
	int *p2 = new int(2);
	ScopedPtr<int> sp1(p1);
	//ScopedPtr<int> ap4(ap3);
}

void Test3()
{
	int *p1 = new int(1);
	int *p2 = new int(2);
	SharedPtr<int> sp1(p1);
	SharedPtr<int> sp2(sp1);
	SharedPtr<int> sp3(p2);
	sp3 = sp1;
}

int main()
{
	//Test1();
	//Test2();
	Test3();
	return 0; 
}