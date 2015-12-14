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
    
    typedef rbtree_color bool;
    const rbtree_color red=false;
    const rbtree_color black=true;
    
    //define the base node
    struct rbtree_basenode{
        typedef rbtree_color color;
        typedef *rbtree_basenode ptr;
        
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
    class rbtree_node:public rbtree_basenode
    {
        typedef rbtree_node<T>* link_type;
        T value;
    };
    
    //define the base iterator
    struct rbtree_baseiterator{
        typedef rbtree_basenode::ptr base_ptr;
        //how to use???
        typedef bidirectional_iterator_tag iterator_category;
        typedef ptrdiff_t difference_type;
        
        base_ptr node;
    };
}
#endif /* myRBtree_h */
