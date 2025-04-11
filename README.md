# memory_management

 Memory Types in C++
 Stack Memory
 Heap Memory
Data Section (Static/Global Memory)  

 Dynamic Memory Allocation in C++
Memory Leaks and Dangling Pointers
a) Memory Leak
A memory leak occurs when dynamically allocated memory is not properly freed. This means that memory is still reserved but is no longer accessible to the program, causing inefficient use of memory.


b) Dangling Pointer
A dangling pointer occurs when a pointer continues to reference a memory location that has already been freed. Dereferencing a dangling pointer can cause undefined behavior.

Example of a dangling pointer:

cpp
Copy
int* ptr = new int(10); 
delete ptr; 
*ptr = 5;  // Dangerous, as ptr is now a dangling pointer
To avoid dangling pointers, set the pointer to nullptr after calling delete.

cpp
Copy
int* ptr = new int(10);
delete ptr;
ptr = nullptr;  // Safeguard against dangling pointer


4. Smart Pointers (C++11 and Beyond)
To simplify memory management and reduce common errors like memory leaks and dangling pointers, C++11 introduced smart pointers, which are objects that manage the memory of dynamically allocated objects. They automatically free the memory when no longer needed.

There are three main types:

std::unique_ptr: Represents exclusive ownership of a dynamically allocated object.

std::shared_ptr: Represents shared ownership of a dynamically allocated object.

std::weak_ptr: Used to break circular references in shared pointers.

interview Questions 
Mention 3 way to turn your program in the segmentation fault s

RAII

Working of the garbage Coloctor 
refer Count 


process is the 
type 
independent and Cooperating
IPC: To Share Memory Or To Send Messages
Inter process communition [Inter process communition ](https://youtu.be/Y2mDwW2pMv4?si=jYeM3tQejO5Z-dMK)

variable size [Link](https://youtu.be/hwyRnHA54lI?si=qn6g7hcYMGD9lqjz)

[Leak-Freedom in C++.](https://youtu.be/JfmTagWcqoE?si=OUhyzxISWNXM7GzI)


https://danluu.com/malloc-tutorial/

Icp Type 
shared memory 
Messing passing 
