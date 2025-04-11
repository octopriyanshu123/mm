#ifndef MY_ALLOC_HPP
#define MY_ALLOC_HPP

#include <iostream>
#include <mutex>
#include <map>
#include <memory>
#include <sys/mman.h>
#include <fcntl.h>
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
    // void *allocate(size_t size);

    int allocate(std::string type);

    // Free the allocated memory
    void deallocate(void *ptr);

    // Return the current heap usage
    size_t getHeapUsage() const;

    // Optional: Swap between heap and stack memory
    void swapStackToHeap(void *stack_ptr);

    // Enable garbage collection (optional)
    void garbageCollect();

    virtual void moniterFile(const char *path, int interval);
    bool writeFile(const char *filename, std::string str);

private:
    // Structure to represent a block of allocated memory
    struct MemoryBlock
    {
        int id;
        void *ptr ;
        size_t size;       // Size of the block
        bool is_free;      // Whether the block is free
        MemoryBlock *next; // Pointer to the next memory block (for managing free blocks)
    };
    std::map<std::string, int> typeSizes;

    // Method to manage the heap memory (could use sbrk or mmap)
    void *requestMemory(size_t size);

    // A simple linked list to track free blocks in the heap
    MemoryBlock *free_list_;

    // A map to track allocated memory blocks for easy deallocation
    std::map<int, MemoryBlock *> allocations_;

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
    void *curr_break_point();
    void *inc_break_point(size_t size);
    void *dec_break_point(size_t size);

    int generate_random_int(size_t length);
};

class MMap : public MYALLOC
{
public:
    MMap(const char *filename) : filename(filename), src_ptr(nullptr), file_size(0), src_fd(-1)
    {
        std::cout << "MMap is created" << std::endl;
    }
    MMap()
    {
        std::cout << "MMap is created" << std::endl;
    }
    ~MMap()
    {
        if (src_ptr != nullptr)
        {
            munmap(src_ptr, file_size); // Unmap the source file
        }
        if (src_fd != -1)
        {
            close(src_fd); // Close the file descriptor
        }
        std::cout << "Deconstructor" << std::endl;
    }

    void moniterFile(const char *path, int interval);
    bool writeFileMmap(const char *path, std::string str, std::string *strPtr, size_t size, bool newLine, bool append);

private:
    bool mapFileInMemory();
    const char *filename;
    void *src_ptr;    // Pointer to the memory-mapped file
    size_t file_size; // Size of the file
    int src_fd;
    void printContent() const;
};

#endif // MY_ALLOC_HPP
