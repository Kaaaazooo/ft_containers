#ifndef RB_TREE_H
#define RB_TREE_H

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

	template<class K, class V>
		class Node
		{
			public:
				K key;
				V value;
				Node<K, V> *left;
				Node<K, V> *right;
				Node<K, V> *parent;
				bool isLeftChild;
				bool black;

				Node (K k, V v) : key(k), value(v), left(NULL), right(NULL), parent(NULL),
					isLeftChild(false), black(false) { }
		};

	template<class K, class V>
		class rb_tree
		{
			protected:
				Node<K,V>	*_root;
				size_t		_size;
			public:
				rb_tree(void) : _root(NULL), _size(0) { }

				void add (K key, V value)
				{
					Node<K, V> *node = new Node<K, V>(key, value);
					if (_root == NULL)
					{
						_root = node;
						_root->black = true;
					}
					else
					{
						add(_root, node);
					}
					++_size;
				}
			private:
				void add(Node<K, V> *parent, Node<K, V> *newNode)
				{
					if (newNode->key > parent->key)
					{
						if (parent->right == NULL)
						{
							parent->right = newNode;
							newNode->parent = parent;
						}
						else
							add(parent->right, newNode);
					}
					else
					{
						if (parent->left == NULL)
						{
							parent->left = newNode;
							newNode->parent = parent;
							newNode->isLeftChild = true;
						}
						else
							add(parent->left, newNode);
					}
					checkColor(newNode);
				}

				void checkColor(Node<K, V> *node)
				{

					if (node == _root)
					{
						if (!node->black)
							node->black = true;
						return;
					}
					if (!node->black && !node->parent->black)
						correctTree(node);
					if (node != _root)
						checkColor(node->parent);
				}

				void correctTree(Node<K, V> *node)
				{
					if (node->parent->isLeftChild)
					{
						// aunt is node.parent.parent.right
						if (node->parent->parent->right == NULL || node->parent->parent->right->black)
						{
							rotate(node);
							return ;
						}
						if (node->parent->parent->right)
							node->parent->parent->right->black = true;
						node->parent->parent->black = false;
						node->parent->black = true;
					}
					else
					{
						// aunt is node.parent.parent.left
						if (node->parent->parent->left == NULL || node->parent->parent->left->black)
						{
							rotate(node);
							return ;
						}
						if (node->parent->parent->left)
							node->parent->parent->left->black = true;
						node->parent->parent->black = false;
						node->parent->black = true;
					}
				}

				void rotate (Node<K, V> *node)
				{
					if (node->isLeftChild)
					{
						if (node->parent->isLeftChild)
						{
							rightRotate(node->parent->parent);
							node->black = false;
							node->parent->black = true;
							if (node->parent->right)
								node->parent->right->black = false;
						}
						else
						{
							rightLeftRotate(node->parent->parent);
							node->black = true;
							node->right->black = false;
							node->left->black = false;
						}
					}
					else
					{
						if (!node->parent->isLeftChild)
						{
							leftRotate(node->parent->parent);
							node->black = false;
							node->parent->black = true;
							if (node->parent->left)
								node->parent->left->black = false;
						}
						else
						{
							leftRightRotate(node->parent->parent);
							node->black = true;
							node->left->black = false;
							node->right->black = false;
						}
					}
				}

				void leftRotate(Node<K, V> *node)
				{
					Node<K, V> *tmp = node->right;
					node->right = tmp->left;
					if (node->right)
					{
						node->right->parent = node;
						node->right->isLeftChild = false;

					}
					if (node->parent == NULL)
					{
						_root = tmp;
						tmp->parent = NULL;
					}
					else
					{
						tmp->parent = node->parent;
						if (node->isLeftChild)
						{
							tmp->isLeftChild = true;
							tmp->parent->left = tmp;
						}
						else
						{
							tmp->isLeftChild = false;
							tmp->parent->right = tmp;
						}
					}
					tmp->left = node;
					node->isLeftChild = true;
					node->parent = tmp;
				}

				void rightRotate(Node<K, V> *node)
				{
					Node<K, V> *tmp = node->left;
					node->left = tmp->right;
					if (node->left)
					{
						node->left->parent = node;
						node->left->isLeftChild = true;

					}
					if (node->parent == NULL)
					{
						_root = tmp;
						tmp->parent = NULL;
					}
					else
					{
						tmp->parent = node->parent;
						if (!node->isLeftChild)
						{
							tmp->isLeftChild = false;
							tmp->parent->right = tmp;
						}
						else
						{
							tmp->isLeftChild = true;
							tmp->parent->left = tmp;
						}
					}
					tmp->right = node;
					node->isLeftChild = false;
					node->parent = tmp;
				}

				void leftRightRotate(Node<K, V> *node)
				{
					leftRotate(node->left);
					rightRotate(node);
				}

				void rightLeftRotate(Node<K, V> *node)
				{
					rightRotate(node->right);
					leftRotate(node);
				}

				public:
					size_t height(void)
					{
						if (_root == NULL)
							return (0);
						return height(_root) - 1;
					}

					size_t height(Node<K, V> *node)
					{
						if (node == NULL)
							return (0);
						size_t leftHeight = height(node->left) + 1;
						size_t rightHeight = height(node->right) + 1;
						return (leftHeight > rightHeight ? leftHeight : rightHeight);
					}

					size_t blackNodes(void)
					{
						blackNodes(_root);
					}

					size_t blackNodes(Node<K, V> *node)
					{
						if (node == NULL)
							return 1;
						size_t rightBlackNodes = blackNodes(node->right);
						size_t leftBlackNodes = blackNodes(node->left);
						if (rightBlackNodes != leftBlackNodes)
						{
							throw "invalid red black tree";
						}
						if (node->black)
						{
							++leftBlackNodes;
						}
						return leftBlackNodes;
					}

					void print(Node<K, V> *root, int space)
					{
						// Base case
						if (root == NULL)
							return;

						// Increase distance between levels
						space += 10;

						// Process right child first
						print(root->right, space);

						// Print current node after space
						// count
						std::cout << std::endl;
						for (int i = 10; i < space; i++)
							std::cout << " ";
						if (root->black)
							std::cout << "\033[1;34m" << root->key << "\033[0m\n";
						else
							std::cout << "\033[1;31m" << root->key << "\033[0m\n";

						// Process left child
						print(root->left, space);
					}

					void print(void)
					{
						print(_root, 0);
					}
		};

}

#endif
