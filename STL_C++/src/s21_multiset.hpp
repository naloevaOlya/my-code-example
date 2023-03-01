#pragma once
#include <iostream>

#include "s21_tree.hpp"

namespace s21 {
template <class Key>
class multiset : public BST<Key> {
 public:
    using key_type = Key;
    using value_type = Key;

    multiset(){};

    ~multiset(){};

    multiset(std::initializer_list<value_type> const& items) : multiset() {
        for (auto iter = items.begin(); iter != items.end(); ++iter) {
            Key val = *iter;
            this->insert(val);
        }
    };

    multiset &operator=(multiset &&src) {
        std::swap(this->_root, src._root);
        src._root = nullptr;
        return *this;
    };

    inline multiset(const multiset& other) : multiset() { this->copyFromBST(other._root, other); };

    inline multiset(multiset&& other) { this->swap(other); };

    typename s21::BST<value_type>::iterator insert(const value_type& value) {
        typename s21::BST<value_type>::iterator result{};
        auto newNode = new typename s21::BST<value_type>::Node(value);
        auto tmp = this->_root;
        if (this->empty()) {
            this->insert_ifEmpty(tmp, newNode);
        } else if (!this->contains(value)) {
            this->insert_unique(tmp, newNode);
        } else {
            this->insert_duplicate(newNode, value);
        }
        result = this->find(value);
        return result;
    };

    void swap(multiset& other) {
        typename s21::BST<key_type>::Node* tmp = this->_root;
        this->_root = other._root;
        other._root = tmp;
    };

    void merge(multiset& other) {
        auto iter = other.begin();
        while (iter != other.end()) {
            auto iter_tmp = iter;
            ++iter_tmp;
            this->insert(iter.getNodePointer()->key);
            other.erase
            (iter);
            iter = iter_tmp;
        }
    };

    typename s21::BST<value_type>::size_type count(const Key& key) {
        typename s21::BST<value_type>::size_type result = 0;
        for (auto iter = this->begin(); iter != this->end(); ++iter) {
            if (iter.getNodePointer()->key == key) {
                result += 1;
            }
        }
        return result;
    }

    std::pair<typename s21::BST<value_type>::iterator, typename s21::BST<value_type>::iterator> equal_range(
        const Key& key) {
        std::pair<typename s21::BST<value_type>::iterator, typename s21::BST<value_type>::iterator> result;
        result.first = lower_bound(key);
        result.second = upper_bound(key);
        return result;
    };

    //  Возвращает итератор, указывающий на первый элемент в multiset с ключом, который больше или равен
    //  указанному ключу.
    typename s21::BST<value_type>::iterator lower_bound(const Key& key) {
        typename s21::BST<value_type>::iterator result = this->begin();
        while (result.getNodePointer()->key < key) {
            if (result == this->end()) {
                break;
            }
            ++result;
        }
        return result;
    };

    //  Возвращает итератор, указывающий на первый элемент в multiset с ключом, который больше указанного
    //  ключа.
    typename s21::BST<value_type>::iterator upper_bound(const Key& key) {
        typename s21::BST<value_type>::iterator result = this->begin();
        while (result.getNodePointer()->key <= key) {
            if (result == this->end()) {
                break;
            }
            ++result;
        }
        return result;
    };

    template <class... Args>
    std::vector<typename s21::BST<value_type>::iterator> emplace(Args&&... args) {
        std::vector<typename s21::BST<value_type>::iterator> out;
        std::vector<value_type> in = {args...};
        for (size_t i = 0; i < in.size(); i++) {
            out.push_back(insert(in[i]));
        }
        return out;
    }

 private:
    void insert_unique(typename s21::BST<value_type>::Node* tmp,
                       typename s21::BST<value_type>::Node* newNode) {
        this->insert_searchPosition(&tmp, &newNode);
        this->insert_intoPos(&tmp, &newNode);
    }

    void insert_duplicate(typename s21::BST<value_type>::Node* newNode, const value_type& value) {
        typename s21::BST<value_type>::iterator iter_dublicate = this->find(value);
        while (iter_dublicate.getNodePointer()->key == value) {
            ++iter_dublicate;
        }
        --iter_dublicate;
        if ((iter_dublicate == (--this->end())) || (iter_dublicate.getNodePointer()->right)) {
            iter_dublicate.getNodePointer()->right->parent = newNode;
            newNode->right = iter_dublicate.getNodePointer()->right;
        }
        iter_dublicate.getNodePointer()->right = newNode;
        newNode->parent = iter_dublicate.getNodePointer();
    }
    void copyFromBST(typename s21::BST<value_type>::Node* leaf, const multiset& other) {
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
