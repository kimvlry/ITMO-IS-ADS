#include <iostream>
#include <vector>



struct Node {
	int value;
	Node* left;
	Node* right;
	int depth;


	Node(int val, int d) {
		value = val;
		left = nullptr;
		right = nullptr;
		depth = d;
	}
};



struct BST {
	Node* root = nullptr;
	int tree_height = 0;
	std::vector<int> ans;


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


	Node* Insert(int x, int h, Node* dir) {
		if (dir == nullptr) {
			if (h + 1 > ans.size()) {
				ans.push_back(x);
			}
			else {
				ans[h] = std::max(ans[h], x);
			}
			tree_height = std::max(tree_height, h);
			return new Node(x, h);
		}

		if (x < dir->value) {
			dir->left = Insert(x, ++h, dir->left);
		}
		else if (x > dir->value) {
			dir->right = Insert(x, ++h, dir->right);
		}
		return dir;
	}


	void Insert(int x) {
		if (Exists(x)) {
			return;
		}
		root = Insert(x, 0, root);
	}


	Node* Min(Node* cur) {
		if (cur->left == nullptr) {
			return cur;
		}
		return Min(cur->left);
	}


	Node* Max(Node* cur) {
		if (cur->right == nullptr) {
			return cur;
		}
		return Max(cur->right);
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
			cur->right = Delete(cur->right, x);
			return cur;
		}
		if (cur->left != nullptr && cur->right != nullptr) {
			cur->value = Min(cur->right)->value;
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
};



int main() {
	BST tree;
	int n;
	int val;
	std::cin >> n;

	for (int i = 0; i < n; ++i) {
		std::cin >> val;
		tree.Insert(val);
	}

	for (int i = 0; i < tree.tree_height + 1; ++i) {
		std::cout << tree.ans[i] << ' ';
	}
}
