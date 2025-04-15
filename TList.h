#pragma once

template <typename T>
class Node
{
public: 
	T data;
	Node* prev;
	Node* next;
public:
	Node(T data)
	{
		this->data = data;
		this->prev = this->next = null;
	}
};

template <typename T>
class LinkedList
{
private:
	Node<T>* head;
	Node<T>* tail;
public:
	LinkedList()
	{
		this->head = this->tail = null;
	}
	Node* pushFront(T data)
	{
		Node<T>* res = new Node<T>(data);
		res->next = head;
		if (head != null)
		{
			head->prev = res;
		}
		if (tail == null)
		{
			tail = res;
		}
		head = res;
		return res;
	}
	Node* pushBack(T data)
	{
		Node<T> res = new Node<T>(data);
		res->prev = tail;
		if (tail != null)
		{
			tail->next = res;
		}
		if (head == null)
		{
			head = res;
		}
		tail = res;
		return res;
	}
	void popFront()
	{
		if (head == null)
		{
			return;
		}
		Node<T>* res = head->next;
		if (res != null)
		{
			res->prev = null;
		}
		else
		{
			tail = null;
		}
		delete head;
		head = res;
	}
	void popBack()
	{
		if (tail == null)
		{
			return;
		}
		Node<T> res = tail->prev;
		if (res != null)
		{
			res->next = null;
		}
		else
		{
			head = null;
		}
		delete tail;
		tail = res;
	}
	Node* getAt(size_t i)
	{
		Node* res = head;
		size_t n = 0;
		while (n != i)
		{
			if (res == null)
			{
				return res;
			}
			res = res->next;
			n++
		}
		return res;
	}
	Node* operator[] (size_t i)
	{
		return getAt(i);
	}
	Node* insert(size_t i, T data)
	{
		Node<T> right = getAt(i);
		if (right == null)
		{
			return pushBack(data);
		}
		Node<T>* left = right->prev;
		if (left == null)
		{
			return pushFront(data);
		}
		Node<T>* res = new Node<T>(data);
		res->prev = left;
		res->next = right;
		left->next = res;
		right->prev = res;
		return res;
	}
	void erase(size_t i)
	{
		Node<T>* res = getAt(i);
		if (res == null)
		{
			return;
		}
		if (res->prev == null)
		{
			popFront();
			return;
		}
		if (res->next == null)
		{
			popBack();
			return;
		}
		Node<T>* left = res->prev;
		Node<T>* right = res->next;
		left->next = right;
		right->prev = left;
		delete res;
	}
	~LinkedList()
	{
		while (head != null)
		{
			popFront();
		}
	}
};