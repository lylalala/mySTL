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
    myvector(size_type n,value_type value=0){
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
};

#endif /* myvector_hpp */
