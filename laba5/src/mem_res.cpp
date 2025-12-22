#include "../include/mem_res.hpp"
#include <iostream>
#include <cstring>

Fmem_res::Fmem_res(std::size_t pool_size) 
    : m_pool_size(pool_size), m_used(0) {
    m_pool = ::operator new(pool_size);
}

Fmem_res::~Fmem_res() {
    ::operator delete(m_pool);
}

void* Fmem_res::do_allocate(std::size_t bytes, std::size_t alignment) {
    std::size_t aligned_bytes = (bytes + alignment - 1) & ~(alignment - 1);
    
    if (m_used + aligned_bytes > m_pool_size) {
        throw std::bad_alloc();
    }
    
    void* ptr = static_cast<char*>(m_pool) + m_used;
    m_allocations.emplace_back(ptr, aligned_bytes);
    m_used += aligned_bytes;
    
    return ptr;
}

void Fmem_res::do_deallocate(void* p, std::size_t bytes, std::size_t alignment) {
    for (auto it = m_allocations.begin(); it != m_allocations.end(); ++it) {
        if (it->first == p) {
            m_allocations.erase(it);
            break;
        }
    }
}

bool Fmem_res::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}