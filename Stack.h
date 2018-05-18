#pragma once

template <class T>
class Stack
{
private:
	T* _a;
	size_t _size;
	size_t _capacity;
public:

	Stack()
		:_a(NULL)
		,_size(0)
		,_capacity(0)
	{}
	~Stack()
	{
		if(_a)
		{
			delete[] _a;
			_a = NULL;
		}
	}
	void Push(const T& x)
	{
		Expand();
		_a[_size++] = x;

	}

	void Pop()
	{
		assert(_size>0);
		_size--;
	}

	size_t Size()
	{
		return _size;
	}
	size_t Capacity()
	{
		return _capacity;
	}

	bool Empty()
	{
		if(_size == 0)
			return true;
		else
			return false;
	}

	T& Top()
	{
		assert(_size > 0);
		return _a[_size-1];
	}
	void Expand()
	{
		if(_size == _capacity)
		{
			size_t newcapacity = _capacity==0 ? 3:_capacity*2;
			T* tmp = new T[newcapacity];
			for(size_t i = 0;i < _size;++i)
			{
				tmp[i] = _a[i];
			}
			delete[] _a;
			//swap(_a,tmp);
			_a = tmp;
			 _capacity = newcapacity;
		}
	}
};