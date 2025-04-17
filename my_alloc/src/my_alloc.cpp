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

// int MYALLOC::generate_random_int(size_t length)
// {
//     if (length == 0 || length > 9)
//     {
//         throw std::invalid_argument("Length must be between 1 and 9 for a valid int.");
//     }

//     std::random_device random_device;
//     std::mt19937 generator(random_device());

//     // Calculate the lower and upper bounds based on the length
//     int lower = static_cast<int>(std::pow(10, length - 1));
//     int upper = static_cast<int>(std::pow(10, length)) - 1;

//     std::uniform_int_distribution<> distribution(lower, upper);

//     return distribution(generator);
// }

// void MYALLOC::moniterFile(const char *path, int interval)
// {
//     std::unique_ptr<MYALLOC> allocator = std::make_unique<MMap>(path);
//     allocator->moniterFile(path, 1);
// }

// bool MYALLOC::writeFile(const char *path, std::string str)
// {
//     std::string *strPtr = &str;
//     size_t size = str.size();
//     bool newLine = false;
//     bool append = false;
//     // std::unique_ptr<MYALLOC> writeFileallocator = std::make_unique<MMap>(path);
//     MMap m;
//     m.writeFileMmap(path, str, strPtr, size, newLine, append);

//     return true;
// }

// //------------------------------------------------MMap----------------------------------------------------

// void MMap::moniterFile(const char *path, int interval)
// {
//     std::cout << "moniterFile" << std::endl;
//     int i = 0;
//     MMap::mapFileInMemory();
//     MMap::printContent();
//     while (i++ < 5)
//     {
//         // Set up and print file content
//         if (MMap::mapFileInMemory())
//         {
//             MMap::printContent();
//         }
//         else
//         {
//             std::cerr << "File setup failed." << std::endl;
//         }

//         // Wait for the specified interval (in seconds)
//         std::this_thread::sleep_for(std::chrono::seconds(interval));
//     }
// }

// void MMap::printContent() const
// {
//     if (src_ptr != nullptr)
//     {
//         std::cout.write(reinterpret_cast<char *>(src_ptr), file_size);
//         std::cout << std::endl;
//     }
//     else
//     {
//         std::cerr << "Error: File not mapped correctly." << std::endl;
//     }
// }

// bool MMap::mapFileInMemory()
// {
//     std::cout << filename << std::endl;
//     src_fd = open(filename, O_RDONLY);
//     if (src_fd == -1)
//     {
//         perror("Error opening source file");
//         return false;
//     }

//     // Get the size of the source file
//     struct stat st;
//     if (fstat(src_fd, &st) == -1)
//     {
//         perror("Error getting file size");
//         close(src_fd);
//         return false;
//     }
//     file_size = st.st_size;

//     // Memory map the source file
//     src_ptr = mmap(nullptr, file_size, PROT_READ, MAP_PRIVATE, src_fd, 0);
//     if (src_ptr == MAP_FAILED)
//     {
//         perror("Error mapping source file to memory");
//         close(src_fd);
//         return false;
//     }
//     return true;
// }

// bool MMap::writeFileMmap(const char *path, std::string str, std::string *strPtr, size_t size, bool newLine, bool append)
// {

//     // 1. Determine write mode
//     int flags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC);
//     int dest_fd = open(path, flags, 0644);
//     if (dest_fd == -1)
//     {
//         perror("Error opening destination file for writing");
//         return false;
//     }

//     // 2. If appending, and newline flag is true, add a newline if needed
//     if (append && newLine)
//     {
//         off_t current_offset = lseek(dest_fd, 0, SEEK_END);
//         if (current_offset > 0)
//         {
//             const char *newline = "\n";
//             if (write(dest_fd, newline, 1) == -1)
//             {
//                 perror("Error writing newline to destination file");
//                 close(dest_fd);
//                 return false;
//             }
//         }
//     }

//     // 3. Choose content to write (string vs pointer)
//     const char *data = nullptr;
//     size_t write_size = 0;

//     if (strPtr)
//     {
//         data = strPtr->c_str();
//         write_size = size;
//     }
//     else
//     {
//         data = str.c_str();
//         write_size = size;
//     }

//     // 4. Perform the write
//     if (write(dest_fd, data, write_size) == -1)
//     {
//         perror("Error writing content to destination file");
//         close(dest_fd);
//         return false;
//     }

//     // 5. Clean up
//     close(dest_fd);
//     return true;
// }

// Initialize static members
void* my_alloc::heap_start = nullptr;
size_t my_alloc::heap_size = 0;
size_t my_alloc::total_allocated = 0;
size_t my_alloc::currently_allocated = 0;

my_alloc::Chunk_List my_alloc::alloced_chunks = {0};
my_alloc::Chunk_List my_alloc::temp_chunks = {0};
my_alloc::Chunk_List my_alloc::freed_chunks = {0};

int my_alloc::chunks_list_insert(Chunk_List* list, void* start, size_t size) {
    assert(list->count < 5611520);
    list->chunks[list->count].start = start;
    list->chunks[list->count].size = size;

    for (size_t i = list->count; i > 0 && list->chunks[i].start < list->chunks[i - 1].start; --i) {
        Chunk t = list->chunks[i];
        list->chunks[i] = list->chunks[i - 1];
        list->chunks[i - 1] = t;
    }

    list->count++;
    return 0;
}

void my_alloc::chunks_list_dump(const Chunk_List* list) {
    printf("Count %zu\n", list->count);
    for (size_t i = 0; i < list->count; i++) {
        printf("Start %p Size %zu\n", list->chunks[i].start, list->chunks[i].size);
    }
}

int my_alloc::chunks_list_find(Chunk_List* list, void* ptr) {
    for (size_t i = 0; i < list->count; ++i) {
        if (list->chunks[i].start == ptr) {
            return (int)i;
        }
    }
    return -1;
}

void my_alloc::chunks_list_remove(Chunk_List* list, size_t index) {
    assert(index < list->count);
    for (size_t i = index; i < list->count - 1; i++) {
        list->chunks[i] = list->chunks[i + 1];
    }
    list->count--;
}

void my_alloc::chunk_list_merge(Chunk_List* dst, const Chunk_List* src) {
    dst->count = 0;
    for (size_t i = 0; i < src->count; ++i) {
        const Chunk chunk = src->chunks[i];

        if (dst->count > 0) {
            Chunk* top_chunk = &dst->chunks[dst->count - 1];

            if ((char*)top_chunk->start + top_chunk->size == chunk.start) {
                top_chunk->size += chunk.size;
            } else {
                chunks_list_insert(dst, chunk.start, chunk.size);
            }
        } else {
            chunks_list_insert(dst, chunk.start, chunk.size);
        }
    }
}

void* my_alloc::heap_alloc(size_t size) {
    if (size < 1) {
        return nullptr;
    }

    if (heap_start == nullptr) {
        heap_start = sbrk(0);
        if (heap_start == (void*)-1) {
            return nullptr;
        }
    }

    chunk_list_merge(&temp_chunks, &freed_chunks);
    freed_chunks = temp_chunks;

    for (size_t i = 0; i < freed_chunks.count; ++i) {
        const Chunk chunk = freed_chunks.chunks[i];

        if (chunk.size >= size) {
            chunks_list_remove(&freed_chunks, i);

            const size_t tail_size = chunk.size - size;
            chunks_list_insert(&alloced_chunks, chunk.start, size);
            total_allocated += size;
            currently_allocated += size;

            if (tail_size > 0) {
                chunks_list_insert(&freed_chunks, (char*)chunk.start + size, tail_size);
            }

            return chunk.start;
        }
    }

    void* current_brk = sbrk(0);
    if (current_brk == (void*)-1) {
        return nullptr;
    }

    void* new_mem = sbrk(size);
    if (new_mem == (void*)-1) {
        return nullptr;
    }

    chunks_list_insert(&alloced_chunks, new_mem, size);
    heap_size += size;
    total_allocated += size;
    currently_allocated += size;

    return new_mem;
}

void my_alloc::heap_free(void* ptr) {
    if (ptr != nullptr) {
        const int index = chunks_list_find(&alloced_chunks, ptr);
        if (index >= 0) {
            currently_allocated -= alloced_chunks.chunks[index].size;
            chunks_list_insert(&freed_chunks,
                alloced_chunks.chunks[index].start,
                alloced_chunks.chunks[index].size);
            chunks_list_remove(&alloced_chunks, (size_t)index);
        }
    }
}

void my_alloc::heap_dump_stats() {
    printf("\nHeap Statistics:\n");
    printf("Total heap size: %zu bytes\n", heap_size);
    printf("Total allocated: %zu bytes\n", total_allocated);
    printf("Currently allocated: %zu bytes\n", currently_allocated);
    printf("Allocated chunks: %zu\n", alloced_chunks.count);
    chunks_list_dump(&alloced_chunks);
    printf("Free chunks: %zu\n", freed_chunks.count);
    chunks_list_dump(&freed_chunks);
}




