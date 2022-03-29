#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <stdexcept>
# include <algorithm>

# include "iterator.hpp"
# include "pair.hpp"
# include "rb_tree.hpp"

namespace ft
{

	template < class Key, class T, class Compare = std::less<Key>,
		class Alloc = std::allocator<pair<const Key,T> > >
		class map
		{
			public:
				typedef Key										key_type;
				typedef T										mapped_type;
				typedef ft::pair<const key_type, mapped_type>	value_type;
				typedef Compare									key_compare;
				class value_compare : std::binary_function<value_type, value_type, bool>
				{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
					friend class map;
					protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
					public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
				};

				typedef rb_tree<value_type, Compare, Alloc>							tree_t;

				typedef Alloc  allocator_type;
				typedef typename allocator_type::reference							reference;
				typedef typename allocator_type::const_reference					const_reference;
				typedef typename allocator_type::pointer							pointer;
				typedef typename allocator_type::const_pointer						const_pointer;

				typedef rb_tree_iterator<value_type, Compare>						iterator;
				typedef const_rb_tree_iterator<value_type, Compare>					const_iterator;
				typedef typename ft::reverse_iterator<iterator>						reverse_iterator;
				typedef typename ft::reverse_iterator<const_iterator>				const_reverse_iterator;
				typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;
				typedef size_t														size_type;

			private:
				allocator_type		_alloc;
				key_compare			_comp;
				tree_t				_tree;

			public:
				void print(void) const { _tree.print(); }

				explicit map (const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type())
					: _alloc(alloc), _comp(comp), _tree() { }

				template <class InputIterator>
					map (InputIterator first, InputIterator last,
						const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type())
						: _alloc(alloc), _comp(comp), _tree()
					{
						this->insert(first, last);
					}

				map (const map& x) : _alloc(x._alloc), _comp(x._comp), _tree(x._tree) { }

				map& operator= (const map& x)
				{
					if (&x == this)
						return (*this);
					this->clear();
					this->insert(x.begin(), x.end());
					return (*this);
				}

				// Iterators

				iterator begin()
				{ return (iterator(_tree.getMin(), _tree.getEnd())); }

				const_iterator begin() const
				{ return (const_iterator(_tree.getMin(), _tree.getEnd())); }

				iterator end()
				{ return (iterator(_tree.getEnd(), _tree.getEnd())); }

				const_iterator end() const
				{ return (const_iterator(_tree.getEnd(), _tree.getEnd())); }

				reverse_iterator rbegin()
				{ return (reverse_iterator(this->end())); }

				const_reverse_iterator rbegin() const
				{ return (const_reverse_iterator(this->end())); }

				reverse_iterator rend()
				{ return (reverse_iterator(this->begin())); }

				const_reverse_iterator rend() const
				{ return (const_reverse_iterator(this->begin())); }

				// Capacity

				bool empty() const
				{ return (this->size() ? false : true); }

				size_type size() const
				{ return _tree.size(); }

				size_type max_size() const
				{ return (_tree.max_size()); }

				// Element access

				mapped_type& operator[] (const key_type& k)
				{
					return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
				} 

				// Modifiers

				pair<iterator,bool> insert (const value_type& val)
				{
					size_type size_before = size();
					return ft::make_pair(iterator(_tree.add(val), _tree.getEnd()),
							size_before != size());
				}

				iterator insert (iterator position, const value_type& val)
				{
					(void)position;
					return (iterator(_tree.add(val), _tree.getEnd()));
				}

				template <class InputIterator>
					void insert (InputIterator first, InputIterator last)
					{
						while (first != last)
							this->insert(*first++);
					}

				void erase (iterator position)
				{ this->erase((*position).first); }

				size_type erase (const key_type& k)
				{
					return (_tree.del(k));
				}

				void erase (iterator first, iterator last)
				{
					while (first != last)
						this->erase(first++);
				}

				void swap (map& x)
				{ _tree.swap(x._tree); }

				void clear()
				{ _tree.clear(); }

				// Observers

				key_compare key_comp() const
				{ return (key_compare()); }

				value_compare value_comp() const
				{ return (value_compare(key_compare())); }

				// Operations

				iterator find (const key_type& k)
				{ return (iterator(_tree.find(k), _tree.getEnd())); }

				const_iterator find (const key_type& k) const
				{ return (const_iterator(_tree.find(k), _tree.getEnd())); }

				size_type count (const key_type& k) const
				{
					return (_tree.find(k) != _tree.getEnd());
				}

				iterator lower_bound (const key_type& k)
				{ return (iterator(_tree.lower_bound(k), _tree.getEnd())); }

				const_iterator lower_bound (const key_type& k) const
				{ return (const_iterator(_tree.lower_bound(k), _tree.getEnd())); }

				iterator upper_bound (const key_type& k)
				{ return (iterator(_tree.upper_bound(k), _tree.getEnd())); }

				const_iterator upper_bound (const key_type& k) const
				{ return (const_iterator(_tree.upper_bound(k), _tree.getEnd())); }

				ft::pair<const_iterator, const_iterator> equal_range (const key_type& k) const
				{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }

				ft::pair<iterator, iterator> equal_range (const key_type& k)
				{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }

				// Allocator

				allocator_type get_allocator() const
				{ return _tree.getAllocator(); }

				iterator get_max(void) const { return iterator(_tree.getMax(), _tree.getEnd()); }
		};

	template <class Key, class T, class Compare, class Alloc>
		bool operator== ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ){
			if (lhs.size() != rhs.size())
				return (false);
			typename ft::map<Key, T, Compare, Alloc>::const_iterator lhs_it = lhs.begin();
			typename ft::map<Key, T, Compare, Alloc>::const_iterator rhs_it = rhs.begin();
			while (lhs_it != lhs.end())
			{
				if (*lhs_it != *rhs_it)
					return (false);
				lhs_it++;
				rhs_it++;
			}
			return (true);
		}

	template <class Key, class T, class Compare, class Alloc>
		bool operator!= ( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs ) {
			return !(lhs == rhs);
		}

	template <class Key, class T, class Compare, class Alloc>
		bool operator<  ( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs ){
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

	template <class Key, class T, class Compare, class Alloc>
		bool operator<= ( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs ){
			return !(rhs < lhs);
		}

	template <class Key, class T, class Compare, class Alloc>
		bool operator>  ( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs ){
			return (rhs < lhs);
		}

	template <class Key, class T, class Compare, class Alloc>
		bool operator>= ( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs ){
			return !(lhs < rhs);
		}

	template< class Key, class T, class Compare, class Alloc >
		void swap( ft::map<Key, T, Compare, Alloc>& lhs, ft::map<Key, T, Compare, Alloc>& rhs ){
			lhs.swap(rhs);
		}
}

#endif
