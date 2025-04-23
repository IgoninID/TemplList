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
    list.FrontOut();
    list.RevOut();
    for (Node<int>* ptr = list.getHead(); ptr != NULL; ptr = ptr->next)
        cout << ptr->data << " ";
    cout << endl;
    for (Node<int>* ptr = list.getTail(); ptr != NULL; ptr = ptr->prev)
        cout << ptr->data << " ";
    cout << endl;
}