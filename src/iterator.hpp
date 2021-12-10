#pragma once //  NOLINT
#include "list.hpp"

template<typename T>
task::list<T>::iterator::iterator() {
	user_iterator = nullptr;
}

template<typename T>
task::list<T>::iterator::iterator(const iterator& other_iterator) {
    user_iterator = other_iterator.user_iterator;
}

template<typename T>
task::list<T>::iterator::iterator(Node<T>* node_ptr) {
    user_iterator = node_ptr;
}

template<typename T>
typename task::list<T>::iterator& task::list<T>::iterator::operator=
(const iterator& other_iterator) {
    user_iterator = other_iterator.user_iterator;
    return *this;
}

template<typename T>
typename task::list<T>::iterator& task::list<T>::iterator::operator++() {
    if (this->user_iterator != nullptr && this->user_iterator->m_next != nullptr) {
        user_iterator = user_iterator->m_next;
    }
    return *this;
}

template<typename T>
typename task::list<T>::iterator task::list<T>::iterator::operator++(int i) {
    iterator current_iterator(*this);
    if (this->user_iterator != nullptr && this->user_iterator->m_next != nullptr) {
        user_iterator = user_iterator->m_next;
    }
    return current_iterator;
}

template<typename T>
typename task::list<T>::iterator::reference task::list<T>::iterator::operator*() const {
    if (user_iterator != nullptr) {
        return user_iterator->m_data;
    } else {
        return T();
    }
}

template<typename T>
typename task::list<T>::iterator::pointer task::list<T>::iterator::operator->() const {
    if (user_iterator != nullptr && user_iterator->m_next != nullptr) {
        return &this->user_iterator->m_data;
    }
}

template <typename T>
typename task::list<T>::iterator& task::list<T>::iterator::operator--() {
    if (this->user_iterator != nullptr && this->user_iterator->m_prev != nullptr) {
        user_iterator = user_iterator->m_prev;
    }
    return *this;
}

template <typename T>
typename task::list<T>::iterator task::list<T>::iterator::operator--(int) {
    iterator current_iterator(*this);
    if (this->user_iterator != nullptr && this->user_iterator->m_prev != nullptr) {
        user_iterator = user_iterator->m_prev;
    }
    return current_iterator;
}

template <typename T>
bool task::list<T>::iterator::operator==(iterator other) const {
    return (this->user_iterator == other.user_iterator);
}

template <typename T>
bool task::list<T>::iterator::operator!=(iterator other) const {
    return (this->user_iterator != other.user_iterator);
}
