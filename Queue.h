#pragma once
/*
queue是一种先进先出的数据结构，只能在队尾入数据，对头出数据
*/
template<class T>
struct QueueNode
{
	T _data;
	QueueNode<T>* _next;

	QueueNode(const T& x)
		:_data(x)
		,_next(NULL)
	{}
};

template<class T>
class Queue
{
private:
	typedef QueueNode<T> node;
	node* _head;
	node* _tail;
public:
	Queue()
		:_head(NULL)
		,_tail(NULL)
	{}
	~Queue()
	{
		while(!Empty())
		{
			Pop();
		}
	}

	void Push(const T& x)
	{
		if(_head == NULL)
		{
			_head = _tail = new node(x);
		}
		else 
		{
			_tail->_next = new node(x);
			_tail = _tail->_next;
		}
	}

	T& Front()
	{
		assert(_head);
		return _head->_data;
	}

	T& Back()
	{
		assert(_head);
		return _tail->_data;
	}

	void Pop()
	{
		assert(_head);
		if(_head == NULL)
			return;
		else if(_head == _tail)
		{
			delete _head;
			_head = _tail = NULL;
		}
		else 
		{
			node* tmp = _head;
			_head = _head->_next;
			delete tmp;
		}
	}

	size_t Size()
	{
		node* cur = _head;
		size_t count = 0;
		while(cur)
		{
			count++;
			cur = cur->_next;
		}
		return count;
	}

	bool Empty()
	{
		if(_head == NULL)
			return true;
		else 
		return false;
	}


	
};