#pragma once
#include <iostream>

namespace s21 {
template <class T>
class queue {
 public:
    using value_type = T;
    using reference = value_type &;
    using const_reference = const reference;
    using size_type = size_t;
    using node = s21::node<T>;

 private:
    node *_head;
    node *_tail;

 public:
    queue() : _head(nullptr), _tail(_head){};

    queue(std::initializer_list<value_type> const &items) : queue() {
        for (auto iter = items.begin(); iter != items.end(); ++iter) {
            value_type val = *iter;
            push(val);
        }
    };

    queue(const queue &q) : queue() {
        for (node *current = q._head; current; current = current->_next) {
            value_type val = current->_value;
            push(val);
        }
    };

    queue(queue &&q) : _head(q._head), _tail(q._tail) {
        q._head = nullptr;
        q._tail = nullptr;
    };

    ~queue() {
        while (!empty()) {
            pop();
        }
    };

    queue &operator=(queue &&other) {
        this->_head = other._head;
        this->_tail = other._tail;
        other._head = other._tail = nullptr;
        return *this;
    };

    inline const_reference front() { return _head->_value; };

    inline const_reference back() { return _tail->_value; };

    inline bool empty() { return size() == 0; };

    size_type size() {
        size_type _size{};
        node *current = _head;
        while (current) {
            _size++;
            current = current->_next;
        }
        return _size;
    };

    void push(const_reference value) {
        node *new_node = new node(value);
        new_node->_next = nullptr;
        if (empty()) {
            _head = _tail = new_node;
            new_node->_prev = nullptr;
        } else {
            node *prev = _tail;
            prev->_next = new_node;
            new_node->_prev = prev;
            _tail = new_node;
        }
    };

    void pop() {
        node *new_head = _head->_next;
        delete (_head);
        _head = new_head;
    };

    void swap(queue &other) noexcept {
        node *swap_node = _head;
        _head = other._head;
        other._head = swap_node;

        swap_node = _tail;
        _tail = other._tail;
        other._tail = swap_node;
    };

    template <class... Args>
    void emplace_back(Args &&...args) {
        value_type data[] = {args...};
        for (value_type i : data) {
            push(i);
        }
    };
};
}  // namespace s21
