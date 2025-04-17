# Custom Memory Allocation Library
## **Overview**
The `my_alloc` project aims to implement a custom memory allocation library that offers fine-grained control over memory management by memory allocator, file I/O, inter-process communication (IPC). The goal is to create a highly flexible, efficient, and scalable allocator with custom memory management techniques.

---

## **Features and Implementation**

### 1. **Memory Allocation Using `sbrk` and `brk` System Call**
   - **Purpose**: Implement a memory allocator `heep_alloc()` using `sbrk()` and `brk()` system calls to manage the program's heap.
   - **Challenges**: 
     - `sbrk` is deprecated on some platforms.
     - Fragmentation management.
     - Efficient block management.
     - Implement memory allocation using `sbrk` (or `mmap` as an alternative).
     - Consider using **buddy allocation**, **first-fit**, or **best-fit** strategies to reduce fragmentation.
     - Track allocated and free blocks using **free lists**.
---

### 2. **Free Memory After Use (Delete Memory)**
   - **Purpose**: Implement a `heep_free()` function to release memory back to reuse.
   - **Challenges**:
     - Handling fragmentation and reusing freed blocks.
     - Safely managing errors like double-free or invalid free.
     - Use a **linked list** or **free list** to manage free memory blocks.
     - Implement **safety checks** (e.g., double-free detection).
     - Merge adjacent free blocks to reduce fragmentation.

---

### 3. **File I/O: Reading and Writing Data Using a Buffer**
   - **Purpose**: Implement buffered reading and writing of data from/to files.
   - **Challenges**:
     - Efficient buffering to minimize system calls.
     - Handling large files.
     - Use **circular buffers** for continuous read/write operations.
     - Implement **memory-mapped files** (`mmap`) for large files to directly map them into memory, improving performance.
     - Implement **flushing** to ensure data integrity on crash or program exit.

---

### 4. **IPC: Shared Memory Region in RAM**
   - **Purpose**: Implement shared memory in RAM for inter-process communication (IPC).
   - **Challenges**:
     - Memory access synchronization across processes.
     - Preventing race conditions.
     - Use **POSIX shared memory** (`shm_open`, `mmap`) or **System V shared memory** (`shmget`, `shmat`).
     - Implement synchronization using **mutexes** or **semaphores** to ensure safe access.
     - Provide an API for easy memory allocation and deallocation in shared memory.

---

### 5. **Track Memory Usage in the Heap**
   - **Purpose**: Track allocated memory and monitor heap usage.
   - **Challenges**:
     - Efficient memory tracking without introducing overhead.
     - Managing fragmented memory.
     - Maintain **metadata** for each allocated block (e.g., size, status).
     - Use a **linked list** or **bitmap** to track the status of each block in the heap.
     - Implement debugging tools for memory fragmentation statistics.

---


### **Features**

#### 1. **Thread Safety**
   - Ensure that the allocator is thread-safe when used in multi-threaded environments.
  
- Use **mutexes** or **locks** to synchronize memory access in multi-threaded applications.
- Consider using **lock-free data structures** or **atomic operations** to reduce contention.

#### 2. **Performance Optimization**
   - Optimize the memory allocator for performance, reducing overhead and fragmentation.
- Implement **benchmarking tools** to test performance under various scenarios.
- Profile memory usage and fragmentation, and experiment with **block size** tuning.
- Consider using **slab allocation** for objects of fixed sizes to speed up allocation.

#### 3. **Memory Leak Detection**
   - Implement a tool to detect memory leaks in programs using your allocator.
- Keep track of all allocated blocks and check for any unfreed memory at program exit.
- Provide **error messages** or warnings if memory is not freed properly.
- Use **debugging tools** to inspect memory allocation patterns and detect leaks.
  
#### 5. **Documentation and Debugging Tools**
   - Provide comprehensive documentation for your memory allocator, and tools to assist with debugging.
- Provide detailed usage documentation for all features and API functions.
- Implement a **logging mechanism** to track memory allocations, deallocations, and errors.
- Create a **visualization tool** for monitoring heap usage and fragmentation over time.



---

### **Project Milestones**

1. **Basic Memory Allocation**: Implement `heap_alloc()`/`heap_free()` using `sbrk` or `mmap`.
2. **Memory Management Features**: Add free memory management, fragmentation handling, and memory tracking.
3. **File I/O**: Implement buffered read/write to files and memory-mapped files for large data.
4. **IPC Shared Memory**: Implement shared memory regions and synchronize inter-process communication.
7. **Documentation and Debugging Tools**: Create comprehensive documentation and debugging tools for users.


---


This documentation provides an overview of the key features and design decisions for the `my_alloc` project. As you implement each feature, refer to this documentation to ensure you stay on track and address potential challenges. It's important to incrementally build and test each component, starting with basic memory allocation and progressing to more advanced features like garbage collection and IPC. As the project grows, keep iterating, benchmarking, and optimizing for performance.
