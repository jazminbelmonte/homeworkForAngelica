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
  //private:
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

  void sortByBubble(bool reversed = false){
    for(LinkedListIterator<T> i = this->begin(); i != this->end(); ++i){
      for(LinkedListIterator<T> j = this->begin(); j != i; ++j){
        if(lessOrGreaterThan(i.current, j.current, reversed)){
          swap(j.current, i.current);
        }
      }
    }
  }

  void sortBySelection(bool reversed = false){
    LinkedListIterator<T> j = this->end();
    for(LinkedListIterator<T> i = this->begin(); i != j; ++i){
      swap(i.current, minOrMaxInRange(i.current, reversed));
    }
  }

  //because there would be too many iterators i decided to do this the normal way
  //by just using pointers to nodes, and having those act like iterators
  void sortByInsertion(bool reversed = false){
    Node<T> *lastInOrder = first;
    Node<T> *firstOutOfOrder;
    Node<T> *current;
    Node<T> *trailCurrent;

    while(lastInOrder->link!= nullptr){
      firstOutOfOrder = lastInOrder->link;
      //I made sure to implement the lessOrGreaterThan function here so that
      //the sort would still work when we needed to sort them in reverse
      if(lessOrGreaterThan(firstOutOfOrder, first, reversed)){
        lastInOrder->link = firstOutOfOrder->link;
        firstOutOfOrder->link = first;
        first = firstOutOfOrder;
      } else {
          trailCurrent = first;
          current = first->link;

          while(lessOrGreaterThan(current, firstOutOfOrder, reversed)){
            trailCurrent = current;
            current = current->link;
          }

          if(current!=firstOutOfOrder){
            lastInOrder->link = firstOutOfOrder->link;
            firstOutOfOrder->link = current;
            trailCurrent->link = firstOutOfOrder;
          } else {
            lastInOrder = lastInOrder->link;
          }
      }//end else
    }//end while
  }//end sort

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

  Node<T>* minOrMaxInRange(Node<T> *start, bool reversed = false){
    auto minOrMax = start;
    auto current = start;

    while(current != nullptr){
      if(lessOrGreaterThan(current, minOrMax, reversed)){
        minOrMax = current;
      }
      else {
        current = current->link;
      }
    }
    return minOrMax;
  }

};

#endif

