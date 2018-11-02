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

  void sortByBubble(bool reversed = false){

    for (int i = 0; i < count; i++) {
      //bubble sorting only swaps values next to each other
      //so we only need the first and the second node
      Node<T> *a = first;
      Node<T> *b = first->link;
      while (b != nullptr) {
        if (lessOrGreaterThan(b, a, reversed)) {
          swap(b, a);
        }
        //move both nodes forward
        a = b;
        b = b->link;
      }
    }
  }

  void sortBySelection(bool reversed = false){
    //for selection we only have to worry about the first
    //and making sure we don't go past last
    Node<T>* a = first;
    Node<T>* b = last;
    while(a != nullptr){
      //swap the first of value of the unsorted section
      //with the minimum
      swap(a, minOrMaxInRange(a, reversed));
      //then that node becomes the first value of the
      //sorted section so we make the first
      //value of the unsorted section the next one
      a = a->link;
    }
  }

  //since we cannot move backward like the insertion
  //in the collection array we will have to move
  //forward
  void sortByInsertion(bool reversed = false){
    //we will treat these two nodes as the current
    //and the iterator to the current
    Node<T>* a = first;
    Node<T>* b = first->link;
    while(a != nullptr){
      swap(a, minOrMaxInRange(a, reversed));
      a = a->link;
    }
  };

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
    //only swap info inside the nodes, not the actual nodes
    T temp = a->info;
    a->info = b->info;
    b->info = temp;
  }

  bool lessOrGreaterThan(Node<T> *a, Node<T> *b, bool reversed = false){
    //only compare info inside the nodes, not the actual nodes
    return (!reversed && a->info < b->info) || (reversed && a->info > b->info);
  }

  //because the loop will automatically stop when it hits
  //the end of the list which is null we don't need to pass
  //in an ending value
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

