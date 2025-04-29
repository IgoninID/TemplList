// Автор: Игонин В.Ю.

#include "TList.h"

using namespace std;

int main()
{
    test();
    LinkedList<int> list;
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    list.pushBack(4);
    list.insert(3, 6);
    list.FrontOut();
    list.RevOut();
    LinkedList<int> list2 = list;
    list2.FrontOut();
    list.FrontOut();
    cout << endl;
}