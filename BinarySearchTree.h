#pragma once
#include <iostream>
#include "Queue.h"
#include "Stack.h"

template <class T>
class BinarySearchTree
{
private:
	template <class N>
	struct Node {
		N key_; // the key value contained in the node
		Node<N>* left_; // pointer to the left subtree
		Node<N>* right_; // pointer to the right subtree
		Node<N>* p_; // pointer to the parent

		//node constructor
		Node(N key, Node* left = nullptr, Node* right = nullptr, Node* p = nullptr) : key_(key), left_(left), right_(right), p_(p) {}
		~Node() {
			if (left_) {
				left_->~Node();
			}
			if (right_)
			{
				right_->~Node();
			}
		}
	};
	Node<T>* root_; // Pointer to the root node

	// 1.2 The function of searching the node address by key in the binary search tree
	Node<T>* iterativeSearchNode(const T& key) const
	{
		Node<T>* current = root_;
		while (current != nullptr and key != current->key_) {
			if (key < current->key_) {
				current = current->left_;
			}
			else {
				current = current->right_;
			}
		}
		return current;
	}

	// 4.2 Recursive function to output a tree image to the output stream
	void printNode(std::ostream& out, Node<T>* root) const
	{
		if (root) {
			out << root->key_;
			if (root->left_ or root->right_) {
				out << '(';
				if (root->left_) { 
					printNode(out, root->left_); 
				}
				out << ')';

				out << '(';
				if (root->right_) { 
					printNode(out, root->right_); 
				}
				out << ')';
			}
		}
	}

	// 5.2 Recursive function for determining the number of tree nodes
	int getCount(const Node<T>* node) const
	{
		if (node == nullptr) {
			return 0;
		}
		return 1 + getCount(node->left_) + getCount(node->right_);
	}

	// 6.2 Recursive function for determining the height of a tree
	int getHeight(const Node<T>* node) const
	{
		if (node == nullptr) {
			return -1;
		}
		int leftHeight = getHeight(node->left_);
		int rightHeight = getHeight(node->right_);
		return 1 + std::max(leftHeight, rightHeight);
	}

	// 8.2 Recursive function for infix traversal of tree nodes.
	void inorderWalk(Node<T>* node) const
	{
		if (node) {
			inorderWalk(node->left_);
			std::cout << node->key_ << " ";
			inorderWalk(node->right_);
		}
	}

	bool isSimilarHelper(Node<T>* root1, Node<T>* root2) const {
		if (!root1 and !root2) {
			return true;
		}
		if (!root1 or !root2) {
			return false;
		}
		return isSimilarHelper(root1->left_, root2->left_) and
			isSimilarHelper(root1->right_, root2->right_);
	}

	bool isIdenticalKeyHelper(Node<T>* root1, Node<T>* root2) const {
		if (!root1 and !root2) {
			return true;
		}
		if (!root1 or !root2) {
			return false;
		}
		return (root1->key_ == root2->key_) or
			isIdenticalKeyHelper(root1->left_, root2->left_) or
			isIdenticalKeyHelper(root1->right_, root2->right_);
	}

public:
	//default constructor
	BinarySearchTree() : root_(nullptr) {} 

	//copy constructor
	BinarySearchTree(const BinarySearchTree<T>& scr) = delete; 

	// move constructor
	BinarySearchTree(BinarySearchTree<T>&& scr) noexcept : root_(scr.root_) 
	{
		scr.root_ = nullptr;
	}

	//copying assignment operator
	BinarySearchTree <T>& operator= (const BinarySearchTree <T>& src) = delete;

	//moving assignment operator
	BinarySearchTree <T>& operator= (BinarySearchTree <T>&& src) noexcept
	{
		if (this != &src)
		{
			delete root_;
			root_ = src.root_;
			src.root_ = nullptr;
		}
		return *this;
	}

	//destructor
	virtual ~BinarySearchTree()
	{
		root_->~Node();
	}

	// 1.1 Key search function in binary search tree
	bool iterativeSearch(const T& key) const
	{
		Node<T>* current = this->root_;
		while (current != nullptr) {
			if (key == current->key_) {
				return true;
			}
			else if (key < current->key_) {
				current = current->left_;
			}
			else {
				current = current->right_;
			}
		}
		return false;
	}

	// 2 Inserting a new element into the tree: true if the element has been added; false if the element has already been
	bool insert(const T& key)
	{
		Node<T>* parent = nullptr;
		Node<T>* current = this->root_;

		// Find the parent of the new node
		while (current != nullptr) {
			parent = current;
			if (key == current->key_) {
				return false; // Element already exists
			}
			else if (key < current->key_) {
				current = current->left_;
			}
			else {
				current = current->right_;
			}
		}

		// Create the new node
		Node<T>* newNode = new Node<T>(key);

		// Set the parent of the new node
		newNode->p_ = parent;

		// Insert the new node
		if (parent == nullptr) {
			root_ = newNode; // The tree was empty
		}
		else if (key < parent->key_) {
			parent->left_ = newNode;
		}
		else {
			parent->right_ = newNode;
		}

		return true;
	}

	// 3.1 Deleting an element from the tree that does not violate the order of elements; 
	// true if the element is deleted; false if there was no element
	bool deleteKey(const T& key)
	{
		Node<T>* nodeToDelete = iterativeSearchNode(key);
		if (!nodeToDelete) {
			return false;
		}
		else if (!nodeToDelete->left_ and !nodeToDelete->right_) {
			if (nodeToDelete->p_->key_ < nodeToDelete->key_) {
				nodeToDelete->p_->right_ = nullptr;
			}
			else {
				nodeToDelete->p_->left_ = nullptr;
			}
		}
		else if (!nodeToDelete->left_ or !nodeToDelete->right_) {
			if (nodeToDelete->p_ == nullptr) {
				if (nodeToDelete->left_) {
					root_ = nodeToDelete->left_;
				}
				else {
					root_ = nodeToDelete->right_;
				}
			}
			else if (nodeToDelete->left_) {
				if (nodeToDelete->key_ < nodeToDelete->p_->key_) {
					nodeToDelete->p_->left_ = nodeToDelete->left_;
				}
				else {
					nodeToDelete->p_->right_ = nodeToDelete->left_;
				}
			}
			else {
				if (nodeToDelete->key_ < nodeToDelete->p_->key_) {
					nodeToDelete->p_->left_ = nodeToDelete->right_;
				}
				else {
					nodeToDelete->p_->right_ = nodeToDelete->right_;
				}
			}
			delete nodeToDelete;
		}
		else {
			Node<T>* temp = nodeToDelete->right_;
			while (temp->left_ != nullptr) {
				temp = temp->left_;
			}
			nodeToDelete->key_ = temp->key_;
			if (temp->p_->key_ == nodeToDelete->key_) {
				temp->p_->right_ = nullptr;
			}
			else {
				temp->p_->left_ = nullptr;
			}
			delete temp;
		}
		return true;
	}

	// 4.1 Printing a string image of a tree to the output stream out,
	void print(std::ostream& out) const
	{
		if (root_) {
			printNode(out, root_);
		}
		out << std::endl;
	}

	// 5.1 Determining the number of tree nodes
	int getCount() const
	{
		return getCount(this->root_);
	}

	// 6.1 Determining the height of the tree
	int getHeight() const
	{
		return getHeight(this->root_);
	}

	// 7 Infix tree traversal (iterative)
	void iterativeInorderWalk() const
	{
		if (root_ == nullptr) {
			return;
		}

		StackArray<Node<T>*> stack(this->getCount());
		Node<T>* current = root_;

		while (current != nullptr or !stack.isEmpty()) {
			if (current != nullptr) {
				stack.push(current);
				current = current->left_;
			}
			else {
				current = stack.top();
				stack.pop();
				std::cout << current->key_ << " ";
				current = current->right_;
			}
		}
	}

	// 8.1 Infix tree traversal (recursive)
	void inorderWalk() const
	{
		inorderWalk(root_);
	}

	// 9 Traversing the binary tree by levels (in width).
	void walkByLevels() const
	{
		if (root_ == nullptr) { 
			return; 
		}

		QueueArray<Node<T>*> queue(getCount());
		queue.enQueue(root_);

		Node<T>* current = nullptr;

		while (!queue.isEmpty()) {
			current = queue.deQueue();
			std::cout << current->key_ << " ";

			if (current->left_) { 
				queue.enQueue(current->left_); 
			}
			if (current->right_) { 
				queue.enQueue(current->right_); 
			}
		}
	}

	// 10 Are two trees similar
	bool isSimilar(const BinarySearchTree<T>& other) const {
		return isSimilarHelper(root_, other.root_);
	}

	// 11 There are identical keys in two search trees
	bool isIdenticalKey(const BinarySearchTree<T>& other) const {
		return isIdenticalKeyHelper(root_, other.root_);
	}
};