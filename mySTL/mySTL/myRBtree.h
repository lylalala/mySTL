//
//  myRBtree.h
//  mySTL
//
//  Created by ly on 15/12/14.
//  Copyright © 2015年 ly. All rights reserved.
//

#ifndef myRBtree_h
#define myRBtree_h
namespace JJ{
    template <class T>
    struct identity : public unary_function<T, T> {
        const T& operator()(const T& x) const { return x; }
    };
}
    typedef bool rbtree_color;
    const rbtree_color red=false;
    const rbtree_color black=true;
    
    //define the base node
    struct rbtree_basenode{
        typedef rbtree_color color;
        typedef rbtree_basenode* ptr;
        
        color cl;
        ptr father;
        ptr left;
        ptr right;
        
        static ptr minimum(ptr root){
            ptr temp=root;
            while(temp->left!=NULL)
                temp=temp->left;
            return temp;
        }
        
        static ptr maximum(ptr root){
            ptr temp=root;
            while(temp->right!=NULL)
                temp=temp->right;
            return temp;
        }
    };
    
    //define the node
    template<typename T>
    struct rbtree_node:public rbtree_basenode
    {
        typedef rbtree_node<T>* link_type;
        T value_filed;
    };
    
    //define the base iterator
    struct rbtree_baseiterator{
        typedef rbtree_basenode::ptr base_ptr;
        //how to use???
        typedef bidirectional_iterator_tag iterator_category;
        typedef ptrdiff_t difference_type;
        base_ptr node;
        //
        
        void increment(){
            //you should note that the root's father is header, and the header is end()
            //it is a technique to deal with the boundary
            if(node->right!=NULL){
                node=node->right;
                while(node->left!=NULL)
                    node=node->left;
            }else{
                base_ptr y=node->father;
                while(y->right==node){
                    node=y;
                    y=node->father;
                }
                if(node->right!=y)
                    node=y;
            }
        }
        
        void decrement(){
            if(node->cl!=black&&node->father->father==node)
                node=node->right;
            else if(node->left!=NULL){
                node=node->left;
                while(node->right!=NULL)
                    node=node->right;
            }else{
                base_ptr y=node->father;
                while(y->left==node){
                    node=y;
                    y=node->father;
                }
                node=y;
            }
        }
    };
    
    //还没有理解
    template<typename Value, typename Ref, class Ptr>
    struct rbtree_iterator:public rbtree_baseiterator
    {
        typedef Value value_type;
        typedef Ref reference;
        typedef Ptr pointer;
        typedef rbtree_iterator<Value,Value&,Value*> iterator;
        typedef rbtree_iterator<Value,const Value&,const Value*> const_iterator;
        typedef rbtree_node<Value>* link_type;
        
        rbtree_iterator(){}
        rbtree_iterator(link_type x){node=x;}
        rbtree_iterator(const iterator& it){node=it.node;}
        
        //reference operator*() const {return link_type->value_filed;}
        reference operator*() const {return link_type(node)->value_filed;}
        pointer operator->() const {return &(operator*());}
        bool operator!=(const rbtree_iterator& a)const{return node!=a.node;}
        bool operator==(const rbtree_iterator& a)const{return node==a.node;}

        rbtree_iterator& operator++(){increment();return *this;}
        rbtree_iterator operator++(int){
            rbtree_iterator tmp=*this;
            increment();
            return tmp;
        }
        rbtree_iterator& operator--(){decrement();return *this;}
        rbtree_iterator operator--(int){
            rbtree_iterator tmp=*this;
            decrement();
            return tmp;
        }
    };

    //some inline function
    inline void __rb_tree_rotate_left(rbtree_basenode* x,rbtree_basenode*& root){
        rbtree_basenode* y=x->right;
        if (y->left!=NULL) {
            y->left->father=x;
        }
        x->right=y->left;
        y->father=x->father;
        if (x==root) {
            root=y;
        }else{
            if (x==x->father->left)
                x->father->left=y;
            else
                x->father->right=y;
        }
        x->father=y;
        y->left=x;
    }

    inline void __rb_tree_rotate_right(rbtree_basenode* x,rbtree_basenode*& root){
        rbtree_basenode* y=x->left;
        if (y->right!=NULL) {
            y->right->father=x;
        }
        x->left=y->right;
        y->father=x->father;
        if (x==root) {
            root=y;
        }else{
            if (x==x->father->left) {
                x->father->left=y;
            }else
                x->father->right=y;
        }
        y->right=x;
        x->father=y;
    }

    inline void __rb_tree_rebalance(rbtree_basenode* x,rbtree_basenode*& root){
        x->cl=red;
        while (x!=root&&x->father->cl==red) {
            if (x->father==x->father->father->left) {
                //father's brother
                rbtree_basenode* y=x->father->father->right;
                if (y&&y->cl==red) {
                    x->father->cl=black;
                    y->cl=black;
                    y->father->cl=red;
                    x=y->father;
                }else{
                    //father dont have brother or the brother is black
                    if (x==x->father->right) {
                        x=x->father;
                        __rb_tree_rotate_left(x,root);
                    }
                    x->father->cl=black;
                    x->father->father->cl=red;
                    __rb_tree_rotate_right(x->father->father,root);
                }
            }
            else{
                rbtree_basenode* y=x->father->father->left;
                if (y&&y->cl==red) {
                    x->father->cl=black;
                    y->cl=black;
                    y->father->cl=red;
                    x=y->father;
                }else{
                    if (x==x->father->left) {
                        x=x->father;
                        __rb_tree_rotate_right(x,root);
                    }
                    x->father->cl=black;
                    x->father->father->cl=red;
                    __rb_tree_rotate_left(x->father->father,root);
                }
            }
        }
        root->cl=black;
    }



    template<class Key,class Value,class KeyOfValue,class Compare,class Alloc=JJ::malloc_alloc>
    class myrb_tree{
    protected:
        typedef void* void_pointer;
        typedef rbtree_basenode* base_ptr;
        typedef rbtree_node<Value> rb_tree_node;
        typedef JJ::simple_alloc<rbtree_node<Value>, Alloc> rb_tree_node_allocator;
        typedef rbtree_color color_type;
    public:
        typedef Key key_type;
        typedef Value value_type;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef rb_tree_node* link_type;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
    public:
        typedef rbtree_iterator<value_type, reference, pointer> iterator;
    protected:
        size_type node_count;//the number of treeNode
        link_type header;
        Compare key_compare;
    protected:
        link_type get_node(){return rb_tree_node_allocator::allocate();}
        void put_node(link_type p){rb_tree_node_allocator::deallocate(p);}
        link_type creat_node(const_reference x){
            link_type tmp=get_node();
            JJ::construct(&tmp->value_filed, x);
            return tmp;
        }
        
        link_type& root(){return (link_type&)header->father;}
        link_type& leftmost(){return (link_type&)header->left;}
        link_type& rightmost(){return (link_type&)header->right;}
        
        static link_type& parent(link_type x){return (link_type&)x->father;}
        static link_type& left(link_type x){return (link_type&)x->left;}
        static link_type& right(link_type x){return (link_type&)x->right;}
        static color_type& color(link_type x){return (color_type&)x->cl;}
        static const Key& key(link_type x){return KeyOfValue()(value(x));}
        static reference value(link_type x){return x->value_filed;}
        
        static link_type& parent(base_ptr x){return (link_type&)x->father;}
        static link_type& left(base_ptr x){return (link_type&)x->left;}
        static link_type& right(base_ptr x){return (link_type&)x->right;}
        static color_type& color(base_ptr x){return (color_type&)x->cl;}
        static const Key& key(base_ptr x){return KeyOfValue()(value(x));}
        static reference value(base_ptr x){return ((link_type&)x)->value_filed;}

    public:
        iterator begin(){return leftmost();}
        iterator end(){return header;}
        size_type size(){return node_count;}
        
    public:
        myrb_tree(const Compare& comp=Compare()):node_count(0),key_compare(comp){init();}
        //myrb_tree(){
            
        //}
        
        //insert
        iterator insert_equal(const_reference v){
            link_type y=header;
            link_type x=root();
            while (x!=NULL) {
                y=x;
                x=key_compare(KeyOfValue()(v),key(x))?left(x):right(x);
            }
            return __insert(x,y,v);
        }
        
        pair<iterator, bool> insert_unique(const_reference v){
            link_type y=header;
            link_type x=root();
            bool comp=true;
            while (x!=NULL) {
                y=x;
                comp=key_compare(KeyOfValue()(v),key(x));
                x=comp?left(x):right(x);
            }
            iterator j=iterator(y);
            if(comp){
                if (j==begin()) {
                    return pair<iterator, bool>(__insert(x,y,v),true);
                }else
                    j--;
            }
            if (key_compare(key(j.node),KeyOfValue()(v))) {
                return pair<iterator, bool>(__insert(x,y,v),true);
            }
            return pair<iterator, bool>(j,false);
        }
    
        /*iterator find(const Key& v){
            link_type y=header;
            link_type x=root();
            while (x!=NULL) {
                if (key_compare(key(x),v)) {
                    y=x,x=right(y);
                }else
                    x=left(x);
            }
            iterator j=iterator(y);
            if (y==header||key_compare()) {
                <#statements#>
            }
        }*/
        
    private:
        void init(){
            //header point to the header node
            header=get_node();
            color(header)=red;
            root()=0;
            leftmost()=header;
            rightmost()=header;
        }
        
        iterator __insert(base_ptr x_,base_ptr y_,const_reference v){
            //link_type x=(link_type) x_;
            link_type y=(link_type) y_;
            link_type z=creat_node(v);
            
            if(y==header||key_compare(KeyOfValue()(v),key(y))){
                left(y)=z;
                if(y==header){
                    root()=z;
                    rightmost()=z;
                }else if(y==leftmost()){
                    leftmost()=z;
                }
            }
            else{
                right(y)=z;
                if (y==rightmost()) {
                    rightmost()=z;
                }
            }
            
            parent(z)=y;
            left(z)=NULL;
            right(z)=NULL;
            __rb_tree_rebalance(z,header->father);
            node_count++;
            return iterator(z);
            //return z;
        }
    };

#endif /* myRBtree_h */
