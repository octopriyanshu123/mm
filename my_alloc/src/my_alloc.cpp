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

MYALLOC::MYALLOC() : heap_total_grown_(0) , heap_usage_(0),MYALLOC::MemoryBlock.next(nullptr) {
    std::cout << "MyAllocator initialized!" << std::endl;
}

MYALLOC::~MYALLOC(){
    std::cout<<"Heap grow upto "<<heap_total_grown_<<std::endl;
    
    std::cout<<"Curr Heap "<<heap_usage_<<std::endl;

    std::cout << "MyAllocator dinitialized!" << std::endl;

}

int MYALLOC::init(int argc,char** argv){
    if(argc<1){
        return 1;
    }
    return 0 ;
}

void* MYALLOC::allocate(size_t size){
 
    // check wether the heep is growth upto the required size or not 
    if(size>heap_total_grown_){
        std::cout << "Heep is not growthe up to size ask" << std::endl;
        inc_break_point(size + 1);
    }
    // else{
    //     // check whether there is avaliabl space to allocate the memory 
    //     if()
    // }


    //


    static MemoryBlock curr_allocation ;
    curr_allocation.id = generate_random_string(10);
    curr_allocation.is_free = false;
    curr_allocation.size = size;


    void *prev_break;
    void *new_break;
    prev_break = curr_break_point();
    new_break = inc_break_point(size);
    if (new_break == (void*)-1) {
        perror("sbrk failed");
        return nullptr;
    }
    return prev_break ;
}

void* MYALLOC::curr_break_point(){
    return sbrk(0);
}

void* MYALLOC::inc_break_point(size_t size){
    heap_total_grown_+= size;
    heap_usage_+= size;
    return sbrk(size);
}


void* MYALLOC::dec_break_point(size_t size){
    heap_usage_+= size;
    return sbrk(size);
}

void MYALLOC::deallocate(void *ptr){
    dec_break_point(-8);
}


std::string MYALLOC::generate_random_string(size_t length) {
    const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::string random_string;
    for (size_t i = 0; i < length; ++i) {
        random_string += characters[distribution(generator)];
    }

    return random_string;
}
