#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;



/*
#include"boost\shared_ptr.hpp"

void Test1()
{
	boost::shared_ptr<int> sp1(new int(1));
	cout << sp1.use_count() << endl;
}
*/

#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<memory>

auto_ptr<int> FunTest()
{
	auto_ptr<int> ap1(new int(20));
	return ap1;//返回值为一个匿名对象
}

void FunTest1(auto_ptr<int> ap)
{}

void Test1()
{
	auto_ptr<int> ap1(new int(10));//构造函数
	
	FunTest1(ap1);
	*ap1 = 20;//程序会崩溃，ap1内封装的指针已为空，也就是野指针问题无法规避
}


int main()
{
	Test1();
	return 0;
}
