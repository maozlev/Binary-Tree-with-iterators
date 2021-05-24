#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <stack>
#include <string>
#include <deque>          
#include <list>           
#include <queue>


namespace ariel{

    template<class T>
    class BinaryTree{
    
        struct Node {
        T data;
        bool is_printed_in = false;
        bool is_printed_post = false;
        Node *left = nullptr;
        Node *right = nullptr;
        Node(T info): data(info), left(nullptr), right(nullptr), is_printed_in(false),
        is_printed_post(false) {}
        };
        Node *root=nullptr;

        

        public:
            BinaryTree<T>(){}
            BinaryTree<T> add_root(const T& data){
                if(root==nullptr){
                    root = new Node(data);   
                }
                else{
                    root->data=data;
                }
                return *this;
            }

            BinaryTree<T> add(const T& daddy,const T& son, bool left_flag){
                std::stack<Node*> s;
                   Node *p = root;
                   while (p != nullptr || !s.empty()){   
                       while (p !=  NULL){
                           s.push(p);
                           p = p->right;
                       }
                       p = s.top();
                       s.pop();
                       if(p->data == daddy){
                           if(left_flag){
                                if(p->left == nullptr){
                                    p->left = new Node(son);
                                }else{
                                    p->left->data = son;
                                }
                           }else{
                               if(p->right == nullptr){
                                    p->right = new Node(son);
                                }
                                else{
                                    p->right->data = son;
                                }
                           }
                            return *this;
                       }
                       p = p->left;
                   }
                throw std::invalid_argument{"daddy is not exist"};
            }
                   

            BinaryTree<T> add_left(const T& daddy,const T& son){
                if(root == nullptr){
                    throw std::string{"no root existing"};
                }
                add(daddy, son, true);
                return *this;
            }
                
            BinaryTree<T> add_right(const T& daddy,const T& son){
                if(root == nullptr){
                    throw std::string{"no root existing"};
                }
                add(daddy, son, false);
                return *this;
            }

        class iterator{

            private:
                int Order;
                std::stack<Node*> s;
                std::queue<Node*> q;
                Node* p;

            public:

                void clean_nodes(Node* t){
                    if(t != nullptr){
                        t->is_printed_in = false;
                        t->is_printed_post = false;
                        if(t->left != nullptr){
                            clean_nodes(t->left);
                        }
                        if(t->right != nullptr){
                            clean_nodes(t->right);
                        }
                    }
                    return;      
                }
                T& operator*() const {
                    return p->data;
                }

                T* operator->() const {
                    return &(p->data);
                }

                iterator(int order, Node* ptr=nullptr):p(ptr) {
                    Order = order;
                    if(p!=nullptr){
                        clean_nodes(p);
                        if(order == 0){ //preorder
                            if(p->right!=nullptr){
                                s.push(p->right);
                            }
                            if(p->left!=nullptr){
                                s.push(p->left);
                            }
                        }
                        else if(order == 1){    //inorder
                            while(p != nullptr){
                                s.push(p);
                                p = p->left;
                            }
                            p = s.top();
                            p->is_printed_in = true;
                            s.pop();
                        }                            
                        
                        else if(order == 2){    //postorder
                            while(p != nullptr){
                                s.push(p);
                                p = p->left;
                            }
                            p = s.top();
                            p->is_printed_post = true;
                            s.pop();
                        }    
                    }
                }

                // pre fix ++i;
                iterator& operator++() {
                    if(s.empty()){
                        p = nullptr;
                        return *this;
                    }
                    
                    if(Order == 0){ // pre order
                        p = s.top();
                        s.pop();
                        if(p->right != nullptr){
                            s.push(p->right);
                        }
                        if(p->left != nullptr){
                            s.push(p->left);
                        }
                        return *this;
                    }

                    else if(Order == 1){ // in order
                        p = s.top();
                        s.pop();
                            if(p->right != nullptr){
                                if(!p->right->is_printed_in){
                                    Node* tmp = p->right;
                                    s.push(p->right);
                                    p->right->is_printed_in = true;
                                    while(tmp->left != nullptr){
                                        tmp = tmp->left;
                                        s.push(tmp);
                                        tmp->is_printed_in = true;
                                    }
                                }
                            }
                            if(p->left != nullptr){
                                if(!p->left->is_printed_in){
                                    s.push(p->left);
                                    p->left->is_printed_in = true;
                                }
                            }
                        p->is_printed_in = true;
                        return *this;
                    }
                    else if(Order == 2){ // post order
                        p = s.top();
                        if(p->is_printed_post){
                            s.pop();
                        }
                        p = s.top();
                        s.pop();
                        Node* tmp = p;
                        if(p->right != nullptr && !p->right->is_printed_post){
                            if(!p->is_printed_post){
                                s.push(p);
                                p->is_printed_post = true;
                            } 
                            s.push(p->right);
                            p->right->is_printed_post = true;
                            tmp = p->right;
                        }
                        if(p->left != nullptr && !p->left->is_printed_post){
                            if(!p->is_printed_post){
                                s.push(p);
                                p->is_printed_post = true;
                            }
                            s.push(p->left);
                            p->left->is_printed_post = true;
                            tmp = p->left;
                        }
                        p = tmp;
                        return *this;
                    }
                    return *this;
                }
                    
                // post fix i++;
                const iterator operator++(int) {
                    iterator tmp = *this;
                        if(s.empty()){
                            p = nullptr;
                            return tmp;
                        }
                        p = s.top();
                        s.pop();
                        if(p->right != nullptr){
                            s.push(p->right);
                        }
                        if(p->left != nullptr){
                            s.push(p->left);
                        }
                    return tmp;
                }

                bool operator==(const iterator& other) const {
                    return p == other.p;
                }

                bool operator!=(const iterator& other) const {
                    return p != other.p;
                }
            };  


            iterator begin_preorder(){
                return iterator(0, root);
            }
            iterator end_preorder(){
                return iterator(0, nullptr);
            }
            iterator begin_inorder(){
                return iterator(1, root);
            }
            iterator end_inorder(){
                return iterator(1, nullptr);
            }
            iterator begin_postorder(){
                return iterator(2, root);
            }
            iterator end_postorder(){
                return iterator(2, nullptr);
            }
            iterator begin(){
                return iterator(1, root);
            }
            iterator end(){
                return iterator(1, nullptr);
            }

            friend std::ostream& operator<<(std::ostream& os, const BinaryTree<T> &bt){
                if (bt.root == NULL)
                    return os;
                std::stack<Node*> s;
                s.push(bt.root);
            
                while (!s.empty()) {
                    Node* node = s.top();
                    os<<node->data<<" ";
                    s.pop();
                    if (node->right)
                        s.push(node->right);
                    if (node->left)
                        s.push(node->left);
                }
                return os;
            }

    };
}