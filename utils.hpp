#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{
	template <class InputIterator1, class InputIterator2>
		bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, InputIterator2 last2)
		{
			while (first1 != last1)
			{
				if (first2 == last2 || *first2 < *first1)
					return (false);
				else if (*first1 < *first2)
					return (true);
				++first1;
				++first2;
			}
			return (first2 != last2);
		}
	// Checks if type is an integral
	template <typename T>
		struct is_integral { static const bool value = false; };

	template <>
		struct is_integral<bool> { static const bool value = true; };

	template <>
		struct is_integral<char> { static const bool value = true; };

	template <>
		struct is_integral<short> { static const bool value = true; };

	template <>
		struct is_integral<int> { static const bool value = true; };

	template <>
		struct is_integral<long> { static const bool value = true; };

	template <>
		struct is_integral<long long> { static const bool value = true; };

	template <>
		struct is_integral<unsigned char> { static const bool value = true; };

	template <>
		struct is_integral<unsigned short> { static const bool value = true; };

	template <>
		struct is_integral<unsigned int> { static const bool value = true; };

	template <>
		struct is_integral<unsigned long> { static const bool value = true; };

	template <>
		struct is_integral<unsigned long long> { static const bool value = true; };


	struct true_type {
		operator bool() { return true; }
	};
	struct false_type  {
		operator bool() { return false; }
	};

	// Checks if T and U name the same type
	template<class T, class U>
		struct is_same {
			enum { value = 0 };
			typedef false_type type;
		};

	template<class T>
		struct is_same<T, T> {
			enum { value = 1 };
			typedef true_type type;
		};

	// Define a nested type if some predicate holds.
	template<bool Cond, class T = void> struct enable_if {};
	template<class T> struct enable_if<true, T> { typedef T type; };

	/*
	 ** Iterators tags :
	 ** Defines the category of an iterator. Each tag is an empty type. 
	 */
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };
}

#endif
