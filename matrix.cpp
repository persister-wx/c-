#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<cassert>

template<class T>
class  Matrix
{
public :
	Matrix(T* array, int N)//N代表方阵的行或列,将二维数组看作是一维数组
		:_pData(NULL)
	{
		int index = 0;
		_pData = new T[N * (N + 1) >> 1];//给下三角矩阵开辟空间
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j <= i; ++j)
			{
				_pData[index] = array[i * N + j];
				index++;
			}
		}
	}

	//访问矩阵中的元素
	T& Access(int row, int col)
	{
		if (row < col)
		{
			std::swap(row, col);
		}
		return _pData[row*(row + 1)>>1 + col];
	}

	~Matrix()
	{
		if (_pData != NULL)
		{
			delete[] _pData;
			_pData = NULL;
		}
	}
private:
	T* _pData;
};

void Test()
{
	int a[5][5] = {
		{ 0, 1, 2, 3, 4 },
		{ 1, 0, 1, 2, 3 },
		{ 2, 1, 0, 1, 2 },
		{ 3, 2, 1, 0, 1 },
		{ 4, 3, 2, 1, 0 } };

	Matrix<int> m((int*)a,5);
	cout << m.Access(0,4);
}

int main()
{
	Test();
	return 0;
}
