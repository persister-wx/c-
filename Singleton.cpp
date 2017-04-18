#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

class Singleton
{
	Singleton()//将构造函数设置为private的，是为了防止在类外构造对象
	{
		cout << "Singleton" << endl;
	}
	static Singleton* _instance;//指向该类对象的指针
public:
	static Singleton* Get()//获取指向该类对象的指针,
		//因为在类外不能创建对象，所以要将该函数声明为static的,
		//使得在类外可以使用类的作用域限定符来获取
	{
	//	if (NULL == _instance)
	//	{
	//		_instance = new Singleton();//保证了只创建一份实例
	//		cout << "creat once" << endl;
	//	}
		  return _instance;
	}
};

Singleton* Singleton::_instance = new Singleton();//静态成员变量需要在类外进行定义

void Test()
{
	//Singleton tmp1;//证明不能在类外创建对象
	//Singleton tmp2 = new Singleton();
	Singleton* tmp3 = Singleton::Get();
	Singleton* tmp4 = Singleton::Get();

	cout << (tmp3 == tmp4) << endl;
}

int main()
{
	cout << "main()" << endl;
	Test();
	return 0;
}


