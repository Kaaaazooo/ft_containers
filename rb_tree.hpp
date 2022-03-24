#ifndef RB_TREE_H
#define RB_TREE_H

# include "pair.hpp"

# define RED true
# define BLACK false

namespace ft
{
	/*
	 *	- Red Black Tree Rules :
	 *		1) Every node is red or black.
	 *		2) Root is always black.
	 *		3) New insertions are always red.
	 *		4) Every path from root - leaf has the same nb of BLACK nodes.
	 *		5) No path can have 2 consecutive RED nodes.
	 *		6) Nulls are black.
	 *	- Fixing Rules :
	 *		1) If aunt is BLACK : rotate -> Parent = BLACK, Children = RED.
	 *		2) If aunt is RED : color flip -> Parent = RED Children = BLACK.
	 */


	template<class T>
		class Node
		{
			public:
				T data;
				Node<T> *left;
				Node<T> *right;
				Node<T> *parent;
				bool color;

				Node (void) : data(), left(NULL), right(NULL), parent(NULL), color(RED) { }
				Node (T d) : data(d), left(NULL), right(NULL), parent(NULL), color(RED) { }

				bool isLeftChild(void) { return this->parent->left == this; }
				bool isBlack(void) { return this->color == BLACK; }
		};

	template<class T>
		class rb_tree
		{
			public:
				typedef T									value_type;
				typedef typename value_type::first_type		key_type;
				typedef typename value_type::second_type	mapped_type;
				typedef Node<value_type>*					NodePtr;

			protected:
				NodePtr	_tnull;
				NodePtr	_root;
				size_t	_size;

			public:
				rb_tree(void)
				{
					_tnull = new Node<T>();
					_tnull->parent = NULL;
					_tnull->left = NULL;
					_tnull->right = NULL;
					_tnull->color = BLACK;
					_root = _tnull;
					_size = 0;
				}
				~rb_tree(void)
				{
					freeTree(_root);
					delete(_tnull);
				}
				void add (value_type newMapped)
				{
					NodePtr node = new Node<value_type>(newMapped);
					node->data = newMapped;
					node->left = _tnull;
					node->right = _tnull;
					node->parent = _tnull;
					if (_root == _tnull)
					{
						_root = node;
						_root->color = BLACK;
					}
					else
					{
						add(_root, node);
					}
					++_size;
				}
				void del(key_type key)
				{
					del(find(key, _root));
				}
				mapped_type find (key_type key)
				{
					NodePtr node = find(key, _root);
					if (node && node != _tnull)
						return (node->data.second);
					else
						return (mapped_type());
				}
			private:
				void freeTree(NodePtr node)
				{
					if (node == NULL || node == _tnull)
						return ;
					freeTree(node->left);
					freeTree(node->right);
					delete(node);
					node = NULL;
				}

				void rotate (NodePtr node)
				{
					if (node->isLeftChild())
					{
						if (node->parent->isLeftChild())
						{
							rightRotate(node->parent->parent);
							node->color = RED;
							node->parent->color = BLACK;
							if (node->parent->right != _tnull)
								node->parent->right->color = RED;
						}
						else
						{
							rightLeftRotate(node->parent->parent);
							node->color = BLACK;
							node->right->color = RED;
							node->left->color = RED;
						}
					}
					else
					{
						if (!node->parent->isLeftChild())
						{
							leftRotate(node->parent->parent);
							node->color = RED;
							node->parent->color = BLACK;
							if (node->parent->left != _tnull)
								node->parent->left->color = RED;
						}
						else
						{
							leftRightRotate(node->parent->parent);
							node->color = BLACK;
							node->left->color = RED;
							node->right->color = RED;
						}
					}
				}

				void leftRotate(NodePtr node)
				{
					NodePtr tmp = node->right;
					node->right = tmp->left;
					if (node->right != _tnull)
					{
						node->right->parent = node;
					}
					if (node->parent == _tnull)
					{
						_root = tmp;
						tmp->parent = _tnull;
					}
					else
					{
						tmp->parent = node->parent;
						if (node->isLeftChild())
						{
							tmp->parent->left = tmp;
						}
						else
						{
							tmp->parent->right = tmp;
						}
					}
					tmp->left = node;
					node->parent = tmp;
				}

				void rightRotate(NodePtr node)
				{
					NodePtr tmp = node->left;
					node->left = tmp->right;
					if (node->left != _tnull)
					{
						node->left->parent = node;
					}
					if (node->parent == _tnull)
					{
						_root = tmp;
						tmp->parent = _tnull;
					}
					else
					{
						tmp->parent = node->parent;
						if (!node->isLeftChild())
						{
							tmp->parent->right = tmp;
						}
						else
						{
							tmp->parent->left = tmp;
						}
					}
					tmp->right = node;
					node->parent = tmp;
				}

				void leftRightRotate(NodePtr node)
				{
					leftRotate(node->left);
					rightRotate(node);
				}

				void rightLeftRotate(NodePtr node)
				{
					rightRotate(node->right);
					leftRotate(node);
				}
				void checkColor(NodePtr node)
				{
					if (node == _root)
					{
						if (!node->isBlack())
							node->color = BLACK;
						return;
					}
					if (!node->isBlack() && !node->parent->isBlack())
					{
						correctTree(node);
					}
					if (node != _root)
						checkColor(node->parent);
				}

				void correctTree(NodePtr node)
				{
					if (node->parent->isLeftChild())
					{
						// aunt is node.parent.parent.right
						if (node->parent->parent->right == _tnull || node->parent->parent->right->isBlack())
						{
							rotate(node);
							return ;
						}
						if (node->parent->parent->right != _tnull)
							node->parent->parent->right->color = BLACK;
						node->parent->parent->color = RED;
						node->parent->color = BLACK;
					}
					else
					{
						// aunt is node.parent.parent.left
						if (node->parent->parent->left == _tnull || node->parent->parent->left->isBlack())
						{
							rotate(node);
							return ;
						}
						if (node->parent->parent->left != _tnull)
							node->parent->parent->left->color = BLACK;
						node->parent->parent->color = RED;
						node->parent->color = BLACK;
					}
				}

				void add(NodePtr parent, NodePtr newNode)
				{
					if (newNode->data > parent->data)
					{
						if (parent->right == _tnull)
						{
							parent->right = newNode;
							newNode->parent = parent;
						}
						else
							add(parent->right, newNode);
					}
					else
					{
						if (parent->left == _tnull)
						{
							parent->left = newNode;
							newNode->parent = parent;
						}
						else
							add(parent->left, newNode);
					}
					checkColor(newNode);
				}

				void fixDelete(NodePtr node)
				{
					NodePtr tmp;
					while (node != _root && node->color == BLACK)
					{
						if (node->isLeftChild())
						{
							tmp = node->parent->right;
							if (tmp->color == RED)
							{
								tmp->color = BLACK;
								node->parent->color = RED;
								leftRotate(node->parent);
								tmp = node->parent->right;
							}

							if (tmp->left->color == BLACK && tmp->right->color == BLACK)
							{
								tmp->color = RED;
								node = node->parent;
							}
							else
							{
								if (tmp->right->color == BLACK)
								{
									tmp->left->color = BLACK;
									tmp->color = RED;
									rightRotate(tmp);
									tmp = node->parent->right;
								} 
								tmp->color = node->parent->color;
								node->parent->color = BLACK;
								tmp->right->color = BLACK;
								leftRotate(node->parent);
								node = _root;
							}
						}
						else
						{
							tmp = node->parent->left;
							if (tmp->color == RED)
							{
								tmp->color = BLACK;
								node->parent->color = RED;
								rightRotate(node->parent);
								tmp = node->parent->left;
							}

							if (tmp->right->color == BLACK && tmp->right->color == BLACK)
							{
								tmp->color = RED;
								node = node->parent;
							}
							else
							{
								if (tmp->left->color == BLACK)
								{
									tmp->right->color = BLACK;
									tmp->color = RED;
									leftRotate(tmp);
									tmp = node->parent->left;
								} 

								tmp->color = node->parent->color;
								node->parent->color = BLACK;
								tmp->left->color = BLACK;
								rightRotate(node->parent);
								node = _root;
							}
						} 
					}
					node->color = BLACK;
				}

				void transplant(NodePtr u, NodePtr v){
					if (u == _root)
						_root = v;
					else if (u->isLeftChild())
						u->parent->left = v;
					else
						u->parent->right = v;
					v->parent = u->parent;
				}

				void del(NodePtr node)
				{
					if (node == NULL || node == _tnull)
						return ;
					NodePtr z = node;
					NodePtr y = z;
					NodePtr x = z;
					bool y_color = y->color;
					if (z->left == _tnull || z->right == _tnull)
					{
						x = z->left == _tnull ? z->right : z->left;
						transplant(z, x);
					}
					else
					{
						y = z->right;
						while (y->left != _tnull)
							y = y->left;
						y_color = y->color;
						x = y->right;
						if (y->parent == z)
							x->parent = y;
						else
						{
							transplant(y, y->right);
							y->right = z->right;
							y->right->parent = y;
						}
						transplant(z, y);
						y->left = z->left;
						y->left->parent = y;
						y->color = z->color;
					}
					delete z;
					if (y_color == 0)
						fixDelete(x);
				}

				NodePtr find (key_type key, NodePtr node)
				{
					if (node == _tnull)
						return (_tnull);
					if (key == node->data.first)
						return node;
					else if (key < node->data.first)
						return (find(key, node->left));
					else
						return (find(key, node->right));
				}

			public:

				void print(NodePtr node, int space)
				{
					// Base case
					if (node == _tnull)
						return;

					// Increase distance between levels
					space += 10;

					// Process right child first
					print(node->right, space);

					// Print current node after space
					// count
					std::cout << std::endl;
					for (int i = 10; i < space; i++)
						std::cout << " ";
					if (node->isBlack())
						std::cout << "\033[1;34m" << node->data.first << "\033[0m\n";
					else
						std::cout << "\033[1;31m" << node->data.first << "\033[0m\n";

					// Process left child
					print(node->left, space);
				}

				void print(void)
				{
					print(_root, 0);
				}
		};

}

#endif
