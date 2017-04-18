#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<memory>
/*
template<class T>
class AutoPtr
{
public:
    AutoPtr(T* ptr = 0)//构造函数
        :_ptr(ptr)
    {
        ptr = NULL;
    }

    AutoPtr(AutoPtr<T>& ap)//拷贝构造函数
        :_ptr(ap._ptr)
    {
        ap._ptr = NULL;
    }

    AutoPtr<T>& operator=(AutoPtr<T>& ap)//赋值运算符重载
    {
        if (this != &ap)
        {
            if (_ptr)
            {
                delete _ptr;
            }
            _ptr = ap._ptr;
            ap._ptr = NULL;
        }
        return *this;
    }

    ~AutoPtr()//析构函数
    {
        if (_ptr)
        {
            delete _ptr;
            _ptr = NULL;
        }
    }

    T& operator*()
    {
        return *_ptr;
    }

    T* operator->()
    {
        return _ptr;
    }
private:
    T* _ptr;
};

AutoPtr<int> Funtest()
{
    AutoPtr<int> ap(new int(1));
    return ap;
}

void Test1()
{
    AutoPtr<int> ap(new int(1));
    AutoPtr<int> ap1(ap);
    AutoPtr<int> ap2;
    ap2 = ap1;
    AutoPtr<int> ap4(Funtest());//返回值以值的形式返回，则为一个匿名变量，
    //匿名变量具有常性，所以在拷贝构造ap4时，拷贝构造函数的参数应该由const修饰
	AutoPtr<int> ap1(AutoPtr<int>(new int(10)));
}


template<class T>
class AutoPtr
{
public:
    AutoPtr(T* ptr = 0)//构造函数
        :_ptr(ptr)
        , _owner(true)//当独占资源时将其设置为true
    {
        if (!_ptr)
        {
            _owner = false;
        }
    }

    AutoPtr(const AutoPtr<T>& ap)//拷贝构造函数
        :_ptr(ap._ptr)
        , _owner(true)
    {
        ap._owner = false;
    }

    AutoPtr& operator=(const AutoPtr<T>& ap)//赋值运算符重载
    {
        if (this != &ap)
        {
            delete _ptr;
            _owner = true;
            _ptr = ap._ptr;
            ap._owner = false;
        }
        return *this;
    }

    ~AutoPtr()
    {
        if (_owner)
        {
            delete _ptr;
			_ptr = NULL;
			cout<<"~AutoPtr()"<<endl;
        }
    }

    T& operator*()
    {
        return *_ptr;
    }

    T* operator->()
    {
        return _ptr;
    }
private:
    T* _ptr;
    mutable bool _owner;//可被修改的
};

void TestAutoPtr()
{
    AutoPtr<int> ap(new int(10));
    AutoPtr<int> ap1(new int(20));
    AutoPtr<int> ap2(ap1);
    AutoPtr<int> ap3;
    ap3 = ap;
    AutoPtr<int> ap4(AutoPtr<int>(new int(20)));
    if (true)
    {
        AutoPtr<int> ap5(ap4);
    }//作用域结束之后ap5已被析构
    *ap4 = 10;//这时ap5与ap4共享一块空间，既然ap5已被释放，那么ap4对象维护的指针已成为野指针
}



//防拷贝、防赋值
template<class T>
class ScopedPtr
{
public :
    ScopedPtr(T* ptr)//构造函数
        :_ptr(ptr)
    {}//不用交出管理权限
    ~ScopedPtr()//析构函数
    {
        if (NULL != _ptr)
        {
            delete _ptr;
            _ptr = NULL;
        }
    }

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}
private :
    ScopedPtr(const ScopedPtr& ap);//拷贝构造函数
    ScopedPtr& operator=(const ScopedPtr& ap);//赋值运算符重载函数
    T* _ptr;
};

void Test1()
{
	ScopedPtr<int> sp1(new int(10));
	*sp1 = 20;
}

template<class T>
struct Node
{
	Node(const T& value)
		:_prev(NULL)
		,_next(NULL)
		,_value(value)
	{}
	shared_ptr<Node<T> >_prev;
	shared_ptr<Node<T> >_next;

	T _value;
};

void Test1()
{
	//shared_ptr<int> sp(new int(10));
	//shared_ptr<file*> sp2(fopen("test.txt","rb"));
	shared_ptr<Node<int>> p1(new Node<int>(1));
	shared_ptr<Node<int>> p2(new Node<int>(2));
	p1->_next = p2;
	p2->_prev = p1;*/


template<class T>
class SharedPtr
{
public:
    SharedPtr(T* ptr = 0)//构造函数
        :_ptr(ptr)
        , _pCount(NULL)
    {
        if (_ptr)
        {
            _pCount = new int(1);
        }
    }
    SharedPtr(const SharedPtr<T>& ap)//拷贝构造
        :_ptr(ap._ptr)
        , _pCount(ap._pCount)
    {
        if (_ptr)
        {
            ++UseCount();
        }
    }
    //ap1 = ap2;赋值运算符重载
    //①ap1内部封装的指针为空
    //②ap1独占一块空间
    //③ap1与其他对象共享一块空间
    SharedPtr& operator=(const SharedPtr<int>& ap)
    {
        if (this != &ap)
        {
            if (_ptr)
            {
                Release();
            }
            //ap1与其他对象共享一块空间
            _ptr = ap._ptr;
            _pCount = ap._pCount;
            ++UseCount();
        }
        return *this;
    }

	T* operator->()
	{
		return _ptr;
	}

	T& operator*()
	{
		return *_ptr;
	}

    //析构函数
    ~SharedPtr()
    {
        Release();
    }
    //检查引用计数并释放空间
    void Release()
    {
        if (0 == --UseCount())
        {
            delete _pCount;
            _pCount = NULL;
            delete _ptr;
            _ptr = NULL;
        }
    }
    //获取引用计数
    int& UseCount()
    {
            return *_pCount;
    }
private:
    T* _ptr;
    int* _pCount;
};

template<class T>
class Node
{
public:
    Node(const T& value)
        :_pNext(NULL)
        ,_pPre(NULL)
        ,_value(value)
    {}
   SharedPtr<Node<T>> _pNext;
   SharedPtr<Node<T>> _pPre;
    T _value;
};
 
void FunTest()
{
	SharedPtr<Node<int> >  sp1(new Node<int>(10));
	SharedPtr<Node<int> >  sp2(new Node<int>(20));
	sp1->_pNext = sp2;
	cout<<sp2.UseCount()<<endl;
	sp2->_pPre = sp1;
	cout<<sp1.UseCount()<<endl;
}

int main()
{
	FunTest();
	return 0;
}
