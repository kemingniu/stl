#pragma once
/************************************************************************/
/* list是一个双向循环链表                                          */
/************************************************************************/
template<class T>
struct __ListNode
{
	__ListNode<T>* _next;
	__ListNode<T>* _prev;
	T _data;

	__ListNode(const T& x)
		:_next(NULL)
		,_prev(NULL)
		,_data(x)
	{}
};


template<typename T,typename Ref,typename Ptr>
struct __ListIterator
{
	typedef __ListNode<T> Node;
	typedef __ListIterator<T,Ref,Ptr> Self;
	Node* _node;


	__ListIterator(Node* node)
		:_node(node)
	{}

	Ref operator*()
	{
		return _node->_data;
	}

	Ptr operator->()
	{
		return &(operator*());
	}

	Self& operator++()
	{
		_node = _node->_next;
		return *this;
	}

	Self operator++(int)
	{
		Self tmp = _node;
		_node = _node->_next;
		return tmp;
	}

	Self& operator--()
	{
		_node = _node->_prev;
		return *this;
	}

	Self operator--(int)
	{
		Self tmp = _node;
		_node = _node->_prev;
		return tmp;
	}

	bool operator==(const Self& l)
	{
		return _node==l._node;
	}

	bool operator!=(const Self& l)
	{
		return _node!=l._node;
	}
};


template<typename T>
class List
{
	typedef __ListNode<T> Node;
public:
	typedef __ListIterator<T,T&,T*> Iterator;
	typedef __ListIterator<T,const T&,const T*> ConstIterator;
protected:
	Node* _head;

public:
	List()
	{
		_head = new Node(T());
		_head->_next = _head;
		_head->_prev = _head;
	}

	Iterator Begin()
	{
		return _head->_next;
	}

	Iterator End()
	{
		return _head;
	}

	ConstIterator Begin() const 
	{
		return _head->_next;
	}

	ConstIterator End() const
	{
		return _head;
	}

	//l(l1)
	List(const List& l)
	{
		_head = new Node(T());
		_head->_next = _head;
		_head->_prev = _head;
		ConstIterator it = l.Begin();
		while(it != l.End())
		{
			PushBack(*it);
			++it;
		}
	}

	~List()
	{
		Clear();
		delete _head;
		_head = NULL;
	}

	void Clear()
	{
		Iterator it = Begin();
		while(it != End())
		{
			Node* del = it._node;
			++it;
			delete del;
		}
		_head->_next = _head;
		_head->_prev = _head;
	}


	void PushBack(const T& x)
	{
		Insert(End(),x);
	}

	void PopFront(const T& x)
	{
		Insert(Begin(),x);
	}

	void PopFront()
	{
		Erase(Begin());
	}

	void PopBack()
	{
		Erase(--End());
	}
	void Insert(Iterator pos,const T& x)
	{
		Node* cur = pos._node;
		Node* prev = cur->_prev;
		Node* tmp = new Node(x);
		prev->_next = tmp;
		tmp->_prev = prev;
		tmp->_next = cur;
		cur->_prev = tmp;
	}

	Iterator Erase(Iterator& pos)
	{
		assert(pos!=End());

		Node* prev = pos._node->_prev;
		Node* next = pos._node->_next;

		prev->_next = next;
		next->_prev = prev;

		delete pos._node;

		pos._node = prev;

		return Iterator(next);

	}
};

void Print_list(const List<int>& l)
{
	List<int>::ConstIterator it = l.Begin();
	while(it != l.End())
	{
		std::cout<<*it<<" ";
		++it;
	}
	std::cout<<std::endl;
}

void test_list()
{
    List<int> l;
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	Print_list(l);

	List<int>::Iterator it = l.Begin();
	while (it != l.End())
	{
		if (*it % 2 == 0)
		{
			it = l.Erase(it);
		}
		else
		{
			++it;
		}
	/*if (*it % 2 == 0)
	{
		l.Erase(it);
	}

	++it;*/
	}

	Print_list(l);
}