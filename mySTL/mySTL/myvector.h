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
using namespace std;

template <class T,class Alloc=JJ::allocator<T> >
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
    
private:
    Alloc alloc;
    //std::allocator<T> alloc;
    
protected://有什么属性？
    //typedef  <#name#>
    iterator start;//可用空间和使用开始
    iterator finish;//可用空间结尾
    iterator end_of_storage;//可用
public://构造函数和析构函数
    myvector():start(0),finish(0),end_of_storage(0) {};
    explicit myvector(size_t n,T value){
        start=alloc.allocate(n);
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
        for (iterator i=start; i!=end_of_storage; i++) {
            //alloc.destory(i);
            //alloc.deallocate(i);
            //JJ::_destroy(i);
            alloc.destroy(i);
        }
        //JJ::_deallocate(start);
        alloc.deallocate(start,end_of_storage-start);
        //alloc.deallocate(start, end_of_storage - start);
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
    /*void push_back(const T& value){
     
     }*/
};

//template<class T>
//std::allocator<T> myvector<T>::alloc;


#endif /* myvector_hpp */
