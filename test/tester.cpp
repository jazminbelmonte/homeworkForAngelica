#define CATCH_CONFIG_MAIN
#include <string>
#include <sstream>
#include "catch.hpp"
#include "collection.h"
#include "linked_list.h"
using namespace std;

TEST_CASE("Test Bubble Sort - Array-based") {
    string msg = "bubblesortarraybased";
    Collection<char> c;
    for(char l : msg){
      c.add(l);
    }
    stringstream aout;
    c.sortByBubble();
    aout << c;
    CHECK(aout.str() == "a a a b b b b d e e l o r r r s s t u y ");
    stringstream bout;
    c.sortByBubble(true);
    bout << c;
    CHECK(bout.str() =="y u t s s r r r o l e e d b b b b a a a ");
}

TEST_CASE("Test Bubble Sort - Linked-list-based") {
    string msg = "bubblesortlinkedlistbased";
    LinkedList<char> c;
    for(char l : msg){
      c.add(l);
    }
    stringstream aout;
    c.sortByBubble();
    aout << c;
    CHECK(aout.str() == "a b b b b d d e e e i i k l l l n o r s s s t t u ");
    stringstream bout;
    c.sortByBubble(true);
    bout << c;
    CHECK(bout.str() =="u t t s s s r o n l l l k i i e e e d d b b b b a ");
}

TEST_CASE("Test Selection Sort - Array-based") {
    string msg = "selectionsortarraybased";
    Collection<char> c;
    for(char l : msg){
      c.add(l);
    }
    stringstream aout;
    c.sortBySelection();
    aout << c;
    CHECK(aout.str() == "a a a b c d e e e i l n o o r r r s s s t t y ");
    stringstream bout;
    c.sortBySelection(true);
    bout << c;
    CHECK(bout.str() =="y t t s s s r r r o o n l i e e e d c b a a a ");
}

TEST_CASE("Test Selection Sort - Linked-list-based") {
    string msg = "selectionsortlinkedlistbased";
    LinkedList<char> c;
    for(char l : msg){
      c.add(l);
    }
    stringstream aout;
    c.sortBySelection();
    aout << c;
    CHECK(aout.str() == "a b c d d e e e e i i i k l l l n n o o r s s s s t t t ");
    stringstream bout;
    c.sortBySelection(true);
    bout << c;
    CHECK(bout.str() == "t t t s s s s r o o n n l l l k i i i e e e e d d c b a ");
}

TEST_CASE("Test Insertion Sort - Array-based") {
    string msg = "insertionsortarraybased";
    Collection<char> c;
    for(char l : msg){
      c.add(l);
    }
    stringstream aout;
    c.sortByInsertion();
    aout << c;
    CHECK(aout.str() == "a a a b d e e i i n n o o r r r r s s s t t y ");
    stringstream bout;
    c.sortByInsertion(true);
    bout << c;
    CHECK(bout.str() =="y t t s s s r r r r o o n n i i e e d b a a a ");
}

TEST_CASE("Test Insertion Sort - Linked-list-based") {
    string msg = "bubblesortlinkedlistbased";
    LinkedList<char> c;
    for(char l : msg){
      c.add(l);
    }
    stringstream aout;
    c.sortByInsertion();
    aout << c;
    CHECK(aout.str() == "a b b b b d d e e e i i k l l l n o r s s s t t u ");
    stringstream bout;
    c.sortByInsertion(true);
    bout << c;
    CHECK(bout.str() =="u t t s s s r o n l l l k i i e e e d d b b b b a ");
}