/**
 * This source file is all bout simplified STL allocator deallocator construct and destroy
 * just for fun !
 * 1 of 6 about Allocator
 * Most of the codes are copyed from jjhou ¡¶STLÔ´ÂëÆÊÎö¡·
 *
 * Copyleft reserved.
 * Karel 2016/04/27
 */
#include <new>			// for placement new
#include <cstddef>		// for ptrdiff_t, size_t
#include <cstdlib>		// for exit()
#include <climits>		// UINT_MAX
#include <iostream>		// for cerr

namespace karel {

	template <class T>
	inline T* _allocate(ptrdiff_t size, T*) {
		//set_new_handler(0);
		T* tmp = (T*)(::operator new ((size_t)(size * sizeof(T))));
		if (tmp == 0) {
			cerr << "out of memory" << endl;
			exit(1);
		}
		return tmp;
	}

	template <class T>
	inline void _deallocate(T* buffer) {
		::operator delete (buffer);
	}

	template <class T1, class T2>
	inline void _construct(T1* p, const T2& value) {
		new (p) T1(value);	// placement new, invoke constructor of T1
	}

	template <class T>
	inline void _destroy(T* ptr) {
		ptr->~T();
	}

	/**
	 * The members including data members and function 
	 * members are the same as the STL allocator standard, 
	 * just their name!
	 */
	template <class T>
	class allocator {
	public:
		typedef T			value_type;
		typedef T*			pointer;
		typedef const T*	const_pointer;
		typedef T&			reference;
		typedef const T&	const_reference;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;

		//rebind allocator of type U
		template <class U>
		struct rebind {
			typedef allocator<U> other; // for what ?
		};

		// hint used for locality.
		pointer allocate(size_type n, const void* hint = 0) {
			return _allocate((difference_type)n, (pointer)0);
		}

		void deallocate(pointer p, size_type n) { _deallocate(p); }

		void construct(pointer p, const T& value) {
			_construct(p, value);
		}

		void destroy(pointer p) { _destroy(p); }

		pointer address(reference x) { return (pointer)&x; }

		const_pointer const_address(const_reference x) { return (const_reference)&x; }

		size_type max_size() const { return size_type(UINT_MAX / sizeof(T)); }
	};
}


// for test...
// karel::allocator above can't be applied to vector as a class parameter

#include <vector>
#include <iterator>

int main()
{
	int a[5] = { 1,2,3,4,5 };
	std::vector<int, karel::allocator<int>> v(a, a + 5);
	std::ostream_iterator<int> out_it(std::cout, ", ");
	std::copy(v.begin(), v.end(), out_it);

	system("pause");
	return 0;
}