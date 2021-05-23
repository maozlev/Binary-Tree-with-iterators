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
        bool is_printed = false;
        Node *left = nullptr;
        Node *right = nullptr;
        Node(T info): data(info), left(nullptr), right(nullptr), is_printed(false){}
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
                stack<Node*> s;
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
                    throw string{"no root existing"};
                }
                add(daddy, son, true);
                return *this;
            }
                
            BinaryTree<T> add_right(const T& daddy,const T& son){
                if(root == nullptr){
                    throw string{"no root existing"};
                }
                add(daddy, son, false);
                return *this;
            }

        class iterator{

            private:
                int Order;
                stack<Node*> s;
                queue<Node*> in_order_queue;
                
                Node* p;

            public:

                iterator(int order, Node* ptr=nullptr):p(ptr) {
                    Order = order;
                    if(p!=nullptr){
                        if(order == 0){ //preorder
                            cout<<"in constaructor: "<<p->data<<endl;
                            if(p->right!=nullptr){
                                s.push(p->right);
                            }
                            if(p->left!=nullptr){
                                s.push(p->left);
                            }
                        }
                        else if(order == 1){ //inorder
                            while(p != nullptr){
                                s.push(p);
                                p = p->left;
                            }
                            p = s.top();
                            s.pop();
                            p->is_printed = true;
                            // cout<<"in constaructor: "<<p->data<<endl;
                        }                            
                        
                        else if(order == 2){//postorder
                            s.push(ptr);
                        }    
                    }
                }

                T& operator*() const {
                    return p->data;
                }

                T* operator->() const {
                    return &(p->data);
                }

                // pre fix ++i;
                iterator& operator++() {
                    if(s.empty()){
                        p = nullptr;
                        return *this;
                    }
                    if(Order == 0){ // preorder
                    cout<<"in operator 1: "<<p->data<<endl;
                    p = s.top();
                    s.pop();
                    if(p->right != nullptr){
                        s.push(p->right);
                    }
                    if(p->left != nullptr){
                        s.push(p->left);
                    }
                    cout<<"in operator 2: "<<p->data<<endl;
                    return *this;
                    }

                    else if(Order == 1){ // inorder
                    // cout<<"in operator 1: "<<p->data<<endl;
                    p = s.top();
                    s.pop();
                        if(p->right != nullptr){
                            if(!p->right->is_printed){
                                Node* tmp = p->right;
                                s.push(p->right);
                                p->right->is_printed = true;
                                while(tmp->left != nullptr){
                                    tmp = tmp->left;
                                    s.push(tmp);
                                    tmp->is_printed = true;
                                }
                            }
                        }
                        if(p->left != nullptr){
                            if(!p->left->is_printed){
                                s.push(p->left);
                                p->left->is_printed = true;
                            }
                        }
                        
                        p->is_printed = true;
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
                stack<Node*> s;
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