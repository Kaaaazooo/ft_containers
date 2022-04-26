#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <iostream>
# include <stdexcept>

# include "iterator.hpp"
# include "vector_iterator.hpp"
# include "utils.hpp"

namespace ft
{
	template <class T>
		class vector_iterator;
	template <class T, class Allocator = std::allocator<T> >
		class vector
		{
			public:
				typedef T												value_type;
				typedef Allocator										allocator_type;

				typedef typename allocator_type::reference				reference;
				typedef typename allocator_type::const_reference		const_reference;
				typedef typename allocator_type::pointer				pointer;
				typedef typename allocator_type::const_pointer			const_pointer;

				typedef vector_iterator<value_type>						iterator;
				typedef vector_iterator<const value_type>				const_iterator;
				typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
				typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

				typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
				typedef size_t	size_type;

			protected:
				allocator_type _alloc;
				pointer _start;
				pointer _finish;
				pointer _end_of_storage;

			public:

				//Constructors
				explicit vector (const allocator_type& alloc = allocator_type())
					: _alloc(alloc), _start(NULL), _finish(NULL), _end_of_storage(NULL) { }

				explicit vector (size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type()) : _alloc(alloc)
				{
					_start = _alloc.allocate(n);
					_finish = _start;
					_end_of_storage = _start + n;
					while (n--)
					{
						_alloc.construct(_finish, val);
						++_finish;
					}
				}

				template <class InputIterator>
					vector(InputIterator first, InputIterator last,
							const allocator_type& alloc = allocator_type(),
							typename enable_if<!is_integral<InputIterator>::value>::type* = 0) : _alloc(alloc)
					{
						size_t size = 0;
						InputIterator tmp = first;
						while (tmp++ != last)
							++size;
						_start = _alloc.allocate(size);
						_finish = _start + size;
						_end_of_storage = _finish;
						for (size_t i = 0; i < size; i++)
							_alloc.construct(_start + i, *first++);
					}

				vector(const vector& x) : _alloc(x._alloc) {
					_start = _alloc.allocate(x.size());
					_finish = _start + x.size();
					_end_of_storage = _finish;
					size_t n = 0;
					for (const_iterator it = x.begin(); it != x.end(); it++)
						_alloc.construct(_start + n++, *it);
				}

				// Destructor
				~vector()
				{
					for (iterator it = begin(); it != end(); it++)
						_alloc.destroy(&(*it));
					_alloc.deallocate(_start, capacity());
				}

				// Content assignation
				vector& operator= (const vector& x)
				{
					if (this != &x)
						assign(x.begin(), x.end());
					return *this;
				}

				// Iterators
				iterator begin()				{ return iterator(_start); }
				const_iterator begin() const	{ return const_iterator(_start); }

				iterator end()				{ return iterator(_finish); }
				const_iterator end() const	{ return const_iterator(_finish); }

				reverse_iterator rbegin() { return reverse_iterator(this->end()); }
				const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }

				reverse_iterator rend() { return reverse_iterator(this->begin()); }
				const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }

				// Capacity
				size_type size() const	{ return _finish - _start; }

				size_type max_size() const { return _alloc.max_size(); }

				void resize(size_type n, value_type val = value_type())
				{
					if (n > max_size())
						throw (std::length_error("vector::resize: n > this->max_size()"));
					if (n > capacity())
						reallocate(capacity() * 2 >= n ? capacity() : n);
					if (n < size())
					{
						while (n < size())
						{
							_alloc.destroy(--_finish);
						}
					}
					else
					{
						while (n > size())
						{
							push_back(val);
						}
					}
				}

				size_type capacity() const { return _end_of_storage - _start; }

				bool empty() const { return (size() ? false : true); }

				void reserve (size_type n)
				{
					if (n > max_size())
						throw (std::length_error("vector::reserve: n > this->max_size()"));
					else if (n > capacity())
						reallocate(n);
				}

				// Element access
				reference operator[] (size_type n) { return *(_start + n); }
				const_reference operator[] (size_type n) const { return *(_start + n); }

				reference at(size_type n) {
					if (n < size())
						return *(_start + n);
					else
						throw std::out_of_range("vector::at: out of range");
				}
				const_reference at (size_type n) const {
					if (n < size())
						return *(_start + n);
					else
						throw std::out_of_range("vector::at: out of range");
				}

				reference front() { return *_start; }
				const_reference front() const { return *_start; }

				reference back() { return *(_finish - 1); }
				const_reference back() const { return *(_finish - 1); }

				// Modifiers
				template <class InputIterator>
					void assign (InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value,
							InputIterator>::type* = NULL)
					{
						size_type new_size = 0;
						for (InputIterator tmp = first; tmp != last; tmp++)
							++new_size;
						if (new_size > capacity())
							reallocate(new_size);
						this->clear();
						while (first != last)
							this->push_back(*first++);
					}

				void assign (size_type n, const T& val)
				{
					if (n > capacity())
						reallocate(n);
					this->clear();
					while (n--)
						this->push_back(val);
				}

				void push_back (const value_type& val)
				{
					if (_finish == _end_of_storage)
						this->reallocate(size() ? size() * 2 : 1);
					_alloc.construct(_finish++, val);
				}

				void pop_back () { _alloc.destroy(--_finish); }

				iterator insert (iterator position, const value_type& val)
				{
					size_type pos = position - begin();
					if (position == end())
					{
						push_back(val);
					}
					else if (pos < size())
					{
						if (_finish == _end_of_storage)
							this->reallocate(size() ? size() * 2 : 1);
						_alloc.construct(_finish, *(_finish - 1));
						size_type n = size();
						while (n > pos)
						{
							_start[n] = _start[n - 1];
							--n;
						}
						_start[pos] = val;
						++_finish;
					}
					return (_start + pos);
				}

				void insert (iterator position, size_type n, const value_type& val)
				{
					if (size() + n > capacity())
					{
						difference_type diff = position - begin();
						this->reallocate(size() + n);
						position = begin() + diff;
					}
					for (size_t i = 0; i < n; i++)
					{
						position = insert(position, val);
						++position;
					}
				}

				template <class InputIterator>
					void insert (iterator position, InputIterator first, InputIterator last,
					 typename ft::enable_if<!ft::is_integral<InputIterator>::value,
					 	InputIterator>::type* = NULL)
					{
						size_type i = 0;
						for (InputIterator tmp = first; tmp!=last; tmp++)
							++i;
						if (size() + i > capacity())
						{
							difference_type diff = position - begin();
							this->reallocate(size() + i);
							position = begin() + diff;
						}
						while (first != last)
						{
							position = insert(position, *first++);
							++position;
						}
					}

				iterator erase (iterator position)
				{
					if (size())
					{
						size_type n = position.base() - begin().base();
						while (_start + n < _finish - 1)
						{
							_start[n] = _start[n + 1];
							++n;
						}
						_alloc.destroy(_finish--);
					}
					return (position);
				}

				iterator erase (iterator first, iterator last)
				{
					if (size())
					{
						size_type i = first.base() - begin().base();
						size_type n = last.base() - begin().base();
						while (_start + n < _finish)
						{
							_start[i] = _start[n];
							++i;
							++n;
						}
						while (_finish != _start + i)
							_alloc.destroy(_finish--);
					}
					return (first);
				}

				void swap (vector& x)
				{
					if (x != *this)
					{
						pointer tmp_start = x._start;
						pointer tmp_finish = x._finish;
						pointer tmp_end_of_storage = x._end_of_storage;
						allocator_type tmp_allocator = x._alloc;

						x._start = this->_start;
						x._finish = this->_finish;
						x._end_of_storage = this->_end_of_storage;
						x._alloc = this->_alloc;

						this->_start = tmp_start;
						this->_finish = tmp_finish;
						this->_end_of_storage = tmp_end_of_storage;
						this->_alloc = tmp_allocator;
					}
				}

				void clear()
				{
					for (size_type i = 0; i < size(); i ++)
						_alloc.destroy(_start + i);
					_finish = _start;
				}

				// Allocator
				allocator_type get_allocator() const { return _alloc; }

			protected:
				void reallocate(size_type new_capacity)
				{
					pointer new_start = _alloc.allocate(new_capacity);
					pointer new_finish = new_start;
					for (size_type i = 0; _start + i != _finish; i++)
					{
						_alloc.construct(new_finish++, _start[i]);
						_alloc.destroy(_start + i);
					}
					if (_start)
						_alloc.deallocate(_start, capacity());
					_start = new_start;
					_finish = new_finish;
					_end_of_storage = _start + new_capacity;
				}
		};

	template <class T, class Alloc>
		bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

	template <class T, class Alloc>
		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return !(lhs == rhs); }

	template <class T, class Alloc>
		bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

	template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return !(rhs < lhs); }

	template <class T, class Alloc>
		bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return rhs < lhs; }

	template <class T, class Alloc>
		bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return !(lhs < rhs); }

	template <class T, class Alloc>
		void swap(vector<T, Alloc>& x, vector<T, Alloc>& y) { x.swap(y); }
}

#endif
