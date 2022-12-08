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
            };   

        /* -----preorder_iterator ----- */
        class preorder_iterator{

            private:
                Node* current;

            public:

                preorder_iterator(Node* n = nullptr) : current(n){}

                preorder_iterator& operator++(){return *this;}

                bool operator<(preorder_iterator& iter){return false;}

                bool operator!=(const preorder_iterator& iter){return false;}

                T& operator*(){return current->data;}

                T* operator->(){return &(current->data);}
        };

        /* -----inorder_iterator ----- */
        class inorder_iterator{

            private:
                Node* current;

            public:

                inorder_iterator(Node* n = nullptr) : current(n){}

                inorder_iterator& operator++(){return *this;}

                bool operator<(inorder_iterator& it){return false;}

                bool operator!=(const inorder_iterator& it){return false;}

                T& operator*(){return current->data;}

                T* operator->(){ return &(current->data);}
        };

        /* -----postorder_iterator ----- */
        class postorder_iterator{
            private:
                Node* current;

            public:

                postorder_iterator(Node* p = nullptr) : current(p){}

                postorder_iterator& operator++(){ return *this;}

                bool operator<(postorder_iterator& iter){return false;}

                bool operator!=(const postorder_iterator& iter){ return false;}

                T& operator*(){return current->data;}

                T* operator->(){ return &(current->data);}
        };

        /* ----- Back to BinaryTree ----- */
        private:
            Node* root;
        
        public:
        BinaryTree<T> add_root(T v){
            return *this;
        }

        BinaryTree<T> add_left(T father,T left_child){
            return *this;
        }

        BinaryTree<T> add_right(T father,T right_child){
            return *this;
        }

        preorder_iterator begin_preorder(){
            return preorder_iterator(root);
        }

        preorder_iterator end_preorder(){
            return preorder_iterator(root);
        }

        inorder_iterator begin_inorder(){
            return inorder_iterator(root);
        }

        inorder_iterator end_inorder(){
            return inorder_iterator(root);
        }

        postorder_iterator begin_postorder(){
            return postorder_iterator(root);
        }

        postorder_iterator end_postorder(){
            return postorder_iterator(root);
        }

        inorder_iterator end(){
            return inorder_iterator(root);
        }

        inorder_iterator begin(){
            return inorder_iterator(root);
        }

         friend std::ostream& operator<<(std::ostream& os, const BinaryTree& t){
            return os << "stam";
        }

    };
}