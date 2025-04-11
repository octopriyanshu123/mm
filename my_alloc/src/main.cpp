#include <iostream>
#include <memory>  
#include <vector>
#include "my_alloc.hpp"
using namespace std;



int main(int argc,char ** argv) {
    // init the MYALLOc
    int res = MYALLOC::init(argc,argv);
    
    if(res ==0){ 
        std::cout<<"MYALLOC::init success full"<<std::endl;
    }
    else{
        std::cout<<"MYALLOC::init Fails full"<<std::endl;
    }
    // object of the memory management
    MYALLOC mm;
    // you ask for the a 4 bit of memory sizeof(int) i will provide the starting of the memory address
    // make the int float string  Character Boolean Date/Time  Arrays Objectson the heap

    // int* ptr =  (int *)mm.allocate(sizeof(int)*2);
    // *ptr = 4;
    // ptr++;
    // *ptr = 5;
    // std::cout<<*ptr<<std::endl;
    // ptr--;
    // std::cout<<*ptr<<std::endl;
    // mm.deallocate(ptr);

    // moniter the file  at interval
    // read the file set the int 1 
    // const char* filename = "/home/octobotics/Desktop/Working/memory_management/mm/my_alloc/include/my_alloc.hpp";
    // mm.moniterFile(filename,5);

    // write the str on the file and control the condition 
    // const char* filename = "/home/octobotics/Desktop/Working/memory_management/mm/my_alloc/test/test.txt";
    // std::string str = "✅ Final Goal: writeFile() Method in MMap Class";
    // mm.writeFile(filename, str);



    
    return 0;
}