#ifndef MY_ALLOC_HPP
#define MY_ALLOC_HPP

#include <iostream>
#include <mutex>
#include <map>
#include <memory>
#include <cstdlib>


// The main allocator class
class MYALLOC
{
public:
    // Constructor
    MYALLOC();

    // Destructor
    ~MYALLOC();

    static int init(int argc, char **argv);

    // Allocate memory of a specified size
    void *allocate(size_t size);

    // Free the allocated memory
    void deallocate(void *ptr);

    // Return the current heap usage
    size_t getHeapUsage() const;

    // Optional: Swap between heap and stack memory
    void swapStackToHeap(void *stack_ptr);

    // Enable garbage collection (optional)
    void garbageCollect();

private:
    // Structure to represent a block of allocated memory
    struct MemoryBlock
    {
        std::string id;
        size_t size;       // Size of the block
        bool is_free;      // Whether the block is free
        MemoryBlock *next; // Pointer to the next memory block (for managing free blocks)
    };

    // Method to manage the heap memory (could use sbrk or mmap)
    void *requestMemory(size_t size);

    // A simple linked list to track free blocks in the heap
    MemoryBlock *free_list_;

    // A map to track allocated memory blocks for easy deallocation
    std::map<void *, MemoryBlock *> allocations_;

    // Mutex for thread-safety
    std::mutex alloc_mutex_;

    // Variable to track total heap memory usage
    size_t heap_usage_;

    // amount of memory avaliable list of the avaliable chunchs
    size_t heap_avaliable;

    // TOTAL amount of heap ask by system call 
    size_t heap_total_grown_;

    // Optional: Garbage collector logic for memory management
    void collectGarbage();
    void* curr_break_point();
    void* inc_break_point(size_t size);
    void* dec_break_point(size_t size);

    std::string generate_random_string(size_t length);
};

#endif // MY_ALLOC_HPP
