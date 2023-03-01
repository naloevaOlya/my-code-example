#pragma once

#include <iostream>

namespace s21 {
template <class T>
class vector {
 public:
    using value_type = T;
    using reference = value_type &;
    using const_reference = const reference;
    using size_type = size_t;

 private:
    size_type _size;
    size_type _capacity;
    value_type *arr;

 public:
    class iterator {
     protected:
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

    class const_iterator : public iterator {
     public:
        const_iterator(T *pointer, size_t position) : iterator(pointer, position){};
        const T &operator*() const { return *this->_pointer; };

        iterator get_iterator() { return iterator(this->_pointer, this->_position); };
    };

    vector() : _size(0), _capacity(0), arr(nullptr){};

    explicit vector(size_type n) : _size(n), _capacity(n), arr(n ? new value_type[n] : nullptr){};

    vector(std::initializer_list<value_type> const &items) : vector((size_type)items.size()) {
        int i{};
        for (auto iter = items.begin(); iter != items.end(); ++iter, ++i) {
            value_type val = *iter;
            at(i) = val;
        }
    };

    vector(const vector &v) : vector(v._size) {
        for (size_type i = 0; i < _size; i++) {
            at(i) = v.arr[i];
        }
    };

    vector(vector &&v) : _size(v._size), _capacity(v._capacity), arr(v.arr) {
        v.arr = nullptr;
        v._size = 0;
        v._capacity = 0;
    };

    ~vector() { delete[] arr; };

    vector &operator=(const vector &&v) {
        delete[](this->arr);
        this->arr = new value_type[v._size];
        this->_size = v._size;
        this->_capacity = v._capacity;
        for (size_type i = 0; i < _size; i++) {
            at(i) = v.arr[i];
        }
        return *this;
    };

    reference at(size_type pos) {
        if (pos >= _size) {
            throw std::out_of_range("Out of range method \'at\'");
        }
        return arr[pos];
    };

    inline reference operator[](size_type pos) { return at(pos); };

    inline const_reference front() { return arr[0]; }

    inline const_reference back() { return arr[_size - 1]; }

    inline iterator data() { return begin(); };

    inline iterator begin() { return iterator(&arr[0], 0); }

    inline iterator end() { return iterator(&arr[_size], _size); }

    inline const_iterator cbegin() { return const_iterator(&arr[0], 0); };

    inline const_iterator cend() { return const_iterator(&arr[_size], _size); };

    inline bool empty() { return _size == 0; }

    inline size_type size() { return _size; }

    inline size_type max_size() { return std::numeric_limits<intmax_t>::max() / sizeof(T); };

    void reserve(size_type size) {
        if (size > _capacity) {
            value_type *buff = new value_type[size];
            for (size_type i = 0; i < size; ++i) buff[i] = std::move(arr[i]);
            delete[] arr;
            arr = buff;
            _capacity = size;
        }
    };

    inline size_type capacity() { return _capacity; }

    void shrink_to_fit() {
        if (_size < _capacity) {
            value_type *buff = new value_type[_size];
            for (size_type i = 0; i < _size; ++i) buff[i] = std::move(arr[i]);
            delete[] arr;
            arr = buff;
            _capacity = _size;
        }
    };

    void clear() {
        while (_size) {
            erase(begin());
        }
    };

    iterator insert(iterator position, const_reference value) {
        size_type current_position = position.getPosition();
        reserve(_size + 1);
        _size++;
        value_type temp = at(current_position);
        at(current_position) = value;
        iterator return_value(&arr[current_position], current_position);
        for (size_type i = current_position + 1; i < _size; ++i) {
            value_type buff = at(i);
            at(i) = temp;
            temp = buff;
        }
        return return_value;
    };

    void erase(iterator position) {
        size_type current_position = position.getPosition();
        for (size_type i = current_position + 1; i < _size; i++) {
            arr[i - 1] = arr[i];
        }
        _size--;
    };

    void push_back(const_reference value) {
        if (_size == _capacity) {
            reserve(_size * 2);
        }
        arr[_size++] = value;
    };

    void pop_back() { erase(--this->end()); };

    void swap(vector &other) {
        value_type *swap_arr = arr;
        size_type swap_size = size();
        size_type swap_capacity = capacity();

        _size = other._size;
        _capacity = other._capacity;
        other._size = swap_size;
        other._capacity = swap_capacity;

        arr = other.arr;
        other.arr = swap_arr;
    };

    template <class... Args>
    iterator emplace(const_iterator pos, Args &&...args) {
        iterator tmp = pos.get_iterator();
        value_type array[] = {args...};
        for (value_type i : array) {
            tmp = insert(tmp, i);
        }
        return tmp;
    };

    template <class... Args>
    void emplace_back(Args &&...args) {
        value_type array[] = {args...};
        for (value_type i : array) {
            push_back(i);
        }
    };
};

}  // namespace s21
