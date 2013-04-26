#ifndef DOUBLYLINK_H
#define DOUBLYLINK_H
#include <stdexcept>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

template<typename T>
class Node
{
public:
  T element;  // Element contained in the node
  Node<T> *next; // Pointer to the next node
  Node<T> *previous;// Pointer to the previous node

  Node() // No-arg constructor
  {
    next = NULL;
    previous = NULL;
  }

  Node(T element) // Constructor
  {
    this->element = element;
    next = NULL;
    previous = NULL;
  }
};

template<typename T>
class Iterator : public std::iterator<std::forward_iterator_tag, T>
{
 public:
   Iterator(Node<T> *p)
   {
     current = p;
   }
   Iterator operator++(int dummy)
   {
     current = current->next;
     return *this;
   }
   T &operator*()
   {
     return current->element;
   }
   bool operator==(const Iterator<T> &iterator)
   {
     return current == iterator.current;
   }
   bool operator!=(const Iterator<T> &iterator)
   {
     return current != iterator.current;
   }

   private:
     Node<T> *current;
};

template<typename T>
class LinkedList
{
public:
  LinkedList();
  T getFirst();
  T getLast();
  T removeFirst() throw (runtime_error); 
  T removeLast(); 
  void add(T element); // add elements in alphabetical order
  void clear();
  bool contains(T element); 
  bool isEmpty();
  int getSize();
  T removeAt(int index);
  T remove(T element); 
  void printAsc(); // print in ascending order
  void printDes(); // print in descending order
  void addFile(const string& filename); // allows strings from files to be added to list

  Iterator<T> begin()
  {
    return Iterator<T>(head);
  }
  Iterator<T> end()
  {
    return Iterator<T>(tail->next);
  }

private:
  Node<T> *head, *tail;
  int size;
};
 
string toUpperCase(string s)
{
  for (int i = 0; i < s.length(); i++)
    s[i] = toupper(s[i]);

  return s;
}


template<typename T>
LinkedList<T>::LinkedList()
{
  head = tail = NULL;
  size = 0;
}

template<typename T>
void LinkedList<T>::printAsc()
{
  Node<T> *current = head;
  while(current != NULL)
  {
    cout << current->element << " ";
    current = current->next;
  }
}

template<typename T>
void LinkedList<T>::printDes()
{
  Node<T> *current = tail;
  while(current != NULL)
  {
    cout << current->element << " ";
    current = current->previous;
  }
} 

template<typename T>
void LinkedList<T>::addFile(const string& filename)
{
  ifstream input(filename.c_str());
  if(input.fail())
  {
    cout << filename << " does not exist." << endl;
    return;  // exits method
  }

  string data;
  while(!input.eof())
  {
    getline(input, data, '#'); // Data delimited by hashtag symbol 
    add(data);
  }
}

template<typename T>
T LinkedList<T>::remove(T element) 
{
  Node<T> *current = head;
  if(current->element == element)
    return removeFirst();
  else if(tail->element == element)
    return removeLast();
  else
  {
    while(current != NULL)
    {
      if (current->element == element)
      {
        Node<T> *left = current->previous;
        left->next = current->next;
        Node<T> *right = current->next;
        right->previous = current->previous;

        size--;
        delete current;
        //i = size;
        return element;
      }
      else current = current->next;
    }
  } 
}

template<typename T>
bool LinkedList<T>::contains(T element) 
{
  Node<T> *stuff = head;
  while(stuff != NULL)
  {
    if(stuff->element == element)
    {
      return true;
    }
    else
    {
      stuff = stuff->next;
    }
  }
  return false;
}

template<typename T>
T LinkedList<T>::getFirst()
{
  if (size == 0)
    throw runtime_error("Index out of range");
  else
    return head->element;
}

template<typename T>
T LinkedList<T>::getLast()
{
  if (size == 0)
    throw runtime_error("Index out of range");
  else
    return tail->element;
}

template<typename T>
T LinkedList<T>::removeFirst() throw (runtime_error)
{
  if (size == 0)
   throw runtime_error("No elements in the list");
  else
  {
    Node<T> *temp = head;
    head = head->next;
    head->previous = NULL;// new part
    size--;
    T element = temp->element;
    delete temp;
    return element;
  }
}

template<typename T>
T LinkedList<T>::removeLast()
{
  if (size == 0)
    throw runtime_error("No elements in the list");
  else if (size == 1)
  {
    Node<T> *temp = head;
    head = tail = NULL;
    size = 0;
    T element = temp->element;
    delete temp;
    return element;
  }
  else
  {
    Node<T> *current = head;
    head->previous = NULL; // new part

    for (int i = 0; i < size - 2; i++)
      current = current->next;

    Node<T> *temp = tail;
    tail = current;
    tail->next = NULL;
    size--;
    T element = temp->element;
    delete temp;
    return element;
  }
}

template<typename T>
void LinkedList<T>::add(T element)
{
  Node<T> *current = head;
  if(head == NULL)
    head = tail = new Node<T>(element);
  else if(toUpperCase(tail->element) < toUpperCase(element))
  {
    Node<T> *newNode = new Node<T>(element);
    tail->next = newNode;
    newNode->previous = tail;
    tail = newNode;
  }
  else 
  {
    while(toUpperCase(current->element) < toUpperCase(element))
      current = current->next;
    Node<T> *temp = current->previous;
    Node<T> *newNode = new Node<T>(element);
    current->previous = newNode;
    newNode->next = current;
    newNode->previous = temp;
    temp->next = newNode;
  }
  size++;
}

template<typename T>
void LinkedList<T>::clear()
{
  while (head != NULL)
  {
    Node<T> *temp = head;
    delete temp;
    head = head->next;
  }

  tail = NULL;
}

template<typename T>
bool LinkedList<T>::isEmpty()
{
  return head == NULL;
}

template<typename T>
int LinkedList<T>::getSize()
{
  return size;
}

#endif



