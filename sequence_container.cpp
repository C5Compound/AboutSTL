/**
* This source file is all bout STL sequence containers
* just for fun !
* 3 of 6 about Allocator
* Most of the codes are copyed from jjhou ¡¶STLÔ´ÂëÆÊÎö¡·
*
* Copyleft reserved.
* Karel 2016/04/28
*/
namespace karel {

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
	};

	template <class T, class Alloc = std::allocator>
	class List {
		typedef T				value_type;
		typedef value_type*		pointer;
		typedef value_type*		iterator;
	};
}