#pragma once //  NOLINT
#include "list.hpp"

template<typename T>
task::list<T>::const_iterator::const_iterator() {
	user_const_iterator = nullptr;
}

template<typename T>
task::list<T>::const_iterator::const_iterator
(const const_iterator& other_iterator) {
    user_const_iterator = other_iterator.user_const_iterator;
}

template<typename T>
task::list<T>::const_iterator::const_iterator
(const iterator& other_iterator) {
    this->user_const_iterator = other_iterator.user_iterator;
}

template<typename T>
task::list<T>::const_iterator::const_iterator(Node<T>* node_ptr) {
    user_const_iterator = node_ptr;
}

template<typename T>
typename task::list<T>::const_iterator& task::list<T>::const_iterator::operator=
(const task::list<T>::const_iterator& other_iterator) {
    user_const_iterator = other_iterator.user_const_iterator;
    return *this;
}

template<typename T>
typename task::list<T>::const_iterator& task::list<T>::const_iterator::operator++() {
    if (this->user_const_iterator != nullptr && this->user_const_iterator->m_next != nullptr) {
        user_const_iterator = user_const_iterator->m_next;
    }
    return *this;
}

template<typename T>
typename task::list<T>::const_iterator task::list<T>::const_iterator::operator++(int i) {
    const_iterator current_iterator(*this);
    if (this->user_const_iterator != nullptr && this->user_const_iterator->m_next != nullptr) {
        user_const_iterator = user_const_iterator->m_next;
    }
    return current_iterator;
}

template<typename T>
typename task::list<T>::const_iterator::const_reference task::list<T>::const_iterator::operator*() const {
    if (user_const_iterator != nullptr) {
        return user_const_iterator->m_data;
    }
}

template<typename T>
typename task::list<T>::const_iterator::const_pointer task::list<T>::const_iterator::operator->() const {
    if (user_const_iterator != nullptr && user_const_iterator->m_next != nullptr) {
        return &this->user_iterator->m_data;
    }
}

template <typename T>
typename task::list<T>::const_iterator& task::list<T>::const_iterator::operator--() {
    if (this->user_const_iterator != nullptr && this->user_const_iterator->m_prev != nullptr) {
        user_const_iterator = user_const_iterator->m_prev;
    }
    return *this;
}

template <typename T>
typename task::list<T>::const_iterator task::list<T>::const_iterator::operator--(int) {
    const_iterator current_iterator(*this);
    if (this->user_const_iterator != nullptr && this->user_const_iterator->m_prev != nullptr) {
        user_const_iterator = user_const_iterator->m_prev;
    }
    return current_iterator;
}

template <typename T>
bool task::list<T>::const_iterator::operator==(const_iterator other) const {
    return (this->user_const_iterator == other.user_const_iterator);
}

template <typename T>
bool task::list<T>::const_iterator::operator!=(const_iterator other) const {
    return (this->user_const_iterator != other.user_const_iterator);
}
