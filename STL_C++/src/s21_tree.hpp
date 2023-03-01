#pragma once
#include <iostream>

namespace s21 {
template <class Key>
class BST {
 public:
    using value_type = Key;
    using size_type = size_t;
    using reference = value_type &;
    using const_reference = const reference;

    struct Node {
        value_type key;
        Node *left;
        Node *right;
        Node *parent;

        Node() : key(value_type()), left(nullptr), right(nullptr), parent(nullptr){};
        explicit Node(value_type k) : left(nullptr), right(nullptr), parent(nullptr), key(value_type(k)){};

        void assignNewParent(Node *newParent) { parent = newParent; }
    };

 protected:
    Node *_root;

 public:
    class iterator {
     private:
        Node *_pointer;

     public:
        explicit iterator(Node *pointer = nullptr) : _pointer(pointer){};

        value_type &operator*() { return _pointer->key; };

        iterator &operator++() {
            if (_pointer->right) {
                _pointer = _pointer->right;

                while (_pointer->left) {
                    _pointer = _pointer->left;
                }

            } else if (!isEnd()) {
                while (_pointer == _pointer->parent->right && _pointer->parent->parent) {
                    _pointer = _pointer->parent;
                }
                _pointer = _pointer->parent;
            }
            return *this;
        };

        iterator &operator--() {
            if (_pointer->left) {
                _pointer = _pointer->left;

                while (_pointer->right) {
                    _pointer = _pointer->right;
                }
            } else if (!isBegin()) {
                while (_pointer == _pointer->parent->left && _pointer->parent->parent) {
                    _pointer = _pointer->parent;
                }
                _pointer = _pointer->parent;
            } else {
                _pointer = nullptr;
            }

            return *this;
        };

        inline bool operator==(const iterator &t) const { return t._pointer == _pointer; };

        inline bool operator!=(const iterator &t) const { return t._pointer != _pointer; };

        inline Node *getNodePointer() const { return _pointer; };

        inline bool hasChild() { return (_pointer->left || _pointer->right); };

     private:
        bool isBegin() {
            if (hasChild()) {
                return false;
            };

            bool isBegin{true};
            while (_pointer->parent) {
                if (_pointer != _pointer->parent->left) {
                    isBegin = false;
                    break;
                }
                _pointer = _pointer->parent;
            }
            return isBegin;
        };

        bool isEnd() {
            if (hasChild()) {
                return false;
            }

            bool isEnd{true};
            while (_pointer->parent) {
                if (_pointer != _pointer->parent->right) {
                    isEnd = false;
                    break;
                }
                _pointer = _pointer->parent;
            }
            return isEnd;
        };
    };

    inline bool empty() { return _root->left || _root->right ? false : true; };

    size_type size() const {
        iterator start = begin();
        iterator i_end = end();
        size_type i{};
        for (; start != i_end; i++) {
            ++start;
        }
        return i;
    };

    inline size_type max_size() {
        return std::numeric_limits<intmax_t>::max() / (sizeof(Node) + sizeof(iterator));
    };

    std::pair<iterator, bool> insert(const value_type &value) {
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
    }

    void erase(iterator pos) {
        if (pos != end()) {
            Node *posNode = pos.getNodePointer();
            auto posParent = posNode->parent;
            auto posRightChild = posNode->right;
            auto posLeftChild = posNode->left;

            bool posIsRoot = !posParent;
            bool posIsBegin = pos == begin();
            if (!posRightChild && !posLeftChild) {
                eraseChildlessNode(posNode);
            } else if (posIsBegin && posIsRoot) {
                _root = posRightChild;
                _root->parent = nullptr;
            } else if (pos == --end()) {
                eraseLastNode(posLeftChild, posRightChild, posParent, posNode);
            } else {
                eraseNode(posLeftChild, posRightChild, posParent, posNode, posIsRoot);
            }
            delete posNode;
        }
    };

    iterator find(const value_type &key) {
        Node *tmp = _root;
        bool found{};
        iterator result;
        while (tmp) {
            if (tmp->key == key) {
                result = iterator(tmp);
                found = true;
                break;
            } else if (tmp->key < key) {
                tmp = tmp->right;
            } else {
                tmp = tmp->left;
            }
        }

        if (!found) {
            result = end();
        }

        return result;
    };

    bool contains(const value_type &key) {
        iterator i_end = end();
        return find(key) != i_end ? true : false;
    };

    iterator begin() const {
        iterator iter(_root);
        while (iter.getNodePointer()->left) {
            iter = iterator(iter.getNodePointer()->left);
        }
        return iter;
    };

    iterator end() const {
        iterator iter(_root);
        while (iter.getNodePointer()->right) {
            iter = iterator(iter.getNodePointer()->right);
        }
        return iter;
    };

    BST() : _root(new Node()){};

    ~BST() {
        delete _root;
    };

    void clear() {
        while (begin() != end()) {
            erase(begin());
        }
    }

 private:
    void eraseNode(Node *LeftChild, Node *RightChild, Node *Parent, const Node *currentNode, bool IsRoot) {
        if (LeftChild) {
            auto tmp = LeftChild;
            bool tmpHasRight = tmp->right;
            while (tmp->right) {
                tmp = tmp->right;
            }
            if (tmpHasRight) {
                tmp->parent->right = nullptr;
            }

            if (!IsRoot) {
                (currentNode == Parent->left ? Parent->left : Parent->right) = tmp;
                tmp->parent = Parent;
            }

            if (RightChild && tmp != RightChild) {
                tmp->right = RightChild;
                RightChild->parent = tmp;
            }

            if (tmp != LeftChild) {
                tmp->left = LeftChild;
                LeftChild->parent = tmp;
            }

            if (IsRoot) {
                _root = tmp;
            }
        } else {
            auto nodeIsLeftOfParent = Parent->left == currentNode;
            if (nodeIsLeftOfParent) {
                Parent->left = RightChild;
            } else {
                Parent->right = RightChild;
            }
            RightChild->parent = Parent;
        }
    }

    void eraseChildlessNode(Node *node) {
        auto nodeIsLeftOfParent = node->parent->left == node;
        if (nodeIsLeftOfParent) {
            node->parent->left = nullptr;
        } else {
            node->parent->right = nullptr;
        }
    }

    void eraseLastNode(Node *LeftChild, Node *RightChild, Node *Parent, Node *CurrentNode) {
        if (LeftChild) {
            Parent->right = LeftChild;
            LeftChild->parent = Parent;
            LeftChild->right = CurrentNode->right;
            CurrentNode->right->parent = LeftChild;
        } else {
            Parent->right = RightChild;
            RightChild->parent = Parent;
        }
    }

 protected:
    void insert(Node *newNode) {
        Node *tmp = _root;
        if (empty()) {
            insert_ifEmpty(tmp, newNode);
        } else {
            insert_searchPosition(&tmp, &newNode);
            insert_intoPos(&tmp, &newNode);
        }
    };

    void insert_ifEmpty(typename s21::BST<value_type>::Node *tmp,
                        typename s21::BST<value_type>::Node *newNode) {
        this->_root = newNode;
        this->_root->right = tmp;
        tmp->parent = this->_root;
    }

    void insert_searchPosition(Node **tmp, Node **newNode) {
        while (tmp) {
            if ((*newNode)->key < (*tmp)->key) {
                if ((*tmp)->left) {
                    (*tmp) = (*tmp)->left;
                } else {
                    break;
                }
            } else {
                if ((*tmp)->right && !(iterator((*tmp)->right) == end())) {
                    (*tmp) = (*tmp)->right;
                } else {
                    break;
                }
            }
        }
    }

    void insert_intoPos(Node **tmp, Node **newNode) {
        if ((*newNode)->key < (*tmp)->key) {
            (*tmp)->left = (*newNode);
            (*newNode)->parent = (*tmp);
        } else {
            if ((*tmp)->right && !(*tmp)->right->right) {
                Node *emptyNode = (*tmp)->right;
                (*newNode)->right = emptyNode;
                emptyNode->parent = (*newNode);
            }

            (*tmp)->right = (*newNode);
            (*newNode)->parent = (*tmp);
        }
    }
};
}  // namespace s21
