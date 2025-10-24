// Автор: Игонин В.Ю.

#include <cassert>
#include <vector>
#include "TList.h"

/// <summary>
/// Тесты методов двусвязного списка
/// </summary>
void test()
{
	//тест конструктора по умолчанию
	LinkedList<int> lst;
	assert(lst.getSize() == 0);

	//тест вставки в конец
	for (size_t i = 0; i < 3; i++)
	{
		lst.pushBack(i);
		assert(lst.getSize() == i + 1);
		assert(lst[i] == i);
	}

	//тест конструктора копирования
	LinkedList<int> lstc(lst);
	assert(lstc.getSize() == lst.getSize());
	for (size_t i = 0; i < lstc.getSize(); i++)
	{
		assert(lstc[i] == lst[i]);
	}

	//тест оператора копирования
	LinkedList<int> lstoc = lstc;
	assert(lstoc.getSize() == lstc.getSize());
	for (size_t i = 0; i < lstoc.getSize(); i++)
	{
		assert(lstoc[i] == lstc[i]);
	}

	//тест конструктора перемещения
	LinkedList<int> lstm(move(lstc));
	assert(lstc.getSize() == 0);
	assert(lstm.getSize() == 3);
	for (size_t i = 0; i < lstm.getSize(); i++)
	{
		assert(lstm[i] == i);
	}

	//тест оператора перемещения
	LinkedList<int> lstom = move(lstm);
	assert(lstm.getSize() == 0);
	assert(lstom.getSize() == 3);
	for (size_t i = 0; i < lstom.getSize(); i++)
	{
		assert(lstom[i] == i);
	}

	//тест получения узла списка по индексу
	for (size_t i = 0; i < lstom.getSize(); i++)
	{
		assert(lstom.getAt(i)->data == i);
	}

	//тест получения элемента в узле списка по индексу
	for (size_t i = 0; i < lstom.getSize(); i++)
	{
		assert(lstom.At(i) == i);
	}

	//тест вставки в начало
	LinkedList<int> lstfpu;
	for (size_t i = 0; i < 3; i++)
	{
		lstfpu.pushFront(i);
		assert(lstfpu.getSize() == i + 1);
		assert(lstfpu[0] == i);
	}

	//тест вставки по индексу
	lstfpu.insert(3, 6); // вставка в конец
	assert(lstfpu.getSize() == 4);
	assert(lstfpu[3] == 6);

	lstfpu.insert(0, 9); // вставка в начало
	assert(lstfpu.getSize() == 5);
	assert(lstfpu[0] == 9);

	lstfpu.insert(2, 10);
	assert(lstfpu.getSize() == 6);
	assert(lstfpu[2] == 10);

	//тест удаления узла списка из начала
	LinkedList<int> voidlst;
	assert(voidlst.getSize() == 0);
	lstfpu.popFront();
	assert(lstfpu.getSize() == 5);
	assert(lstfpu[0] == 2);
	voidlst.popFront(); // удаление из пустого списка
	assert(voidlst.getSize() == 0);
	voidlst.pushBack(5);
	voidlst.popFront(); // удаление из списка с 1 элементом
	assert(voidlst.getSize() == 0);

	//тест удаления узла списка из конца
	voidlst.popBack(); // удаление из пустого списка
	assert(voidlst.getSize() == 0);
	voidlst.pushBack(5);
	voidlst.popBack(); // удаление из списка с 1 элементом
	assert(voidlst.getSize() == 0);
	lstfpu.popBack();
	assert(lstfpu.getSize() == 4);
	assert(lstfpu[3] == 0);

	//тест удаления узла списка по индексу
	voidlst.erase(0); // удаление из пустого списка
	assert(voidlst.getSize() == 0);
	voidlst.pushBack(5);
	voidlst.erase(0); // удаление из списка с 1 элементом
	assert(voidlst.getSize() == 0);

	lstfpu.erase(0); // удаление из начала
	assert(lstfpu.getSize() == 3);
	assert(lstfpu[0] == 10);
	lstfpu.erase(2); // удаление из конца
	assert(lstfpu.getSize() == 2);
	assert(lstfpu[1] == 1);
	lstfpu.erase(5); // удаление из не существующего индекса (ничего не удалит)
	assert(lstfpu.getSize() == 2);
	assert(lstfpu[0] == 10);
	assert(lstfpu[1] == 1);

	//тест очистки списка
	voidlst.clear(); // очистка пустого списка
	assert(voidlst.getSize() == 0);
	lstfpu.clear(); // очистка списка
	assert(lstfpu.getSize() == 0);
}

void test_inc()
{
	// пустой список
	{
		LinkedList<int> lst;
		auto it = lst.begin();
		auto e = lst.end();
		assert(!(it != e));
		++it;
		assert(!(it != e));
	}

	// один элемент
	{
		LinkedList<int> lst;
		lst.pushBack(5);
		auto it = lst.begin();
		auto e = lst.end();
		assert(*it == 5);
		++it;
		assert(!(it != e));
	}

	// 3 элемента
	{
		LinkedList<int> lst;
		lst.pushBack(5);
		lst.pushBack(4);
		lst.pushBack(3);
		auto it = lst.begin();
		auto e = lst.end();
		vector<int> see;
		for (auto it : lst)
		{
			see.push_back(it);
		}
		assert((see == vector<int>{5, 4, 3}));
	}

	// много элементов
	{
		LinkedList<int> lst;
		for (int i = 0; i < 100; i++)
		{
			lst.pushBack(i);
		}
		size_t count = 0;
		for (auto it = lst.begin(); it != lst.end(); ++it)
		{
			assert(*it == count);
			++count;
		}
		assert(count == 100);
	}

	// много ++ после end
	{
		LinkedList<int> lst;
		lst.pushBack(5);
		lst.pushBack(4);
		auto it = lst.begin();
		auto e = lst.end();
		for (int k = 0; k < 10; k++)
		{
			++it;
		}
		assert(!(it != e));
	}

}

void test_def()
{
	// пустой список
	{
		LinkedList<int> lst;
		try 
		{
			int x = *lst.begin();
			assert(false);
		}
		catch (out_of_range&)
		{

		}
	}

	// 1 элемент значение меняется через итератор
	{
		LinkedList<int> lst;
		lst.pushBack(5);
		auto it = lst.begin();
		assert(*it == 5);
		*it = 100;
		assert(lst[0] == 100);
	}

	// второй элемент можно получить и изменить
	{
		LinkedList<int> lst;
		lst.pushBack(5);
		lst.pushBack(4);
		lst.pushBack(3);
		auto it = lst.begin();
		++it;
		assert(*it == 4);
		*it = 40;
		assert(lst[1] == 40);
	}

	// разыменование end
	{
		LinkedList<int> lst;
		lst.pushBack(5);
		auto e = lst.end();
		try
		{
			int x = *e;
			assert(false);
		}
		catch (out_of_range&)
		{

		}
	}

	// два итератора на один и тот же узел
	{
		LinkedList<int> lst;
		lst.pushBack(1);
		lst.pushBack(2);
		auto it = lst.begin();
		auto it1 = lst.begin();
		assert(*it == *it1);
		*it = 5;
		assert(*it1 == 5);
		assert(lst[0] == 5);
	}

}

void test_comp()
{
	// пустой список
	{
		LinkedList<int> lst;
		assert(!(lst.begin() != lst.end()));
	}

	// один элемент
	{
		LinkedList<int> lst;
		lst.pushBack(1);
		auto a = lst.begin();
		auto b = a;
		assert(!(a != b));
		assert(a != lst.end());
	}

	// итераторы на разные позиции
	{
		LinkedList<int> lst;
		for (int i = 0; i < 4; i++)
		{
			lst.pushBack(i);
		}
		auto it1 = lst.begin();
		++it1;
		auto it2 = lst.begin();
		++it2;
		++it2;
		assert(it1 != it2);
	}

	// итераторы на разные списки
	{
		LinkedList<int> a, b;
		a.pushBack(1);
		b.pushBack(1);
		auto ia = a.begin();
		auto ib = b.begin();
		assert(ia != ib);
	}

	// достижение конца списка
	{
		LinkedList<int> lst;
		lst.pushBack(1);
		auto it = lst.begin();
		++it;
		assert(!(it != lst.end()));
	}

}

void test_iter()
{
	// пустой список
	{
		LinkedList<int> lst;
		vector<int> out;
		for (auto it : lst)
		{
			out.push_back(it);
		}
		assert(out.empty());
	}

	// один элемент
	{
		LinkedList<int> lst;
		lst.pushBack(1);
		vector<int> out;
		for (auto it : lst)
		{
			out.push_back(it);
		}
		assert(out.size() == 1 && out[0] == 1);
	}
	
	// нечетное колво элементов
	{
		LinkedList<int> lst;
		for (int i = 0; i < 3; i++)
		{
			lst.pushBack(i);
		}
		vector<int> out;
		for (auto it : lst)
		{
			out.push_back(it);
		}
		assert(out == vector<int>({0, 1, 2}));
	}

	// четное количество элементов
	{
		LinkedList<int> lst;
		for (int i = 0; i < 6; i++)
		{
			lst.pushBack(i);
		}
		vector<int> out;
		for (auto it = lst.begin(); it != lst.end(); ++it)
		{
			out.push_back(*it);
		}
		assert(out == vector<int>({ 0, 1, 2, 3, 4, 5 }));
	}

	// большой список
	{
		LinkedList<int> lst;
		int N = 100;
		for (int i = 0; i < N; i++)
		{
			lst.pushBack(i*4);
		}
		int cnt = 0;
		int prev = -1;
		for (auto it = lst.begin(); it != lst.end(); ++it)
		{
			++cnt;
			int v = *it;
			assert(v % 4 == 0);
			if (prev != -1)
			{
				assert(v > prev);
			}
			prev = v;
		}
		assert(cnt == N);
	}

}

void test_case()
{
	// несколько ++ подряд на одном итераторе
	{
		LinkedList<int> lst;
		lst.pushBack(0);
		lst.pushBack(1);
		lst.pushBack(2);
		auto it = lst.begin();
		++it;
		++it;
		++it;
		++it;
		++it;
		++it;
		++it;
		++it;
		assert(!(it != lst.end()));
	}

	// использование итератора после удаления других узлов
	{
		LinkedList<int> lst;
		for (int i = 0; i < 5; i++)
		{
			lst.pushBack(i);
		}
		auto it = lst.begin();
		++it;
		lst.popFront();
		assert(*it == 1);
	}

	// копирование итератора и преобразование данных в одном из них
	{
		LinkedList<int> lst;
		for (int i = 0; i < 5; i++)
		{
			lst.pushBack(i);
		}
		auto it = lst.begin();
		auto it2 = it;
		++it;
		assert(*it2 == 0);
		assert(*it == 1);
	}

	// вставка в середину списка
	{
		LinkedList<int> lst;
		lst.pushBack(0);
		lst.pushBack(1);
		auto it = lst.begin();
		++it;
		lst.insert(1, 2);
		assert(*it == 1);
		vector<int> out;
		for (auto ita : lst)
		{
			out.push_back(ita);
		}
		assert(out == vector<int>({ 0, 2, 1 }));
	}

}