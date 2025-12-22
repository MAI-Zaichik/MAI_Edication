#pragma once
#include <memory_resource>
#include <vector>
#include <cstddef>
    
class Fmem_res : public std::pmr::memory_resource {
private:
    void* m_pool;
    std::size_t m_pool_size;
    std::size_t m_used;
    std::vector<std::pair<void*, std::size_t>> m_allocations;
    
protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;
    
public:
    Fmem_res(std::size_t pool_size);
    Fmem_res(const Fmem_res&) = delete;

    ~Fmem_res() override;

    Fmem_res& operator=(const Fmem_res&) = delete;
};