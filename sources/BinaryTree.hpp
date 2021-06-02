#include <iostream>

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

            public:

                preorder_iterator(Node* n = nullptr) : current(n){}

                preorder_iterator& operator++(){
                    if(current != nullptr){
                        if (current->left != nullptr){
                            current = current->left;
                        }
                        else if (current->right != nullptr){
                            current = current->right;
                        }
                        else{
                            while (current->parent != nullptr){
                                current = current->parent;
                                // missing part//

                            }
                            current = current->right;
                        }       
                    }
                    return *this;
                }

                bool operator==(preorder_iterator& iter){
                    return iter.current == this->current;
                    }

                bool operator!=(const preorder_iterator& iter){
                    return iter.current == this->current;
                    }

                T& operator*()const {
                    return current->data;
                    }

                T* operator->() const{
                    return &current;
                }
        };

        /* -----inorder_iterator ----- */
        class inorder_iterator{

            private:
                Node* current;

            public:

                inorder_iterator(Node* n = nullptr) : current(n){
                    if(current !=nullptr){
                        while(current!=nullptr){
                            current = current->left;
                        }
                    }
                }

                inorder_iterator& operator++(){
                    if(current != nullptr){
                        if(current->right != nullptr){
                            current = current->right;
                            while(current->left != nullptr){
                                current = current->left;
                            }
                        }
                        else{
                            while (current == current->parent->right){
                                current = current->parent;
                                }
                            current = current->parent;
                        }
                    }

                    return *this;
                    }

                bool operator==(inorder_iterator& it){
                    return this->current == it.current;
                }

                bool operator!=(const inorder_iterator& it){
                    return this->current != it.current;
                }

                T& operator*(){
                    return current->data;
                }

                T* operator->(){ 
                    return &current;
                }
        };

        /* -----postorder_iterator ----- */
        class postorder_iterator{
            private:
                Node* current;

            public:

                postorder_iterator(Node* p = nullptr) : current(p){}

                postorder_iterator& operator++(){
                    if (current != nullptr){
                        Node temp = current;
                        if (current->parent != nullptr){
                            current = current->parent;
                            if (current->right != nullptr && current->right != temp){
                                current = current->right;
                                while (current->left != nullptr || current->right != nullptr){
                                    if (current->left != nullptr){
                                        current = current->left;
                                    }
                                    else{
                                        current = current->right;
                                    }
                                }
                            }
                        }
                    }
                    return *this;
                }

                bool operator==(postorder_iterator& iter){
                    return this->current == iter.current;
                }

                bool operator!=(const postorder_iterator& iter){
                    return this->current != iter.current;
                }

                T& operator*(){
                    return current->data;
                }

                T* operator->(){
                    return &(current->data);
                }
        };

        /* ----- Back to BinaryTree ----- */
        private:
            Node* root;
        
        public:
        /* constractor */
        BinaryTree<T>():root(nullptr){}

        /* copy constractor */
        BinaryTree<T>(const BinaryTree<T>& other_tree){}
        
        /* destractor */
        ~BinaryTree<T>(){}

        BinaryTree<T> &operator=(BinaryTree<T> &&other){}
        

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

            else{
                Node* found = search_node_recursive(p,this->root);
                //if exist
                if(found == nullptr){
                    throw std::out_of_range("doesn't exist!");
                }

                else{
                    if(found->left == nullptr){ //doesn't have left child
                        found->left = new Node(left_child);
                        found->left->parent = found;
                    }
                    else{ // had left child - switch data
                        found->left->data = left_child;
                    }
                }
            }
            return *this;
        }

        BinaryTree<T> add_right(T p,T right_child){
             if(this->root == nullptr){
                throw std::invalid_argument("Empty BinaryTree!");
            }
            
            else{
                Node* found = search_node_recursive(p,this->root);
                //if exist
                if(found == nullptr){
                    throw std::out_of_range("doesn't exist!");
                }

                else{
                    if(found->right == nullptr){ //doesn't have right child
                        found->right = new Node(right_child);
                        found->right->parent = found;
                    }
                    else{ // had right child - switch data
                        found->right->data = right_child;
                    }
                }
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