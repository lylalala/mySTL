//
//  myvector.hpp
//  mySTL
//
//  Created by ly on 15/12/8.
//  Copyright © 2015年 ly. All rights reserved.
//

#ifndef myvector_hpp
#define myvector_hpp

//#include <stdio.h>
#include <memory>
#include "myalloc.h"
#include <new>
#include "myconstruct.h"
#include "myuninitialized.h"
using namespace std;

//template <class T,class Alloc=JJ::allocator<T> >
template <class T,class Alloc=JJ::malloc_alloc>
class myvector{
public:
    typedef T value_type;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
protected:
    iterator start;//可用空间和使用开始
    iterator finish;//可用空间结尾
    iterator end_of_storage;//可用
    typedef JJ::simple_alloc<value_type, Alloc> data_allocate;
    
/*
private:
    Alloc alloc;
public://构造函数和析构函数
    myvector():start(0),finish(0),end_of_storage(0) {};
    explicit myvector(size_t n,T value){
        start=alloc.allocate(n);
        //start=alloc.allocate(n);
        end_of_storage=finish=start+n;
        for (iterator i=start; i!=finish; i++) {
            alloc.construct(i,value);
        }
    }
    explicit myvector(iterator startPos,iterator endPos){
        const size_type size=endPos-startPos;
        start=alloc.allocator(size);
        end_of_storage=finish=start+size;
        for (iterator i=start,j=startPos; i!=finish; i++,j++) {
            alloc.construct(i,*j);
        }
    }
    explicit myvector(size_type n){
        start=alloc.allocator(n);
        end_of_storage=finish=start+n;
    }
    ~myvector(){
        for (iterator i=start; i!=finish; i++) {
            alloc.destroy(i);
        }
        alloc.deallocate(start,end_of_storage-start);
    }
*/
public:
    myvector():start(NULL),finish(NULL),end_of_storage(NULL){};
    myvector(const size_type n,const_reference value){
        start=data_allocate::allocate(n);
        finish=end_of_storage=start+n;
        for (iterator i=start; i!=finish; i++) {
            JJ::construct(i, value);
        }
    }
    myvector(iterator startPos,iterator endPos){
        const size_type length=endPos-startPos;
        start=data_allocate::allocate(length);
        finish=end_of_storage=start+length;
        for(iterator i=start,j=startPos;i!=finish;i++,j++){
            JJ::construct(i, *j);
        }
    }
    myvector(myvector<T> &num){
        const size_type length=num.end()-num.begin();
        start=data_allocate::allocate(length);
        finish=end_of_storage=start+length;
        for(iterator i=start,j=num.begin();i!=finish;i++,j++){
            JJ::construct(i, *j);
        }
    }
    ~myvector(){
        for (iterator i=start; i!=finish; i++) {
            JJ::destroy(i);
        }
        data_allocate::deallocate(start);
    }
    
public:
    iterator begin(){return start;}
    iterator end(){return finish;}
    size_type size(){return (finish-start);}
    size_type capacity(){return (end_of_storage-start);}
    bool empty(){return start==finish;}
    reference operator[](size_type n){return *(start+n);}
    reference front(){return *start;}
    reference back(){return *(finish-1);}
    
public:
    void push_back(const T& value){
        if(finish==end_of_storage){
            insert(finish,value);
        }else{
            JJ::construct(finish, value);
            finish++;
        }
    }
    
    void insert(iterator position,const_reference value){
        /*if(finish==end_of_storage){//need to apply for new room
            //bring the data to a new palce
            const size_type length=finish-start;
            const size_type newlength=(length==0)?1:2*length;
            iterator newstart=data_allocate::allocate(newlength);
            iterator newfinish;
            iterator newend_of_storage=newstart+newlength;
            newfinish=JJ::uninitialized_copy(start, position, newstart);
            JJ::construct(newfinish++, value);
            newfinish=JJ::uninitialized_copy(position, end_of_storage, newfinish);
            this->~myvector();//可以这样析构自己吗？
            start=newstart;
            finish=newfinish;
            end_of_storage=newend_of_storage;
        }else{
            finish=JJ::uninitialized_copy_back(position,finish, position+1);
            JJ::construct(position, value);
        }*/
        insert(position, 1,value);
    }
    
    void pop_back(){
        if (start==finish) {
            std::cerr<<"There is no object in this vector"<<endl;
            exit(0);
        }
        finish--;
        JJ::destroy(finish);
    }
    
    iterator erase(iterator first,iterator last){
        iterator newend=JJ::uninitialized_copy(last, finish, first);
        for (iterator i=newend; i!=finish; i++) {
            JJ::destroy(i);
        }
        finish=newend;
        return first;
    }
    
    iterator erase(iterator position){
        this->erase(position,position+1);
        return position;
    }
    
    
    //厂哥建议补充部分
public:
    template<typename InputIterator>
    myvector(InputIterator first, InputIterator second){
        const size_type length=second-first;
        start=data_allocate::allocate(length);
        finish=end_of_storage=start+length;
        iterator j=start;
        for (InputIterator i=first; i!=second; i++,j++) {
            JJ::construct(j, *i);
        }
    }
    
    /*myvector<T>& operator=(std::initializer_list<T> arr){
        const size_type length=arr.begin()-arr.end();
        start=data_allocate::allocate(length);
        finish=end_of_storage=start+length;
        iterator j=start;
        JJ::uninitialized_copy(arr.begin(),arr.end(),start);
    }*/
    
    //template<typename InputIterator>
    void insert(iterator position,size_type n,const_reference value){
        if(finish+n>=end_of_storage){//need to apply for new room
            //bring the data to a new palce
            const size_type length=finish-start;
            size_type newlength=(length==0)?1:2*length;
            newlength=(newlength>length+2*n)?newlength:length+2*n;
            iterator newstart=data_allocate::allocate(newlength);
            iterator newfinish;
            iterator newend_of_storage=newstart+newlength;
            newfinish=JJ::uninitialized_copy(start, position, newstart);
            //iterator i=position;
            while (n>0) {
                JJ::construct(newfinish++, value);
                n--;
            }
            //JJ::construct(newfinish++, value);
            newfinish=JJ::uninitialized_copy(position, end_of_storage, newfinish);
            
            //deallocate the old place
            /*for (iterator i=start; i!=finish; i++) {
             JJ::destroy(i);
             }
             data_allocate::deallocate(start);*/
            this->~myvector();//可以这样析构自己吗？
            start=newstart;
            finish=newfinish;
            end_of_storage=newend_of_storage;
        }else{
            finish=JJ::uninitialized_copy_back(position,finish, position+n);
            iterator i=position;
            while (n>0) {
                JJ::construct(i++, value);
                n--;
            }
        }
    }
};

#endif /* myvector_hpp */
