#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

struct A
{
	int _a;
};

/*
template<class T>
class AutoPtr
{
public :
	AutoPtr(T* ptr = 0)
		:_ptr(ptr)
	{
		ptr = NULL;
	}

	AutoPtr(AutoPtr<T>& pa)//注意参数不能为const类型的
		:_ptr(pa._ptr)
	{
		pa._ptr = NULL;//交权限并将自己置空
	}

	AutoPtr& operator=(AutoPtr<T>& pa)//参数类型不能为const类型的
	{
		if (this != &pa)//判断自赋值
		{
			delete _ptr;
			_ptr = pa._ptr;//交权限并将自己置空
			pa._ptr = NULL;
		}
		return *this;
	}

	~AutoPtr()
	{
		if (_ptr)
		{
			delete _ptr;
			_ptr = NULL;
		}
	}

	T& operator*()
	{
		if (_ptr)
		{
			return *_ptr;
		}
	}

	T* operator->()//没有验证
	{
		return _ptr;
	}

	T* _ptr;
};


void TestAutoPtr()
{
	AutoPtr<int> pa(new int(1));
	*pa = 10;//验证operator*
	AutoPtr<A> pb(new A);
	pb->_a = 20;//验证operator->
	
	AutoPtr<int> pc;

}

template<class T>
class AutoPtr
{
public :
	AutoPtr(T* ptr = 0)//构造函数
		:_ptr(ptr)
		,_owner(true)//当独占资源时将其设置为true
	{}

	AutoPtr(AutoPtr<T>& ap)//拷贝构造函数
		:_ptr(ap._ptr)
		, _owner(true)
	{
		ap._owner = false;
	}

	AutoPtr& operator=(AutoPtr<T>& ap)//赋值运算符重载
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
		}
	}

private :
	T* _ptr;
	bool _owner;
};

void TestAutoPtr()
{
	AutoPtr<int> ap(new int(10));
	AutoPtr<int> ap1(new int(20));
	AutoPtr<int> ap2(ap1);
	AutoPtr<int> ap3;
	ap3 = ap;
}

//防拷贝、防赋值
template<class T>
class ScopedPtr
{
public :
	ScopedPtr(T* ptr = 0)//构造函数
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

private :
	ScopedPtr(const ScopedPtr& ap);//拷贝构造函数
	ScopedPtr& operator=(const ScopedPtr& ap);//赋值运算符重载函数
	T* _ptr;
};


void TestScoped()
{
	ScopedPtr<int> ap1(new int(10));
	//ScopedPtr<int> ap2(ap1);
}

template<class T>
class SharpedPtr
{
public:
	SharpedPtr(T* ptr = 0)//构造函数
		:_ptr(ptr)
		, _pCount(NULL)
	{
		if (ptr)
		{
			_pCount = new int(1);
		}
	}

	SharpedPtr(const SharpedPtr<T>& ap)//拷贝构造
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
	SharpedPtr& operator=(const SharpedPtr<int>& ap)
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

	//析构函数
	~SharpedPtr()
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


void TestSharpedPtr()
{
	SharpedPtr<int> ap1(new int(10));
	SharpedPtr<int> ap2(new int(20));
	SharpedPtr<int> ap3(ap1);
	SharpedPtr<int> ap4;
	ap4 = ap1;
}
*/

//管理数组（防拷贝、防赋值）
template<class T>
class ScopedArray
{
public:
	ScopedArray(T* ptr = 0)//构造函数
		:_ptr(ptr)
	{}

	~ScopedArray()//析构函数
	{
		if (NULL != _ptr)
		{
			delete[] _ptr;
			_ptr = NULL;
		}
	}
	
	T& operator[](size_t index)
	{
		return _ptr[index];
	}

private:
	ScopedArray(const ScopedArray<T>& ap);
	ScopedArray& operator=(const ScopedArray<T>& ap);
	T* _ptr;
};

void TestScopedArray()
{
	ScopedArray<int> ap1(new int[2]);
	//ScopedArray<int> ap2(ap1);
}


int main()
{
	//TestAutoPtr();
	//TestScoped();
	//TestSharpedPtr();
	TestScopedArray();
	return 0;
}
