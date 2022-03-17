#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <memory>
# include <stdexcept>
# include "iterator.hpp"
# include "vector_iterator.hpp"

namespace ft
{
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
				typedef size_t size_type;

			protected:
				allocator_type allocator;
				pointer start;
				pointer finish;
				pointer end_of_storage;

			public:
				const_pointer getStart() const
				{
					return start;
				}

				//Constructors
				explicit vector (const allocator_type& alloc = allocator_type()) :
				allocator(alloc)
				{
					start = NULL;
					finish = NULL;
					end_of_storage = NULL;
				}

				explicit vector (size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type()) : allocator(alloc)
				{
					start = allocator.allocate(n);
					finish = start + n;
					end_of_storage = finish;
					for (size_t i = 0; i < n; i++)
						allocator.construct(start + i, val);
				}

				template <class InputIterator>
					vector(InputIterator first, InputIterator last,
							const allocator_type& alloc = allocator_type(),
							typename enable_if<!is_integral<InputIterator>::value>::type* = 0) : allocator(alloc)
					{
						size_t size = 0;
						InputIterator tmp = first;
						while (tmp++ != last)
							++size;
						start = allocator.allocate(size);
						finish = start + size;
						end_of_storage = finish;
						for (size_t i = 0; i < size; i++)
							allocator.construct(start + i, *first++);
					}

				vector(const vector& x) : allocator(x.allocator) {
					start = allocator.allocate(x.capacity());
					finish = start + x.size();
					end_of_storage = start + x.capacity();
					size_t n = 0;
					for (const_iterator it = x.begin(); it != x.end(); it++)
						allocator.construct(start + n++, *it);
				}

				~vector()
				{
					for (iterator it = begin(); it != end(); it++)
						allocator.destroy(&(*it));
					allocator.deallocate(start, capacity());
				}

				vector& operator= (const vector& x)
				{
					assign(x.begin(), x.end());
					return *this;
				}

				iterator begin()				{ return iterator(start); }
				const_iterator begin() const	{ return const_iterator(start); }

				iterator end()				{ return iterator(finish); }
				const_iterator end() const	{ return const_iterator(finish); }

				reverse_iterator rbegin() { return reverse_iterator(this->end()); }
				const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }

				reverse_iterator rend() { return reverse_iterator(this->begin()); }
				const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }

				size_type size() const	{ return finish - start; }

				size_type max_size() const { return allocator.max_size(); }

				void resize(size_type n, value_type val = value_type())
				{
					if (n > capacity())
						reallocate(n);
					if (n < size())
					{
						while (n < size())
						{
							allocator.destroy(--finish);
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

				size_type capacity() const { return end_of_storage - start; }

				bool empty() const { return (size() ? false : true); }

				void reserve (size_type n)
				{
					if (n > max_size())
						throw (std::length_error("vector::reserve"));
					else if (n > capacity())
						reallocate(n);
				}

				reference operator[] (size_type n) { return *(start + n); }
				const_reference operator[] (size_type n) const { return *(start + n); }

				reference at(size_type n) {
					if (n < size())
						return *(start + n);
					else
						throw std::out_of_range("vector");
				}
				const_reference at (size_type n) const {
					if (n < size())
						return *(start + n);
					else
						throw std::out_of_range("vector");
				}

				reference front() { return *start; }
				const_reference front() const { return *start; }

				reference back() { return *(finish - 1); }
				const_reference back() const { return *(finish - 1); }

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
						size_type i;
						for (i = 0; first != last; i++)
							insert(begin() + i, *(first++));
						while (i < size())
							allocator.destroy(start + i++);
						finish = start + new_size;
					}

				void assign (size_type n, const T& val)
				{
					if (n > capacity())
						this->reallocate(n);
					for (size_type i = 0; i < n; i++)
					{
						allocator.destroy(start + i);
						allocator.construct(start + i, val);
					}
					finish = start + n;
					while (n < size())
						allocator.destroy(start + n++);
				}

				void push_back (const value_type& val)
				{
					if (finish == end_of_storage)
						this->reallocate(size() ? size() * 2 : 1);
					allocator.construct(finish++, val);
				}

				void pop_back () { allocator.destroy(--finish); }

				iterator insert (iterator position, const value_type& val)
				{
					size_type pos = position - begin();
					if (position == end())
					{
						push_back(val);
					}
					else if (pos < size())
					{
						if (finish == end_of_storage)
							this->reallocate(size() ? size() * 2 : 1);
						allocator.construct(finish, *(finish - 1));
						size_type n = size();
						while (n > pos)
						{
							start[n] = start[n - 1];
							--n;
						}
						start[pos] = val;
						++finish;
					}
					return (start + pos);
				}

				void insert (iterator position, size_type n, const value_type& val)
				{
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
						while (start + n < finish - 1)
						{
							start[n] = start[n + 1];
							++n;
						}
						allocator.destroy(finish--);
					}
					return (position);
				}

				iterator erase (iterator first, iterator last)
				{
					if (size())
					{
						size_type i = first.base() - begin().base();
						size_type n = last.base() - begin().base();
						while (start + n < finish)
						{
							start[i] = start[n];
							++i;
							++n;
						}
						while (finish != start + i)
							allocator.destroy(finish--);
					}
					return (first);
				}

				void swap (vector& x)
				{
					if (x != *this)
					{
						pointer tmp_start = x.start;
						pointer tmp_finish = x.finish;
						pointer tmp_end_of_storage = x.end_of_storage;
						allocator_type tmp_allocator = x.allocator;

						x.start = this->start;
						x.finish = this->finish;
						x.end_of_storage = this->end_of_storage;
						x.allocator = this->allocator;

						this->start = tmp_start;
						this->finish = tmp_finish;
						this->end_of_storage = tmp_end_of_storage;
						this->allocator = tmp_allocator;
					}
				}

				void clear()
				{
					for (size_type i = 0; i < size(); i ++)
						allocator.destroy(start + i);
					finish = start;
				}


			protected:
				void reallocate(size_type new_capacity)
				{
					pointer new_start = allocator.allocate(new_capacity);
					pointer new_finish = new_start;
					for (size_type i = 0; start + i != finish; i++)
					{
						allocator.construct(new_finish++, start[i]);
						allocator.destroy(start + i);
					}
					allocator.deallocate(start, capacity());
					start = new_start;
					finish = new_finish;
					end_of_storage = start + new_capacity;
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
}

#endif
