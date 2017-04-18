#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

void Funtest1()
{
	int err = 1;
	throw err;
}

void Test1()
{
	try
	{
		Funtest1();
	}
	catch (const int& h)
	{
		cout << h << endl;
	}
}


class A
{};

class B :public A
{};

void Funtest2()
{
	throw B();//抛出一个匿名对象(派生类)
}

void Test2()
{
	try
	{
		Funtest2();
	}
	catch (A& b)//（基类接收）
	{
		//...
	}
}


void FunTest3(void)
{
	int array[10];
	throw array;
}

void Test3()
{
	try
	{
		FunTest3();
	}
	catch (int* array)
	{
		//...
	}
}

void Funtest5()
{
	cout << "hello" << endl;
}

void Funtest4()
{
	throw Funtest5;
}

void Test4()
{
	try
	{
		Funtest4();
	}
	catch (void (*p)(void))//定义一个函数指针（接收一个函数）
	{
		//..,
	}
}


#include<string>

class Eception
{
public :
	Eception(int errId = 0, char* errMsg = "")
		:_errId(errId)
		,_errMsg(errMsg)
	{}
	void What()const
	{
		cout << "errId:" << _errId << endl;
		cout << "errMsg:" << _errMsg << endl;
	}
private:
	int _errId;//错误ID
	string _errMsg;//错误信息
};

void Func1()
{
	throw string("throw func1 string");
}

void Func2()
{
	try
	{
		Func1();
	}
	catch (string& errMsg)
	{
		cout << errMsg << endl;
		//Eception e(1, "rethorw exception");
		//throw e;
	}
}

void Func3()
{
	try
	{
		Func2();
	}
	catch (Eception& e)//最顶层类的类型
	{
		e.What();//应该不执行
	}
}

int main()
{
	Func3();
	return 0;
}
