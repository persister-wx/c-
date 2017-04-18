#include"Slist.h"

void Slist::PushBack(DataType data)
{
	if (NULL == _pHead)
	{
		_pHead = _tail = new Node(data);
	}
	else
	{
		_tail->_next = new Node(data);
		_tail = _tail->_next;
	}
}

void Slist::Print()
{
	Node* cur = _pHead;
	while (cur)
	{
		cout << cur->_value << "  ";
		cur = cur->_next;
	}
	cout << endl;
}

//从尾到头打印单链表
void Slist:: PrintListFromTail2Head(Node* Head)
{
	if (Head->_next)
	{
		PrintListFromTail2Head(Head->_next);
	}
	cout << Head->_value << endl;
}


void Slist::Destory()
{
	Node* cur = _pHead;
	Node* del = cur;
	while (cur)
	{
		del = cur->_next;
		delete cur;
		cur = del;
	}
}

// 删除无头单链表的非尾结点
void DeleteNotTailNode(Node* pos)
{
	assert(pos != NULL);
	Node* del = pos->_next;
	pos->_value = del->_value;
	pos->_next = del->_next;
	delete del;
}

//查找链表中的某个节点
Node* Slist::Find(DataType data)
{
	Node* cur = _pHead;
	while (cur && cur->_value != data)
	{
		cur = cur->_next;
	}
	if (cur)
	{
		return cur;
	}
	return NULL;
}

//用单链表实现约瑟夫环
Node* JosephCircle(Slist& l1,size_t M)
{
	assert(l1._pHead != NULL);
	Node* cur = l1._pHead;
	while (cur->_next != cur)
	{
		size_t K = M;
		while (--K)//向后执行k-1次到达第M位
		{
			cur = cur->_next;
		}
		Node* del = cur->_next;
		cur->_value = del->_value;
		cur->_next = del->_next;
		delete del;
	}
	return cur;
}

// 逆置单链表--三个指针
//Node* Slist::ReverseList()
//{
//	if (NULL == _pHead || NULL == _pHead->_next)//链表为空或者只有一个节点时
//	{
//		return _pHead;
//	}
//	Node* prev = _pHead;//初始化三个指针（指向前三个节点）
//	Node* cur = prev->_next;
//	Node* pNext = cur->_next;
//	while (pNext)//条件就是可以使得循环体内恰好崩溃的取反条件
//	{
//		cur->_next = prev;//将节点向前连接，并让三个指针同时后移
//		prev = cur;
//		cur = pNext;
//		pNext = pNext->_next;
//	}
//	cur->_next = prev;//应注意：最后一个节点和第一个节点没有处理
//	_pHead->_next = NULL;
//	_pHead = cur;
//}

//链表逆置使用头摘节点并进行头插节点
Node* Slist::ReverseList()
{
	if (NULL == _pHead || NULL == _pHead->_next)//同样，链表为空或者说只有一个节点
	{
		return _pHead;
	}
	Node* newNode = NULL;
	Node* cur = _pHead;//定义两个指针指向前两个节点
	Node* pNext = cur->_next;
	while (pNext)//头摘节点然后头插在新链表中
	{
		cur->_next = newNode;
		newNode = cur;
		cur = pNext;
		pNext = pNext->_next;
	}
	cur->_next = newNode;//还剩最后一个节点没有处理
	_pHead = cur;
	return _pHead;
}

//测试pushback
void Test1()
{
	Slist l;
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.PushBack(5);
	l.PushBack(6);
	l.PushBack(7);

	l.Print();
	l.PrintListFromTail2Head(l._pHead);
}

void TestDeleteNode()
{
	Slist l;
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	Node* pos = l.Find(2);
	l.Print();
	DeleteNotTailNode(pos);
	l.Print();
	pos = l.Find(1);
	DeleteNotTailNode(pos);
	l.Print();
}

void TestCircle()
{
	Slist l;
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.PushBack(5);
	l.PushBack(6);
	l.PushBack(7);
	Node* tail = l.Find(7);
	tail->_next = l._pHead;
	cout << JosephCircle(l, 2)->_value <<endl;
}

//测试链表逆置
void TestListReverse()
{
	Slist l;
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.PushBack(5);
	l.Print();
	l.ReverseList();
	l.Print();
}

   
int main()
{
	//Test1();
	//TestDeleteNode();
	//TestCircle();
	TestListReverse();
	return 0;
}


