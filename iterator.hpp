#ifndef ITERATOR_HPP
#define ITERATOR_HPP

# include <cstddef>
# include <iostream>
# include <iostream>
# include "utils.hpp"

namespace ft
{
	/*
	 ** Iterators tags :
	 ** Defines the category of an iterator. Each tag is an empty type. 
	 */
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	/*
	 ** Iterator class :
	 ** Base class template to derive iterators from it. 
	 */
	template <class Category, class T, class Distance = ptrdiff_t,
	class Pointer = T*, class Reference = T&>
		struct iterator
	{
		typedef Category  iterator_category;
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
	};

	/*
	 ** Iterator Traits class :
	 ** Traits class defining properties of iterators.
	 */
	template <class Iterator>
		struct iterator_traits
	{
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	};

	template <class T>
		struct iterator_traits<T*>
		{
			typedef random_access_iterator_tag	iterator_category;
			typedef T							value_type;
			typedef ptrdiff_t					difference_type;
			typedef T*							pointer;
			typedef T&							reference;
		};

	template <class T>
		struct iterator_traits<const T*>
		{
			typedef random_access_iterator_tag	iterator_category;
			typedef T							value_type;
			typedef ptrdiff_t					difference_type;
			typedef const T*					pointer;
			typedef const T&					reference;
		};

	/*
	 ** Predefined iterators :
	 ** Classes derived from the iterator base class.
	 ** Either an input, an ouput, a forward, a bidirectional or a random access iterator.
	 */

	/*
	 ** Back-insert iterator :
	 ** Special output iterators designed to allow algorithms that usually overwrite elements
	 ** to insert new elements at the end of the container.
	 */
	template <class Container>
		class back_insert_iterator :
			public iterator<output_iterator_tag, void, void, void, void>
	{
		protected:
			Container* container;

		public:
			typedef Container container_type;

			explicit back_insert_iterator (Container& x) : container(&x) {}

			back_insert_iterator<Container>& operator=(typename Container::const_reference value)
			{
				container->push_back(value);
				return *this;
			}
			back_insert_iterator<Container>& operator*()		{ return *this; }
			back_insert_iterator<Container>& operator++()		{ return *this; }
			back_insert_iterator<Container> operator++(int)	{ return *this; }
	};

	/*
	 ** Front-insert iterator :
	 ** Special output iterators designed to allow algorithms that usually overwrite elements
	 ** to insert new elements at the beginning of the container.
	 */
	template <class Container>
		class front_insert_iterator :
			public iterator<output_iterator_tag, void, void, void, void>
	{
		public:
			typedef Container container_type;

		protected:
			Container* container;

		public:
			explicit front_insert_iterator (Container& x) : container(&x) {}
			front_insert_iterator<Container>& operator=(typename Container::const_reference value)
			{
				container->push_front(value);
				return *this;
			}
			front_insert_iterator<Container>& operator*()		{ return *this; }
			front_insert_iterator<Container>& operator++()		{ return *this; }
			front_insert_iterator<Container> operator++(int)	{ return *this; }
	};

	/*
	 ** Insert iterator :
	 ** Special output iterators designed to allow algorithms that usually overwrite elements
	 ** to insert new elements at a specific position in the container.
	 */
	template <class Container>
		class insert_iterator :
			public iterator<output_iterator_tag, void, void, void, void>
	{
		public:
			typedef Container container_type;

		protected:
			Container* container;
			typename Container::iterator iter;

		public:
			explicit insert_iterator (Container& x, typename Container::iterator i)
				: container(&x), iter(i) {}
			insert_iterator<Container>& operator=(typename Container::const_reference value)
			{
				iter=container->insert(iter,value);
				++iter;
				return *this;
			}
			insert_iterator<Container>& operator*()		{ return *this; }
			insert_iterator<Container>& operator++()		{ return *this; }
			insert_iterator<Container>& operator++(int)	{ return *this; }
	};

	/*
	 ** Reverse iterator :
	 ** This class reverses the direction in which a bidirectional or random-access iterator
	 ** iterates through a range.
	 */
	template <class Iterator>
		class reverse_iterator :
			iterator<typename iterator_traits<Iterator>::iterator_category
			, typename iterator_traits<Iterator>::value_type
			, typename iterator_traits<Iterator>::difference_type
			, typename iterator_traits<Iterator>::pointer
			, typename iterator_traits<Iterator>::reference>
	{
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;

		protected:
			Iterator baseIt;

		public:
			reverse_iterator() : baseIt() { }
			explicit reverse_iterator(iterator_type it) : baseIt(it) { }
			template <class Iter>
				reverse_iterator (const reverse_iterator<Iter>& rev_it) :
					baseIt(rev_it.base()) { }

			iterator_type base() const { return baseIt; }

			reference operator*() const
			{
				Iterator tmp = baseIt;
				return *--tmp;
			}
			reverse_iterator operator+(difference_type n) const
			{
				return reverse_iterator (baseIt - n);
			}
			reverse_iterator& operator++()
			{
				--baseIt;
				return *this;
			}
			reverse_iterator  operator++(int)
			{
				reverse_iterator tmp = *this;
				++(*this);
				return (tmp);
			}
			reverse_iterator& operator+=(difference_type n)
			{
				baseIt -= n;
				return *this;
			}
			reverse_iterator operator-(difference_type n) const
			{
				return reverse_iterator (baseIt + n);
			}
			reverse_iterator& operator--()
			{
				++baseIt;
				return *this;
			}
			reverse_iterator  operator--(int)
			{
				reverse_iterator tmp = *this;
				--(*this);
				return (tmp);
			}
			reverse_iterator& operator-=(difference_type n)
			{
				baseIt += n;
				return *this;
			}
			pointer operator->() const						{ return &(operator*()); }
			reference operator[](difference_type n) const	{ return base()[- n - 1]; }

			template <class IteratorF>
				friend bool operator>=(const reverse_iterator<IteratorF>& lhs,
						const reverse_iterator<IteratorF>& rhs);
			template <class IteratorF>
				friend bool operator>(const reverse_iterator<IteratorF>& lhs,
						const reverse_iterator<IteratorF>& rhs);
			template <class IteratorF>
				friend bool operator<=(const reverse_iterator<IteratorF>& lhs,
						const reverse_iterator<IteratorF>& rhs);
			template <class IteratorF>
				friend bool operator<(const reverse_iterator<IteratorF>& lhs,
						const reverse_iterator<IteratorF>& rhs);
			template <class IteratorF>
				friend bool operator!=(const reverse_iterator<IteratorF>& lhs,
						const reverse_iterator<IteratorF>& rhs);
			template <class IteratorF>
				friend bool operator==(const reverse_iterator<IteratorF>& lhs,
						const reverse_iterator<IteratorF>& rhs);

	};
	template <class IteratorL, class IteratorR>
		bool operator==(const reverse_iterator<IteratorL>& lhs,
				const reverse_iterator<IteratorR>& rhs)
		{
			return lhs.base() == rhs.base();
		}

	template <class Iterator>
		bool operator==(const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return lhs.base() == rhs.base();
		}

	template <class IteratorL, class IteratorR>
		bool operator!=(const reverse_iterator<IteratorL>& lhs,
				const reverse_iterator<IteratorR>& rhs)
		{
			return !(lhs == rhs);
		}

	template <class Iterator>
		bool operator!=(const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return !(lhs == rhs);
		}

	template <class IteratorL, class IteratorR>
		bool operator<(const reverse_iterator<IteratorL>& lhs,
				const reverse_iterator<IteratorR>& rhs)
		{
			return lhs.base() > rhs.base();
		}

	template <class Iterator>
		bool operator<(const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return lhs.base() > rhs.base();
		}

	template <class IteratorL, class IteratorR>
		bool operator<=(const reverse_iterator<IteratorL>& lhs,
				const reverse_iterator<IteratorR>& rhs)
		{
			return lhs.base() >= rhs.base();
		}

	template <class Iterator>
		bool operator<=(const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return lhs.base() >= rhs.base();
		}

	template <class IteratorL, class IteratorR>
		bool operator>(const reverse_iterator<IteratorL>& lhs,
				const reverse_iterator<IteratorR>& rhs)
		{
			return lhs.base() < rhs.base();
		}

	template <class Iterator>
		bool operator>(const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return lhs.base() < rhs.base();
		}

	template <class IteratorL, class IteratorR>
		bool operator>=(const reverse_iterator<IteratorL>& lhs,
				const reverse_iterator<IteratorR>& rhs)
		{
			return lhs.base() <= rhs.base();
		}

	template <class Iterator>
		bool operator>=(const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return lhs.base() <= rhs.base();
		}

	template <class Iterator>
		reverse_iterator<Iterator>
		operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> rhs)
		{
			return reverse_iterator<Iterator>(rhs.base() - n);
		}

	template <class Iterator>
		typename reverse_iterator<Iterator>::difference_type
		operator-(const reverse_iterator<Iterator> lhs, const reverse_iterator<Iterator> rhs)
		{
			return rhs.base() - lhs.base();
		}

	template <class IteratorL, class IteratorR>
		typename reverse_iterator<IteratorL>::difference_type
		operator-(const reverse_iterator<IteratorL> lhs, const reverse_iterator<IteratorR> rhs)
		{
			return rhs.base() - lhs.base();
		}

}

#endif
