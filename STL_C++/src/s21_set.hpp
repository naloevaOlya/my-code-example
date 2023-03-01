#pragma once
#include <iostream>

#include "s21_tree.hpp"

namespace s21 {
template <class Key>
class set : public BST<Key> {
 public:
    using key_type = Key;
    using value_type = Key;

    set(){};

    ~set(){};

    set(std::initializer_list<value_type> const& items) : set() {
        for (auto iter = items.begin(); iter != items.end(); ++iter) {
            Key val = *iter;
            this->insert(val);
        }
    };

    inline set(const set& other) : set() { this->copyFromBST(other._root, other); };

    inline set(set&& other) { this->swap(other); };

    std::pair<typename s21::BST<value_type>::iterator, bool> insert(const value_type& value) {
        std::pair<typename s21::BST<value_type>::iterator, bool> result{};

        if (!this->contains(value)) {
            typename s21::BST<value_type>::Node* newNode = new typename s21::BST<value_type>::Node(value);
            typename s21::BST<value_type>::Node* tmp = this->_root;
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
    }

    void merge(set& other) {
        auto iter = other.begin();
        while (iter != other.end()) {
            auto tmp_iter = iter;
            ++tmp_iter;
            if (!this->contains(iter.getNodePointer()->key)) {
                other.erase(iter);
                this->insert(iter.getNodePointer()->key);
            }
            iter = tmp_iter;
        }
    };

    void swap(set& other) {
        typename s21::BST<key_type>::Node* tmp = this->_root;
        this->_root = other._root;
        other._root = tmp;
    };

    set &operator=(set &&src) {
        std::swap(this->_root, src._root);
        src._root = nullptr;
        return *this;
    };

    template <class... Args>
    std::vector<std::pair<typename s21::BST<value_type>::iterator, bool>> emplace(Args&&... args) {
        std::vector<std::pair<typename s21::BST<value_type>::iterator, bool>> out;
        std::vector<value_type> in = {args...};
        for (size_t i = 0; i < in.size(); i++) {
            out.push_back(insert(in[i]));
        }
        return out;
    }

 private:
    void copyFromBST(typename s21::BST<value_type>::Node* leaf, const set& other) {
        this->insert(leaf->key);
        if (leaf->left) {
            this->copyFromBST(leaf->left, other);
        }
        if (leaf->right && leaf != (--other.end()).getNodePointer()) {
            this->copyFromBST(leaf->right, other);
        }
    }
};

}  // namespace s21
