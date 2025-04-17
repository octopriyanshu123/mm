#ifndef MY_ALLOC_HPP
#define MY_ALLOC_HPP

#include <iostream>
#include <mutex>
#include <map>
#include <memory>
#include <sys/mman.h>
#include <fcntl.h>
#include <cstdlib>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <cassert>
#include <cstdio>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <mutex>
#include <atomic>

// The main allocator class
// class MYALLOC
// {
// public:
//     // Constructor
//     MYALLOC();

//     // Destructor
//     ~MYALLOC();

//     static int init(int argc, char **argv);

//     // Allocate memory of a specified size
//     // void *allocate(size_t size);

//     int allocate(std::string type);

//     // Free the allocated memory
//     void deallocate(void *ptr);

//     // Return the current heap usage
//     size_t getHeapUsage() const;

//     // Optional: Swap between heap and stack memory
//     void swapStackToHeap(void *stack_ptr);

//     // Enable garbage collection (optional)
//     void garbageCollect();

//     virtual void moniterFile(const char *path, int interval);
//     bool writeFile(const char *filename, std::string str);

// private:
//     // Structure to represent a block of allocated memory
//     struct MemoryBlock
//     {
//         int id;
//         void *ptr ;
//         size_t size;       // Size of the block
//         bool is_free;      // Whether the block is free
//         MemoryBlock *next; // Pointer to the next memory block (for managing free blocks)
//     };
//     std::map<std::string, int> typeSizes;

//     // Method to manage the heap memory (could use sbrk or mmap)
//     void *requestMemory(size_t size);

//     // A simple linked list to track free blocks in the heap
//     MemoryBlock *free_list_;

//     // A map to track allocated memory blocks for easy deallocation
//     std::map<int, MemoryBlock *> allocations_;

//     // Mutex for thread-safety
//     std::mutex alloc_mutex_;

//     // Variable to track total heap memory usage
//     size_t heap_usage_;

//     // amount of memory avaliable list of the avaliable chunchs
//     size_t heap_avaliable;

//     // TOTAL amount of heap ask by system call
//     size_t heap_total_grown_;

//     // Optional: Garbage collector logic for memory management
//     void collectGarbage();
//     void *curr_break_point();
//     void *inc_break_point(size_t size);
//     void *dec_break_point(size_t size);

//     int generate_random_int(size_t length);
// };

// class MMap : public MYALLOC
// {
// public:
//     MMap(const char *filename) : filename(filename), src_ptr(nullptr), file_size(0), src_fd(-1)
//     {
//         std::cout << "MMap is created" << std::endl;
//     }
//     MMap()
//     {
//         std::cout << "MMap is created" << std::endl;
//     }
//     ~MMap()
//     {
//         if (src_ptr != nullptr)
//         {
//             munmap(src_ptr, file_size); // Unmap the source file
//         }
//         if (src_fd != -1)
//         {
//             close(src_fd); // Close the file descriptor
//         }
//         std::cout << "Deconstructor" << std::endl;
//     }

//     void moniterFile(const char *path, int interval);
//     bool writeFileMmap(const char *path, std::string str, std::string *strPtr, size_t size, bool newLine, bool append);

// private:
//     bool mapFileInMemory();
//     const char *filename;
//     void *src_ptr;    // Pointer to the memory-mapped file
//     size_t file_size; // Size of the file
//     int src_fd;
//     void printContent() const;
// };
class my_alloc
{
private:
    struct Chunk
    {
        void *start;
        size_t size;
    };

    struct Chunk_List
    {
        size_t count;
        Chunk chunks[5611520];
    };

    static void *heap_start;
    static size_t heap_size;
    static size_t total_allocated;
    static size_t currently_allocated;

    static Chunk_List alloced_chunks;
    static Chunk_List temp_chunks;
    static Chunk_List freed_chunks;

    static int chunks_list_insert(Chunk_List *list, void *start, size_t size);
    static void chunks_list_dump(const Chunk_List *list);
    static int chunks_list_find(Chunk_List *list, void *ptr);
    static void chunks_list_remove(Chunk_List *list, size_t index);
    static void chunk_list_merge(Chunk_List *dst, const Chunk_List *src);

public:
    static void *heap_alloc(size_t size);
    static void heap_free(void *ptr);
    static void heap_dump_stats();
    static void printme();
};


// Buffered File I/O Class
class BufferedFile {
    private:
        std::fstream file;
        std::vector<char> read_buffer;
        std::vector<char> write_buffer;
        size_t buffer_size;
        size_t read_pos;
        size_t write_pos;
        std::string mode;
    
        void flush_write_buffer() {
            if (write_pos > 0) {
                file.write(write_buffer.data(), write_pos);
                write_pos = 0;
            }
        }
    
        void fill_read_buffer() {
            file.read(read_buffer.data(), buffer_size);
            read_pos = 0;
        }
    
    public:
        BufferedFile(const std::string& filename, const std::string& mode = "r+", size_t buf_size = 4096)
            : buffer_size(buf_size), read_pos(0), write_pos(0), mode(mode) {
            
            std::ios_base::openmode fmode = std::ios_base::binary;
            if (mode.find('r') != std::string::npos) fmode |= std::ios_base::in;
            if (mode.find('w') != std::string::npos) fmode |= std::ios_base::out;
            if (mode.find('a') != std::string::npos) fmode |= std::ios_base::app;
            if (mode.find('t') != std::string::npos) fmode &= ~std::ios_base::binary;
    
            file.open(filename, fmode);
            if (!file.is_open()) {
                throw std::runtime_error("Failed to open file: " + filename);
            }
    
            read_buffer.resize(buffer_size);
            write_buffer.resize(buffer_size);
            if (mode.find('r') != std::string::npos) {
                fill_read_buffer();
            }
        }
    
        ~BufferedFile() {
            if (mode.find('w') != std::string::npos || mode.find('a') != std::string::npos) {
                flush_write_buffer();
            }
            file.close();
        }
    
        size_t read(char* dest, size_t size) {
            if (mode.find('r') == std::string::npos) {
                throw std::runtime_error("File not opened in read mode");
            }
    
            size_t total_read = 0;
            while (size > 0) {
                size_t available = file.gcount() - read_pos;
                if (available == 0) {
                    fill_read_buffer();
                    available = file.gcount();
                    if (available == 0) break; // EOF
                }
    
                size_t to_copy = std::min(size, available);
                std::memcpy(dest + total_read, read_buffer.data() + read_pos, to_copy);
                read_pos += to_copy;
                total_read += to_copy;
                size -= to_copy;
            }
    
            return total_read;
        }
    
        size_t write(const char* src, size_t size) {
            if (mode.find('w') == std::string::npos && mode.find('a') == std::string::npos) {
                throw std::runtime_error("File not opened in write/append mode");
            }
    
            size_t total_written = 0;
            while (size > 0) {
                size_t available = buffer_size - write_pos;
                if (available == 0) {
                    flush_write_buffer();
                    available = buffer_size;
                }
    
                size_t to_copy = std::min(size, available);
                std::memcpy(write_buffer.data() + write_pos, src + total_written, to_copy);
                write_pos += to_copy;
                total_written += to_copy;
                size -= to_copy;
            }
    
            return total_written;
        }
    
        void seek(size_t pos) {
            flush_write_buffer();
            file.seekg(pos);
            file.seekp(pos);
            read_pos = 0;
            file.gcount(); // Reset gcount
        }
    
        void sync() {
            flush_write_buffer();
            file.flush();
        }
    };
    
    // Shared Memory IPC Class
    class SharedMemory {
    private:
        std::string name;
        int fd;
        void* addr;
        size_t size;
        bool is_owner;
        static std::mutex creation_mutex;
    
        void cleanup() {
            if (addr != MAP_FAILED) {
                munmap(addr, size);
            }
            if (fd != -1) {
                close(fd);
            }
            if (is_owner) {
                shm_unlink(name.c_str());
            }
        }
    
    public:
        SharedMemory(const std::string& name, size_t size, bool create = false)
            : name("/" + name), fd(-1), addr(MAP_FAILED), size(size), is_owner(create) {
            
            std::lock_guard<std::mutex> lock(creation_mutex);
            
            if (create) {
                fd = shm_open(this->name.c_str(), O_CREAT | O_RDWR | O_EXCL, 0666);
                if (fd == -1 && errno == EEXIST) {
                    shm_unlink(this->name.c_str());
                    fd = shm_open(this->name.c_str(), O_CREAT | O_RDWR, 0666);
                }
            } else {
                fd = shm_open(this->name.c_str(), O_RDWR, 0666);
            }
    
            if (fd == -1) {
                throw std::runtime_error("shm_open failed: " + std::string(strerror(errno)));
            }
    
            if (create && ftruncate(fd, size) == -1) {
                cleanup();
                throw std::runtime_error("ftruncate failed: " + std::string(strerror(errno)));
            }
    
            addr = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
            if (addr == MAP_FAILED) {
                cleanup();
                throw std::runtime_error("mmap failed: " + std::string(strerror(errno)));
            }
        }
    
        ~SharedMemory() {
            cleanup();
        }
    
        void* get_address() const {
            return addr;
        }
    
        size_t get_size() const {
            return size;
        }
    
        template<typename T>
        T* get_as() {
            return reinterpret_cast<T*>(addr);
        }
    
        // Atomic operations for inter-process synchronization
        template<typename T>
        T atomic_load(size_t offset) {
            static_assert(std::is_integral<T>::value || std::is_pointer<T>::value, 
                         "Atomic operations only support integral and pointer types");
            return __atomic_load_n(reinterpret_cast<T*>(reinterpret_cast<char*>(addr) + offset), __ATOMIC_SEQ_CST);
        }
    
        template<typename T>
        void atomic_store(size_t offset, T value) {
            static_assert(std::is_integral<T>::value || std::is_pointer<T>::value, 
                         "Atomic operations only support integral and pointer types");
            __atomic_store_n(reinterpret_cast<T*>(reinterpret_cast<char*>(addr) + offset), value, __ATOMIC_SEQ_CST);
        }
    
        template<typename T>
        bool atomic_compare_exchange(size_t offset, T& expected, T desired) {
            static_assert(std::is_integral<T>::value || std::is_pointer<T>::value, 
                         "Atomic operations only support integral and pointer types");
            return __atomic_compare_exchange_n(
                reinterpret_cast<T*>(reinterpret_cast<char*>(addr) + offset),
                &expected,
                desired,
                false,
                __ATOMIC_SEQ_CST,
                __ATOMIC_SEQ_CST
            );
        }
    };
    
    

#endif // MY_ALLOC_HPP



