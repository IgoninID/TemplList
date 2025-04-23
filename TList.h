#pragma once
#include <iostream>

using namespace std;

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
		this->prev = this->next = NULL;
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
		this->head = this->tail = NULL;
	}

	Node<T>* getHead() const
	{
		return head;
	}

	Node<T>* getTail() const
	{
		return tail;
	}
	Node<T>* pushFront(T data)
	{
		Node<T>* res = new Node<T>(data);
		res->next = head;
		if (head != NULL)
		{
			head->prev = res;
		}
		if (tail == NULL)
		{
			tail = res;
		}
		head = res;
		return res;
	}
	Node<T>* pushBack(T data)
	{
		Node<T>* res = new Node<T>(data);
		res->prev = tail;
		if (tail != NULL)
		{
			tail->next = res;
		}
		if (head == NULL)
		{
			head = res;
		}
		tail = res;
		return res;
	}
	void popFront()
	{
		if (head == NULL)
		{
			return;
		}
		Node<T>* res = head->next;
		if (res != NULL)
		{
			res->prev = NULL;
		}
		else
		{
			tail = NULL;
		}
		delete head;
		head = res;
	}
	void popBack()
	{
		if (tail == NULL)
		{
			return;
		}
		Node<T> res = tail->prev;
		if (res != NULL)
		{
			res->next = NULL;
		}
		else
		{
			head = NULL;
		}
		delete tail;
		tail = res;
	}
	Node<T>* getAt(size_t i)
	{
		Node* res = head;
		size_t n = 0;
		while (n != i)
		{
			if (res == NULL)
			{
				return res;
			}
			res = res->next;
			n++;
		}
		return res;
	}
	Node<T>* operator[] (size_t i)
	{
		return getAt(i);
	}
	Node<T>* insert(size_t i, T data)
	{
		Node<T> right = getAt(i);
		if (right == NULL)
		{
			return pushBack(data);
		}
		Node<T>* left = right->prev;
		if (left == NULL)
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
		if (res == NULL)
		{
			return;
		}
		if (res->prev == NULL)
		{
			popFront();
			return;
		}
		if (res->next == NULL)
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
		while (head != NULL)
		{
			popFront();
		}
	}
	void FrontOut() const
	{
		for (Node<T>* ptr = head; ptr != NULL; ptr = ptr->next)
		{
			cout << ptr->data << " ";
		}
		cout << endl;
	}
	void RevOut() const
	{
		for (Node<T>* ptr = tail; ptr != NULL; ptr = ptr->prev)
		{
			cout << ptr->data << " ";
		}
		cout << endl;
	}
};

void test();