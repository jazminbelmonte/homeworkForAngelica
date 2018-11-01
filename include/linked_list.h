#ifndef _LINKED_LIST_ADT_H
#define _LINKED_LIST_ADT_H
#include <iostream>

template <typename T>
struct Node {
  T info;
  Node<T>* link;
  Node(T info): info(info), link(nullptr){}
  ~Node() {}
};

template<typename T>
class LinkedListIterator{
public:
  LinkedListIterator(Node<T>* ptr): current(ptr){}
  LinkedListIterator<T>& operator++(){
    current = current->link;
    return *this;
  }
  T operator*(){ return current->info; }
  bool operator==(const LinkedListIterator<T>& rhs) const {
      return current == rhs.current;
  }
  bool operator!=(const LinkedListIterator<T>& rhs) const {
      return current != rhs.current;
  }
private:
  Node<T>* current;
};

template <typename T>
class LinkedListADT {
public:
  virtual void add(T info) = 0;
  virtual void remove(T info) = 0;
  virtual void print() = 0;
  virtual LinkedListIterator<T> begin() = 0;
  virtual LinkedListIterator<T> end() = 0;
  virtual ~LinkedListADT() {}
};

template <typename T>
class LinkedList : LinkedListADT<T>{
public:
  LinkedList(): count(0), first(nullptr), last(nullptr){}
  LinkedList(const LinkedList<T>& list): LinkedList(){
    auto current = list.first;
    while(current){
      add(current->info);
      current = current->link;
    }
  }

  LinkedList<T>& operator=(const LinkedList<T>& list){
    destroy();
    auto current = list.first;
    while(current){
      add(current->info);
      current = current->link;
    }
    return *this;
  }

  void add(T info){
    Node<T>* newNode = new Node<T>(info);
    if(first == nullptr){ // empty list
      first = newNode;
      last = newNode;
    } else {
      last->link = newNode;
      last = newNode;
    }

    count++;
  }

  void remove(T info){
    if(first == nullptr){
      std::cerr << "Empty list; nothing to remove" << std::endl;
    }else if(first->info == info){
      auto current = first;
      first = current->link;
      delete current;
      count--;
    } else {
      auto current = first->link;
      auto beforeCurrent = first;

      while(current){
        if(current->info == info){
          beforeCurrent->link = current->link;
          delete current;
          count--;
          return;
        }
        beforeCurrent = current;
        current = current->link;
      }

      std::cerr << "Not found" << std::endl;
    }
  }
  void print(){
    std::cout << *this;
  }

  friend std::ostream& operator<<(std::ostream& out, const LinkedList<T> ll){
    auto current = ll.first;
    while(current){
      out << current->info << " ";
      current = current->link;
    }

    return out;
  }

  LinkedListIterator<T> begin(){return LinkedListIterator<T>(first);}
  LinkedListIterator<T> end(){return LinkedListIterator<T>(nullptr);}

  //goes over all the elements and swaps if needed,
  //the algorithm will go over all the elements until
  //it goes through without a swap
  void sortByBubble(bool reversed = false){
  auto current1 = first;
    auto current2 = first;
    while (current1 != nullptr) {
      while (current2 != nullptr) {
        if (lessOrGreaterThan(current2, current1, reversed)) {
          swap(current2, current1);
        }
        current2 = current2->link;
      }
      current1 = current1->link;
    }
  }

  //search and swap
  //search for the maximum and the minimum and then swap them
  void sortBySelection(bool reversed = false){
    //TODO
  }

  //start at second position and then compare left and right
  //swap if necessary, then move one position over and compare left and right again
  //if the right is less than the left, and the left before that then you keep swapping
  //in a loop until the right is greater than
  void sortByInsertion(bool reversed = false){
    //TODO
  }

  ~LinkedList() { destroy();}
protected:
  unsigned count;
  Node<T>* first;
  Node<T>* last;

  void destroy(){
    auto current = first;
    while(current){
      auto temp = current;
      current = current->link;
      delete temp;
      temp = nullptr;
    }

    first = nullptr;
    last = nullptr;
    count = 0;
  }

  void swap(Node<T> *a, Node<T> *b){
    T temp = a->info;
    a->info = b->info;
    b->info = temp;
  }

  bool lessOrGreaterThan(Node<T> *a, Node<T> *b, bool reversed = false){
    return (!reversed && a->info < b->info) || (reversed && a->info > b->info);
  }

  T minOrMaxInRange(Node<T> *start, bool reversed = false){
    auto minOrMax = start;
    auto current = start;
    bool found = false;

    while(current != nullptr && !found){
      if(lessOrGreaterThan(current, minOrMax, reversed)){
        minOrMax = current;
        found = true;
      }
      else {
        current = current->link;
      }
    }
    return minOrMax;
  }

};

#endif
