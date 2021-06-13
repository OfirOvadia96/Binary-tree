
#pragma once
#include <iostream>
#include <stack>

//source : https://www.geeksforgeeks.org/iterative-preorder-traversal/ (the idea of stack)

namespace ariel{
    template<typename T> class BinaryTree{
        
        public:
            /* ----- Node ----- */
            struct Node{
                T data;
                Node* parent;
                Node* left;
                Node* right;

                //constractor
                Node(const T& d, Node* l=nullptr, Node* r=nullptr, Node* p=nullptr):data(d),left(l),right(r),parent(p){}
            };   

        /* -----preorder_iterator ----- */
        class preorder_iterator{

            private:
                Node* current;
                std::stack<Node*> my_stack;

            public:

                preorder_iterator(Node* n = nullptr):current(n){
                    if(n != nullptr){
                        if (current->right !=nullptr) {
                            my_stack.push(current->right);
                            }

                        if (current->left != nullptr) {
                            my_stack.push(current->left);
                            }
                    }
                }

                preorder_iterator operator++(int){
                    preorder_iterator temp = *this;
                    ++(*this);
                    return temp;
                }

                preorder_iterator& operator++(){
                    if (my_stack.empty()) {
                        current = nullptr;
                    }
                    
                    else{
                        current = my_stack.top();
                        my_stack.pop();
                        if(current->right) {
                            my_stack.push(current->right);
                        }

                        if (current->left) {
                            my_stack.push(current->left);
                        }
                    } 
                    return *this;
                }

                bool operator==(const preorder_iterator& iter){
                    return iter.current == this->current;
                    }

                bool operator!=(const preorder_iterator& iter){
                    return iter.current != this->current;
                    }

                T& operator*()const {
                    return current->data;
                    }

                T* operator->() const{
                    return &current->data;
                }
        };

        /* -----inorder_iterator ----- */
        class inorder_iterator{

            private:
                Node* current;
                std::stack<Node*> my_stack;

            public:

                inorder_iterator(Node* n = nullptr):current(n) {
                    if(current != nullptr){
                        while(current != nullptr) {
                            my_stack.push(current);
                            current = current->left;
                        }
                            current = my_stack.top();
                            my_stack.pop();
                    }
                }

                inorder_iterator operator++(int){
                    inorder_iterator temp = *this;
                    ++(*this);
                    return temp;
                }

                inorder_iterator& operator++(){
                    if(current != nullptr){
                        current = current->right;
                        if (!my_stack.empty() || current != nullptr) {
                        
                            while(current != nullptr) {
                                my_stack.push(current);
                                current = current->left;
                            }

                            current = my_stack.top();
                            my_stack.pop();
                        }
                    }
                    return *this;
                }

                bool operator==(const inorder_iterator& it){
                    return this->current == it.current;
                }

                bool operator!=(const inorder_iterator& it){
                    return this->current != it.current;
                }

                T& operator*(){
                    return current->data;
                }

                T* operator->() const{ 
                    return &current->data;
                }
        };

        /* -----postorder_iterator ----- */
        class postorder_iterator{
            private:
                Node* current;
                std::stack<Node*> first;
                std::stack<Node*> second;

            public:

                postorder_iterator(Node* p = nullptr):current(p){
                    if (current != nullptr) {
                        first.push(p);
                        while (!first.empty()) {
                            current = first.top();
                            first.pop();
                            second.push(current);
                            if (current->left) {
                                first.push(current->left);
                            }

                            if (current->right) {
                                first.push(current->right);
                            }
                        }
                        
                    current = second.top();
                    second.pop();
                    }
                }

                postorder_iterator operator++(int){
                    postorder_iterator temp = *this;
                    ++(*this);
                    return temp;
                }

                postorder_iterator& operator++(){ 
                    if (!second.empty()) { //if there is more nodes
                        current = second.top();
                        second.pop();
                    }

                    else{ //if there not
                       current = nullptr;
                    }

                    return *this;
                }

                bool operator==(const postorder_iterator& iter){
                    return this->current == iter.current;
                }

                bool operator!=(const postorder_iterator& iter){
                    return this->current != iter.current;
                }

                T& operator*(){
                    return current->data;
                }

                T* operator->() const{
                    return &current->data;
                }
        };

        /* ----- Back to BinaryTree ----- */
        private:
            Node* root;
        
        public:
        /* constractor */
        BinaryTree<T>():root(nullptr){}

        /* copy constractor */
        BinaryTree<T>(const BinaryTree<T>& other_tree){
            if (other_tree.root == nullptr) {
                return;
            }
            this->root = new Node(other_tree.root->data); //create root
            nodes_copy_rec(*other_tree.root, *this->root); //copy the other nodes
        }

        BinaryTree(BinaryTree<T> && other_tree) noexcept {
            this->root = other_tree.root; // point to the same root
            other_tree.root = nullptr;  // "remove" the older pointer
        }

        static void nodes_copy_rec(const Node& other_tree, Node& new_tree){
            if (other_tree.left != nullptr) {
                new_tree.left = new Node(other_tree.left->data);
                nodes_copy_rec(*other_tree.left, *new_tree.left);
            }

            if (other_tree.right != nullptr) {
                new_tree.right = new Node(other_tree.right->data);
                nodes_copy_rec(*other_tree.right, *new_tree.right);
            }
        }
        
        /* destractor */
        ~BinaryTree<T>(){
            remove_tree(this->root);
        }

        void remove_tree(Node* curr){
             if (curr != nullptr){
                remove_tree(curr->left);
                remove_tree(curr->right);
            }
            delete curr;
        }

        
        //deep copy
        BinaryTree<T>& operator=(const BinaryTree<T>& other_tree){
            if(this == &other_tree){
                return *this;
            }

            if(other_tree.root == nullptr){ 
                this->root = nullptr;
                return *this;
            }

            if(this->root != nullptr){
                //deleting the existing one
                delete this->root;
            }

            this->root = new Node(other_tree.root->data); //create a new one
            nodes_copy_rec(*other_tree.root, *this->root); //copy the other nodes
            
            return *this;
            }

        //superficial copy - "move constructor"
        BinaryTree<T>& operator=(BinaryTree<T>&& other_tree) noexcept{
            this->root = other_tree->root; // point to the same root
            other_tree->root = nullptr; // "remove" the older pointer
            return *this;
        }
        

          Node* search_node_recursive(T d, Node* node){
            if(node->data == d){
                return node; //node found
            }

            Node* n = nullptr;

            if(node->left != nullptr && n == nullptr){
                n = search_node_recursive(d, node->left);
            }

            if(node->right != nullptr && n == nullptr){
                n = search_node_recursive(d, node->right);
            }
            return n;
        }

        BinaryTree<T> add_root(T d){
            if(this->root == nullptr){
                this->root = new Node(d);
            }
            else{
                this->root->data = d;
            }

            return *this;
        }

        BinaryTree<T> add_left(T p,T left_child){
            if(this->root == nullptr){
                throw std::invalid_argument("Empty BinaryTree!");
            }

            Node* found = search_node_recursive(p,this->root);
            //if exist
            if(found == nullptr){
                throw std::out_of_range("doesn't exist!");
            }

            if(found->left == nullptr){ //doesn't have left child
                found->left = new Node(left_child);
                found->left->parent = found;
                }
            else if(found->left != nullptr){ // had left child - switch data
                found->left->data = left_child;
            }
            return *this;
        }

        BinaryTree<T> add_right(T p,T right_child){
            if(this->root == nullptr){
                throw std::invalid_argument("Empty BinaryTree!");
            }
            
            Node* found = search_node_recursive(p,this->root);
            //if exist
            if(found == nullptr){
                throw std::out_of_range("doesn't exist!");
            }

            if(found->right == nullptr){ //doesn't have right child
                found->right = new Node(right_child);
                found->right->parent = found;
            }
            else{ // had right child - switch data
                found->right->data = right_child;
            }
            return *this;
        }

        preorder_iterator begin_preorder(){
            return preorder_iterator(root);
        }

        preorder_iterator end_preorder(){
            return preorder_iterator();
        }

        inorder_iterator begin_inorder(){
            return inorder_iterator(root);
        }

        inorder_iterator end_inorder(){
            return inorder_iterator();
        }

        postorder_iterator begin_postorder(){
            return postorder_iterator(root);
        }

        postorder_iterator end_postorder(){
            return postorder_iterator();
        }

        inorder_iterator end(){
            return inorder_iterator();
        }

        inorder_iterator begin(){
            return inorder_iterator(root);
        }

         friend std::ostream& operator<<(std::ostream& os, const BinaryTree& t){
            return os << "stam";
        }

    };
}