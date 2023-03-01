#pragma once

#include <iostream>

namespace s21 {

template <class T>
class node {
 public:
    node *_next;
    node *_prev;
    T _value;

    node() : _value(T()), _next(nullptr), _prev(nullptr){};
    explicit node(T value) : node() { _value = value; };
    node(T value, node *next) : node(value) { _next = next; };
};

template <class T>
class list {
 public:
    class iterator {
     protected:
        node<T> *_pointer;

     public:
        explicit iterator(node<T> *pointer = nullptr) : _pointer(pointer){};

        T &operator*() { return _pointer->_value; }

        iterator &operator++() {
            _pointer = _pointer->_next;
            return *this;
        }

        iterator &operator--() {
            _pointer = _pointer->_prev;
            return *this;
        }

        bool operator==(const iterator &t) const { return t._pointer == this->_pointer; }

        bool operator!=(const iterator &t) const { return t._pointer != this->_pointer; }

        node<T> *get() { return _pointer; }
    };

    class const_iterator : public iterator {
     public:
        explicit const_iterator(node<T> *pointer = nullptr) : iterator(pointer){};
        const T &operator*() const { return this->_pointer->_value; };
        iterator get_iterator() { return iterator(this->_pointer); };
    };

    using value_type = T;
    using reference = value_type &;
    using const_reference = const reference;
    using size_type = size_t;
    using node = s21::node<T>;

 private:
    node *_head;
    node *_tail;

 public:
    list() : _head(new node()), _tail(_head){};

    explicit list(size_type n) : list() {
        for (size_type i = 0; i < n; i++) {
            value_type new_val{};
            push_front(new_val);
        }
    };

    list(const std::initializer_list<value_type> &items) : list() {
        for (auto iter = items.begin(); iter != items.end(); ++iter) {
            value_type val = *iter;
            push_back(val);
        }
    };

    list(const list &l) : list() {
        iterator l_end(l._tail->_next);
        for (iterator iter(l._head); iter != l_end; ++iter) {
            push_back(*iter);
        }
    };

    list(list &&l) : _head(l._head), _tail(l._tail) {
        l._head = nullptr;
        l._tail = nullptr;
    };

    ~list() {
        clear();
        delete (_tail);
        _head = _tail = nullptr;
    }

    list &operator=(list &&other) {
        this->_head = other._head;
        this->_tail = other._tail;
        other._head = other._tail = nullptr;
        return *this;
    };

    inline bool empty() { return _head->_next == nullptr; };

    size_type size() {
        size_type _size = 0;
        iterator iter_end = end();
        for (iterator iter = begin(); iter != iter_end; ++iter) {
            _size += 1;
        }
        return _size;
    };

    inline size_type max_size() { return std::numeric_limits<intmax_t>::max() / sizeof(node); };

    inline const_reference front() { return _head->_value; };

    inline const_reference back() { return _tail->_value; };

    void clear() noexcept {
        while (_head && _head->_next) {
            pop_back();
        }
    };

    void push_back(const_reference value) {
        node *new_node = new node(value);
        if (empty()) {
            new_node->_next = _head;
            _head->_prev = nullptr;
            _head = _tail = new_node;
        } else {
            node *nill = _tail->_next;
            node *prev = _tail;
            nill->_prev = new_node;
            new_node->_next = nill;
            new_node->_prev = _tail;
            _tail = new_node;
            prev->_next = new_node;
        }
    };

    void push_front(const_reference value) {
        node *new_node = new node(value);
        if (empty()) {
            new_node->_next = _head;
            _head->_prev = new_node;
            _head = _tail = new_node;
        } else {
            _head->_prev = new_node;
            new_node->_next = _head;
            _head = new_node;
        }
        _head->_prev = nullptr;
    };

    void pop_back() {
        node *nill = _tail->_next;

        if (size() == 1) {
            delete (_head);
            _head = _tail = nill;
        } else {
            node *prev = _tail->_prev;
            delete (_tail);
            prev->_next = nill;
            nill->_prev = prev;
            _tail = prev;
        }
    };

    void pop_front() {
        node *new_head = _head->_next;
        delete (_head);
        _head = new_head;
        _head->_prev = nullptr;

        if (size() == 1 || empty()) {
            _tail = _head;
        }
    };

    void swap(list &other) noexcept {
        node *swap_node = _head;
        _head = other._head;
        other._head = swap_node;

        swap_node = _tail;
        _tail = other._tail;
        other._tail = swap_node;
    };

    void sort() {
        node *left = _head, *right = _head->_next;
        value_type temp;
        iterator end_iter = end();
        for (iterator iter_left(left); iter_left != end_iter; ++iter_left) {
            for (iterator iter_right(right); iter_right != end_iter; ++iter_right) {
                if (left->_value > right->_value) {
                    temp = left->_value;
                    left->_value = right->_value;
                    right->_value = temp;
                }
                right = right->_next;
            }
            left = left->_next;
            right = left->_next;
        }
    };

    void merge(list &other) {
        for (iterator iter = other.begin(), iter_end = other.end(); iter != iter_end; ++iter) {
            this->push_back(*iter);
        }
        other.clear();
    };

    void reverse() noexcept {
        bool evenSize = size() % 2 == 0;
        size_type middle = evenSize ? size() / 2 : size() / 2 + 1;
        iterator left = begin(), right = --end();
        for (size_type i = 1; i <= middle; i++, ++left, --right) {
            value_type temp = *left;
            *left = *right;
            *right = temp;
        }
    };

    void erase(iterator position) {
        if (position == begin()) {
            pop_front();
        } else if (position == --end()) {
            pop_back();
        } else {
            node *prev = position.get()->_prev;
            node *next = position.get()->_next;

            delete (position.get());

            prev->_next = next;
            next->_prev = prev;
        }
    };

    void unique() {
        for (iterator left = begin(), right = ++begin(); right != end(); ++left, ++right) {
            while (*left == *right && right != end()) {
                iterator tmp = right;
                ++tmp;
                erase(right);
                right = tmp;
            }
            if (right == end()) {
                break;
            }
        }
    };

    iterator insert(iterator position, const_reference value) {
        if (position == begin()) {
            push_front(value);
        } else if (position == end()) {
            push_back(value);
        } else {
            node *new_node = new node(value);
            node *current = position.get();
            node *prev = current->_prev;

            prev->_next = new_node;
            new_node->_prev = prev;

            current->_prev = new_node;
            new_node->_next = current;
        }
        return --position;
    };

    void splice(const_iterator position, list &other) {
        iterator iter(position.get());
        iterator other_iter_end = other.end();

        for (iterator other_iter = other.begin(); other_iter != other_iter_end; ++other_iter, ++iter) {
            iter = insert(iter, *other_iter);
        }
        other.clear();
    };

    iterator begin() { return iterator(_head); };

    iterator end() { return _tail->_next ? iterator(_tail->_next) : iterator(_tail); };

    const_iterator cbegin() { return const_iterator(_head); };

    const_iterator cend() { return const_iterator(_tail->_next); };

    template <class... Args>
    iterator emplace(const_iterator pos, Args &&...args) {
        iterator tmp = pos.get_iterator();
        value_type data[] = {args...};
        for (value_type i : data) {
            tmp = insert(tmp, i);
        }
        return tmp;
    };

    template <class... Args>
    void emplace_back(Args &&...args) {
        value_type data[] = {args...};
        for (value_type i : data) {
            push_back(i);
        }
    };

    template <class... Args>
    void emplace_front(Args... args) {
        value_type data[] = {args...};
        for (value_type i : data) {
            push_front(i);
        }
    };
};
}  // namespace s21
