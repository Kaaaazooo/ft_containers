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

	template < class T >
		class const_rb_tree_iterator;

	template < class T >
		class rb_tree_iterator : iterator<bidirectional_iterator_tag, T>
		{
			friend class const_rb_tree_iterator<T>;
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

			public:
			rb_tree_iterator()
				: _current(), _tnull() { }

			rb_tree_iterator(node_pointer current, node_pointer tnull)
				: _current(current), _tnull(tnull) { }

			rb_tree_iterator(const self_type& it)
				: _current(it._current), _tnull(it._tnull) { }

			virtual ~rb_tree_iterator() { }

			self_type &operator=(const self_type& it)
			{
				if (*this == it)
					return (*this);
				this->_current = it._current;
				this->_tnull = it._tnull;
				return (*this);
			}

			bool operator==(const self_type& it)
			{ return (this->_current == it._current); }

			bool operator==(const const_rb_tree_iterator<T>& it)
			{ return (this->base() == it.base()); }

			bool operator!=(const self_type& it)
			{ return (this->_current != it._current); }

			bool operator!=(const const_rb_tree_iterator<T>& it)
			{ return (this->base() != it.base()); }

			reference operator*() const
			{ return (this->_current->data); }

			pointer operator->() const
			{ return (&this->_current->data); }

			self_type& operator++(void)
			{
				if (_current == _tnull)
				{
					_current = _tnull->left;
				}
				else if (_current->right != _tnull)
				{
					_current = _current->right;
					while (_current->left != _tnull)
						_current = _current->left;
				}
				else
				{
					node_pointer cursor = _current->parent;
					while (cursor->right != _tnull && cursor->right == _current)
					{
						_current = cursor;
						cursor = cursor->parent;
					}
					if (_current->right != cursor)
						_current = cursor;
				}
				return *this;
			}

			self_type operator++(int)
			{
				self_type tmp(*this);
				operator++();
				return (tmp);
			}

			self_type& operator--(void)
			{
				if (_current == _tnull)
					_current = _tnull->right;
				else if (_current->left != _tnull)
				{
					_current = _current->left;
					while (_current->right != _tnull)
						_current = _current->right;
				}
				else
				{
					node_pointer cursor = _current->parent;
					while (cursor->left == _current)
					{
						_current = cursor;
						cursor = cursor->parent;
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

			node_pointer base() const
			{
				return _current;
			}
		};

	template < class T >
	class const_rb_tree_iterator : iterator<bidirectional_iterator_tag, T>
	{
		friend class rb_tree_iterator<T>;
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

		public:

			const_rb_tree_iterator()
				: _current(), _tnull() { }

			const_rb_tree_iterator(node_pointer node, node_pointer tnull)
				: _current(node), _tnull(tnull) { }

			const_rb_tree_iterator(const self_type& it)
				: _current(it._current), _tnull(it._tnull) { }

			const_rb_tree_iterator(const rb_tree_iterator<T>& it)
				: _current(it._current), _tnull(it._tnull) { }

			virtual ~const_rb_tree_iterator() { }

			self_type &operator=(const self_type& it)
			{
				if (*this == it)
					return (*this);
				this->_current = it._current;
				this->_tnull = it._tnull;
				return (*this);
			}
			
			bool operator==(const self_type& it)
			{ return (this->_current == it._current); }

			bool operator==(const rb_tree_iterator<T>& it)
			{ return (this->base() == it.base()); }

			bool operator!=(const self_type& it)
			{ return (this->_current != it._current); }

			bool operator!=(const rb_tree_iterator<T>& it)
			{ return (this->base() != it.base()); }

			reference operator*() const
			{ return (this->_current->data); }

			pointer operator->() const
			{ return (&this->_current->data); }

			self_type& operator++(void)
			{
				if (_current == _tnull)
				{
					_current = _tnull->left;
				}
				else if (_current->right != _tnull)
				{
					_current = _current->right;
					while (_current->left != _tnull)
						_current = _current->left;
				}
				else
				{
					node_pointer cursor = _current->parent;
					while (cursor->right != _tnull && cursor->right == _current)
					{
						_current = cursor;
						cursor = cursor->parent;
					}
					if (_current->right != cursor)
						_current = cursor;
				}
				return *this;
			}

			self_type operator++(int)
			{
				self_type tmp(*this);
				operator++();
				return (tmp);
			}

			self_type& operator--(void)
			{
				if (_current == _tnull)
					_current = _tnull->right;
				else if (_current->left != _tnull)
				{
					_current = _current->left;
					while (_current->right != _tnull)
						_current = _current->right;
				}
				else
				{
					node_pointer cursor = _current->parent;
					while (cursor->left == _current)
					{
						_current = cursor;
						cursor = cursor->parent;
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

			node_pointer base() const
			{
				return _current;
			}
	};
}

#endif
