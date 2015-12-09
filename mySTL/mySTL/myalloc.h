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
//#define simpleAlloc
    
    
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
    
    //第一级适配器_malloc_alloc_template
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

#define defaultAlloc_MaxSize 128
#define align 8
#define nfreelists defaultAlloc_MaxSize/align
    //第二级适配器_default_alloc_template
    union obj{
        union obj* free_list_link;
        char client_data[1];
    };
    
    template<int inst>
    class _default_alloc_template{
    private:
        static obj* free_list[nfreelists];
        static size_t freeList_index(size_t thisSize){
            return (thisSize+align-1)/align-1;
        }
        static size_t roundup(size_t thisSize){
            return ((thisSize+align-1)/align)*align;
        }
        static char* start_free;
        static char* end_free;
        static size_t heap_size;
        
    public:
        static void* allocate(size_t n){
            //if the space size required is bigger than "defaultAlloc_MaxSize", just use "malloc"
            if(n>defaultAlloc_MaxSize){
                void* result=malloc(n);
                return result;
            }
            //if smaller, use a List to implement fine-grained allocator
            else{
                obj** my_free_list=free_list+freeList_index(n);
                obj* result=*my_free_list;
                if(result==0){
                    void *r=refill(roundup(n));
                    return r;
                }
                *my_free_list=result->free_list_link;
                return result;
            }
        }
        
        static void deallocate(void *ptr,size_t n){
            if(n>defaultAlloc_MaxSize){
                free(ptr);
            }
            else{
                obj** my_free_list=free_list+freeList_index(n);
                ((obj*)ptr)->free_list_link=*my_free_list;
                *my_free_list=((obj*)ptr);
            }
        }
        
        static void *refill(size_t n){
            //理想中希望能拿出来20个块，其中一个用来给allocate返回
            int nobjs=20;
            char* result=chunk_alloc(n, nobjs);
            if(nobjs==1)
                return (void*)result;
            else{
                obj** my_free_list=free_list+freeList_index(n);
                char* res=result;//用来返回
                nobjs--;
                int i=nobjs;
                char* first=result+n;
                char* second;
                *my_free_list=(obj*)first;
                while (1) {
                    second=first+n;
                    if (i==1) {
                        break;
                    }
                    ((obj*)first)->free_list_link=((obj*)second);
                    first=second;
                    i--;
                }
                return (void*) res;
            }
        }
        
        static char* chunk_alloc(size_t size,int &nobjs){
            char* result;
            size_t total_bytes=size*nobjs;
            size_t bytes_left=end_free-start_free;
            //情况一，内存池中的内存足够所有请求，直接分配
            if (bytes_left>=total_bytes) {
                //从内存池起始端开始分配
                result=start_free;
                //内存池起始端移动
                start_free+=total_bytes;
                return result;
            }
            //情况二，内存池中的空间只能满足一个及以上空间的请求，直接分配
            else if(bytes_left>=size){
                nobjs=int(bytes_left/size);
                result=start_free;
                start_free+=(nobjs*size);
                return result;
            }
            //情况三，内存池中的空间不能满足一个，情况比较复杂
            else{
                //请求空间的大小应该是可以随意设置的
                size_t bytes_to_get=2*total_bytes;
                //情况三.1 处理内存池中的零头
                if (bytes_left>0) {
                    obj**my_free_list=free_list+freeList_index(bytes_left);
                    //插入到此free_list的头部
                    ((obj*)start_free)->free_list_link=*my_free_list;
                    *my_free_list=((obj*)start_free);
                }
                //2.采用原始malloc的办法往内存池加入内存
                start_free=(char*)(std::malloc(bytes_to_get));
                if(start_free==NULL){
                    
                }else{
                    end_free=start_free+bytes_to_get;
                    return (chunk_alloc(size, nobjs));
                }
                
            }
            //不加最后的return会报错
            return NULL;
        }
    };
    
    template<int inst>
    obj* _default_alloc_template<inst>::free_list[nfreelists]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    
    template<int inst>
    char* _default_alloc_template<inst>::start_free=0;
    
    template<int inst>
    char* _default_alloc_template<inst>::end_free=0;
    
    template<int inst>
    size_t _default_alloc_template<inst>::heap_size=0;
    
    
#ifdef simpleAlloc
    typedef _malloc_alloc_template<0> malloc_alloc;
#else
    typedef _default_alloc_template<0> malloc_alloc;
#endif
    
}

#endif /* myalloc_h */

