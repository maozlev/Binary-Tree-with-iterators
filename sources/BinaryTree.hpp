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
        Node *left = nullptr;
        Node *right = nullptr;
        Node(T info): data(info), left(nullptr), right(nullptr){}
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
                std::stack<Node*> out;
                std::queue<Node*> q;
                Node* p;

            public:

                iterator(int order, Node* ptr=nullptr):p(ptr) {
                    Order = order;
                    if(p!=nullptr){
                        if(order == 0){ //preorder
                            if(p->right!=nullptr){
                                s.push(p->right);
                            }
                            if(p->left!=nullptr){
                                s.push(p->left);
                            }
                        }

                         else if(order == 1){ //inorder
                            Node* tmp = p;
                            while (tmp != nullptr || !s.empty()) {
                                while (tmp !=  nullptr) {
                                    s.push(tmp);
                                    tmp = tmp->left;
                                }
                                tmp = s.top();
                                q.push(tmp);
                                s.pop();
                                tmp = tmp->right;
                            }
                            p = q.front();
                            q.pop();
                        }                                
                        
                        else if(order == 2){    //postorder
                            s.push(p); 
                            while (!s.empty()){
                                Node* curr = s.top();
                                s.pop();
                                out.push(curr);
                                if (curr->left) {
                                    s.push(curr->left);
                                }
                                if (curr->right) {
                                    s.push(curr->right);
                                }
                            }
                            p = out.top();
                            out.pop();    
                        }     
                    }
                }

                // pre fix ++i;
                iterator& operator++() {
                    if(!s.empty() || !out.empty() || !q.empty()){
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
                        else if(Order == 1){ // inorder
                            p = q.front();
                            q.pop();
                            return *this;
                        }
                        else{ // post order
                            p = out.top();
                            out.pop();
                            return *this;
                        }
                    }    
                    p = nullptr;
                    return *this;
                }
                    
                // post fix i++;
                const iterator operator++(int) {
                    iterator tmp = *this;
                    if(!s.empty() || !out.empty() || !q.empty()){
                        if(Order == 0){ // pre order
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
                         else if(Order == 1){ // inorder
                            p = q.front();
                            q.pop();
                            return tmp;
                        }
                        else{ // post order
                            p = out.top();
                            out.pop();
                            return tmp;
                        }
                    }    
                    p = nullptr;
                    return tmp;
                }

                bool operator==(const iterator& other) const {
                    return p == other.p;
                }

                bool operator!=(const iterator& other) const {
                    return p != other.p;
                }
                
                T& operator*() const {
                    return p->data;
                }

                T* operator->() const {
                    return &(p->data);
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