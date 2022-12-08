#include "doctest.h"
#include "BinaryTree.hpp"
using namespace ariel;

TEST_CASE("test 1"){
    BinaryTree<int> tree;
    CHECK_NOTHROW(tree.add_root(3));
    CHECK_NOTHROW(tree.add_left(3,4));
    CHECK_NOTHROW(tree.add_left(4,5));
    CHECK_NOTHROW(tree.add_right(3,2));
    CHECK_NOTHROW(tree.add_right(2,1));
    CHECK_NOTHROW(tree.add_root(3));

    CHECK_NOTHROW(tree.add_right(1,3));
    CHECK_NOTHROW(tree.add_right(3,567));
}
TEST_CASE("test 2"){
    BinaryTree<int> tree;
    CHECK_NOTHROW(tree.add_root(10));
    CHECK_NOTHROW(tree.add_right(10,-3));
  
    CHECK_THROWS(tree.add_right(11,3));
    CHECK_NOTHROW(tree.add_left(11,-3));
}
TEST_CASE("test 3"){
    BinaryTree<int> tree;

    CHECK_THROWS(tree.add_left(4,6)); // dont have root
    CHECK_NOTHROW(tree.add_right(1,2));
    CHECK_NOTHROW(tree.add_root(1)); // add root

    CHECK_NOTHROW(tree.add_right(1,2));
    CHECK_NOTHROW(tree.add_left(1,3));
    CHECK_NOTHROW(tree.add_right(2,6));
    CHECK_NOTHROW(tree.add_right(3,4));
    CHECK_NOTHROW(tree.add_left(3,5));
    CHECK_NOTHROW(tree.add_right(6,22));
    CHECK_NOTHROW(tree.add_left(5,14));
    CHECK_NOTHROW(tree.add_right(6,88));
    CHECK_NOTHROW(tree.add_right(4,11));
    CHECK_NOTHROW(tree.add_left(4,33));
    
    //replace root
    for(int i=0; i<50; i++){
    CHECK_NOTHROW(tree.add_root(i));
    }
}

