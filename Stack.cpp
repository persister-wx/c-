#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<cassert>
struct Seat//设置坐标
{
    Seat(int x, int y)
    :_x(x)
    , _y(y)
    {}
    int _x;
    int _y;
};
//定义要查找的四个方向
//Seat move1[4] = { { -1, 0 }, { 0, 1 }, { 0, -1 }, { 1, 0 }, };
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
        fclose(fp);
    }
    bool PassMaze(Seat s)
    {
        if (s._x < 0 || s._y < 0 || s._x >= _row || s._y >= _col)
        {
            return true;
        }
        if (IsPass(s) && (_map[s._x][s._y] != 2))
        {
            _map[s._x][s._y] = 2;
            //向前查找
            Seat Front(s._x - 1, s._y);
           //向左查找
            Seat  Left(s._x, s._y - 1);
            //向右查找
            Seat  Right(s._x, s._y + 1);
            Seat Down(s._x + 1, s._y);
            //向前查找 
            if ( PassMaze(Front))
            {
                return true;
            }//向左查找
            else if (PassMaze(Left))
            {
                return true;
            }//向右查找
            else if (PassMaze(Right))
            {
                return true;
            }//向后查找
            else if (PassMaze(Down))
            {
                return true;
            }
            else
            {
                //路径错误，做标记
                _map[s._x][s._y] = 3;
            }
        }
        return false;
    }
    //bool PassMaze(Seat s)  //参数为入口                                    
    //{
    //  if (s._x < 0 || s._y < 0 || s._x >= MAX_ROW || s._y >= MAX_COL)
    //  {
    //      return true;
    //  }
    //  _map[s._x][s._y] = 2;
    //  int tmp_x = 0;
    //  int tmp_y = 0;
    //  for (int i = 0; i < 4; ++i)//探查四个方向
    //  {
    //      tmp_x = s._x + move1[i]._x;
    //      tmp_y = s._y + move1[i]._y;
    //      if (_map[tmp_x][tmp_y] && _map[tmp_x][tmp_y] != 2)
    //      {
    //
    //          if (PassMaze(Seat(tmp_x, tmp_y)))
    //          {
    //              cout << "(" << tmp_x << "," << tmp_y << ")"<<" ";
    //              return true;
    //          }
    //      }
    //  }
    //  
    //}
    bool IsPass(const Seat& s)//判断位置是否合法
    {
        if (s._x >= 0 && s._x < _row && s._y >= 0 && s._y < _col\
            && _map[s._x][s._y] )//判断是否越界
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
    int** _map;
    int _row;
    int _col;
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
    
    Maze maze(arr, row, col,fp);//初始化迷宫
    cout << maze << endl;
    cout << maze.PassMaze(Seat(Start_x, Start_y)) << endl;
    cout << maze << endl;
    fclose(fp);
}
int main()
{
    Test();
    return 0;
}
