//
//  myconstruct.h
//  mySTL
//
//  Created by ly on 15/12/9.
//  Copyright © 2015年 ly. All rights reserved.
//

#ifndef myconstruct_h
#define myconstruct_h
#include<new>
#include<iostream>
namespace JJ{
    using namespace std;
    
    //2.
    template<class T1,class T2>
    inline void construct(T1* ptr, const T2& value){
        new(ptr) T1(value);
    }
    
    template<class T1>
    inline void destroy(T1* ptr){
        ptr->~T1();
    }
}

#endif /* myconstruct_h */
