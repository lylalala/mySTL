//
//  myalloc.h
//  mySTL
//
//  Created by ly on 15/12/7.
//  Copyright © 2015年 ly. All rights reserved.
//

//第一版本：实现简单的alloc，里面包含分配，释放，构造，析构，并可以配合简版的vector使用
//第二版本：实现完整的第一级适配器，并可以配合简单的vector使用
//第三版本：


/*#ifdef _USE_COMPLEX_MALLO
    typedef _malloc_alloc_template<0> malloc_alloc;
    typedef malloc_alloc alloc;
#else
    typedef _default_alloc_template<0> alloc;
#endif*/

#ifndef myalloc_h
#define myalloc_h
#include<new>
#include<iostream>

namespace JJ {
    using namespace std;
#define simpleAlloc
    
    
    /*
    //1.
    template<class T>
    inline T* _allocate(ptrdiff_t size,T*){
        std::set_new_handler(0);
        T* tmp=(T*)(::operator new((size_t)(size * sizeof(T))));
        if(tmp==0){
            std::cerr<<"out of memory"<<std::endl;
            exit(1);
        }
        return tmp;
    }
    
    //1.
    template<class T>
    inline void _deallocate(T* buffer){
        ::operator delete(buffer);
    }
    
    //1.第一版本的构造析构函数，第二版本移至myconstruct.h中
    //构造和析构使用简单的new和本身的析构，暂不支持对迭代器的析构
    template<class T1,class T2>
    inline void _construct(T1* p,const T2 & value){
        new(p) T1(value);
    }
    
    template<class T>
    inline void _destroy(T* ptr){
        ptr->~T();
    }
    
    //template<class T>
    template<int inis>
    class allocator{
    public:
        typedef T value_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef const T& const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        
        template<class U>
        struct rebind{
            typedef allocator<U> other;
        };
        
        pointer allocate(size_type n,const void* hint=0){
            return _allocate((difference_type)n,(pointer)0);
            cout<<"allocate"<<endl;
        }
        
        //1.第一版的deallocate
        void deallocate(pointer p,const T& value){
            _deallocate(p);
            cout<<"deallocate"<<endl;
        }
        
        void dealocate(pointer p,size_type n){
            free(p);
            cout<<"deallocate"<<endl;
        }
        
        //1.第一版的构造和析构函数
        void construct(pointer p,const T& value){
            _construct(p,value);
            cout<<"construct"<<endl;
        }
        
        void destroy(pointer p){
            _destroy(p);
            cout<<"destory"<<endl;
        }
        
        pointer address(reference x){
            return (pointer)&x;
        }
        
        const_pointer const_address(reference x){
            return (const_pointer)&x;
        }
        
        size_type max_size() const{
            return size_type(UINT_MAX/sizeof(T));
        }
        
        size_type init_page_size(){
            return std::max(size_type(1),size_type(4096/sizeof(T)));
            cout<<"init_page_size"<<endl;
        }
    };*/
    
    //包装的接口
    template<class T,class Alloc>
    class simple_alloc{
    public:
        
        static T *allocate(size_t n){
            void* result=(n==0)?NULL:(Alloc::allocate(n*sizeof(T)));
            return (T*)result;
        }
        static T *allocate(){
            return Alloc::allocate(sizeof(T));
        }
        static void deallocate(T* p,size_t n){
            if(n!=0)
                Alloc::deallocate(p,n*sizeof(T));
        }
        static void deallocate(T *p){
            Alloc::deallocate(p,sizeof(T));
        }
    };
    
    template<int inst>
    class _malloc_alloc_template{
    public:
        static void* allocate(size_t n){
            void* result=malloc(n);
            return result;
        }
        static void deallocate(void *p,size_t){
            free(p);
        }
        static void* reallocate(void *p,size_t,size_t new_sz){
            void* result=realloc(p, new_sz);
            return result;
        }
    };
    
    template<int inst>
    class _default_alloc_template{
        
    };
    
#ifdef simpleAlloc
    typedef _malloc_alloc_template<0> malloc_alloc;
#else
    typedef _default_alloc_template<0> malloc_alloc;
#endif
    
}

#endif /* myalloc_h */

