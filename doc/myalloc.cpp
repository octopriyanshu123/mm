#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <iostream>

#define HEAP_CUP 640000
#define HEAP_ALLOCED_CAP 1024
#define HEAP_FREED_CAP 1024

#define CHUNKS_LIST_CUP 1024


typedef struct {
    void* start;
    size_t size;
} Chunk;

typedef struct {
   size_t count;
   Chunk chunks[HEAP_ALLOCED_CAP];
} Chunk_List;

char heap[HEAP_CUP] = {0};

size_t heap_size = 0;
// Heap_Chunk heap_alloced[HEAP_ALLOCED_CAP] = {0};
// Heap_Chunk heep_freed[HEAP_ALLOCED_CAP] = {0};
size_t heap_alloced_size = 0;
size_t heap_freed_size = 0;

Chunk_List alloced_chunks = {0};
Chunk_List freed_chunks = {0};


int chunks_list_insert(Chunk_List *list, void* start, size_t size){
    std::cout << "heap_alloced_size " << list->count << std::endl;
    assert(list->count < CHUNKS_LIST_CUP);
    list->chunks[list->count].start = start;
    list->chunks[list->count].size = size;
    for(size_t i= list->count ; 
        i>0 && list->chunks[i].start< list->chunks[i-1].start;
        --i){
        const Chunk t = list->chunks[i];
        list->chunks[i] =     list->chunks[i-1];
        list->chunks[i-1] = t;
    }
    list->count++;
    return 0 ;
}

void *heap_alloc(size_t size) {
    if (size < 1) {
        return nullptr;
    }
    assert(heap_size + size <= HEAP_CUP);
    void *ptr = heap + heap_size;
    heap_size += size;

    chunks_list_insert(&alloced_chunks,ptr,size);

    // const Heap_Chunk chunk = {
    //     .start = ptr,
    //     .size = size
    // };

    // assert(heap_alloced_size < HEAP_ALLOCED_CAP);
    // heap_alloced[heap_alloced_size++] = chunk;

    return ptr;
}

void chunks_list_dump(const Chunk_List *list) {
    std::cout << "list->count " << list->count << std::endl;
    for (size_t i = 0; i < list->count; i++) {
        std::cout << "Start " << list->chunks->start << " Size " << list->chunks->start << std::endl;
    }
}


heep_free(void * ptr){
    for(size_t =0; i<heap_alloced_size; i++){
        if(heap_alloced[i].start == ptr){

        }
    }
}

int main() {
    for (int i = 0; i < 100; i++) {
        void* p = heap_alloc(i);
        if (p == nullptr) {
            std::cout << "Fail to allocate the memory "<< std::endl;
        }
        else if(i%2==0){
           heep_free(p);
        }
        
    }

    // char* root = (char *)heap_alloc(26);
    // for (int i = 0; i < 26; i++) {
    //     root[i] = i + 'a';
    // }

    // for (int i = 0; i < 26; i++) {
    //     std::cout << root[i]; 
    // }
    // std::cout << std::endl;

    chunks_list_dump(&alloced_chunks);

    return 0;
}
