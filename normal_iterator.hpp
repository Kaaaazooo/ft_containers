#ifndef NORMAL_ITERATOR_HPP
#define NORMAL_ITERATOR_HPP

# include "iterator.hpp"

namespace ft
{
	// NORMAL ITERATOR

	template<typename tIterator, typename tContainer>
		class normal_iterator
		{
			protected:
				tIterator	current;
				typedef ft::iterator_traits<tIterator>				traits_type;
			public:
				typedef tIterator									iterator_type;
				typedef typename traits_type::iterator_category		iterator_category;
				typedef typename traits_type::value_type			value_type;
				typedef typename traits_type::difference_type		difference_type;
				typedef typename traits_type::reference				reference;
				typedef typename traits_type::pointer				pointer;

				normal_iterator() {}
				explicit normal_iterator( const tIterator& i ) : current(i) {}
				template<typename Iter>
					normal_iterator(const normal_iterator<Iter, typename ft::enable_if<
							(ft::is_same<Iter, typename tContainer::pointer>::value)
							, tContainer>::type>& i) : current(i.base()) {}

				reference operator*() const		{ return *current; }
				pointer operator->() const		{ return current; }

				normal_iterator& operator++() {
					++current;
					return *this;
				}
				normal_iterator operator++(int) { return normal_iterator(current++); }

				normal_iterator& operator--() {
					--current;
					return *this;
				}
				normal_iterator operator--(int) { return normal_iterator(current--); }

				reference operator[](difference_type n) const	{ return current[n]; }

				normal_iterator& operator+=(difference_type n) {
					current += n;
					return *this;
				}

				normal_iterator operator+(difference_type n) { return normal_iterator(current + n); }

				normal_iterator& operator-=(difference_type n) {
					current -= n;
					return *this;
				}

				normal_iterator operator-(difference_type n) { return normal_iterator(current - n); }

				const tIterator& base() const	{ return current; }
		};

	template<typename Iterator, typename Container>
		bool operator==(const normal_iterator<Iterator, Container>& lhs,
				const normal_iterator<Iterator, Container>& rhs)
		{
			return lhs.base() == rhs.base();
		}

	template<typename Iterator, typename Container>
		bool operator!=(const normal_iterator<Iterator, Container>& lhs,
				const normal_iterator<Iterator, Container>& rhs)
		{
			return lhs.base() != rhs.base();
		}

	template<typename Iterator, typename Container>
		bool operator<(const normal_iterator<Iterator, Container>& lhs,
				const normal_iterator<Iterator, Container>& rhs)
		{
			return lhs.base() < rhs.base();
		}

	template<typename Iterator, typename Container>
		bool operator>(const normal_iterator<Iterator, Container>& lhs,
				const normal_iterator<Iterator, Container>& rhs)
		{
			return lhs.base() > rhs.base();
		}

	template<typename Iterator, typename Container>
		bool operator<=(const normal_iterator<Iterator, Container>& lhs,
				const normal_iterator<Iterator, Container>& rhs)
		{
			return lhs.base() <= rhs.base();
		}

	template<typename Iterator, typename Container>
		bool operator>=(const normal_iterator<Iterator, Container>& lhs,
				const normal_iterator<Iterator, Container>& rhs)
		{
			return lhs.base() >= rhs.base();
		}

	template<typename IteratorL, typename IteratorR, typename Container>
		typename normal_iterator<IteratorL, Container>::difference_type
		operator-(const normal_iterator<IteratorL, Container> lhs,
				const normal_iterator<IteratorR, Container> rhs)
		{
			return lhs.base() - rhs.base();
		}

	template<typename Iterator, typename Container>
		typename normal_iterator<Iterator, Container>::difference_type
		operator-(const normal_iterator<Iterator, Container> lhs,
				const normal_iterator<Iterator, Container> rhs)
		{
			return lhs.base() - rhs.base();
		}

	template<typename IteratorL, typename IteratorR, typename Container>
		typename normal_iterator<IteratorL, Container>::difference_type
		operator+(const normal_iterator<IteratorL, Container> lhs,
				const normal_iterator<IteratorR, Container> rhs)
		{
			return lhs.base() + rhs.base();
		}

	template<typename Iterator, typename Container>
		typename normal_iterator<Iterator, Container>::difference_type
		operator+(const normal_iterator<Iterator, Container> lhs,
				const normal_iterator<Iterator, Container> rhs)
		{
			return lhs.base() + rhs.base();
		}
}
#endif
