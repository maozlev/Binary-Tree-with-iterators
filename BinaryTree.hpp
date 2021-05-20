#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#pragma once


namespace ariel{
    template<class T>
    class BinaryTree{
        
         private:

            struct Node {
                T data;
                Node *left = nullptr;
                Node *right = nullptr;
                Node(T x): data(x), left(nullptr), right(nullptr){}
            };
            Node *root = nullptr;

        public:

            BinaryTree<T>(){
                this->root = nullptr;
            }
            BinaryTree<T> add_root(const T& data){
               
                return *this;
            }
            BinaryTree<T> add_left(const T& data_left, const T& data_right){
                return *this;
            }
            
            BinaryTree<T> add_right(const T& data_left, const T& data_right){
                return *this;
            }


        class preorder_iterator{
            
            private:
                Node* p;

            public:
                preorder_iterator(Node* ptr = nullptr):p(ptr){}

                T& operator*() const{
                    return p->data;
                }

                T* operator->() const{
                    return &(p->data);
                }

                preorder_iterator& operator++(int){
                    // preorder_iterator tmp = *this;
                    return *this;
                }

                preorder_iterator& operator++(){
                    return *this;
                }

                bool operator ==(const preorder_iterator& rhs) const{
                    return p == rhs.p;
                }

                bool operator !=(const preorder_iterator& rhs) const{
                    return p != rhs.p;
                }  

        };
            
            preorder_iterator begin_preorder(){
                return preorder_iterator{root};  
            }
            preorder_iterator end_preorder(){
                return preorder_iterator{nullptr};
            }
            preorder_iterator begin_inorder(){
                return preorder_iterator{root};  
            }
            preorder_iterator end_inorder(){
                return preorder_iterator{nullptr};
            }
            preorder_iterator begin_postorder(){
                return preorder_iterator{root};  
            }
            preorder_iterator end_postorder(){
                return preorder_iterator{nullptr};
            }
            preorder_iterator begin(){
                return preorder_iterator{root};  
            }
            preorder_iterator end(){
                return preorder_iterator{nullptr};
            }

        friend std::ostream& operator<< (std::ostream& os, const BinaryTree& a){
            os<<"beutifull life";
            return os;
        }

    };
};