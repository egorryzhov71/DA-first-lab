#pragma once 
#include <memory_resource>
#include <iostream>
#include <map>
#include <iterator>
#include <memory>

class MemoryResource : public std::pmr::memory_resource {
private:
    std::map<void*, size_t> blocks;

public:
    void* do_allocate(size_t bytes, size_t alignment) override {
        void* ptr = std::malloc(bytes);
        if (!ptr) throw std::bad_alloc();

        blocks[ptr] = bytes;
        std::cout << "Выделено " << bytes << " байт" << std::endl;
        return ptr;
    }

    void do_deallocate(void* ptr, size_t bytes, size_t alignment) override {
        if (ptr && blocks.count(ptr)) {
            std::free(ptr);
            blocks.erase(ptr);
            std::cout << "Память освобождена" << std::endl;
        }
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }

    ~MemoryResource() {
        for (auto& [ptr, size] : blocks) {
            std::free(ptr);
        }
        std::cout << "Память очищена" << std::endl;
    }
};

template <typename T>
class Iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

private:
    T* ptr;
    size_t index;
    size_t max_size;
    
public:
    Iterator(T* p, size_t i, size_t max) : ptr(p), index(i), max_size(max) {}

    reference operator*() {
        if (index >= max_size) throw std::out_of_range("Выход за границу");
        return ptr[index];
    }

    Iterator& operator++() {
        index++;
        return *this;
    }

    Iterator operator++(int) {
        Iterator temp = *this;
        index++;
        return temp;
    }

    bool operator!=(const Iterator &other) const {
        return index != other.index;
    }

    bool operator==(const Iterator& other) const {
        return index == other.index;
    }
};

template<typename T>
class DynamicArray {
private:
    T* data;
    size_t size_;
    size_t capacity_;
    std::pmr::polymorphic_allocator<T> allocator;

    void resize() {
        size_t new_capacity = capacity_ * 2;
        T* new_data = allocator.allocate(new_capacity);

        for (size_t i = 0; i < size_; i++) {
            new (new_data + i) T(std::move(data[i]));
            data[i].~T();
        }

        allocator.deallocate(data, capacity_);

        data = new_data;
        capacity_ = new_capacity;
        std::cout << "Ёмкость увеличена до " << capacity_ << std::endl;
    }
    
public:
    using value_type = T;

    DynamicArray(size_t capacity, std::pmr::polymorphic_allocator<T> alloc = {})       
        : capacity_(capacity), size_(0), allocator(alloc) {
        data = allocator.allocate(capacity_);
        std::cout << "Создан массив ёмкостью " << capacity_ << std::endl;
    }

    ~DynamicArray() {
        for (size_t i = 0; i < size_; ++i) {
            data[i].~T();
        }
        allocator.deallocate(data, capacity_);
    }

    void push_back(const T& value) {
        if (size_ >= capacity_) {
            resize();
        }
        new (data + size_) T(value);
        size_++;
    }

    void push_back(T&& value) {
        if (size_ >= capacity_) {
            resize();
        }
        new (data + size_) T(std::move(value));
        size_++;
    }

    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Индекс за границами массива");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Индекс за границами массива");
        }
        return data[index];
    }

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }

    Iterator<T> begin() { return Iterator<T>(data, 0, size_); }
    Iterator<T> end() { return Iterator<T>(data, size_, size_); }
    Iterator<const T> begin() const { return Iterator<const T>(data, 0, size_); }
    Iterator<const T> end() const { return Iterator<const T>(data, size_, size_); }
};