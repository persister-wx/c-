#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<string>

/*
void move(int n, char from, char to)
{
	cout << "将第" << n << "盘子从" << from << "到" << to << endl;
}

void Hanio(int n, char from, char middle, char to)
{
	if (1 == n)
	{
		move(1, from, to);
	}
	else
	{
		Hanio(n - 1, from, to, middle);//将前n-1个盘子从A移动到B(借助C)
		move(n, from,to);//将A上面的最后一个盘子从A挪到C
		Hanio(n - 1, middle,from, to);//将B上面的n-1个盘子挪到C(借助A)
	}
}

void Test1()
{
	Hanio(3, 'A', 'B', 'C');
}


long long Factorial(int n)
{
	if (n == 0)
	{
		return 1;
	}
	else
	{
		return n * Factorial(n - 1);
	}
}


void RecFunc(int arr[], int n)
{
	if (n >= 0)
	{
		cout << arr[n] << endl;
		n--;
		RecFunc(arr, n);
	}
