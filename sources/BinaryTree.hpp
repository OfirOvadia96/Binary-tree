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
                
                //destractor
                ~Node() {
                delete parent;
                delete left;
                delete right;
                }
            };   

        /* -----preorder_iterator ----- */
        class preorder_iterator{

            private:
                Node* current;

            public:

                preorder_iterator(Node* n = nullptr):current(n){}

                preorder_iterator operator++(int){
                    preorder_iterator temp = *this;
                    ++(*this);
                    return temp;
                }

                preorder_iterator& operator++(){ //need fix!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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

                bool operator==(const preorder_iterator& iter){
                    return iter.current == this->current;
                    }

                bool operator!=(const preorder_iterator& iter){
                    return iter.current == this->current;
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

            public:
                inorder_iterator():current(nullptr){}

                inorder_iterator(Node* n):current(n){
                    if(this->current !=nullptr){
                        while(this->current!=nullptr){
                            this->current = this->current->left;
                        }
                    }
                }
                inorder_iterator operator++(int){
                    inorder_iterator temp = *this;
                    ++(*this);
                    return temp;
                }

                inorder_iterator& operator++(){ //need fix!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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

            public:

                postorder_iterator():current(nullptr){}

                postorder_iterator(Node* p):current(p){
                    if (this->current == nullptr){return;}
                    
                    while (this->current->left != nullptr || this->current->right != nullptr){
                        if (this->current->left != nullptr){
                            this->current = this->current->left;
                        }
                        else if(this->current->right != nullptr){
                            this->current = this->current->right;
                        }
                    }
                }

                postorder_iterator operator++(int){
                    postorder_iterator temp = *this;
                    ++(*this);
                    return temp;
                }

                postorder_iterator& operator++(){ // need fix!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    if (this->current != nullptr){
                        Node* temp = this->current;
                        if (this->current->parent != nullptr){
                            this->current = this->current->parent;
                            if (this->current->right != nullptr && this->current->right != temp){
                                this->current = this->current->right;
                                while (this->current->left != nullptr || this->current->right != nullptr){
                                    if (this->current->left != nullptr){
                                        this->current = this->current->left;
                                    }
                                    else{
                                        this->current = this->current->right;
                                    }
                                }
                            }
                        }
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

        BinaryTree(BinaryTree<T> && other_tree){
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
        ~BinaryTree<T>(){}
        
        //deep copy
        BinaryTree<T>& operator=(BinaryTree<T>& other_tree){
            if(this->root != nullptr){
                delete this->root; //deleting the existing one
            }

            this->root = new Node(other_tree.root->data); //create a new one
            nodes_copy_rec(*other_tree.root, *this->root); //copy the other nodes
            
            return *this;
            }

        //superficial copy - "move constructor"
        BinaryTree<T>& operator=(BinaryTree<T>&& other_tree){
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