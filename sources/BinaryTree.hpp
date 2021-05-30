#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <stack>
#include <string>
#include <deque>          
#include <list>           
#include <queue>

using namespace std;
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
        
        stack<Node*> stack_nodes;

        public:
            // BinaryTree&();
            // BinaryTree&(const BinaryTree&& other);
            // ~BinaryTree&();

            void copy_tree(Node &newroot, const Node &origin_root){
                if (origin_root.left != nullptr){
                    newroot.left = new Node(origin_root.left->data);
                    copy_tree(*newroot.left, *origin_root.left);
                }
                if (origin_root.right != nullptr){
                    newroot.right = new Node(origin_root.right->data);
                    copy_tree(*newroot.right, *origin_root.right);
                }
            }
            
            BinaryTree(){
                root = nullptr;
            }

            BinaryTree(const BinaryTree& other){
                // cout << "copy constructor doing deep copy" << endl;
                T t = other.root->data;
                root = new Node(t);
                copy_tree(*root, *other.root);
            }

            BinaryTree(BinaryTree &&tree) noexcept {
                root = tree.root;
                tree.root = nullptr;
            }

  
            BinaryTree& add_root(const T& data){
                if(root==nullptr){
                    root = new Node(data);
                    stack_nodes.push(root);   
                }
                else{
                    root->data=data;
                }
                return *this;
            }
            
            ~BinaryTree(){
                if(root != nullptr){
                    delete root;
                }
            }

            T find_daddy(Node* p, const T& son){
                if(p->left->data == son){
                    return p->data;
                }
                if(p->right->data == son){
                    return p->data;
                }
                if(p->left != nullptr){
                    return find_daddy(p->left, son);
                }
                if(p->right != nullptr){
                    return find_daddy(p->right, son);
                }
                throw invalid_argument{"no daddy for you"}; 
            }

            BinaryTree& add(const T& daddy,const T& son, bool left_flag){
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
                                }
                                if(p->left != nullptr){
                                    p->left->data = son;
                                }
                           }else{
                               if(p->right == nullptr){
                                    p->right = new Node(son);
                                }
                                if(p->right != nullptr){
                                    p->right->data = son;
                                }
                           }
                           
                           return *this;
                       }
                       
                       p = p->left;
                   }
                throw std::invalid_argument{"daddy is not exist"};
            }
                   

            BinaryTree& add_left(const T& daddy,const T& son){
                if(root == nullptr){
                    throw std::string{"no root existing"};
                }
                add(daddy, son, true);
                return *this;
            }
                
            BinaryTree& add_right(const T& daddy,const T& son){
                if(root == nullptr){
                    throw std::string{"no root existing"};
                }
                add(daddy, son, false);
                return *this;
            }
            BinaryTree &operator=(BinaryTree second){
                if(this == &second){
                    return *this;
                }
                delete root;
                root = new Node(second.root->data);
                copy_tree(*root, *second.root);
                return *this;
            }

            BinaryTree& operator=(BinaryTree &&tree) noexcept {
                if (root != nullptr) {
                    delete root;
                }
                root = tree.root;
                tree.root = nullptr;
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

                        if(order == 1){ //inorder
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
                        
                        if(order == 2){    //postorder
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
                        }
                        if(Order == 1){ // inorder
                            p = q.front();
                            q.pop();
                        }
                        if(Order == 2){ // post order
                            p = out.top();
                            out.pop();
                        }
                    return *this;
                    }    
                    p = nullptr;
                    return *this;
                }
                    
                // post fix i++;
                iterator operator++(int) {
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
                        }
                        if(Order == 1){ // inorder
                            p = q.front();
                            q.pop();
                        }
                        if(Order == 2){ // post order
                            p = out.top();
                            out.pop();
                        }
                        return tmp;
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
        static void print(std::ostream& os, const std::string& prefix, const Node* node, bool isLeft){
            if( node != nullptr ){
                os << prefix;
                if(isLeft){
                    os <<  "├──";
                }
                else{
                    os << "└──";
                }
                os << node->data << std::endl;
                print(os, prefix + (isLeft ? "│   " : "    "), node->left, true);
                print(os, prefix + (isLeft ? "│   " : "    "), node->right, false);
                }
        }

        static void print(std::ostream& os, const Node* node){
            print(os, "", node, false);    
        }

        friend std::ostream& operator<<(std::ostream& os, const BinaryTree &bt){
            if (bt.root == nullptr){
                return os;
            }
            os<<std::endl;
            print(os, bt.root);
            os<<std::endl;
            return os;
        }
    };
}
