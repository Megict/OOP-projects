#pragma once
#include <stack>

template <class T,size_t BLOCK_COUNT>
class allocator
{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;

    allocator()
    {
        _used_blocks = nullptr;
        _free_count = 0;

        _used_blocks = (T*)malloc(sizeof(T) * (BLOCK_COUNT+1));
        if (_used_blocks == nullptr)
        {
            throw std::bad_alloc();
        }

        for (size_t i = 0; i < BLOCK_COUNT; ++i)
        {
            _free_blocks.push(&_used_blocks[i]);
        }
        _free_count = BLOCK_COUNT;

    }

    ~allocator()
    {
        free(_used_blocks);
    }

    T* allocate(size_t n)
    {
        T* ptr = nullptr;
        if (_free_count > 0)
        {
            for (size_t i = 1; i < n; ++i)
            {
                std::cout << _free_blocks.top() << " ";
                _free_blocks.pop();
            }

            ptr = (T*)_free_blocks.top();

            std::cout << _free_blocks.top() << " ";
            std::cout << std::endl;
            _free_blocks.pop();
        }
        else
        {
            throw std::bad_alloc();
        }
        _free_count -= n;

        return ptr;
    }

    template <class K>
    struct rebind
    {
        using other = allocator<K,BLOCK_COUNT>;
    };

    template <typename U,typename... Args>
    void construct(U* p, Args&&... args)
    {
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(pointer p)
    {
        p->~T();
    }

private:
    T* _used_blocks;
    std::stack<void*> _free_blocks;
    size_t _free_count;
};