// �����: ������ �.�.

#pragma once
#include <iostream>
#include <stdexcept>
#include "../InterfIter/AbstrIter.h"

using namespace std;

/// <summary>
/// ��������� ����� ���� ����������� ������
/// </summary>
/// <typeparam name="T - ��� ��������� ������"></typeparam>
template <typename T>
class Node
{
public: 
	T data; // ������� ������
	Node* prev; // ���������� ����
	Node* next; // ��������� ����
public:
	/// <summary>
	/// ����������� ���� ������
	/// </summary>
	/// <param name="data - ������� ������"></param>
	Node(T data)
	{
		this->data = data;
		this->prev = this->next = NULL;
	}
};

/// <summary>
/// ��������� ����� ���������� ������
/// </summary>
/// <typeparam name="T - ��� ��������� ������"></typeparam>
template <typename T>
class LinkedList
{
private:
	Node<T>* head; // ������ ���� ������
	Node<T>* tail; // ��������� ���� ������
	size_t Size; // ������ ������
public:

	/// <summary>
	/// �������� ��� ������������ ������
	/// </summary>
	class Iterator : public AbstrIter<T>
	{
		Node<T>* curr; // ��������� �� ������� ����, �� ������� ��������� ��������
	public:

		/// <summary>
		/// ����������� ���������
		/// </summary>
		/// <param name="node">��������� �� ���� � �������� ���������� ��������</param>
		Iterator(Node<T>* node = nullptr) : curr(node) {}

		/// <summary>
		/// �������� ����������� ����������
		/// </summary>
		/// <returns>������ �� ��������</returns>
		Iterator& operator++() override
		{
			if (curr)
			{
				curr = curr->next;
			}
			return *this;
		}

		/// <summary>
		/// �������� ��������������
		/// </summary>
		/// <exception cref = "out_of_range �������������, �������� ��������� �� ����� ������� ��� ����� ������"></exception>
		/// <returns>������ �� ������ �������� ���� ������</returns>
		T& operator *() const override
		{
			if (!curr)
			{
				throw out_of_range("������� �� ����������");
			}
			return curr->data;
		}

		/// <summary>
		/// �������� ��������� �� �����������
		/// </summary>
		/// <param name="other">������ ��������</param>
		/// <returns>1 - ��������� �� ������ ����, 0 - ��������� �� ���� � ��� �� ����</returns>
		bool operator !=(const AbstrIter<T>& other) const override
		{
			const Iterator* it = dynamic_cast<const Iterator*>(&other);
			return !it || this->curr != it->curr;
		}
	};

	/// <summary>
	/// ����� ������������ ��������� � ��������� ��������� ������
	/// </summary>
	/// <returns>�������� ����������� �� ������ ������� ������</returns>
	Iterator begin() const
	{
		return Iterator(head);
	}

	/// <summary>
	/// ����� ������������ ��������� � nullptr
	/// </summary>
	/// <returns>�������� ����������� �� ������� ����� ����������</returns>
	Iterator end() const
	{
		return Iterator(nullptr);
	}

	/// <summary>
	/// ���������� �� ��������� (������ ������ � 0 ��������)
	/// </summary>
	LinkedList()
	{
		this->head = this->tail = NULL;
		Size = 0;
	}

	/// <summary>
	/// ����������� �����������
	/// </summary>
	/// <param name="lst - ���������� ������"></param>
	LinkedList(const LinkedList<T>& lst)
	{
		Node<T>* curr = lst.head;
		while (curr)
		{
			pushBack(curr->data);
			curr = curr->next;
		}
		Size = lst.getSize();
	}

	/// <summary>
	/// ����������� �����������
	/// </summary>
	/// <param name="lst - ������������ ������"></param>
	LinkedList(LinkedList<T>&& lst) noexcept : head(lst.head), tail(lst.tail), Size(lst.Size)
	{
		lst.head = nullptr;
		lst.tail = nullptr;
		lst.Size = 0;
	}

	/// <summary>
	/// �������� ������������ ������������
	/// </summary>
	/// <param name="lst - ���������� ������"></param>
	/// <returns>
	/// ������ �� ������
	/// </returns>
	LinkedList<T>& operator =(const LinkedList<T>& lst)
	{
		if (this != &lst)
			return LinkedList<T>(lst);
		return *this;
	}

	/// <summary>
	/// �������� ������������ ������������
	/// </summary>
	/// <param name="lst - ������������ ������"></param>
	/// <returns>
	/// ������ �� ������
	/// </returns>
	LinkedList<T>& operator =(LinkedList<T>&& lst)
	{
		if (this != &lst)
			return LinkedList<T>(lst);
		return *this;
	}

	/// <summary>
	/// ��������� ������� ������
	/// </summary>
	/// <returns>
	/// ������ ������
	/// </returns>
	size_t getSize() const
	{
		return Size;
	}

	/// <summary>
	/// ������� �������� � ������ ������
	/// </summary>
	/// <param name="data - �������"></param>
	/// <returns>
	/// ��������� �� ���� � ��������� � ������
	/// </returns>
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
		Size++;
		return res;
	}

	/// <summary>
	/// ������� � ����� ������
	/// </summary>
	/// <param name="data - �������"></param>
	/// <returns>
	/// ��������� �� ���� � ��������� � ������
	/// <returns>
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
		Size++;
		return res;
	}

	/// <summary>
	/// �������� �������� �� ������ ������
	/// </summary>
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
		Size--;
	}

	/// <summary>
	/// �������� �������� �� ����� ������
	/// </summary>
	void popBack()
	{
		if (tail == NULL)
		{
			return;
		}
		Node<T>* res = tail->prev;
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
		Size--;
	}

	/// <summary>
	/// ��������� ���� ������
	/// </summary>
	/// <param name="i - ������ ���� ������"></param>
	/// <returns>
	/// ���� ������
	/// </returns>
	Node<T>* getAt(size_t i)
	{
		Node<T>* res = head;
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

	/// <summary>
	/// ��������� �������� � ���� ������
	/// </summary>
	/// <param name="i - ������ ���� ������"></param>
	/// <returns>
	/// ������� ���� ������
	/// </returns>
	T& At(size_t i)
	{
		Node<T>* res = getAt(i);
		if (res == NULL)
			throw out_of_range("�� ��������� ������");
		return res->data;
	}

	/// <summary>
	/// ���������� ��������� [] (��������� �������� ���� ������)
	/// </summary>
	/// <param name="i - ������ �������� ���� ������"></param>
	/// <returns>
	/// ������� ���� ������
	/// </returns>
	T& operator[] (size_t i)
	{
		return At(i);
	}

	/// <summary>
	/// ������� �������� �� �������
	/// </summary>
	/// <param name="i - ������ ���� ������"></param>
	/// <param name="data - �������"></param>
	/// <returns>
	/// ��������� �� ���� � ��������� � ������
	/// </returns>
	Node<T>* insert(size_t i, T data)
	{
		Node<T>* right = getAt(i);
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
		Size++;
		return res;
	}

	/// <summary>
	/// �������� ���� ������ �� �������
	/// </summary>
	/// <param name="i - ������ ���� ������"></param>
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
		Size--;
		delete res;
	}

	/// <summary>
	/// ������� ������
	/// </summary>
	void clear()
	{
		Node<T>* curr = head;
		while (curr)
		{
			Node<T>* next = curr->next;
			delete curr;
			curr = next;
		}
		head = tail = NULL;
		Size = 0;
	}

	/// <summary>
	/// ���������� ������
	/// </summary>
	~LinkedList()
	{
		while (head != NULL)
		{
			popFront();
		}
	}

	/// <summary>
	/// ����� ������ � ������
	/// </summary>
	void FrontOut() const
	{
		for (Node<T>* ptr = head; ptr != NULL; ptr = ptr->next)
		{
			cout << ptr->data << " ";
		}
		cout << endl;
	}

	/// <summary>
	/// ����� ������ � �����
	/// </summary>
	void RevOut() const
	{
		for (Node<T>* ptr = tail; ptr != NULL; ptr = ptr->prev)
		{
			cout << ptr->data << " ";
		}
		cout << endl;
	}
};

/// <summary>
/// ����� ������� ����������� ������
/// </summary>
void test();