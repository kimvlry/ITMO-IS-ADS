#include <iostream>
#include <vector>
#include <string>



struct Node {
	std::string value;
	Node* left;
	Node* right;
	Node* parent;

	Node(std::string val, Node* l, Node* r, Node* prnt) {
		value = val;
		left = l;
		right = r;
		parent = prnt;
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


	Node* Search(std::string x) {
		Node* cur = root;
		while (cur != nullptr && cur->value != x) {
			if (x < cur->value) {
				cur = cur->left;
			}
			else {
				cur = cur->right;
			}
		}
		return cur;
	}


	bool Exists(std::string x) {
		return (Search(x) != nullptr);
	}


	void Insert(std::string x) {
		if (Exists(x)) {
			return;
		}
		if (root == nullptr) {
			root = new Node(x, nullptr, nullptr, nullptr);
		}
		else {
			Node* cur = root;
			while (!((cur->value > x && cur->left == nullptr)
				|| (cur->value < x && cur->right == nullptr))) {
				if (cur->value > x) {
					cur = cur->left;
				}
				else {
					cur = cur->right;
				}
			}
			if (cur->value > x) {
				cur->left = new Node(x, nullptr, nullptr, cur);
			}
			else {
				cur->right = new Node(x, nullptr, nullptr, cur);
			}
		}
	}
};



int main() {
	int n;
	std::cin >> n;

	BST fella1;
	BST fella2;
	BST fella3;
	int score1 = 0;
	int score2 = 0;
	int score3 = 0;
	std::vector<std::string> files1;
	std::vector<std::string> files2;
	std::vector<std::string> files3;

	std::string task;
	std::string currently_checking;
	int match;

	for (int i = 0; i < n; ++i) {
		std::cin >> task;
		fella1.Insert(task);
		files1.push_back(task);
	}

	for (int i = 0; i < n; ++i) {
		std::cin >> task;
		fella2.Insert(task);
		files2.push_back(task);
	}

	for (int i = 0; i < n; ++i) {
		std::cin >> task;
		fella3.Insert(task);
		files3.push_back(task);
	}

	for (int i = 0; i < n; ++i) {
		currently_checking = files1[i];
		match = fella2.Exists(currently_checking) + fella3.Exists(currently_checking);
		if (match == 0) {
			score1 += 3;
		}
		else if (match == 1) {
			score1 += 1;
		}
	}

	for (int i = 0; i < n; ++i) {
		currently_checking = files2[i];
		match = fella1.Exists(currently_checking) + fella3.Exists(currently_checking);
		if (match == 0) {
			score2 += 3;
		}
		else if (match == 1) {
			score2 += 1;
		}
	}

	for (int i = 0; i < n; ++i) {
		currently_checking = files3[i];
		match = fella1.Exists(currently_checking) + fella2.Exists(currently_checking);
		if (match == 0) {
			score3 += 3;
		}
		else if (match == 1) {
			score3 += 1;
		}
	}

	std::cout << score1 << ' ' << score2 << ' ' << score3;
}
