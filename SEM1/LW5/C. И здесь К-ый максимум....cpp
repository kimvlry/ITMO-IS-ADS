#include <iostream>



struct Node {
	int value;
	Node* left;
	Node* right;
	int cnt_right_children;

	Node(int val) {
		value = val;
		left = nullptr;
		right = nullptr;
		cnt_right_children = 0;
	}
};



struct BST {
	Node* root = nullptr;


	void EraseTree(Node* cur) {
		if (cur == nullptr) {
			return;
		}
		EraseTree(cur->left);
		EraseTree(cur->right);
		delete cur;
	}


	~BST() {
		EraseTree(root);
	}


	Node* Search(int x, Node* cur) {
		if (cur == nullptr || cur->value == x) {
			return cur;
		}
		if (x > cur->value) {
			return Search(x, cur->right);
		}
		return Search(x, cur->left);
	}


	Node* Search(int x) {
		return Search(x, root);
	}


	bool Exists(int x) {
		return (Search(x, root)) != nullptr;
	}


	Node* Next(int x) {
		Node* cur = root;
		Node* successor = nullptr;
		while (cur != nullptr) {
			if (cur->value > x) {
				successor = cur;
				cur = cur->left;
			}
			else {
				cur = cur->right;
			}
		}
		return successor;
	}


	Node* Prev(int x) {
		Node* cur = root;
		Node* successor = nullptr;
		while (cur != nullptr) {
			if (cur->value >= x) {
				cur = cur->left;
			}
			else {
				successor = cur;
				cur = cur->right;
			}
		}
		return successor;
	}


	Node* Insert(int x, Node* dir) {
		if (dir == nullptr) {
			return new Node(x);
		}

		if (x < dir->value) {
			dir->left = Insert(x, dir->left);
		}
		else if (x > dir->value) {
			++dir->cnt_right_children;
			dir->right = Insert(x, dir->right);
		}
		return dir;
	}


	void Insert(int x) {
		if (Exists(x)) {
			return;
		}
		root = Insert(x, root);
	}


	Node* Min(Node* cur) {
		if (cur->left == nullptr) {
			return cur;
		}
		return Min(cur->left);
	}


	Node* Delete(Node* cur, int x) {
		if (cur == nullptr) {
			return cur;
		}
		if (x < cur->value) {
			cur->left = Delete(cur->left, x);
			return cur;
		}
		if (x > cur->value) {
			--cur->cnt_right_children;
			cur->right = Delete(cur->right, x);
			return cur;
		}
		if (cur->left != nullptr && cur->right != nullptr) {
			cur->value = Min(cur->right)->value;
			--cur->cnt_right_children;
			cur->right = Delete(cur->right, cur->value);
		}
		else {
			if (cur->left != nullptr) {
				cur = cur->left;
			}
			else if (cur->right != nullptr) {
				cur = cur->right;
			}
			else {
				cur = nullptr;
			}
		}
		return cur;
	}


	void Delete(int x) {
		if (!Exists(x)) {
			return;
		}
		root = Delete(root, x);
	}


	Node* KthMaximum(int k, Node* cur) {
		if (cur->cnt_right_children == k - 1 || cur == nullptr) {
			return cur;
		}
		if (cur->cnt_right_children < k - 1 && cur->left != nullptr) {
			return KthMaximum(k - 1 - cur->cnt_right_children, cur->left);
		}
		if (cur->right != nullptr) {
			return KthMaximum(k, cur->right);
		}
	}
};



int main() {
	BST tree;

	int n;
	int command;
	int value;

	std::cin >> n;

	for (int i = 0; i < n; ++i) {
		std::cin >> command >> value;
		if (command == 1) {
			tree.Insert(value);
		}
		else if (command == 0) {
			if (tree.KthMaximum(value, tree.root) != nullptr) {
				std::cout << tree.KthMaximum(value, tree.root)->value << '\n';
			}
		}
		else {
			tree.Delete(value);
		}
	}
}
