
//Stack.h
//自定义栈
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<cassert>

//------------使用类型萃取来拷贝栈内元素-------------
struct _TrueType
{
    bool Get()
    {
        return true;
    }
};

struct _FalseType
{
    bool Get()
    {
        return false;
    }
};

template<class _Tp>
struct TypeTraits
{
    typedef _FalseType _IsPODType;
};

template<>
struct TypeTraits<bool>
{
    typedef _TrueType _IsPODType;
};

template<>
struct TypeTraits<int>
{
    typedef _TrueType _IsPODType;
};

template<>
struct TypeTraits<unsigned int>
{
    typedef _TrueType _IsPODType;
};

template<>
struct TypeTraits<char>
{
    typedef _TrueType _IsPODType;
};

template<>
struct TypeTraits< float >
{
    typedef _TrueType _IsPODType;
};

template<>
struct TypeTraits< double >
{
    typedef _TrueType _IsPODType;
};

template<>
struct TypeTraits<long>
{
    typedef _TrueType _IsPODType;
};

template<>
struct TypeTraits< unsigned long>
{
    typedef _TrueType _IsPODType;
};

template<class T>
void Copy(T* dst, T* src, size_t size)
{
    if (TypeTraits<T>::_IsPODType().Get())
    {
        memcpy(dst, src, size);
    }
    else
    {
        for (int i = 0; i < size; ++i)
        {
            dst[i] = src[i];
        }
    }
}

template<class T>
struct TypeTraits< T* >
{
    typedef _TrueType _IsPODype;
};

//-------------------------栈的基本操作----------------
template<class T>
class Stack
{
public:
    //构造函数
    Stack(int capacity = 10)
        :_pData(NULL)
        , _capacity(capacity)
        , _size(0)
    {
        _pData = new T[capacity];
    }

    //拷贝构造函数
    Stack(const Stack<T>& s)
        :_pData(new T[s._capacity])
        , _size(s._size)
        , _capacity(s._capacity)
    {
        for (int i = 0; i < _size; ++i)
        {
            _pData[i] = s._pData[i];
        }
    }

    //赋值运算符函数
    Stack& operator=(Stack<T> s)
    {
        std::swap(_pData, s._pData);
        _size = s._size;
        _capacity = s._capacity;
        return *this;
    }

    //入栈
    void Push(const T& data)
    {
        CheckCapacity();
        _pData[_size++] = data;
    }
    //出栈
    void Pop()
    {
        if (!Empty())
        {
            --_size;
        }
    }

    //获取栈顶元素
    T& Top()
    {
        if (!Empty())
        {
            return _pData[_size - 1];
        }
    }

    const T& Top()const
    {
        if (!Empty())
        {
            return _pData[_size - 1];
        }
    }

    size_t Size()const
    {
        return _size;
    }

    bool Empty()const
    {
        return 0 == _size;
    }

    //析构函数（释放资源）
    ~Stack()
    {
        if (_pData)
        {
            delete[] _pData;
            _pData = NULL;
        }
    }

private:
    //增容
    void CheckCapacity()
    {
        if (_size >= _capacity)
        {
            _capacity = 2 * _capacity + 3;
            T* tmp = new T[_capacity];
            //拷贝原数据
            //释放旧空间
            //指向新空间
            //需要进行类型萃取
            Copy<T>(_pData, tmp, _size);
            delete[] _pData;
            _pData = tmp;
        }
    }

    T* _pData;
    int _capacity;
    int _size;
};


//------------------------------------------------------------------------------------------------
MAZE.CPP


#include"Stack.h"

//定义坐标
struct Seat
{
    Seat()
    {}

    Seat(int x, int y)
    :_x(x)
    , _y(y)
    {}
    int _x;
    int _y;
};

class Maze
{
public:
    Maze(int **arr, int row, int col, FILE* fp)//构造迷宫
        :_row(row)
        , _col(col)
        , _map(arr)
    {
        int ch = 0;
        assert(fp);

        for (size_t i = 0; i < _row; ++i)//从文件中读取迷宫
        {
            for (size_t j = 0; j < _col;)
            {
                char ch = fgetc(fp);
                if (ch == '0' || ch == '1')
                {
                    _map[i][j] = ch - '0';
                    ++j;
                }
            }
        }
    }

    bool PassMaze(Seat& pos)
    {
        //排除从入口出迷宫的条件
        if (pos._x < 0 || pos._x >= _row || pos._y < 0 || pos._y >= _col)
        {
            return false;
        }
        s.Push(pos);//起始位置进栈
        while (!s.Empty())
        {
            Seat& cur = s.Top();
            Seat next = cur;
            //检查是否是迷宫出口
            if (cur._x < 0 || cur._y < 0 || cur._x  >= _row || cur._y >= _col)
            {
                return true;
            }
            _map[cur._x][cur._y] = 2;

            //向上查探
            next._x--;
            if (IsPass(next))
            {
                s.Push(next);
                continue;
            }
            next = cur;
            //向左查探
            next._y--;
            if (IsPass(next))
            {
                s.Push(next);
                continue;
            }
            next = cur;

            //向右查探
            next._y++;
            if (IsPass(next))
            {
                s.Push(next);
                continue;
            }
            next = cur;

            //向后查探
            next._x++;
            if (IsPass(next))
            {
                s.Push(next);
                continue;
            }
            //四个方向都走不出去，说明这条路走错了----用3标记
            _map[cur._x][cur._y] = 3;
            s.Pop();
        }
        return false;
    }

    ////走迷宫
    //bool PassMaze(Seat& pos)
    //{
    //  if (IsPass(pos))
    //  {
    //      s.Push(pos);
    //      _map[pos._x][pos._y] = 2;
    //      while (!s.Empty())
    //      {
    //          //向上查找
    //          Seat top = s.Top();
    //          Seat front(top._x - 1, top._y);
    //          Seat left(top._x, top._y - 1);
    //          Seat right(top._x, top._y + 1);
    //          Seat down(top._x + 1, top._y);
    //          if (IsPass(front) && _map[front._x][front._y] != 2)
    //          {
    //              _map[front._x][front._y] = 2;
    //              s.Push(front);
    //              continue;
    //          }
    //          else
    //          {
    //              if (front._x < 0 || front._x > _row || front._y < 0 || front._y > _col)
    //              {
    //                  return true;
    //              }
    //          }
    //          if (IsPass(left) && _map[left._x][left._y] != 2)
    //          {
    //              _map[left._x][left._y] = 2;
    //              s.Push(left);
    //              continue;
    //          }
    //          else
    //          {
    //              if (front._x < 0 || front._x > _row || front._y < 0 || front._y > _col)
    //              {
    //                  return true;
    //              }
    //          }
    //          if (IsPass(right) && _map[right._x][right._y] != 2)
    //          {
    //              _map[right._x][right._y] = 2;
    //              s.Push(right);
    //              continue;
    //          }
    //          else
    //           {
    //               if (front._x < 0 || front._x > _row || front._y < 0 || front._y > _col)
    //               {
    //                   return true;
    //               }
    //           }
    //          if (IsPass(down) && _map[down._x][down._y] != 2)
    //          {
    //              _map[down._x][down._y] = 2;
    //              s.Push(down);
    //              continue;
    //          }
    //          else
    //          {
    //              if (front._x < 0 || front._x > _row || front._y < 0 || front._y > _col)
    //              {
    //                  return true;
    //              }
    //          }
    //              _map[top._x][top._y] = 3;
    //              s.Pop();
    //      }
    //  }
    //  return false;
    //}

    //判断是否是通路
    bool IsPass(Seat& pos)
    {
        //这个判断语句是为了使得下面的程序不崩溃
        if (pos._x < 0 || pos._x >= _row || pos._y < 0 || pos._y >= _col)
        {
            return true;
        }
        //迷宫中只有1才表示是通路
        if (_map[pos._x][pos._y] == 1)
        {
            return true;
        }

        return false;
    }
    friend ostream& operator<<(ostream& out, Maze& m);
    ~Maze()
    {
        for (int i = 0; i <_row; ++i)
        {
            delete[] _map[i];
        }
        delete[] _map;
    }

private:
    int _row;
    int _col;
    int** _map;
    Stack<Seat> s;
};

ostream& operator<<(ostream& out, Maze& m)
{
    for (int i = 0; i < m._row; ++i)
    {
        for (int j = 0; j < m._col; ++j)
        {
            out << m._map[i][j] << "  ";
        }
        cout << endl;
    }
    return out;
}

void Test()
{
    FILE* fp = fopen("Maze.txt", "r");
    int row = 0;
    int col = 0;
    fscanf(fp, "%d %d", &row, &col);
    int Start_x = 0;
    int Start_y = 0;
    fscanf(fp, "%d %d", &Start_x, &Start_y);

    //动态开辟二维数组
    int **arr = new int*[row];
    for (int i = 0; i < col; ++i)
    {
        arr[i] = new int[col];
    }
    Maze maze(arr, row, col, fp);//初始化迷宫
    cout << maze << endl;
    maze.PassMaze(Seat(Start_x, Start_y));
    cout << maze << endl;
    fclose(fp);
}

int main()
{
    Test();
    return 0;
}

