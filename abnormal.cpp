#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

/*
/*
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
	catch (void(*p)(void))//定义一个函数指针（接收一个函数）
	{
		//..,
	}
}


#include<string>
class Eception
{
public:
	Eception(int errId = 0, char* errMsg = "")
		:_errId(errId)
		, _errMsg(errMsg)
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
		//throw;//抛出还给系统（会终止程序）
		throw errMsg;//在程序中没有捕获异常，所以最终由操作系统捕获（终止程序）
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
		e.What();
	}
}



class A
{
public:
	A()
	{
		cout << "A()" << endl;
	}
	void Fun()throw();
};


void A::Fun()
{
	throw 1;
}

void FunTest()throw ()
{
	throw 1;
}

int main()
{
	try
	{
		FunTest();
	}
	catch (int a)
	{
		cout << a << endl;
	}
	return 0;
}


#include <string>

#include <setjmp.h>


jmp_buf buf;
	void FunTest1()
{
	longjmp(buf, 0);
}

	void FunTest2()
{
	longjmp(buf, 2);
}


int main()
{
	int iState = setjmp(buf);//16个int大小
	if(0  == iState)
	{
		FunTest1();
		FunTest2();
	}
	else
	{
		switch(iState)
		{
		case 1:
			 cout<<"FunTest1()"<<endl;
			 break;
		case 2:
			 cout<<"FunTest2()"<<endl;
			break;
	    }
   }
	return 0;
}


class A
{
public:
	A()
	{
		cout << "A()" << endl;
	}
	~A()
	{
		cout << "~A()" << endl;
	}
};

void Funtest1()
{
	A a;
	FILE* fp;
	//int* p = new int[0x7fffffff / 4];//程序崩溃
	try
	{
		fp = fopen("1.txt", "rb");
		if (NULL == fp)
		{
			double err = 1;
			cout << (int*)&err << endl;
			throw err;//打开文件失败时会抛出错误码1
		}
	}
	catch (double& err)
	{
		//delete[] p;
		return;
	}
	fclose(fp);//返回之前会调A的析构函数
}


void Funtest2()
{
	int* p = (int*)malloc(0x7fffffff);//失败
	if (NULL == p)
	{
		throw 2;//内存开辟失败会抛出错误2
		//...(正常操作)
		free(p);
	}
}

void Funtest3()
{
	int* p = new int[10];
	try
	{
		Funtest1();
	}
	catch (...)//任何异常都可捕获
	{
		delete[] p;
		throw;
	}
}

void Funtest()
{
	try
	{
		Funtest3();
	}
	catch (char& err1)
	{
		cout << (int*)&err1 << endl;
		switch (err1)
		{
		case 1:
			cout << "文件打开失败" << endl;
			break;
		case 2:
			cout << "申请内存失败！" << endl;
			break;
		default:
			cout << "未知错误" << endl;
			break;
		}
	}
	catch (int err)
	{
		;
	}
	catch (double& err)
	{
		cout << err << endl;
	}
	catch (...)
	{
		cout << "未知异常" << endl;
	}

}

#include<windows.h>

class A
{
public:
	A()
	{
		_start = GetTickCount();
		cout << _start << endl;
	}
	~A()
	{
		_end = GetTickCount() - _start;
		cout << _end << endl;
	}
private :
	int _start;
	int _end;
};

#ifdef _DEBUG
#define TestTime A t;
#else
#define TestTime
#endif

*/

template<class T>
class AutoPtr
{
public:
	AutoPtr(T* p)
		:_p(p)
	{
		cout << "AutoPtr()" << endl;
	}
	~AutoPtr()
	{
		cout << "~AutoPtr()" << endl;
		if (_p)
		{
			delete _p;
			_p = NULL;
		}
	}
protected :
	T* _p;
};

void Funtest()
{
	int* p = new int;
	AutoPtr<int> ap(p);
}

int main()
{
	Funtest();
	return 0;
}
