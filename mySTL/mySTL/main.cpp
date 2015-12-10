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
#include "myvector.h"
using namespace std;
int main(){
    //调试myalloc.h
    /*int ia[5]={1,2,3};
    vector<int,JJ::allocator<int>> ii(ia,ia+3);
    for(int i=0;i<ii.size();i++)
        cout<<ii.at(i)<<endl;*/
    /*JJ::allocator<int> test;
    cout<<test.max_size()<<endl;
    cout<<test.init_page_size()<<endl;
    cout<<4096/sizeof(int)<<endl;
    int a=3;
    int *ptr=test.address(a);
    cout<<*ptr<<endl;
    cout<<"return"<<endl;*/
    
    //调试myvector
    myvector<int> iv(2,1);
    iv.push_back(2);
    for (int i=0; i<iv.size(); i++) {
        cout<<iv[i]<<" ";
    }
    cout<<endl;
    iv.insert(iv.begin(), 4);
    for (int i=0; i<iv.size(); i++) {
        cout<<iv[i]<<" ";
    }
    cout<<endl;
    iv.insert(iv.begin()+2, 5);
    for (int i=0; i<iv.size(); i++) {
        cout<<iv[i]<<" ";
    }
    cout<<endl;
    iv.erase(iv.begin(), iv.begin()+2);
    for (int i=0; i<iv.size(); i++) {
        cout<<iv[i]<<" ";
    }
    cout<<endl;
    iv.erase(iv.begin());
    for (int i=0; i<iv.size(); i++) {
        cout<<iv[i]<<" ";
    }
    cout<<endl;
    return 0;
}