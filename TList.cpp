#include <cassert>
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