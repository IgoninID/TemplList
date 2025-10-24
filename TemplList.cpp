// Автор: Игонин В.Ю.

#include "TList.h"

using namespace std;

int main()
{
    test();
    test_inc();
    test_def();
    test_comp();
    test_iter();
    test_case();
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
    for (auto t : list)
    {
        cout << t << " ";
    }
    cout << endl;
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        cout << *it << " ";
    }
}