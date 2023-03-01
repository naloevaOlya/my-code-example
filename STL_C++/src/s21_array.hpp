#pragma once
#include <iostream>

namespace s21 {
template <class T, size_t _size>
class array {
 public:
    class iterator {
     private:
        T *_pointer;
        size_t _position{0};

     public:
        iterator(T *pointer, size_t position) : _pointer(pointer), _position(position){};

        T &operator*() { return *_pointer; }

        iterator &operator++() {
            _pointer++;
            _position++;
            return *this;
        }

        iterator &operator--() {
            _pointer--;
            _position--;
            return *this;
        }

        bool operator==(const iterator &t) const { return t._pointer == this->_pointer; }

        bool operator!=(const iterator &t) const { return t._pointer != this->_pointer; }

        size_t getPosition() const { return _position; }
    };

 public:
    using value_type = T;
    using reference = value_type &;
    using const_reference = const reference;
    using const_iterator = const iterator;
    using size_type = size_t;

 private:
    value_type arr[_size];

 public:
    array(){};

    ~array(){};

    inline size_type size() const { return _size; };
    inline size_type max_size() const { return size(); };

    array(const array &other) {
        for (size_type i = 0; i < other.size(); i++) {
            at(i) = other.arr[i];
        }
    };

    array(array &&other) { swap_without_deletion(other); };

    array(std::initializer_list<value_type> const &items) {
        size_type i{};
        for (auto iter = items.begin(); iter != items.end(); ++iter, ++i) {
            value_type val = *iter;
            at(i) = val;
        }
    };

    array operator=(array &&other) {
        swap_without_deletion(other);
        return *this;
    };

    inline bool empty() { return this->size() == 0; };

    reference at(size_type pos) {
        if (!(pos < _size)) {
            throw std::out_of_range("Out of range method \'at\' ");
        }
        return arr[pos];
    };

    inline reference operator[](size_type pos) { return at(pos); };

    inline const_reference front() { return arr[0]; };

    inline const_reference back() { return arr[_size - 1]; };

    inline iterator data() { return begin(); };

    inline iterator begin() { return iterator(&arr[0], 0); };

    inline iterator end() { return iterator(&arr[_size], _size); };

    void swap(array &other) {
        value_type swap_arr[this->size()];
        for (size_type i = 0; i < other.size(); i++) {
            swap_arr[i] = this->arr[i];
            at(i) = other.arr[i];
            other.arr[i] = swap_arr[i];
        }
    };

    void fill(const_reference value) {
        for (auto i = 0; i != this->size(); ++i) {
            at(i) = value;
        }
    };

 private:
    void swap_without_deletion(const array &other) {
        value_type swap_arr[this->size()];
        for (size_type i = 0; i < other.size(); i++) {
            at(i) = other.arr[i];
        }
    };
};
}  // namespace s21
