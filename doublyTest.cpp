#include "doublyLink.h"
#include <iostream>
#include <string>
using namespace std;

void printList(LinkedList<string> &list)
{
  for(int i = 0; i < list.getSize(); i++)
  {
    cout << list.get(i) << " ";
  }
  cout << endl;
}

int main()
{
  LinkedList<string> list;
  list.addFirst("Sean");
  cout << "(best) ";
  printList(list);

  return 0;
}   
