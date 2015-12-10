//
//  myuninitialized.h
//  mySTL
//
//  Created by ly on 15/12/10.
//  Copyright © 2015年 ly. All rights reserved.
//

#ifndef myuninitialized_h
#define myuninitialized_h
#include "myconstruct.h"
namespace JJ{
    //not use traits
    template<class inputIterator,class outputIterator>
    outputIterator uninitialized_copy(inputIterator first,inputIterator last,outputIterator result){
        inputIterator i=first;
        outputIterator j=result;
        for (; i!=last; i++,j++) {
            construct(j,*i);
        }
    }
    
    template<class outIterator,class T>
    void uninitialed_fill(outIterator first,outIterator last,T& value){
        for (outIterator i=first; i!=last; i++) {
            construct(i, value);
        }
    }
    
    template<class outIterator,class Size,class T>
    void uninitialed_fill_n(outIterator result,Size n,T& value){
        Size length=n;
        for (outIterator i=result; length>0; i++,length--) {
            construct(i, value);
        }
    }
}
#endif /* myuninitialized_h */
