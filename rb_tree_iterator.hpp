#ifndef RB_TREE_ITERATOR_HPP
#define RB_TREE_ITERATOR_HPP

# include "iterator.hpp"
# include "rb_tree.hpp"

namespace ft
{
	template<class T>
		class Node;

	template <class T, class Compare , class Alloc>
		class rb_tree;

	template < class T, class Compare >
		class const_rb_tree_iterator;

	template < class T, class Compare = std::less<typename T::first> >
		class rb_tree_iterator : iterator<bidirectional_iterator_tag, T>
		{
			friend class const_rb_tree_iterator<T, Compare>;
			public:
				typedef T												    value_type;
				typedef iterator<bidirectional_iterator_tag, value_type>	iterator_type;
				typedef typename iterator_type::iterator_category			iterator_category;
				typedef typename iterator_type::difference_type				difference_type;
				typedef typename iterator_type::pointer						pointer;
				typedef typename iterator_type::reference					reference;

				typedef Node<T>*			node_pointer;

			private:
				typedef rb_tree_iterator	self_type;

				node_pointer				_current;
				node_pointer				_tnull;
				Compare						_key_comp;

			public:
			rb_tree_iterator(const Compare& key_comp = Compare())
				: _current(), _tnull(), _key_comp(key_comp) { }

			rb_tree_iterator(node_pointer current, node_pointer tnull, const Compare& key_comp = Compare())
				: _current(current), _tnull(tnull), _key_comp(key_comp) { }

			rb_tree_iterator(const self_type& it)
				: _current(it._current), _tnull(it._tnull), _key_comp(it._key_comp) { }

			virtual ~rb_tree_iterator() { }

			self_type &operator=(const self_type& it)
			{
				if (*this == it)
					return (*this);
				this->_current = it._current;
				this->_tnull = it._tnull;
				this->_key_comp = it._key_comp;
				return (*this);
			}

			bool operator==(const self_type& it)
			{ return (this->_current == it._current); }

			bool operator!=(const self_type& it)
			{ return (this->_current != it._current); }

			reference operator*() const
			{ return (this->_current->data); }

			pointer operator->() const
			{ return (&this->_current->data); }

			self_type& operator++(void)
			{
				node_pointer cursor = _current;

				if (cursor == _tnull)
				{
					_current = _tnull->right;
					return *this;
				}
				else if (_current->right == _tnull)
				{
					cursor = _current->parent;
					while (cursor != _tnull
						&& _key_comp(cursor->data.first, _current->data.first))
						cursor = cursor->parent;
					_current = cursor;
				}
				else
				{
					cursor = _current->right;
					if (cursor == _tnull->parent
						&& cursor->right == _tnull)
						_current = cursor;
					else
					{
						while (cursor->left != _tnull)
							cursor = cursor->left;
					}
					_current = cursor;
				}
				return (*this);
			}

			self_type operator++(int)
			{
				self_type tmp(*this);
				operator++();
				return (tmp);
			}

			self_type& operator--(void)
			{
				node_pointer cursor = _current;

				if (cursor == _tnull)
				{
					//std::cout << "_tnull->right :" << _tnull->right->data.first << std::endl;
					_current = _tnull->right;
					return *this;
				}
				else if (_current->left == _tnull)
				{
					cursor = _current->parent;
					while (cursor != _tnull
						&& !_key_comp(cursor->data.first, _current->data.first))
						cursor = cursor->parent;
					_current = cursor;
				}
				else
				{
					cursor = _current->left;
					if (cursor == _tnull->parent
						&& cursor->left == _tnull)
						_current = cursor;
					else
					{
						while (cursor->right != _tnull)
							cursor = cursor->right;
					}
					_current = cursor;
				}
				return (*this);
			}

			self_type operator--(int)
			{
				self_type tmp(*this);
				operator--();
				return (tmp);
			}            
		};

	template < class T, class Compare = std::less<typename T::first> >
	class const_rb_tree_iterator : iterator<bidirectional_iterator_tag, T>
	{
		friend class rb_tree_iterator<T, Compare>;
		public :
			typedef const T												    value_type;

			typedef iterator<bidirectional_iterator_tag, value_type>	iterator_type;
			typedef typename iterator_type::iterator_category			iterator_category;
			typedef typename iterator_type::difference_type				difference_type;
			typedef typename iterator_type::pointer						pointer;
			typedef typename iterator_type::reference					reference;

			typedef Node<T>*					node_pointer;

		private:
			typedef const_rb_tree_iterator		self_type;

			node_pointer						_current;
			node_pointer						_tnull;
			Compare								_key_comp;

		public:

			const_rb_tree_iterator(const Compare& key_comp = Compare())
				: _current(), _tnull(), _key_comp(key_comp) { }

			const_rb_tree_iterator(node_pointer node, node_pointer tnull,
				const Compare& key_comp = Compare())
				: _current(node), _tnull(tnull), _key_comp(key_comp) { }

			const_rb_tree_iterator(const self_type& it)
				: _current(it._current), _tnull(it._tnull), _key_comp() { }

			const_rb_tree_iterator(const rb_tree_iterator<T, Compare>& it)
				: _current(it._current), _tnull(it._tnull), _key_comp() { }

			virtual ~const_rb_tree_iterator() { }

			self_type &operator=(const self_type& it)
			{
				if (*this == it)
					return (*this);
				this->_current = it._current;
				this->_tnull = it._tnull;
				this->_key_comp = it._key_comp;
				return (*this);
			}
			
			bool operator==(const self_type& it)
			{ return (this->_current == it._current); }

			bool operator!=(const self_type& it)
			{ return (this->_current != it._current); }

			reference operator*() const
			{ return (this->_current->data); }

			pointer operator->() const
			{ return (&this->_current->data); }

			self_type& operator++(void)
			{
				node_pointer cursor = _current;

				if (_current->right == _tnull)
				{
					cursor = _current->parent;
					while (cursor != _tnull
						&& _key_comp(cursor->data.first, _current->data.first))
						cursor = cursor->parent;
					_current = cursor;
				}
				else if (cursor == _tnull)
					_current = _tnull->right;
				else
				{
					cursor = _current->right;
					if (cursor == _tnull->parent
						&& cursor->right == _tnull)
						_current = cursor;
					else
					{
						while (cursor->left != _tnull)
							cursor = cursor->left;
					}
					_current = cursor;
				}
				return (*this);
			}

			self_type operator++(int)
			{
				self_type tmp(*this);
				operator++();
				return (tmp);
			}

			self_type& operator--(void)
			{
				node_pointer cursor = _current;

				if (_current->left == _tnull)
				{
					cursor = _current->parent;
					while (cursor != _tnull
						&& !_key_comp(cursor->data.first, _current->data.first))
						cursor = cursor->parent;
					_current = cursor;
				}
				else if (cursor == _tnull)
					_current = _tnull->right;
				else
				{
					cursor = _current->left;
					if (cursor == _tnull->parent
						&& cursor->left == _tnull)
						_current = cursor;
					else
					{
						while (cursor->right != _tnull)
							cursor = cursor->right;
					}
					_current = cursor;
				}
				return (*this);
			}

			self_type operator--(int)
			{
				self_type tmp(*this);
				operator--();
				return (tmp);
			}            
	};
}

#endif
