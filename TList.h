// Автор: Игонин В.Ю.

#pragma once
#include <iostream>
#include <stdexcept>
#include "../InterfIter/AbstrIter.h"

using namespace std;

/// <summary>
/// Шаблонный класс узел двусвязного списка
/// </summary>
/// <typeparam name="T - тип элементов списка"></typeparam>
template <typename T>
class Node
{
public: 
	T data; // элемент списка
	Node* prev; // предыдущий узел
	Node* next; // следующий узел
public:
	/// <summary>
	/// Конструктор узла списка
	/// </summary>
	/// <param name="data - элемент списка"></param>
	Node(T data)
	{
		this->data = data;
		this->prev = this->next = NULL;
	}
};

/// <summary>
/// Шаблонный класс двусвязный список
/// </summary>
/// <typeparam name="T - тип элементов списка"></typeparam>
template <typename T>
class LinkedList
{
private:
	Node<T>* head; // первый узел списка
	Node<T>* tail; // последний узел списка
	size_t Size; // размер списка
public:

	/// <summary>
	/// Итератор для двухсвязного списка
	/// </summary>
	class Iterator : public AbstrIter<T>
	{
		Node<T>* curr; // указатель на текущий узел, на который указывает итератор
	public:

		/// <summary>
		/// Конструктор итератора
		/// </summary>
		/// <param name="node">Указатель на узел с которого начинается итерация</param>
		Iterator(Node<T>* node = nullptr) : curr(node) {}

		/// <summary>
		/// Оператор префиксного инкремента
		/// </summary>
		/// <returns>Ссылка на итератор</returns>
		Iterator& operator++() override
		{
			if (curr)
			{
				curr = curr->next;
			}
			return *this;
		}

		/// <summary>
		/// Оператор разыименования
		/// </summary>
		/// <exception cref = "out_of_range Выбрасывается, итератор указывает на несущ элемент или конец списка"></exception>
		/// <returns>Ссылка на данные текущего узла списка</returns>
		T& operator *() const override
		{
			if (!curr)
			{
				throw out_of_range("Элемент не существует");
			}
			return curr->data;
		}

		/// <summary>
		/// Оператор сравнения на неравенство
		/// </summary>
		/// <param name="other">Другой итератор</param>
		/// <returns>1 - указывают на разные узлы, 0 - указывают на один и тот же узел</returns>
		bool operator !=(const AbstrIter<T>& other) const override
		{
			const Iterator* it = dynamic_cast<const Iterator*>(&other);
			return !it || this->curr != it->curr;
		}
	};

	/// <summary>
	/// Вызов конструктора итератора с начальным элементом списка
	/// </summary>
	/// <returns>Итератор указывающий на первый элемент списка</returns>
	Iterator begin() const
	{
		return Iterator(head);
	}

	/// <summary>
	/// Вызов конструктора итератора с nullptr
	/// </summary>
	/// <returns>Итератор указывающий на элемент после последнего</returns>
	Iterator end() const
	{
		return Iterator(nullptr);
	}

	/// <summary>
	/// Коструктор по умолчанию (пустой список с 0 размером)
	/// </summary>
	LinkedList()
	{
		this->head = this->tail = NULL;
		Size = 0;
	}

	/// <summary>
	/// Конструктор копирования
	/// </summary>
	/// <param name="lst - копируемый список"></param>
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
	/// Конструктор перемещения
	/// </summary>
	/// <param name="lst - перемещаемый список"></param>
	LinkedList(LinkedList<T>&& lst) noexcept : head(lst.head), tail(lst.tail), Size(lst.Size)
	{
		lst.head = nullptr;
		lst.tail = nullptr;
		lst.Size = 0;
	}

	/// <summary>
	/// Оператор присваивания копированием
	/// </summary>
	/// <param name="lst - копируемый список"></param>
	/// <returns>
	/// Ссылка на список
	/// </returns>
	LinkedList<T>& operator =(const LinkedList<T>& lst)
	{
		if (this != &lst)
			return LinkedList<T>(lst);
		return *this;
	}

	/// <summary>
	/// Оператор присваивания перемещением
	/// </summary>
	/// <param name="lst - перемещаемый список"></param>
	/// <returns>
	/// Ссылка на список
	/// </returns>
	LinkedList<T>& operator =(LinkedList<T>&& lst)
	{
		if (this != &lst)
			return LinkedList<T>(lst);
		return *this;
	}

	/// <summary>
	/// Получение размера списка
	/// </summary>
	/// <returns>
	/// Размер списка
	/// </returns>
	size_t getSize() const
	{
		return Size;
	}

	/// <summary>
	/// Вставка элемента в начало списка
	/// </summary>
	/// <param name="data - элемент"></param>
	/// <returns>
	/// Указатель на узел с элементом в списке
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
	/// Вставка в конец списка
	/// </summary>
	/// <param name="data - элемент"></param>
	/// <returns>
	/// Указатель на узел с элементом в списке
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
	/// Удаление элемента из начала списка
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
	/// Удаление элемента из конца списка
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
	/// Получение узла списка
	/// </summary>
	/// <param name="i - индекс узла списка"></param>
	/// <returns>
	/// Узел списка
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
	/// Получение элемента в узле списка
	/// </summary>
	/// <param name="i - индекс узла списка"></param>
	/// <returns>
	/// Элемент узла списка
	/// </returns>
	T& At(size_t i)
	{
		Node<T>* res = getAt(i);
		if (res == NULL)
			throw out_of_range("За пределами списка");
		return res->data;
	}

	/// <summary>
	/// Перегрузка оператора [] (получение элемента узла списка)
	/// </summary>
	/// <param name="i - индекс элемента узла списка"></param>
	/// <returns>
	/// Элемент узла списка
	/// </returns>
	T& operator[] (size_t i)
	{
		return At(i);
	}

	/// <summary>
	/// Вставка элемента по индексу
	/// </summary>
	/// <param name="i - индекс узла списка"></param>
	/// <param name="data - элемент"></param>
	/// <returns>
	/// Указатель на узел с элементом в списке
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
	/// Удаление узла списка по индексу
	/// </summary>
	/// <param name="i - индекс узла списка"></param>
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
	/// Очистка списка
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
	/// Деструктор списка
	/// </summary>
	~LinkedList()
	{
		while (head != NULL)
		{
			popFront();
		}
	}

	/// <summary>
	/// Вывод списка с начала
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
	/// Вывод списка с конца
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
/// Тесты методов двусвязного списка
/// </summary>
void test();