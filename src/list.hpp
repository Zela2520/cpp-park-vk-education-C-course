#pragma once // NOLINT
#include <iterator>
#include <exception>

namespace task {


template<class T>
class list {
    template <typename T>
    class Node {
	    public:
		Node(const T& data = T(), Node* next = nullptr, Node* prev = nullptr) :
			m_data(data),
			m_next(next),
			m_prev(prev)
	    {}
		T m_data;
		Node* m_next;
		Node* m_prev;
	};
	Node<T>* head;
	Node<T>* tail;
	size_t list_size;

 public:
    class iterator {
	    public:
		    using difference_type = ptrdiff_t;
		    using value_type = T;
		    using pointer = T*;
		    using reference = T&;
		    using iterator_category = std::bidirectional_iterator_tag;

	iterator();
        iterator(Node<T>* node_ptr);
        iterator(const iterator& other_iterator);
        iterator& operator=(const iterator& other_iterator);

        iterator& operator++();
        iterator operator++(int);
        reference operator*() const;
        pointer operator->() const;
        iterator& operator--();
	iterator operator--(int);

        bool operator==(iterator other) const;
        bool operator!=(iterator other) const;

     private:
	Node<T>* user_iterator;
    };
    friend class iterator;

    class const_iterator {
	    public:
		    using difference_type = ptrdiff_t;
		    using value_type = T;
		    using const_pointer = const T*;
		    using const_reference = const T&;
		    using iterator_category = std::bidirectional_iterator_tag;

        const_iterator();
        const_iterator(Node<T>* node_ptr);
        const_iterator(const const_iterator& other_iterator);
        const_iterator& operator=(const const_iterator& other_iterator);
        const_iterator& operator++();
        const_iterator operator++(int);
        const_reference operator*() const;
        const_pointer operator->() const;
        const_iterator& operator--();
        const_iterator operator--(int);

        bool operator==(const_iterator other) const;
        bool operator!=(const_iterator other) const;
	    private:
		Node<T>* user_const_iterator;
    };
    friend class const_iterator;

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;


    list();
    list(size_t count, const T& value);
    explicit list(size_t count);
    ~list();

    list(const list& other);
    list& operator=(const list& other);

    T& front();
    const T& front() const;

    T& back();
    const T& back() const;


    iterator begin() const;
    iterator end() const;

    const_iterator cbegin() const;
    const_iterator cend() const;

    reverse_iterator rbegin() const;
    reverse_iterator rend() const;

    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;


    bool empty() const;
    size_t size() const;
    size_t max_size() const;
    void clear();

    iterator insert(const_iterator pos, const T& value);
    iterator insert(const_iterator pos, size_t count, const T& value);

    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);


    void push_back(const T& value);
    void pop_back();

    void push_front(const T& value);
    void pop_front();

    void resize(size_t count);
    void swap(list& other);


    void merge(list& other);
    void splice(const_iterator pos, list& other);
    void remove(const T& value);
    void reverse();
    void unique();
    void sort();

    // iterator search(const T& data);
};

// Your template function definitions may go here...


}  // namespace task
