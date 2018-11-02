#include <iostream>
#include <chrono>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "linked_list.h"
#include "collection.h"

//used example from class to create this printing format

using namespace std;
using namespace chrono;

enum class SortAlgorithm{
  BUBBLE, SELECTION, INSERTION
};

template <typename T>
struct SortRunningTime {
  SortAlgorithm algorithm;
  duration<double, nano> sorted;
  duration<double, nano> random;
  duration<double, nano> reversed;


  void sort(Collection<T>& c, bool reversed = false){
    switch(algorithm){
      case SortAlgorithm::BUBBLE:
        c.sortByBubble(reversed);
        break;
      case SortAlgorithm::SELECTION:
        c.sortBySelection(reversed);
        break;
      case SortAlgorithm::INSERTION:
        c.sortByInsertion(reversed);
        break;
    }
  }

  string label(){
    switch(algorithm){
      case SortAlgorithm::BUBBLE: return "Bubble";
      case SortAlgorithm::SELECTION: return "Selection";
      case SortAlgorithm::INSERTION: return "Insertion";
    }
  }
};

enum class LSortAlgorithm{
  BUBBLE, SELECTION, INSERTION
};

template <typename T>
struct LSortRunningTime {
  LSortAlgorithm lalgorithm;
  duration<double, nano> sorted;
  duration<double, nano> random;
  duration<double, nano> reversed;


  void sort(LinkedList<T>& l, bool reversed = false){
    switch(lalgorithm){
      case LSortAlgorithm::BUBBLE:
        l.sortByBubble(reversed);
        break;
      case LSortAlgorithm::SELECTION:
        l.sortBySelection(reversed);
        break;
      case LSortAlgorithm::INSERTION:
        l.sortByInsertion(reversed);
        break;
    }
  }

  string label(){
    switch(lalgorithm){
      case LSortAlgorithm::BUBBLE: return "Bubble";
      case LSortAlgorithm::SELECTION: return "Selection";
      case LSortAlgorithm::INSERTION: return "Insertion";
    }
  }
};

int main(){
  srand(time(nullptr));
  const int MAX_COLLECTION_SIZE = 100;

  Collection<char> original;
  for(int i = 0; i < MAX_COLLECTION_SIZE; i++){
    int r = rand() % 26;
    char c = 'a' + r;
    original.add(c);
  }

  LinkedList<char> originalL;
  for(int i = 0; i < MAX_COLLECTION_SIZE; i++){
    int r = rand() % 26;
    char c = 'a' + r;
    originalL.add(c);
  }

  SortRunningTime<char> runningTimes[] = {
    {SortAlgorithm::BUBBLE},
    {SortAlgorithm::SELECTION},
    {SortAlgorithm::INSERTION}
  };

  LSortRunningTime<char> LrunningTimes[] = {
    {LSortAlgorithm::BUBBLE},
    {LSortAlgorithm::SELECTION},
    {LSortAlgorithm::INSERTION}
  };

  for(auto& rt : runningTimes){
    Collection<char> a(original);
    rt.sort(a);
    auto start = high_resolution_clock::now();
    rt.sort(a);
    auto end = high_resolution_clock::now();
    rt.sorted = end - start;

    Collection<char> b(original);
    start = high_resolution_clock::now();
    rt.sort(b);
    end = high_resolution_clock::now();
    rt.random = end - start;

    Collection<char> c(original);
    rt.sort(c, true);
    start = high_resolution_clock::now();
    rt.sort(c);
    end = high_resolution_clock::now();
    rt.reversed = end - start;
  }

  for(auto& lrt : LrunningTimes){
    LinkedList<char> d(originalL);
    lrt.sort(d);
    auto start = high_resolution_clock::now();
    lrt.sort(d);
    auto end = high_resolution_clock::now();
    lrt.sorted = end - start;

    LinkedList<char> e(originalL);
    start = high_resolution_clock::now();
    lrt.sort(e);
    end = high_resolution_clock::now();
    lrt.random = end - start;

    LinkedList<char> f(originalL);
    lrt.sort(f, true);
    start = high_resolution_clock::now();
    lrt.sort(f);
    end = high_resolution_clock::now();
    lrt.reversed = end - start;
  }

  cout << endl
       << setw(40) << "1 - Array-based Report" << endl
       << setfill('=') << setw(60) << "=" << endl
       << setfill(' ')
       << setw(30) << "Sorted"
       << setw(15) << "Random"
       << setw(15) << "Reversed" << endl;

  for(auto& rt : runningTimes){
    cout << fixed << setprecision(3) << setw(15) << rt.label()
         << setw(15) << rt.sorted.count()
         << setw(15) << rt.random.count()
         << setw(15) << rt.reversed.count() << endl;
  }

  cout << endl
       << setw(43) << "2 - Linked-list-based Report" << endl
       << setfill('=') << setw(60) << "=" << endl
       << setfill(' ')
       << setw(30) << "Sorted"
       << setw(15) << "Random"
       << setw(15) << "Reversed" << endl;

  for(auto& lrt : LrunningTimes){
    cout << fixed << setprecision(3) << setw(15) << lrt.label()
         << setw(15) << lrt.sorted.count()
         << setw(15) << lrt.random.count()
         << setw(15) << lrt.reversed.count() << endl;
  }

  return 0;
}