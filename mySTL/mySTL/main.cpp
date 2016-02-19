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
#include "myRBtree.h"
#include "mylist.h"
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
    
    //调试myvector<int>
    /*myvector<int> iv(2,1);
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
    cout<<endl;*/
    
    //调试myvector<struct>
    /*struct yg{
        int first;
        string second;
    };
    yg object;
    object.first=3;
    object.second="hello";
    myvector<yg> iv(3,object);
    for (int i=0; i<iv.size(); i++) {
        cout<<iv[i].first<<" "<<iv[i].second<<" "<<endl;
    }*/
    
    //more function of vector
    /*int a[]={1,2,3};
    myvector<int> aa={a,a+3};
    for (int i=0; i<aa.size(); i++) {
        cout<<aa[i]<<" ";
    }
    cout<<endl;
    //aa.insert(aa.begin(),2,100);
    aa.insert(aa.begin(), 2, 100);
    for (int i=0; i<aa.size(); i++) {
        cout<<aa[i]<<" ";
    }
    cout<<endl;*/
//---------------------------------------------------------------------------------------
    //test of myRBtree
    /*myrb_tree<int, int, JJ::identity<int>, less<int>> itree;
    cout<<itree.size()<<endl;
    itree.insert_unique(10);
    itree.insert_unique(7);
    itree.insert_unique(8);
    itree.insert_unique(15);
    itree.insert_unique(5);
    itree.insert_unique(6);
    itree.insert_unique(11);
    itree.insert_unique(13);
    itree.insert_unique(12);
    cout<<itree.size()<<endl;*/
    //int a=0;
    //for (myrb_tree<int, int, JJ::identity<int>, less<int>>::iterator it=itree.begin(); a<9/*it!=itree.end()*/; it++,a++) {
    //    cout<<*it<<" ";
    //}
    //cout<<endl;
    
//-----------------------------------------------------------------------------------------
    //test of myList
    mylist<int> ilist;
    ilist.push_back(1);
    ilist.push_back(2);
    ilist.push_back(3);
    mylist<int>::iterator it;
    for (it=ilist.begin(); it!=ilist.end(); it++) {
        //cout<<it.node->data<<endl;
        cout<<*it<<endl;
    }
    mylist<int>::iterator it2=ilist.find(1);
    if(it2!=ilist.end()){
        cout<<"find!!"<<endl;
    }else
        cout<<"not find!!"<<endl;
    ilist.push_front(1);
    ilist.pop_back();
    for (it=ilist.begin(); it!=ilist.end(); it++) {
        cout<<*it<<endl;
    }
    //ilist.clear();
    //ilist.push_front(4);
    for (it=ilist.begin(); it!=ilist.end(); it++) {
        cout<<*it<<endl;
    }
    ilist.remove(1);
    for (it=ilist.begin(); it!=ilist.end(); it++) {
        cout<<"lala1"<<endl;
        cout<<*it<<endl;
    }
    return 0;
}