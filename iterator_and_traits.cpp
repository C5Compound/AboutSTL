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

	//struct input_iterator_tag {};
	//struct output_iterator_tag {};
	//struct forward_iterator_tag : public input_iterator_tag {};
	//struct bidirectional_iterator_tag : public forward_iterator_tag {};
	//struct random_access_iterator_tag : public bidirectional_iterator_tag {};
	struct random_access_iterator_tag {};

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
		// typedef typename Iterator::iterator_category	iterator_category;
		// test if VC vector iterator is T*
		typedef typename karel::random_access_iterator_tag		iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	};

	// template partial specialization
	template <class T>
	struct iterator_traits <T*> {
		typedef typename std::random_access_iterator_tag		iterator_category;
		typedef typename T								value_type;
		typedef typename ptrdiff_t						difference_type;
		typedef typename T*								pointer;
		typedef typename T&								reference;
	};

	template <class T>
	struct iterator_traits <const T*> {
		typedef typename std::random_access_iterator_tag		iterator_category;
		typedef typename const T						value_type;
		typedef typename ptrdiff_t						difference_type;
		typedef typename const T*						pointer;
		typedef typename const T&						reference;
	};

	template <class InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last) {
		typedef typename iterator_traits<InputIterator>::iterator_category category;
		return __distance(first, last, category());
	}

	template <class InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type __distance(InputIterator first, InputIterator last, std::input_iterator_tag) {
		std::cout << "input_iterator_tag !" << std::endl;
		return static_cast<typename iterator_traits<InputIterator>::difference_type>(0);
	}

	template <class InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type __distance(InputIterator first, InputIterator last, std::random_access_iterator_tag) {
		std::cout << "random_access_iterator_tag !" << std::endl;
		return static_cast<typename iterator_traits<InputIterator>::difference_type>(0);
	}

	template <class InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type __distance(InputIterator first, InputIterator last, karel::random_access_iterator_tag) {
		std::cout << "VC vector iterator implementation is not T*!" << std::endl;
		return static_cast<typename iterator_traits<InputIterator>::difference_type>(0);
	}
	
	// __type_traits
}

// for test...
#include <vector>

int main()
{
	std::vector<int> v;
	karel::distance(v.begin(), v.end());	// traits iterator category tag from std vector
	int a[5] = { 0,1,2,3,4 };
	karel::distance(a, a + 5);				// test how iterator_traits act when a pointer is passed as a parameter

	system("pause");
	return 0;
}