/**
* This source file is all bout STL sequence containers
* just for fun !
* 3 of 6
* Most of the codes are copyed from jjhou ¡¶STLÔ´ÂëÆÊÎö¡·
*
* Copyleft reserved.
* Karel 2016/04/28
*/
#include <cstddef>	// for ptrdiff_t

namespace karel {

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <class T>
	struct __list_node {
		typedef T* pointer;
		pointer prev;
		pointer next;
		T data;
	};

	// list iterator
	template <class T, class Ref, class Ptr>
	struct __list_iterator {
		typedef __list_iterator<T, T&, T*>		iterator;
		typedef __list_iterator<T, Ref, Ptr>	self;

		typedef bidirectional_iterator_tag iterator_category;
		typedef T		value_type;
		typedef Ptr		pointer;
		typedef Ref		reference;
		typedef __list_node<T>* link_type;
		typedef size_t	size_type;
		typedef ptrdiff_t diffenrence_type;

		link_type node;			// pointer to current node of iterator

		// constructor
		__list_iterator(link_type x) : node(x) {}
		__list_iterator() {}
		__list_iterator(const iterator& x) : node(x.node) {}

		bool operator== (const self& x) const { return node == x.node; }
		bool operator!= (const self& x) const { return node != x.node; }

		// all iterator will overload two operators: *, ->
		reference operator* () {
			return (*node).data;
		}
		pointer operator-> () {
			return &(operator*());
		}

		self& operator++ () {
			node = (link_type)((*node).next);
			return *this;
		}

		self operator++ (int) {
			self tmp = *this;
			++*this;
			return tmp;
		}

		self& operator-- () {
			node = (link_type)((*node).prev);
			return *this;
		}

		self operator-- (int) {
			self tmp = *this;
			--*this;
			return tmp;
		}
	};

	//template <class T, class Alloc = std::allocator>
	//class list {
	//protected:
	//	typedef __list_node<T> list_node;
	//public:
	//	typedef list_node* link_type;
	//protected:
	//	link_type node;
	// to be continued...
	//};

	struct list_node {
		list_node* pre;
		list_node* next;
	};

	template <class T>
	struct __node : public list_node {
		T data;
		__node(T& x) : data(x) {};
	};

	template <class T>
	struct list {
	protected:
		typedef __node<T> node_type;
		typedef __node<T>* link_type;
	public:
		list() : nil(&node) { nil->next = nil; nil->pre = nil; }
		list(T* first, size_t n);
		~list();
		void merge(list<T>&);
		void sort();
		link_type insert(link_type position, const T& x);
		link_type begin() { return nil->next; }
		link_type end() { return nil->pre; }
		bool empty() { return nil->next == nil; }
	private:
		node_type node;
		link_type nil;
	};

	template<class T>
	list<T>::list(T * first, size_t n)
	{
		list();
		if (first == nullptr || n < 0) {
			std::cout << "invalid parameter !" << std::endl;
		}
		for (int i = 0; i < n; ++i) {
			insert(end(), *(first + i));
		}
	}

	template<class T>
	list<T>::~list()
	{
		link_type first = nil->next;
		while (first != nil) {
			link_type tmp = first->next;
			delete first;
			first = tmp;
		}
	}

	template<class T>
	void list<T>::merge(list<T>& x)
	{
		node_type tmp_node;
		link_type first1 = begin(), last1 = end(), first2 = x.begin(), last2 = x.end(), p(&tmp_node);
		while (first1 != last1 && first2 != last2) {
			if (*first1 < *first2) {
				p->next = first1;
				first1->pre = p;
				first1 = first1->next;
			} else {
				link_type tmp = first->next;
				first->next = 
			}
		}
	}

	// iterative mergesort for double-list
	template<class T>
	void list<T>::sort()
	{
		if (nil->next == nil || nil->next->next == nil) return;
		list<T> carry, counter[64];
		int fill = 0;
		while (!empty()) {
			carry.splice(carry.begin(), *this, begin());
			int i = 0;
			while (i < fill && !counter[i].empty()) {
				counter[i].merge(carry);
				carry.swap(counter[i++]);
			}
			carry.swap(counter[i]);
			if (i == fill) ++fill;
		}
		for (int i = 1; i < fill; ++i) {
			counter[i].merge(count[i - 1]);
		}
		swap(counter[fill - 1]);
	}

	template<class T>
	link_type list<T>::insert(link_type position, const T & x)
	{
		link_type tmp = new node_type(x);
		tmp->pre = position->pre;
		tmp->next = position;
		position->pre->next = tmp;
		position->pre = tmp;
		return tmp;
	}
}