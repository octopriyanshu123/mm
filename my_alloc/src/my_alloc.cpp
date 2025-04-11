#include "my_alloc.hpp"
#include <iostream>
#include <stdexcept>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <cassert>
#include <cstring>
#include <random>
#include <sys/stat.h>
#include <thread>

MYALLOC::MYALLOC() : heap_total_grown_(0), heap_usage_(0)
{
    typeSizes["int"] = 4;
    typeSizes["float"] = 8;
    typeSizes["bool"] = 1;
    typeSizes["char"] = 1;

    // Create a new MemoryBlock on the heap
    MemoryBlock *no_allocation = new MemoryBlock;

    no_allocation->id = generate_random_int(5); // Random 5-digit ID
    no_allocation->size = 0;
    no_allocation->next = nullptr;
    no_allocation->ptr = sbrk(0); // Get current program break
    no_allocation->is_free = true;

    // Insert into the map
    allocations_[no_allocation->id] = no_allocation;

    std::cout << "MyAllocator initialized!" << std::endl;
}

MYALLOC::~MYALLOC()
{

    std::cout << "Heap grow upto " << heap_total_grown_ << std::endl;

    std::cout << "Curr Heap " << heap_usage_ << std::endl;
    dec_break_point(heap_total_grown_);
    std::cout << "Heap grow upto " << heap_total_grown_ << std::endl;

    std::cout << "Curr Heap " << heap_usage_ << std::endl;

    std::cout << "MyAllocator dinitialized!" << std::endl;
}

int MYALLOC::init(int argc, char **argv)
{
    if (argc < 1)
    {
        return 1;
    }
    return 0;
}

// void *MYALLOC::allocate(size_t size)
// {

//     // check wether the heep is growth upto the required size or not
//     if (size > heap_total_grown_)
//     {
//         std::cout << "Heep is not growthe up to size ask" << std::endl;
//         inc_break_point(size + 1);
//     }
//     // else{
//     //     // check whether there is avaliabl space to allocate the memory
//     //     if()
//     // }

//     //

//     static MemoryBlock curr_allocation;
//     curr_allocation.id = generate_random_string(10);
//     curr_allocation.is_free = false;
//     curr_allocation.size = size;

//     void *prev_break;
//     void *new_break;
//     prev_break = curr_break_point();
//     new_break = inc_break_point(size);

//     if (new_break == (void *)-1)
//     {
//         perror("sbrk failed");
//         return nullptr;
//     }
//     return prev_break;
// }

int MYALLOC::allocate(std::string type)
{

    int size = typeSizes[type];

    if (size > heap_total_grown_)
    {
        std::cout << "Heep is not growthe up to size ask" << std::endl;
        inc_break_point(size);
    }

    return 0;
}

void *MYALLOC::curr_break_point()
{
    return sbrk(0);
}

void *MYALLOC::inc_break_point(size_t size)
{
    heap_total_grown_ += size;
    heap_usage_ += size;
    return sbrk(size);
}

void *MYALLOC::dec_break_point(size_t size)
{
    heap_usage_ -= size;
    return sbrk(-size);
}

void MYALLOC::deallocate(void *ptr)
{
}

int MYALLOC::generate_random_int(size_t length)
{
    if (length == 0 || length > 9)
    {
        throw std::invalid_argument("Length must be between 1 and 9 for a valid int.");
    }

    std::random_device random_device;
    std::mt19937 generator(random_device());

    // Calculate the lower and upper bounds based on the length
    int lower = static_cast<int>(std::pow(10, length - 1));
    int upper = static_cast<int>(std::pow(10, length)) - 1;

    std::uniform_int_distribution<> distribution(lower, upper);

    return distribution(generator);
}

void MYALLOC::moniterFile(const char *path, int interval)
{
    std::unique_ptr<MYALLOC> allocator = std::make_unique<MMap>(path);
    allocator->moniterFile(path, 1);
}

bool MYALLOC::writeFile(const char *path, std::string str)
{
    std::string *strPtr = &str;
    size_t size = str.size();
    bool newLine = false;
    bool append = false;
    // std::unique_ptr<MYALLOC> writeFileallocator = std::make_unique<MMap>(path);
    MMap m;
    m.writeFileMmap(path, str, strPtr, size, newLine, append);

    return true;
}

//------------------------------------------------MMap----------------------------------------------------

void MMap::moniterFile(const char *path, int interval)
{
    std::cout << "moniterFile" << std::endl;
    int i = 0;
    MMap::mapFileInMemory();
    MMap::printContent();
    while (i++ < 5)
    {
        // Set up and print file content
        if (MMap::mapFileInMemory())
        {
            MMap::printContent();
        }
        else
        {
            std::cerr << "File setup failed." << std::endl;
        }

        // Wait for the specified interval (in seconds)
        std::this_thread::sleep_for(std::chrono::seconds(interval));
    }
}

void MMap::printContent() const
{
    if (src_ptr != nullptr)
    {
        std::cout.write(reinterpret_cast<char *>(src_ptr), file_size);
        std::cout << std::endl;
    }
    else
    {
        std::cerr << "Error: File not mapped correctly." << std::endl;
    }
}

bool MMap::mapFileInMemory()
{
    std::cout << filename << std::endl;
    src_fd = open(filename, O_RDONLY);
    if (src_fd == -1)
    {
        perror("Error opening source file");
        return false;
    }

    // Get the size of the source file
    struct stat st;
    if (fstat(src_fd, &st) == -1)
    {
        perror("Error getting file size");
        close(src_fd);
        return false;
    }
    file_size = st.st_size;

    // Memory map the source file
    src_ptr = mmap(nullptr, file_size, PROT_READ, MAP_PRIVATE, src_fd, 0);
    if (src_ptr == MAP_FAILED)
    {
        perror("Error mapping source file to memory");
        close(src_fd);
        return false;
    }
    return true;
}

bool MMap::writeFileMmap(const char *path, std::string str, std::string *strPtr, size_t size, bool newLine, bool append)
{

    // 1. Determine write mode
    int flags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC);
    int dest_fd = open(path, flags, 0644);
    if (dest_fd == -1)
    {
        perror("Error opening destination file for writing");
        return false;
    }

    // 2. If appending, and newline flag is true, add a newline if needed
    if (append && newLine)
    {
        off_t current_offset = lseek(dest_fd, 0, SEEK_END);
        if (current_offset > 0)
        {
            const char *newline = "\n";
            if (write(dest_fd, newline, 1) == -1)
            {
                perror("Error writing newline to destination file");
                close(dest_fd);
                return false;
            }
        }
    }

    // 3. Choose content to write (string vs pointer)
    const char *data = nullptr;
    size_t write_size = 0;

    if (strPtr)
    {
        data = strPtr->c_str();
        write_size = size;
    }
    else
    {
        data = str.c_str();
        write_size = size;
    }

    // 4. Perform the write
    if (write(dest_fd, data, write_size) == -1)
    {
        perror("Error writing content to destination file");
        close(dest_fd);
        return false;
    }

    // 5. Clean up
    close(dest_fd);
    return true;
}
