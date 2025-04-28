#include <cassert>
#include "TList.h"

/// <summary>
/// ����� ������� ����������� ������
/// </summary>
void test()
{
	//���� ������������ �� ���������
	LinkedList<int> lst;
	assert(lst.getSize() == 0);

	//���� ������� � �����
	for (size_t i = 0; i < 3; i++)
	{
		lst.pushBack(i);
		assert(lst.getSize() == i + 1);
		assert(lst[i] == i);
	}

	//���� ������������ �����������
	LinkedList<int> lstc(lst);
	assert(lstc.getSize() == lst.getSize());
	for (size_t i = 0; i < lstc.getSize(); i++)
	{
		assert(lstc[i] == lst[i]);
	}

	//���� ��������� �����������
	LinkedList<int> lstoc = lstc;
	assert(lstoc.getSize() == lstc.getSize());
	for (size_t i = 0; i < lstoc.getSize(); i++)
	{
		assert(lstoc[i] == lstc[i]);
	}

	//���� ������������ �����������
	LinkedList<int> lstm(move(lstc));
	assert(lstc.getSize() == 0);
	assert(lstm.getSize() == 3);
	for (size_t i = 0; i < lstm.getSize(); i++)
	{
		assert(lstm[i] == i);
	}

	//���� ��������� �����������
	LinkedList<int> lstom = move(lstm);
	assert(lstm.getSize() == 0);
	assert(lstom.getSize() == 3);
	for (size_t i = 0; i < lstom.getSize(); i++)
	{
		assert(lstom[i] == i);
	}

	//���� ��������� ���� ������ �� �������
	for (size_t i = 0; i < lstom.getSize(); i++)
	{
		assert(lstom.getAt(i)->data == i);
	}

	//���� ��������� �������� � ���� ������ �� �������
	for (size_t i = 0; i < lstom.getSize(); i++)
	{
		assert(lstom.At(i) == i);
	}

	//���� ������� � ������
	LinkedList<int> lstfpu;
	for (size_t i = 0; i < 3; i++)
	{
		lstfpu.pushFront(i);
		assert(lstfpu.getSize() == i + 1);
		assert(lstfpu[0] == i);
	}

	//���� ������� �� �������
	lstfpu.insert(3, 6); // ������� � �����
	assert(lstfpu.getSize() == 4);
	assert(lstfpu[3] == 6);

	lstfpu.insert(0, 9); // ������� � ������
	assert(lstfpu.getSize() == 5);
	assert(lstfpu[0] == 9);

	lstfpu.insert(2, 10);
	assert(lstfpu.getSize() == 6);
	assert(lstfpu[2] == 10);

	//���� �������� ���� ������ �� ������
	LinkedList<int> voidlst;
	assert(voidlst.getSize() == 0);
	lstfpu.popFront();
	assert(lstfpu.getSize() == 5);
	assert(lstfpu[0] == 2);
	voidlst.popFront(); // �������� �� ������� ������
	assert(voidlst.getSize() == 0);
	voidlst.pushBack(5);
	voidlst.popFront(); // �������� �� ������ � 1 ���������
	assert(voidlst.getSize() == 0);

	//���� �������� ���� ������ �� �����
	voidlst.popBack(); // �������� �� ������� ������
	assert(voidlst.getSize() == 0);
	voidlst.pushBack(5);
	voidlst.popBack(); // �������� �� ������ � 1 ���������
	assert(voidlst.getSize() == 0);
	lstfpu.popBack();
	assert(lstfpu.getSize() == 4);
	assert(lstfpu[3] == 0);

	//���� �������� ���� ������ �� �������
	voidlst.erase(0); // �������� �� ������� ������
	assert(voidlst.getSize() == 0);
	voidlst.pushBack(5);
	voidlst.erase(0); // �������� �� ������ � 1 ���������
	assert(voidlst.getSize() == 0);

	lstfpu.erase(0); // �������� �� ������
	assert(lstfpu.getSize() == 3);
	assert(lstfpu[0] == 10);
	lstfpu.erase(2); // �������� �� �����
	assert(lstfpu.getSize() == 2);
	assert(lstfpu[1] == 1);
	lstfpu.erase(5); // �������� �� �� ������������� ������� (������ �� ������)
	assert(lstfpu.getSize() == 2);
	assert(lstfpu[0] == 10);
	assert(lstfpu[1] == 1);

	//���� ������� ������
	voidlst.clear(); // ������� ������� ������
	assert(voidlst.getSize() == 0);
	lstfpu.clear(); // ������� ������
	assert(lstfpu.getSize() == 0);
}