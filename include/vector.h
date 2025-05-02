#pragma once

template <typename T>
class Vector {
public:
    T* data;            // ��������� �� ������ ���������
    int size;
    int capacity;

    Vector(int capacity = 1, int size = 0) {
        data = new T[capacity];
        this->size = size;
        this->capacity = capacity;
    }

    ~Vector() {
        delete[] data;
    }

    Vector& operator=(Vector& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new T[capacity];
            for (size_t i = 0; i < capacity; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    void resize(int new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

    void resize(int new_capacity, T val) {
        T* new_data = new T[new_capacity];
        for (int i = 0; i < new_capacity; ++i) {
            new_data[i] = val;
        }
        delete[] data;
        data = new_data;
        size = new_capacity;
        capacity = new_capacity;
    }

    void push_back(T value) {
        if (size >= capacity) {
            int new_capacity = capacity * 2;
            resize(new_capacity);
        }
        data[size++] = value;
    }

    void pop_back() {
        if (size == 0) {
            throw std::out_of_range("Vector is empty");
        }
        --size;
    }

    T& operator[](size_t index) {
        if (index >= capacity) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= capacity) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t get_size() const noexcept {
        return size;
    }

    void clear() noexcept {
        size = 0;
    }

    bool empty() const noexcept {
        return (size == 0);
    }
};