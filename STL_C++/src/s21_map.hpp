#pragma once
#include <iostream>

#include "s21_tree.hpp"

namespace s21 {
template <class Key, class T>
class map : public s21::BST<std::pair<const Key, T>> {
 public:
    using mapped_type = T;
    using key_type = Key;
    using value_type = std::pair<const key_type, T>;

    map(){};

    ~map(){};

    map(std::initializer_list<value_type> const &items) : map() {
        for (auto iter = items.begin(); iter != items.end(); ++iter) {
            std::pair<const Key, T> val = *iter;
            this->insert(val);
        }
    };

    inline map(const map &other) : map() { this->copyFromBST(other._root, other); };

    inline map(map &&other) { this->swap(other); };

    void merge(map &other) {
        auto iter = other.begin();
        while (iter != other.end()) {
            auto tmp_iter = iter;
            ++tmp_iter;
            if (!this->contains(iter.getNodePointer()->key.first)) {
                other.erase(iter);
                this->insert(iter.getNodePointer()->key);
            }
            iter = tmp_iter;
        }
    };

    void swap(map &other) {
        typename s21::BST<value_type>::Node *tmp = this->_root;
        this->_root = other._root;
        other._root = tmp;
    };

    map &operator=(map &&src) {
        std::swap(this->_root, src._root);
        src._root = nullptr;
        return *this;
    };

    std::pair<typename s21::BST<value_type>::iterator, bool> insert(const Key &key, const T &obj) {
        return this->insert(std::pair<const Key, const T>(key, obj));
    }

    std::pair<typename s21::BST<value_type>::iterator, bool> insert(const value_type &value) {
        std::pair<typename s21::BST<value_type>::iterator, bool> result{};

        if (!this->contains(value.first)) {
            typename s21::BST<value_type>::Node *newNode = new typename s21::BST<value_type>::Node(value);
            typename s21::BST<value_type>::Node *tmp = this->_root;
            if (this->empty()) {
                this->insert_ifEmpty(tmp, newNode);
            } else {
                this->insert_searchPosition(&tmp, &newNode);
                this->insert_intoPos(&tmp, &newNode);
                result.second = newNode;
            }
            result.first = this->find(value);
            result.second = true;
        }
        return result;
    };

    std::pair<typename s21::BST<value_type>::iterator, bool> insert_or_assign(const Key &key, const T &obj) {
        std::pair<typename s21::BST<value_type>::iterator, bool> result{};

        if (!this->contains(key)) {
            result = this->insert(key, obj);
        } else {
            result = this->insert_assing(key, obj);
        }

        return result;
    }

    T &operator[](const Key &key) {
        T *retval = new T();
        typename s21::BST<value_type>::iterator find_pos = this->find(key);
        if (find_pos == this->end()) {
            find_pos = this->insert(key, *retval).first;
        }
        T &ret = find_pos.getNodePointer()->key.second;
        return ret;
    };

    T &at(const Key &key) { return (*this->find(key)).second; };

    bool contains(const Key &key) {
        typename s21::BST<value_type>::iterator i_end = this->end();
        return find(key) != i_end ? true : false;
    }

    template <class... Args>
    std::vector<std::pair<typename s21::BST<value_type>::iterator, bool>> emplace(Args &&...args) {
        std::vector<std::pair<typename s21::BST<value_type>::iterator, bool>> out;
        std::vector<value_type> in = {args...};
        for (size_t i = 0; i < in.size(); i++) {
            out.push_back(insert(in[i]));
        }
        return out;
    }

 private:
    void copyFromBST(typename s21::BST<value_type>::Node *leaf, const map &other) {
        this->insert(leaf->key);
        if (leaf->left) {
            this->copyFromBST(leaf->left, other);
        }
        if (leaf->right && leaf != (--other.end()).getNodePointer()) {
            this->copyFromBST(leaf->right, other);
        }
    }

    std::pair<typename s21::BST<value_type>::iterator, bool> insert_assing(const Key &key, const T &obj) {
        std::pair<typename s21::BST<value_type>::iterator, bool> result{};
        result.first = find(value_type(key, obj));
        result.first.getNodePointer()->key.second = obj;
        return result;
    }

    typename s21::BST<value_type>::iterator find(const value_type &pair) {
        typename s21::BST<value_type>::Node *tmp = this->_root;
        bool found{};
        typename s21::BST<value_type>::iterator result;
        while (tmp) {
            if (tmp->key.first == pair.first) {
                result = typename s21::BST<value_type>::iterator(tmp);
                found = true;
                break;
            } else if (tmp->key.first < pair.first) {
                tmp = tmp->right;
            } else {
                tmp = tmp->left;
            }
        }

        if (!found) {
            result = this->end();
        }

        return result;
    };

    typename s21::BST<value_type>::iterator find(const Key &key) {
        typename s21::BST<value_type>::Node *tmp = this->_root;
        bool found{};
        typename s21::BST<value_type>::iterator result;
        while (tmp) {
            if (tmp->key.first == key) {
                result = typename s21::BST<value_type>::iterator(tmp);
                found = true;
                break;
            } else if (tmp->key.first < key) {
                tmp = tmp->right;
            } else {
                tmp = tmp->left;
            }
        }

        if (!found) {
            result = this->end();
        }

        return result;
    };
};
}  // namespace s21
