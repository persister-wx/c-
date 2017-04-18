1.使用递归逆序打印单链表：

#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>using namespace std;

struct Node
{
    Node(int data)
    :_data(data)
    , _next(NULL)
    {}
    int _data;
    Node* _next;
};

void PrintFromTail2Head(Node* pHead)
{
    if (pHead)
    {
        PrintFromTail2Head(pHead->_next);
        cout << pHead->_data << "  ";
    }
}

void Test1()
{
    Node n1(1);
    Node n2(2);
    Node n3(3);
    n1._next = &n2;
    n2._next = &n3;
    PrintFromTail2Head(&n1);
}

int main()
{
    Test1();
    return 0;
}

2.逆序销毁单链表中的节点：

#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

struct Node
{
    Node(int data)
    :_data(data)
    , _next(NULL)
    {}
    int _data;
    Node* _next;
};


void DestoryFromTail2Head(Node*& pHead)
{
    if (pHead)
    {
        DestoryFromTail2Head(pHead->_next);
        delete pHead;
        pHead = NULL;
    }
}


void Test1()
{
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    n1->_next = n2;
    n2->_next = n3;
    DestoryFromTail2Head(n1);
}

int main()
{
    Test1();
    return 0;
}

3.//在单链表中从后向前查找某个值为data的节点
//在单链表中查找某个值为data的节点
Node* FindData(Node* pHead, int data)
{
    if (pHead)
    {
        Node* res = FindData(pHead->_next, data);//需要记录每次递归结束时的返回值
        if (res)
        {
            return res;
        }
        else
        {
            if (pHead->_data == data)
            {
                return pHead;
            }
        }
    }
    return NULL;
}

void Test1()
{
        Node* n1 = new Node(1);
        Node* n2 = new Node(2);
        Node* n3 = new Node(3);
        n1->_next = n2;
        n2->_next = n3;
        Node* p = FindData(n1, 2);

}

int main()
{
    Test1();
    return 0;
}

4.递归逆序打印数组
不要考虑太多，只需改变数组的个数
void PrintArray(int array[],int size)
{
    if (size)
    {
        size--;
        cout << array[size]<<" ";
        PrintArray(array, size);
    }
}

void Test1()
{
    int array[] = { 9, 2, 8, 4, 3, 7, 5 };
    PrintArray(array, 7);
}

int main()
{
    Test1();
    return 0;
}

5.递归算法进行二分查找
递归算法切记不要忘记递归出口
int BinarySearch(int *array, int left, int right, int data)
{
    if (left > right)//递归出口
    {
        return -1;
    }
    int middle = (left & right) + ((left ^ right) >> 1);
    if (data > array[middle])
    {
        BinarySearch(array, middle + 1, right, data);
    }
    else if (data < array[middle])
    {
        BinarySearch(array, left, middle - 1, data);
    }
    else
    {
        return middle;
    }
}

void Test1()
{
    int array[] = { 0,1,2,3,5,6,7};
    int ret = BinarySearch(array, 0, 6, 10);
    cout << ret << endl;
}
int main()
{
    Test1();
    return 0;
}


int BinaryFind(int *arr, int left, int right, int data)
{

    if (left <= right)
    {
        int mid = (left & right) + ((left ^ right) >> 1);

        if (arr[mid] == data)
        {
            return mid;
        }
        else if (arr[mid] < data)
        {
            return  BinaryFind(arr, mid + 1, right, data);//注意加上return
        }
        else
        {
            return  BinaryFind(arr, left, mid - 1, data);
        }
    }
    return -1;
}

void Test1()
{
    int array[] = { 0,1,2,3,5,6,7};
    int ret = BinaryFind(array, 0, 6, 6);
    cout << ret << endl;
}


6.判断一个字符串是否为回文字符串（例如：1221   121）

#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

bool IsPlalindrome(char * str, int len)
{
    if (len <= 1)
    {
        return true;
    }
    else
    {
        if (str[0] != str[len - 1])
        {
            return false;
        }
        IsPlalindrome(str + 1, len - 2);
    }
}

void Test1()
{
    char* str = "1216";
    cout << IsPlalindrome(str, 4) << endl;
}

int main()
{
    Test1();
    return 0;
}

7.求其时间复杂度和基本执行流程：
void Perm(int* arr, int size, int N)
{
    if (size == N)
    {
        for (size_t idx = 0; idx < size; ++idx)
        {
            cout << arr[idx] << "  ";
        }
        cout << endl;
    }
    else
    {
        for (size_t idx = N; idx < size; ++idx)
        {
            std::swap(arr[idx], arr[N]);
            Perm(arr, size, N + 1);
            std::swap(arr[N], arr[idx]);
        }
    }
}

void Test1()
{
    int arr[] = { 1, 2, 3};
    Perm(arr, 3, 1);
}

int main()
{
    Test1();
    return 0;
}

8.尾递归：
优势：
①重复次数减少了
②栈环境只开辟一个。

将斐波那契数列的递归形式改写为尾递归：

int Fib(int first, int second, int N)
{
    if (N < 3)
    {
        return 1;
    }
    else if (N == 3)
    {
        return first + second;
    }
    return Fib(second, first + second, N - 1);
}

void Test1()
{
    cout << Fib(1, 1, 20) << endl;;
}

int main()
{
    Test1();
    return 0;
}

汇编代码如下：
int Fib(int N, int first, int second)
{
00C93840  push        ebp
00C93841  mov         ebp,esp
00C93843  sub         esp,0C0h
00C93849  push        ebx
00C9384A  push        esi
00C9384B  push        edi
00C9384C  lea         edi,[ebp-0C0h]
00C93852  mov         ecx,30h
00C93857  mov         eax,0CCCCCCCCh
00C9385C  rep stos    dword ptr es:[edi]
    if (N < 3)
00C9385E  cmp         dword ptr [N],3
00C93862  jge         Fib+2Bh (0C9386Bh)
    {
        return 1;
00C93864  mov         eax,1
00C93869  jmp         Fib+53h (0C93893h)
    }
    if (3 == N)
00C9386B  cmp         dword ptr [N],3
00C9386F  jne         Fib+39h (0C93879h)
    {
        return first + second;
00C93871  mov         eax,dword ptr [first]
00C93874  add         eax,dword ptr [second]
00C93877  jmp         Fib+53h (0C93893h)
    }
    return Fib(N - 1, second, first + second);
00C93879  mov         eax,dword ptr [first]
00C9387C  add         eax,dword ptr [second]
00C9387F  push        eax
    }
    return Fib(N - 1, second, first + second);
00C93880  mov         ecx,dword ptr [second]
00C93883  push        ecx
00C93884  mov         edx,dword ptr [N]
00C93887  sub         edx,1
00C9388A  push        edx
00C9388B  call        Fib (0C91307h)
00C93890  add         esp,0Ch
}


在编译器中设置以下步骤后：会发现程序的最后根本就不会call Fib函数，而是执行了一条跳转指令，这时编译器对代码进行了优化，
因为是尾递归，所以就不会在后面每次执行递归时，都会开辟栈帧，而是会将前一个函数栈帧中的数据进行了修改，所以时间复杂度
减小，而空间复杂度也减小了。因为递归的深度减小了。

修改编译器下的如下配置：
①将常规里面的调试信息格式 从用于编辑并继续的程序库 修改为程序数据库。
②将优化里面的禁止优化修改为 最小优化为O1。、
③将代码生成里的 两者...改为 默认值。

经过如上配置后，然后调试代码，就会发现反汇编代码 中函数的调用发生了优化。

int Fib(int N, int first, int second)
{
01362642  push        ebp
01362643  mov         ebp,esp
    if (N < 3)
01362645  mov         ecx,dword ptr [N]
01362648  push        esi
01362649  cmp         ecx,3
0136264C  jl          Fib+24h (01362666h)
0136264E  mov         edx,dword ptr [second]
01362651  mov         esi,dword ptr [first]
    }
    if (3 == N)
    {
        return first + second;
    }
    return Fib(N - 1, second, first + second);
01362654  lea         eax,[esi+edx]
01362657  cmp         ecx,3
0136265A  je          Fib+27h (01362669h)
0136265C  dec         ecx
0136265D  mov         esi,edx
0136265F  mov         edx,eax
01362661  cmp         ecx,3
01362664  jge         Fib+12h (01362654h)
    {
        return 1;
01362666  xor         eax,eax
01362668  inc         eax
01362669  pop         esi
}
0136266A  pop         ebp
0136266B  ret
--- 无源文件 -----------------------------------------------------------------------
0136266C  int         3
0136266D  int         3
0136266E  int         3
0136266F  int         3
01362670  int         3
01362671  int         3
01362672  int         3
01362673  int         3
01362674  int         3
01362675  int         3
--- j:\c\classtest2project1\classtest2project1\classtest2.cpp ------------------
    cout << Fib(10, 1, 1) << endl;
01362676  push        13611BDh
0136267B  push        2
0136267D  push        1
0136267F  push        9
01362681  call        Fib (01361172h)
01362686  mov         ecx,dword ptr ds:[136B05Ch]
0136268C  add         esp,0Ch
0136268F  push        eax
01362690  call        dword ptr ds:[136B050h]
01362696  mov         ecx,eax
01362698  call        dword ptr ds:[136B058h]
}
0136269E  ret
---




