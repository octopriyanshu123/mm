// #include <myalloc/my_alloc.hpp>
// #include <iostream>
// #include "ds.hpp"


// #include <memory>  

// using namespace std;

// int main(int argc,char ** argv) {
//     // init the MYALLOc
//     // int res = MYALLOC::init(argc,argv);
    
//     // if(res ==0){ 
//     //     std::cout<<"MYALLOC::init success full"<<std::endl;
//     // }
//     // else{
//     //     std::cout<<"MYALLOC::init Fails full"<<std::endl;
//     // }
//     // // object of the memory management
//     // MYALLOC mm;
//     // you ask for the a 4 bit of memory sizeof(int) i will provide the starting of the memory address
//     // make the int float string  Character Boolean Date/Time  Arrays Objectson the heap

//     // int* ptr =  (int *)mm.allocate(sizeof(int)*2);
//     // *ptr = 4;
//     // ptr++;
//     // *ptr = 5;
//     // std::cout<<*ptr<<std::endl;
//     // ptr--;
//     // std::cout<<*ptr<<std::endl;
//     // mm.deallocate(ptr);

    
//     // int id = mm.allocate("int");
//      //int id = mm.allocate("float");
//     //int id = mm.allocate("char");

//     //int val = mm.get(id);
//     // mm.set(id,5);
//     // mm.deallocate(id);






//     // moniter the file  at interval
//     // read the file set the int 1 
//     // const char* filename = "/home/octobotics/Desktop/Working/memory_management/mm/my_alloc/include/my_alloc.hpp";
//     // mm.moniterFile(filename,5);

//     // write the str on the file and control the condition 
//     // const char* filename = "/home/octobotics/Desktop/Working/memory_management/mm/my_alloc/test/test.txt";
//     // std::string str = "✅ Final Goal: writeFile() Method in MMap Class";
//     // mm.writeFile(filename, str);



    
//     return 0;
// }


// #include <iostream>
// #include <memory>  
// #include <vector>
// #include "my_alloc.hpp"
// using namespace std;



// int main(int argc,char ** argv) {
//     // init the MYALLOc
//     int res = MYALLOC::init(argc,argv);
    
//     if(res ==0){ 
//         std::cout<<"MYALLOC::init success full"<<std::endl;
//     }
//     else{
//         std::cout<<"MYALLOC::init Fails full"<<std::endl;
//     }
//     // object of the memory management
//     MYALLOC mm;
//     // you ask for the a 4 bit of memory sizeof(int) i will provide the starting of the memory address
//     // make the int float string  Character Boolean Date/Time  Arrays Objectson the heap

//     // int* ptr =  (int *)mm.allocate(sizeof(int)*2);
//     // *ptr = 4;
//     // ptr++;
//     // *ptr = 5;
//     // std::cout<<*ptr<<std::endl;
//     // ptr--;
//     // std::cout<<*ptr<<std::endl;
//     // mm.deallocate(ptr);

    
//     int id = mm.allocate("int");
//      //int id = mm.allocate("float");
//     //int id = mm.allocate("char");

//     //int val = mm.get(id);
//     // mm.set(id,5);
//     // mm.deallocate(id);






//     // moniter the file  at interval
//     // read the file set the int 1 
//     // const char* filename = "/home/octobotics/Desktop/Working/memory_management/mm/my_alloc/include/my_alloc.hpp";
//     // mm.moniterFile(filename,5);

//     // write the str on the file and control the condition 
//     // const char* filename = "/home/octobotics/Desktop/Working/memory_management/mm/my_alloc/test/test.txt";
//     // std::string str = "✅ Final Goal: writeFile() Method in MMap Class";
//     // mm.writeFile(filename, str);



    
//     return 0;
// }

// #include "my_alloc.hpp"
// #include <iostream>
// #include <unistd.h> // for sbrk

// #define N 10

// int main() {
//     void* current_brk = sbrk(0);
//     std::cout << "Starting Pointer of the heap is " << current_brk << std::endl;

//     void* ptrs[N] = {0};

//     for (int i = 0; i < N; i++) {
//         ptrs[i] = my_alloc::heap_alloc(i);
//     }

//     for (int i = 0; i < N; i++) {
//         my_alloc::heap_free(ptrs[i]);
//     }

//     void* p = my_alloc::heap_alloc(10);
//     if (p == NULL) {
//         std::cout << "Failed to allocate memory\n";
//     }

//     my_alloc::heap_dump_stats();
//     return 0;
// }


#include <my_alloc/my_alloc.hpp>
#include <iostream>
#include <unistd.h> // for sbrk
#include "ds.hpp"

#define N 10

int main() {
    void* current_brk = sbrk(0);
    std::cout << "Starting Pointer of the heap is " << current_brk << std::endl;

    void* ptrs[N] = {0};

    for (int i = 0; i < N; i++) {
        ptrs[i] = my_alloc::heap_alloc(i);
    }

    for (int i = 0; i < N; i++) {
        my_alloc::heap_free(ptrs[i]);
    }

    void* p = my_alloc::heap_alloc(100);
    if (p == NULL) {
        std::cout << "Failed to allocate memory\n";
    }

    my_alloc::heap_dump_stats();
    return 0;
}
