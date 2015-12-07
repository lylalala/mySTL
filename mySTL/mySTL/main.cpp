//
//  main.cpp
//  mySTL
//
//  Created by ly on 15/12/7.
//  Copyright © 2015年 ly. All rights reserved.
//

#include "myalloc.h"
#include <vector>
#include <iostream>
using namespace std;
int main(){
    int ia[5]={1,2,3,4,5};
    vector<int,JJ::allocator<int>> iv(ia,ia+5);
    for(int i=0;i<iv.size();i++)
        cout<<iv.at(i)<<endl;
    return 0;
}