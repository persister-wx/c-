#include<iostream>
using namespace std;
#include<string>
#include<cassert>
typedef int DataType;


struct Node
{
	Node(int value)
	:_value(value)
	, _next(NULL)
	{}
	int _value;
	Node* _next;
};

class Slist
{
public :
	Slist()
		:_pHead(NULL)
	{}
	void PushBack(DataType data);
	void Print();
	void Destory();
	void  PrintListFromTail2Head(Node* Head);
	Node* Find(DataType data);
	Node* JosephCircle(size_t M);
	Node* ReverseList();
	~Slist()
	{
		Destory();
	}

	Node* _pHead;
	Node* _tail;
};

