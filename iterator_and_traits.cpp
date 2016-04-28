/**
* This source file is all bout simplified STL iterators, iterator traits and type traits
* just for fun !
* 2 of 6 about iterator and traits
* Most of the codes are copyed from jjhou ¡¶STLÔ´ÂëÆÊÎö¡·
*
* Copyleft reserved.
* Karel 2016/04/28
*/

#include <cstdlib>
#include <iostream>

namespace karel {

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <class Category, class T, class Distance = ptrdiff_t,
			  class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};

	template <class Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	};

	// template partial specialization
	template <class T>
	struct iterator_traits <T*> {
		typedef typename random_access_iterator_tag		iterator_category;
		typedef typename T								value_type;
		typedef typename ptrdiff_t						difference_type;
		typedef typename T*								pointer;
		typedef typename T&								reference;
	};

	template <class T>
	struct iterator_traits <const T*> {
		typedef typename random_access_iterator_tag		iterator_category;
		typedef typename const T						value_type;
		typedef typename ptrdiff_t						difference_type;
		typedef typename const T*						pointer;
		typedef typename const T&						reference;
	};

	template <class InputIterator>
	inline iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last) {
		__distance(first, last, iterator_traits<InputIterator>::iterator_category());
	}

	template <class InputIterator>
	inline iterator_traits<InputIterator>::difference_type __distance(InputIterator first, InputIterator last, input_iterator_tag) {
		std::cout << "input_iterator_tag !" << endl;
	}

	template <class InputIterator>
	inline iterator_traits<InputIterator>::difference_type __distance(InputIterator first, InputIterator last, random_access_iterator_tag) {
		std::cout << "random_access_iterator_tag !" << endl;
	}
}