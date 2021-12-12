#pragma once // NOLINT
#include <cassert>
#include <iostream>
#include "list.hpp"

#define MAX_SIZE 1000

template <typename T>
task::list<T>::list() : head(nullptr), tail(nullptr), list_size(0) {}

template <typename T>
task::list<T>::list(size_t count, const T& value) : head(nullptr), tail(nullptr), list_size(0) {
    while (count != this->list_size) {
        push_back(value);
    }

    push_back(T());
    --list_size;
}

template <typename T>
task::list<T>::list(size_t count) {
    while (this->list_size != count) {
        push_back(T());
    }

    push_back(T());
    --list_size;
}

template <typename T>
task::list<T>::~list() {
    clear();
}

template <typename T>
task::list<T>::list(const list& other) {
    list_size = other.list_size;
    list<T> new_list(list_size);
    Node<T>* cur_this = this->head;
    Node<T>* cur_other = other->head;

    while (cur_other != nullptr || cur_this != nullptr) {
        cur_this->data = cur_other->data;
        cur_this = cur_this->m_next;
        cur_other = cur_other->m_next;
    }

    return new_list;
}

template <typename T>
task::list<T>& task::list<T>::operator=(const list& other) {
    list_size = other->list_size;
    list<T> new_list(list_size);
    Node<T>* cur_this = this->head;
    Node<T>* cur_other = other->head;

    while (cur_other != nullptr && cur_this != nullptr) {
        cur_this->data = cur_other->data;
        cur_this = cur_this->m_next;
        cur_other = cur_other->m_next;
    }

    return new_list;
}

template <typename T>
T& task::list<T>::front() {
    if (head != nullptr) {
        return this->head->m_data;
    }
}

template <typename T>
const T& task::list<T>::front() const {
    if (head != nullptr) {
        return this->head->m_data;
    }
}

template <typename T>  //  вопрос
T& task::list<T>::back() {
    if (tail != nullptr && tail->m_prev != nullptr) {
        return this->tail->m_prev->m_data;
    }
}

template <typename T>
const T& task::list<T>::back() const {
    if (tail != nullptr && tail->m_prev != nullptr) {
        return this->tail->m_prev->m_data;
    }
}

template <typename T>
typename task::list<T>::iterator task::list<T>::begin() const {
    iterator first_node(head);
    return first_node;
}

template <typename T>
typename task::list<T>::iterator task::list<T>::end() const {
    iterator last_node(tail);
    return last_node;
}

template <typename T>
typename task::list<T>::const_iterator task::list<T>::cbegin() const {
    const_iterator first_node(head);
    return first_node;
}

template <typename T>
typename task::list<T>::const_iterator task::list<T>::cend() const {
    const_iterator last_node(tail);
    return last_node;
}

template <typename T>
typename task::list<T>::reverse_iterator task::list<T>::rbegin() const {
    return reverse_iterator(tail);
}

template <typename T>
typename task::list<T>::reverse_iterator task::list<T>::rend() const {
    return reverse_iterator(head);
}

template <typename T>
typename task::list<T>::const_reverse_iterator task::list<T>::crbegin() const {
    return const_reverse_iterator(tail);
}

template <typename T>
typename task::list<T>::const_reverse_iterator task::list<T>::crend() const {
    return const_reverse_iterator(head);
}

template <typename T>
bool task::list<T>::empty() const {
    return (this->head == nullptr);
}

template <typename T>
size_t task::list<T>::size() const {
    return this->list_size;
}

template <typename T>
size_t task::list<T>::max_size() const {  //  вопрос
    return MAX_SIZE;
}

template <typename T>
void task::list<T>::clear() {
    while (this->list_size) {
        pop_front();
    }
}

template <typename T>
typename task::list<T>::iterator task::list<T>::insert(const_iterator pos, const T& value) {
    std::cout << pos->m_data << "INSERT\n";
    if (head == nullptr) {
        push_front();
        std::cout << pos->user_const_iterator->m_data << '\n';
        std::cout << value << '\n';
        list<T>::iterator current_iterator(head);
        return current_iterator;
    } else {
        list<T>::iterator current_iterator(head);

        while (current_iterator->user_iterator != pos->user_const_iterator->m_prev) {
            ++current_iterator;
        }

        std::cout << pos->user_const_iterator->m_data << '\n';
        std::cout << value << '\n';

        Node<T>* new_element = new Node<T>(value, current_iterator->user_iterator->m_next,
        current_iterator->user_iterator);
        current_iterator->user_iterator->next = new_element;
        new_element->m_next->m_prev = new_element;

        return current_iterator;
    }
    std::cout << pos->m_data << "INSERT\n";
    ++list_size;
}

template <typename T>
typename task::list<T>::iterator task::list<T>::insert(const_iterator pos, size_t count, const T& value) {
    size_t new_list_size = list_size + count;
    while (list_size != new_list_size) {
        insert(pos, value);
    }
}

template <typename T>
typename task::list<T>::iterator task::list<T>::erase(const_iterator pos) {
    assert(this->head != nullptr);
    if (this->list_size == 1) {
        pop_front();
        list<T>::iterator current_iterator(head);
        return current_iterator;
    } else {
        list<T>::iterator current_iterator(head);
        while (current_iterator->user_iterator != pos->user_const_iterator->m_prev) {
            ++current_iterator;
        }
        Node<T>* to_delete = current_iterator->user_iterator->m_next;
		current_iterator->user_iterator->m_next = to_delete->m_next;
		to_delete->m_next->m_prev = current_iterator->user_iterator;
		delete to_delete;
		to_delete->m_prev = to_delete->m_next = nullptr;
    }
    --list_size;
}

template <typename T>
typename task::list<T>::iterator task::list<T>::erase(const_iterator first, const_iterator last) {
    assert(this->head != nullptr);
    if (first == head) {
        while (head != last) {
            pop_front();
        }
        list<T>::iterator current_iterator(last);
        return current_iterator;
    } else {
        list<T>::iterator current_iterator(head);
        while (first != last) {
            this->erase(first);
        }
        return (current_iterator = last);
    }
}

template <typename T>
void task::list<T>::push_back(const T& value) {
    if (head == nullptr) {
		head = new Node<T>(value);
		tail = head;
	} else {
		Node<T> *current = this->tail;
		tail = new Node<T>(value, nullptr, tail);
		current->m_next = tail;
	}
	++this->list_size;
}

template <typename T>
void task::list<T>::pop_back() {
    assert(this->list_size > 0);
    Node<T>* todelete = this->tail;
	tail = tail->m_prev;
    tail->m_next = nullptr;
	delete todelete;
	todelete = nullptr;
	--this->list_size;
}

template <typename T>
void task::list<T>::push_front(const T& value) {
    if (head == nullptr) {
        push_back(value);
    }
    Node<T>* after_head = this->head;
	head = new Node<T>(value, head, nullptr);
	after_head->m_prev = head;
	++this->list_size;
}

template <typename T>
void task::list<T>::pop_front() {
    assert(this->list_size > 0);
    Node<T>* todelete = this->head;
	head = head->m_next;
    head->m_prev = nullptr;
	delete todelete;
	todelete = nullptr;
	--this->list_size;
}

template <typename T>
void task::list<T>::resize(size_t count) {
    while (this->list_size != count) {
        push_back(T());
        ++this->list_size;
    }
    push_back(T());
}

template <typename T>
void task::list<T>::swap(list& other) {
    Node<T>* temp_head = head;
    Node<T>* temp_tail = tail;
    head = other.head;
    tail = other.tail;
    other.head = temp_head;
    other.tail = temp_tail;
}

template <typename T>
void task::list<T>::merge(list& other) {
}

template <typename T>
void task::list<T>::splice(const_iterator pos, list& other) {
}

template <typename T>
void task::list<T>::remove(const T& value) {
    assert(this->size != 0);
    iterator to_delete(this->head);

    while (to_delete->user_iterator != nullptr) {
        iterator copy_iterator = to_delete;

        if (copy_iterator->m_data == value) {
            erase(copy_iterator);
        }

        ++to_delete;
    }
}

template <typename T>
void task::list<T>::reverse() {
    size_t count = this->size() - 1;
    Node<T>* current = this->head;
    Node<T>* rev_list = current->m_next;
    Node<T>* next_rev_list = rev_list->m_next;

    while (count) {
        if (current != this->head)
            next_rev_list = next_rev_list->m_next;

        rev_list->m_next = current;

        if (current == this->head) {
            current->m_next = nullptr;
        }

        current = rev_list;
        rev_list = next_rev_list;
        count--;
    }

    this->head = current;
}

template <typename T>
void task::list<T>::unique() {}

template <typename T>
void task::list<T>::sort() {
    /*Node<T>* min_elem = this->head;
    for (iterator out_it = this->begin(); it < this->end(); ++it) {
        for (iterator in_it = min_elem->m_next; it < this->end(); ++it) {
            if (min_elem->m_data >= it->user_iterator->m_data) {

            }
        }
        min_elem = min_elem->m_next;
    } */
}

/*template<typename T>
task::list<T>::iterator task::list<T>::search(const T& data) {
	assert(this->size != 0);
	iterator current(this->head);
	while (current != nullptr) {
		if (current->user_iterator->m_data == data) { return current; }
	}
	return nullptr;
}*/
