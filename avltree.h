#include"Code.h"
#pragma once
class AVLTree {
	struct Node {
		Node* left, * right, * parent;
		Code data;
		signed char balance;
		Node(const Code& X) : right(nullptr), left(nullptr), parent(nullptr), data(X), balance(0) {}
		~Node() {
			if (left) delete left;
			if (right) delete right;
			left = right = parent = nullptr;
		}
		Node* minimum() {
			Node* now = this;
			while (now->left) now = now->left;
			return now;
		}
		Node* maximum() {
			Node* now = this;
			while (now->right) now = now->right;
			return now;
		}
		Node* next() {
			if (right) return right->minimum();
			Node* p = parent, * now = this;
			while (p) {
				if (now == p->left) break;
				now = p;
				p = p->parent;
			}
			return p;
		}
		Node* prev() {
			if (left) return left->maximum();
			Node* p = parent, * now = this;
			while (p) {
				if (now == p->right) break;
				now = p;
				p = p->parent;
			}
			return p;
		}
		int level()const {
			int L = (left) ? left->level() : 0;
			int R = (right) ? right->level() : 0;
			return L > R ? L + 1 : R + 1;
		}
	};

	Node* root;
	unsigned int count;
	Node* _RightRotate(Node*);
	Node* _LeftRotate(Node*);
	Node* _DoubleRightRotate(Node*);
	Node* _DoubleLeftRotate(Node*);

public:
	AVLTree() : root(nullptr), count(0) {}
	~AVLTree() {
		if (root)
			delete root;
		root = nullptr;
	}
	unsigned int size()const { return count; }
	int height()const { return (root) ? root->level() : 0; }
	void insert(const Code& X) {
		++count;
		if (root == nullptr) {
			root = new Node(X);
			return;
		}
		Node* now, * p;
		bool toLeft;
		now = root;
		do {
			p = now;
			if (now->data > X) {
				now = now->left; toLeft = true;
			}
			else {
				now = now->right; toLeft = false;
			}
		} while (now);
		now = new Node(X);
		if (toLeft) p->left = now; else p->right = now;
		now->parent = p;
		
		// восстановление баланса
		do {
			if (now->parent->left == now) now->parent->balance -= 1;
			else now->parent->balance += 1;
			now = now->parent;
			switch (now->balance) {
			case 2:
				if (now->right->balance == -1) now = _DoubleLeftRotate(now);
				else now = _LeftRotate(now);
				break;
			case -2:
				if (now->left->balance == 1) now = _DoubleRightRotate(now);
				else now = _RightRotate(now);
				break;
			}
		} while (now!=root && now->balance!=0);

	}

	void insert_by_code(const Code& X) {
		++count;
		if (root == nullptr) {
			root = new Node(X);
			return;
		}
		Node* now, * p;
		bool toLeft;
		now = root;
		do {
			p = now;
			if (less_code(X,now->data)) {
				now = now->left; toLeft = true;
			}
			else {
				now = now->right; toLeft = false;
			}
		} while (now);
		now = new Node(X);
		if (toLeft) p->left = now; else p->right = now;
		now->parent = p;

		// восстановление баланса
		do {
			if (now->parent->left == now) now->parent->balance -= 1;
			else now->parent->balance += 1;
			now = now->parent;
			switch (now->balance) {
			case 2:
				if (now->right->balance == -1) now = _DoubleLeftRotate(now);
				else now = _LeftRotate(now);
				break;
			case -2:
				if (now->left->balance == 1) now = _DoubleRightRotate(now);
				else now = _RightRotate(now);
				break;
			}
		} while (now != root && now->balance != 0);

	}

	class iterator {
		Node* now;
	public:
		iterator(Node* p = nullptr) : now(p) {}
		const Code& operator*()const { return now->data; }
		bool operator==(const iterator& p)const { return now == p.now; }
		bool operator!=(const iterator& p)const { return now != p.now; }
		iterator& operator++() { if (now) now = now->next(); return *this; }
		iterator operator++(int) {
			Node* tmp = now;
			if (now) now = now->next();
			return iterator(tmp);
		}
		friend class AVLTree;
	};
	iterator begin()const {
		if (root) return iterator(root->minimum());
		return end();
	}
	iterator end()const {
		return iterator(nullptr);
	}
	class reverse_iterator {
		Node* now;
	public:
		reverse_iterator(Node* p = nullptr) : now(p) {}
		const Code& operator*()const { return now->data; }
		bool operator==(const reverse_iterator& p)const { return now == p.now; }
		bool operator!=(const reverse_iterator& p)const { return now != p.now; }
		reverse_iterator& operator++() { if (now) now = now->prev(); return *this; }
		reverse_iterator operator++(int) {
			Node* tmp = now;
			if (now) now = now->prev();
			return reverse_iterator(tmp);
		}
	};
	reverse_iterator rbegin()const {
		if (root) return reverse_iterator(root->maximum());
		return rend();
	}
	reverse_iterator rend()const { return reverse_iterator(nullptr); }
	iterator find(const Code& X)const {
		Node* now = root;
		while (now) {
			if (now->data == X) break;
			if (now->data > X) now = now->left;
			else now = now->right;
		}
		return iterator(now);
	}
	iterator find_by_code(const Code& X)const {
		Node* now = root;
		while (now) {
			if (eq_code(X,now->data)) break;
			if (less_code(X,now->data)) now = now->left;
			else now = now->right;
		}
		return iterator(now);
	}
	Code& find_by_code_elem(const Code& X)const {
		Node* now = root;
		while (now) {
			if (eq_code(X,now->data)) break;
			if (less_code(X, now->data)) now = now->left;
			else now = now->right;
		}
		return now->data;
	}
	Code& find_elem(const Code& X)const {
		Node* now = root;
		while (now) {
			if (now->data == X) break;
			if (now->data > X) now = now->left;
			else now = now->right;
		}
		return now->data;
	}
	void erase(iterator); // Удаление узла в дереве
};


