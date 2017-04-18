#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<cassert>

#include<list>
#include<algorithm>


/*
void Test1()
{
	list<int> col1;
	list<int>::iterator pos;

	for (int i = 20; i <= 40; ++i)
	{
		col1.push_back(i);
	}
	
	pos = find_if(col1.begin(), col1.end(),/
		compose_f_gx_hx(logical_or<bool>(), /
		bind2nd(equal_to<int>(), 25),
		bind2nd(equal_to<int>(), 35)));

	swith (*pos)
	{
		case 25:
			pos25 = pos;
			pos35 = find(++pos, col1.end(), 35);

			break;

		case 35:
			pos35 = pos;
			pos25 = find(++pos, col1.end(), 25);
			break;
		
		default:
			break;
	}


}


#include<vector>
#include<list>
#include<deque>
#include<set>

#include<algorithm>

void Test1()
{
	list<int> col1;

	for (int i = 1; i <= 9; i++)
	{
		col1.push_back(i);
	}


	vector<int> col2;
	col2.resize(col1.size(),2);//将col2的size修改为和col1相等
	//覆盖型拷贝（目标容器的size值至少要和源容器相等）
	copy(col1.begin(), col1.end(), col2.begin());

	vector<int>::iterator pos;
	
	for (pos = col2.begin(); pos != col2.end(); ++pos)
	{
		cout << *pos << "  ";
	}
	cout << endl;

	deque<int> col3(col1.size());
	copy(col1.begin(), col1.end(), col3.begin());
	deque<int>::iterator pos2;

	for (pos2 = col3.begin(); pos2 != col3.end(); ++pos2)
	{
		cout << *pos2 << "  ";
	}
	cout << endl;

}


#include<vector>
#include<list>
#include<deque>
#include<set>

#include<algorithm>

void Test1()
{
	list<int> col1;

	for (int i = 1; i <= 9; i++)
	{
		col1.push_back(i);
	}

	vector<int> col2;
	copy(col1.begin(), col1.end(), back_inserter(col2));
	vector<int>::iterator pos;

	for (pos = col2.begin(); pos != col2.end(); ++pos)
	{
		cout << *pos << "  ";
	}
	cout << endl;

	deque<int> col3(col1.size());
	copy(col1.begin(), col1.end(), col3.begin());
	deque<int>::iterator pos2;

	for (pos2 = col3.begin(); pos2 != col3.end(); ++pos2)
	{
		cout << *pos2 << "  ";
	}
	cout << endl;

}

#include<vector>
#include<algorithm>
#include<iterator>

void Test1()
{
	vector<int> col1;

	for (int i = 1; i <= 9; i++)
	{
		col1.push_back(i);
	}

	copy(col1.rbegin(), col1.rend(),\
		ostream_iterator<int>(cout," "));//输出一个容器里的元素
	//接着会输出一个空格，然后才会接着向下输出。
	cout << endl;
}

//移除元素removeing
#include<list>
#include<algorithm>
#include<iterator>

void Test1()
{
	list<int> col1;

	for (int i = 0; i <= 6; i++)
	{
		col1.push_back(i);
		col1.push_front(i);
	}

	copy(col1.begin(), col1.end(), \
		ostream_iterator <int>(cout, " "));
	cout << endl;
	//删除3这个元素
	remove(col1.begin(), col1.end(), 3);//删除之后元素个数不变
	cout << col1.size() << endl;

}

*/
#include<list>
#include<algorithm>
#include<iterator>

void Test1()
{
	list<int> col1;
	for (int i = 0; i <= 6; i++)
	{
		col1.push_back(i);
		col1.push_front(i);
	}
	copy(col1.begin(), col1.end(), \
		ostream_iterator <int>(cout, " "));
	cout << endl;
	//返回值是删除3后的位置（少了两个元素
	//但实际上col1容器的实际元素个数本就没有变化）
	list<int>::iterator end = remove(col1.begin(), col1.end(),3);
	copy(col1.begin(), end, ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << distance(end, col1.end()) << endl;
	//删除一个区间的元素
	col1.erase(end, col1.end());
	copy(col1.begin(), col1.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
}

int main()
{
	Test1();
	return 0;
}
