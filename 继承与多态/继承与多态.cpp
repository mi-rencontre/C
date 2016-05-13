#include <iostream>
using namespace std;

#include <string>
// 1.实现以下几个类的成员函数
// 2.实现一个虚函数的覆盖及调用
// 3.处理菱形继承问题。

// 植物
class Botany
{
public:
	Botany(string& name)
		:_name(name)
	{
		++_sCount;
	}

	Botany(Botany& b)
	{
		_name = b._name;
		++_sCount;
	}

	virtual void Display()
	{
		cout<<_name<<endl;
		cout<<_sCount<<endl;
	}

	virtual ~Botany()
	{
		--_sCount;
	}

protected:
	string _name;  //名字
	static int _sCount;
};

int Botany::_sCount = 0;

class Tree :virtual public Botany
{
public:
	//...实现默认的成员函数
	Tree(string& name, int hight)
		:Botany(name)
		,_hight(hight)
	{}

	Tree(Tree& t)
		:Botany(t)
		,_hight(t._hight)
	{}

	virtual void Display()
	{
		cout<<_name<<endl;
		cout<<_hight<<endl;
		cout<<_sCount<<endl;
	}

	~Tree()
	{
	}

protected:
	int _hight;		
};

class Flower :virtual public Botany
{
public:
	//...实现默认的成员函数
	Flower(string& name, string& colour)
		:Botany(name)
		,_colour(colour)
	{}

	Flower(Flower& f)
		:Botany(f)
		,_colour(f._colour)
	{}

	virtual void Display()
	{
		cout<<_name<<endl;
		cout<<_colour<<endl;
		cout<<_sCount<<endl;
	}

	~Flower()
	{}
protected:
	string _colour;	// 颜色
};

// 白兰花，即是树有时花。
class MicheliaAlba : public Flower, public Tree
{
public:
	// ...
	MicheliaAlba(string& name, int hight, string& colour)
		:Botany(name)
		,Tree(name, hight)
		,Flower(name,colour)
	{}

	MicheliaAlba(MicheliaAlba& m)
		:Botany(m)
		,Tree(m)
		,Flower(m)
	{}

	virtual void Display()
	{
		cout<<_name<<endl;
		cout<<_colour<<endl;
		cout<<_sCount<<endl;
	}

	~MicheliaAlba()
	{}
};

int main()
{
	//string s1 = "aaa";
	//Botany b1(s1);
	//Botany b2(b1);
	//b2.Display();
	//string s2 = "bbb";
	//Tree t1(s2,5);
	//Tree t2(t1);
	//t1.Display();
	string s3 = "ccc";
	string s4 = "yellow";
	Flower f1(s3,s4);
	f1.Display();
	MicheliaAlba m1(s3,3,s4);
	MicheliaAlba m2(m1);
	m1.Display();
	return 0;
}
