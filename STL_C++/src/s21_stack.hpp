#pragma once
#include <iostream>

namespace s21 {
template <class T>
class stack {
 public:
    using value_type = T;
    using reference = value_type &;
    using const_reference = const reference;
    using size_type = size_t;
    using node = s21::node<T>;

 private:
    node *_head;

 public:
    stack() : _head(nullptr){};

    stack(std::initializer_list<value_type> const &items) : stack() {
        for (auto iter = items.begin(); iter != items.end(); ++iter) {
            value_type val = *iter;
            push(val);
        }
    };

    stack(const stack &other) : stack() {
        node *item = other._head;
        while (item->_prev) {
            item = item->_prev;
        }
        while (item) {
            push(item->_value);
            item = item->_next;
        }
    };

    stack(stack &&other) : _head(other._head) { other._head = nullptr; };

    ~stack() {
        delete (_head);
        _head = nullptr;
    };

    stack &operator=(stack &&other) {
        this->_head = other._head;
        other._head = nullptr;
        return *this;
    };

    inline const_reference top() { return _head->_value; };

    inline bool empty() { return size() == 0; };

    size_type size() {
        size_type _size = 0;
        node *temp = _head;
        while (temp) {
            _size += 1;
            temp = temp->_prev;
        }
        return _size;
    };

    void push(const_reference value) {
        node *new_node = new node(value);
        new_node->_next = nullptr;
        if (empty()) {
            new_node->_prev = nullptr;
        } else {
            node *prev = _head;
            prev->_next = new_node;
            new_node->_prev = prev;
        }
        _head = new_node;
    };

    void pop() {
        node *new_head = _head->_prev;
        delete (_head);
        _head = new_head;
    };

    void swap(stack &other) noexcept {
        node *swap_node = _head;
        _head = other._head;
        other._head = swap_node;
    };

    template <class... Args>
    void emplace_front(Args... args) {
        value_type data[] = {args...};
        for (value_type i : data) {
            push(i);
        }
    };
};
}  // namespace s21
