//
//  mylist.h
//  mySTL
//
//  Created by ly on 16/2/17.
//  Copyright © 2016年 ly. All rights reserved.
//

#ifndef mylist_h
#define mylist_h

    //define the node
    template<class T>
    struct __list_node{
        //typedef void* void_pointer;
        //void_pointer prev;
        //void_pointer next;
        __list_node<T>* prev;
        __list_node<T>* next;
        T data;
    };

    template<class T,class Ref, class Ptr>
    struct list_iterator{
        typedef __list_node<T>* link_type;
        typedef list_iterator<T,T&,T*> iterator;
        
        link_type node;
        list_iterator(link_type aNode):node(aNode){};
        list_iterator():node(NULL){};
        //list_iterator(iterator aIterator):
        
        bool operator==(const iterator& x) const {return node==x.node;}
        bool operator!=(const iterator& x) const {return node!=x.node;}
//------------------------------------------------------------------------------
        iterator& operator++(){
            node=node->next;
            return *this;
        }
        iterator operator++(int){
            iterator tmp=*this;
            ++*this;
            return tmp;
        }
        iterator& operator--(){
            node=node->prev;
            return *this;
        }
        iterator operator--(int){
            iterator tmp=*this;
            --*this;
            return tmp;
        }
//------------------------------------------------------------------------------

        T operator*() const {return node->data;}
    };

    template<class T,class Alloc=JJ::malloc_alloc>
    class mylist{
    public:
        typedef T value_type;
        typedef value_type* pointer;
        typedef value_type& reference;
        typedef size_t size_type;
        //typedef ptrdiff_t difference_type;
    public:
        typedef list_iterator<value_type,reference,pointer> iterator;
        
    protected:
        typedef __list_node<T> list_node;
        typedef JJ::simple_alloc<list_node,Alloc> list_node_allocator;
    public:
        typedef list_node* link_type;
    protected:
        link_type node;
        size_type count;
        
    public:
        iterator begin() {return node->next;}
        iterator end() {return node;}
        bool empty() {return node->next==node;}
        //size_type size(){
        //
        //}
        
    protected:
        //construct
        link_type get_node(){return list_node_allocator::allocate();}
        void put_node(link_type p){list_node_allocator::deallocate(p);}
        link_type creat_node(const T& a){
            link_type tmp=get_node();
            JJ::construct(&tmp->data,a);//?&
            return tmp;
        }
        void destroy_node(link_type p){
            JJ::destroy(&p->data);//?&
            put_node(p);
        }
        
    public:
        mylist(){empty_initialize();}
        void push_back(const T& d){insert(end(),d);}
        void push_front(const T& d){insert(begin(), d);}
        void pop_front(){erase(begin());}
        void pop_back(){
            iterator tmp=end();
            tmp--;
            erase(tmp);
        }
        void clear(){
            if (node->next==node) {
                return;
            }
            iterator it=begin();
            while (it!=end()) {
                it=erase(it);
            }
            return;
        }
        iterator find(const T& d){
            iterator tmp=begin();
            while (tmp.node->data!=d&&tmp!=end()) {
                tmp++;
            }
            return tmp;
        }
        void remove(const T& d){
            if(node->next==node)
                return;
            iterator it=begin();
            while (it!=end()) {
                if (*it==d) {
                    it=erase(it);
                }else
                    it++;
            }
            return;
        }
    protected:
        void empty_initialize(){
            node=get_node();
            node->next=node;
            node->prev=node;
        }
        iterator insert(iterator positon,const T& d){
            link_type tmp=creat_node(d);
            tmp->next=positon.node;
            tmp->prev=positon.node->prev;
            tmp->prev->next=tmp;
            positon.node->prev=tmp;
            return tmp;
        }
        iterator erase(iterator position){
            iterator tmpPrev=position.node->prev;
            iterator tmpNext=position.node->next;
            tmpPrev.node->next=tmpNext.node;
            tmpNext.node->prev=tmpPrev.node;
            destroy_node(position.node);
            return tmpNext;
        }
    };

#endif /* mylist_h */
