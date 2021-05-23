#include "doctest.h"
#include "BinaryTree.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace ariel;
using namespace std;

TEST_CASE("build tree - int"){
   
    BinaryTree<int> Tree_int;
    CHECK_NOTHROW(Tree_int.add_root(0));
    CHECK_NOTHROW(Tree_int.add_left(0,2));
    CHECK_NOTHROW(Tree_int.add_right(0,3));

    CHECK_NOTHROW(Tree_int.add_root(1));
    CHECK_THROWS(Tree_int.add_left(0,2));
    CHECK_THROWS(Tree_int.add_right(0,3));

    CHECK_NOTHROW(Tree_int.add_left(0,4));
    CHECK_NOTHROW(Tree_int.add_right(0,5));

    CHECK_NOTHROW(Tree_int.add_left(4,2));
    CHECK_NOTHROW(Tree_int.add_right(5,3));


    CHECK_NOTHROW(Tree_int.add_root(0));
    CHECK_NOTHROW(Tree_int.add_left(0,2));
    CHECK_NOTHROW(Tree_int.add_right(0,3));

    CHECK_NOTHROW(Tree_int.add_root(1));
    CHECK_THROWS(Tree_int.add_left(0,2));
    CHECK_THROWS(Tree_int.add_right(0,3));

    CHECK_NOTHROW(Tree_int.add_left(0,4));
    CHECK_NOTHROW(Tree_int.add_right(0,5));

    CHECK_NOTHROW(Tree_int.add_left(4,2));
    CHECK_NOTHROW(Tree_int.add_right(5,3));

}

TEST_CASE("print by order"){
    BinaryTree<int> Tree_int;
    for (auto it=Tree_int.begin_preorder(); it!=Tree_int.end_preorder(); ++it) {
    CHECK_NOTHROW(cout << (*it) << " ") ;
  }  // prints: 1 2 4 5 3
  for (auto it=Tree_int.begin_inorder(); it!=Tree_int.end_inorder(); ++it) {
    CHECK_NOTHROW(cout << (*it) << " ") ;
  }  // prints: 4 2 5 1 3 
  for (auto it=Tree_int.begin_postorder(); it!=Tree_int.end_postorder(); ++it) {
    CHECK_NOTHROW(cout << (*it) << " ") ;
  }  // prints: 4 5 2 3 1

  for (int element: Tree_int) {  // this should work like inorder
    CHECK_NOTHROW(cout << element << " " );
  }  // prints: 4 2 5 1 3 

    
}

TEST_CASE("test <<"){
    BinaryTree<int> Tree_int;
    CHECK_NOTHROW(cout<<Tree_int);
}