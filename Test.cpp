#include "BinaryTree.hpp"
#include "doctest.h"
#include <algorithm>
#include <iostream>
#include <stack>
using namespace ariel;
using namespace std;


    TEST_CASE("tree of int"){
        BinaryTree<int> tree_of_ints;
        stack<int> check_preOrder;
        stack<int> check_inOrder;
        stack<int> check_postOrder;

        CHECK_NOTHROW
        (tree_of_ints.add_root(1)
        .add_left(1,2)
        .add_left(2,4)
        .add_right(1,3)
        .add_right(2,5)
        .add_left(3,6)
        .add_right(3,7));

        /* tree:
                    1
                  2   3
                 4 5 6 7
        */
        
        check_preOrder.push(7);
        check_preOrder.push(6);
        check_preOrder.push(3);
        check_preOrder.push(5);
        check_preOrder.push(4);
        check_preOrder.push(2);
        check_preOrder.push(1); 
        
        for (auto it=tree_of_ints.begin_preorder(); it!=tree_of_ints.end_preorder(); ++it) {
            if(!check_preOrder.empty()){
                CHECK_EQ(*(it) , check_preOrder.top());
                check_preOrder.pop();
                // cout<<*(it)<<endl;
            }
              
        }

        check_inOrder.push(7);
        check_inOrder.push(3);
        check_inOrder.push(6);
        check_inOrder.push(1);
        check_inOrder.push(5);
        check_inOrder.push(2);
        check_inOrder.push(4); 

        for (auto it=tree_of_ints.begin_inorder(); it!=tree_of_ints.end_inorder(); ++it) {
            if(!check_inOrder.empty()){
                CHECK_EQ(*(it) , check_inOrder.top());
                check_inOrder.pop();
            }
              
        } 

        check_postOrder.push(1);
        check_postOrder.push(3);
        check_postOrder.push(7);
        check_postOrder.push(6);
        check_postOrder.push(2);
        check_postOrder.push(5);
        check_postOrder.push(4); 

        for (auto it=tree_of_ints.begin_postorder(); it!=tree_of_ints.end_postorder(); ++it) {
            if(!check_postOrder.empty()){
                CHECK_EQ(*(it) , check_postOrder.top());
                check_postOrder.pop();
            }
              
        }
 

        check_inOrder.push(7);
        check_inOrder.push(3);
        check_inOrder.push(6);
        check_inOrder.push(1);
        check_inOrder.push(5);
        check_inOrder.push(2);
        check_inOrder.push(4); 

        for (auto it=tree_of_ints.begin(); it!=tree_of_ints.end(); ++it) {
            if(!check_inOrder.empty()){
                CHECK_EQ(*(it) , check_inOrder.top());
                check_inOrder.pop();
            }
              
        } 


        // check overide 

        tree_of_ints.add_root(22);

        CHECK_EQ(*(tree_of_ints.begin_preorder()) , 22);

        tree_of_ints.add_right(22,11);
        tree_of_ints.add_left(22,12);

        check_preOrder.push(7);
        check_preOrder.push(6);
        check_preOrder.push(11);
        check_preOrder.push(5);
        check_preOrder.push(4);
        check_preOrder.push(12);
        check_preOrder.push(22); 
        
        for (auto it=tree_of_ints.begin_preorder(); it!=tree_of_ints.end_preorder(); ++it) {
            if(!check_preOrder.empty()){
                CHECK_EQ(*(it) , check_preOrder.top());
                check_preOrder.pop();
            }
              
        }

        // check exeption

        BinaryTree<int> tree;
        CHECK_THROWS(tree.add_left(1,2));
        CHECK_THROWS(tree.add_right(1,2));

        CHECK_NOTHROW
        (tree.add_root(1)
        .add_left(1,2)
        .add_left(2,4)
        .add_right(1,3)
        .add_right(2,5)
        .add_left(3,6)
        .add_right(3,7));

        CHECK_THROWS(tree.add_left(8,1));
        CHECK_THROWS(tree.add_left(11,1));

        SUBCASE("operator ="){

            BinaryTree<int>t;

            CHECK_NOTHROW(t = tree);
            CHECK(t.begin() != t.end());
            CHECK(t.begin() != tree.begin());

            CHECK_NOTHROW
            (t.add_root(1)
            .add_left(1,2)
            .add_left(2,4)
            .add_right(1,3)
            .add_right(2,5)
            .add_left(3,6)
            .add_right(3,7));

            // address not the same

            CHECK(t.begin() != tree.begin());
            
            // value is same

            CHECK(*(t.begin()) == *(tree.begin()));

        }
    }

    TEST_CASE("checking iterators"){
        BinaryTree<char> tree;
        //  tree is empty, iterators same 

        CHECK((tree.begin() == tree.end()));
        CHECK((tree.begin_inorder() == tree.end_inorder()));
        CHECK((tree.begin_postorder() == tree.end_postorder()));
        CHECK((tree.begin_preorder() == tree.end_preorder()));

        CHECK_NOTHROW(tree.add_root('a'));

        //  After adding root

        CHECK((tree.begin() != tree.end()));
        CHECK((tree.begin_inorder() != tree.end_inorder()));
        CHECK((tree.begin_postorder() != tree.end_postorder()));
        CHECK((tree.begin_preorder() != tree.end_preorder()));

        auto it = tree.begin();
        auto it_in = tree.begin_inorder();
        auto it_post = tree.begin_postorder();
        auto it_pre = tree.begin_preorder();

        //  post fix iterators not same

        CHECK((it++ != tree.end()));
        CHECK((it_in++ != tree.end_inorder()));
        CHECK((it_post++ != tree.end_postorder()));
        CHECK((it_pre++ != tree.end_preorder()));

        CHECK((it == tree.end()));
        CHECK((it_in == tree.end_inorder()));
        CHECK((it_post == tree.end_postorder()));
        CHECK((it_pre == tree.end_preorder()));

        it = tree.begin();
        it_in = tree.begin_inorder();
        it_post = tree.begin_postorder();
        it_pre = tree.begin_preorder();

        //  pre fix should be the same

        CHECK((++it == tree.end_inorder()));
        CHECK((++it_in == tree.end_inorder()));
        CHECK((++it_post == tree.end_postorder()));
        CHECK((++it_pre == tree.end_preorder()));
    }

    TEST_CASE("string tree"){

        // It always seems impossible until its done 

        BinaryTree<string>tree_string;
       
        CHECK_NOTHROW
        (tree_string.add_root("It")
        .add_left("It", "always")
        .add_left("always", "seems")
        .add_right("always", "impossible")
        .add_right("It", "until")
        .add_right("until", "done")
        .add_left("until", "its"));

        CHECK_NOTHROW(cout<<tree_string<<endl);
        
        cout<<endl;
        for (auto it=tree_string.begin_postorder(); it!=tree_string.end_postorder(); ++it) {
                cout<<*(it)<<" ";   
        }
        cout<<endl;
        cout<<endl;

        for (auto it=tree_string.begin(); it!=tree_string.end(); ++it) {
                cout<<*(it)<<" ";    
        }
        cout<<endl;
        cout<<endl;

        for (auto it=tree_string.begin_preorder(); it!=tree_string.end_preorder(); ++it) {
            cout<<*(it)<<" ";   
        }
        cout<<endl;
    }
    