#include"avltree.h"

void AVLTree::erase(AVLTree::iterator pos) {
	Node* toDelete = pos.now;
	if (toDelete == nullptr) return;
	Node* Alt;
	if (toDelete->right == nullptr)
		Alt = toDelete->left;
	else if (toDelete->left == nullptr)
		Alt = toDelete->right;
	else {
		Alt = toDelete->right->minimum();
		if (Alt->parent != toDelete) {
			Alt->parent->left = Alt->right;
			if (Alt->right) Alt->right->parent = Alt->parent;
			Alt->right = toDelete->right;
			toDelete->right->parent = Alt;
		}
		Alt->left = toDelete->left;
		toDelete->left->parent = Alt;
	}

	Node* notBalanced;
	if (Alt == nullptr) {
		notBalanced = toDelete->parent;
		if (notBalanced) {
			if (notBalanced->left == toDelete) notBalanced->balance += 1;
			else notBalanced->balance -= 1;
		}
	}
	else {
		Alt->balance = toDelete->balance;
		if (Alt->parent == toDelete) {
			notBalanced = Alt;
			if (Alt == toDelete->left) notBalanced->balance += 1;
			else notBalanced->balance -= 1;
		}
		else {
			notBalanced = Alt->parent;
			notBalanced->balance += 1;
		}
	}


	if (toDelete->parent == nullptr) {
		root = Alt;
	}
	else {
		if (toDelete->parent->left == toDelete)
			toDelete->parent->left = Alt;
		else
			toDelete->parent->right = Alt;
	}
	if (Alt != nullptr) {
		Alt->parent = toDelete->parent;
	}

	toDelete->right = nullptr; toDelete->left = nullptr;
	delete toDelete;
	--count;

	// восстановление балансировки
	while (notBalanced) {
		switch (notBalanced->balance) {
		case 2:
			if (notBalanced->right->balance == -1)
				notBalanced = _DoubleLeftRotate(notBalanced);
			else
				notBalanced = _LeftRotate(notBalanced);
			break;
		case -2:
			if (notBalanced->left->balance == 1)
				notBalanced = _DoubleRightRotate(notBalanced);
			else
				notBalanced = _RightRotate(notBalanced);
			break;
		}
		if (notBalanced->balance == 1 || notBalanced->balance == -1)
			break;
		if (notBalanced->parent) {
			if (notBalanced->parent->left == notBalanced)
				notBalanced->parent->balance += 1;
			else
				notBalanced->parent->balance -= 1;
		}
		notBalanced = notBalanced->parent;
	}
}

//template <typename Element>
//typename AVLTree<Element>::Node* 
AVLTree::Node* AVLTree::_LeftRotate(Node* a) {
	if (a->balance != 2) return a;
	Node* b = a->right;
	if (b->balance == -1) return a;

	a->right = b->left;
	if (b->left) b->left->parent = a;

	b->parent = a->parent;
	if (a->parent) {
		if (a->parent->left == a)
			a->parent->left = b;
		else
			a->parent->right = b;
	}
	else {
		root = b;
	}

	b->left = a;
	a->parent = b;

	if (b->balance == 1) {
		a->balance = 0; b->balance = 0;
	}
	else {
		a->balance = 1; b->balance = -1;
	}
	return b;
}

//template <typename Element>
//typename AVLTree<Element>::Node*
AVLTree::Node* AVLTree::_RightRotate(Node* b) {
	if (b->balance != -2) return b;
	Node* a = b->left;
	if (a->balance == 1) return b;

	b->left = a->right;
	if (a->right) a->right->parent = b;

	a->parent = b->parent;
	if (b->parent) {
		if (b->parent->left == b)
			b->parent->left = a;
		else
			b->parent->right = a;
	}
	else {
		root = a;
	}

	a->right = b;
	b->parent = a;

	if (a->balance == -1) {
		a->balance = 0; b->balance = 0;
	}
	else {
		a->balance = 1; b->balance = -1;
	}

	return a;
}

//template <typename Element>
//typename AVLTree<Element>::Node*
AVLTree::Node* AVLTree::_DoubleLeftRotate(Node* a) {
	if (a->balance != 2) return a;
	Node* c = a->right;
	if (c->balance != -1) return a;
	Node* b = c->left;

	a->right = b->left; if (b->left) b->left->parent = a;
	c->left = b->right; if (b->right) b->right->parent = c;

	b->parent = a->parent;
	if (a->parent) {
		if (a->parent->left == a)
			a->parent->left = b;
		else
			a->parent->right = b;
	}
	else {
		root = b;
	}

	b->left = a;  a->parent = b;
	b->right = c; c->parent = b;

	if (b->balance == 0) {
		a->balance = 0;  c->balance = 0;
	}
	else if (b->balance == 1) {
		a->balance = -1; c->balance = 0;
	}
	else {
		a->balance = 0;  c->balance = 1;
	}
	b->balance = 0;
	return b;
}

//template <typename Element>
//typename AVLTree<Element>::Node*
AVLTree::Node* AVLTree::_DoubleRightRotate(Node* c) {
	if (c->balance != -2) return c;
	Node* a = c->left;
	if (a->balance != 1) return c;
	Node* b = a->right;

	a->right = b->left; if (b->left) b->left->parent = a;
	c->left = b->right; if (b->right) b->right->parent = c;

	b->parent = c->parent;
	if (c->parent) {
		if (c->parent->left == c)
			c->parent->left = b;
		else
			c->parent->right = b;
	}
	else {
		root = b;
	}

	b->left = a;  a->parent = b;
	b->right = c; c->parent = b;

	if (b->balance == 0) {
		a->balance = 0;  c->balance = 0;
	}
	else if (b->balance == 1) {
		a->balance = -1; c->balance = 0;
	}
	else {
		a->balance = 0;  c->balance = 1;
	}
	b->balance = 0;

	return b;
}