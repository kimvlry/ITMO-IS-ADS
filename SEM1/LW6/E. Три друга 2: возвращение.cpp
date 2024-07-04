#include <iostream>
#include <vector>
#include <string>



struct Node {
	std::string value;
	Node* left;
	Node* right;
	int height;


	Node(std::string val, Node& l, Node& r) {
		value = val;
		left = &l;
		right = &r;
		height = 1;
	}


	Node(std::string val) {
		value = val;
		height = 1;
		left = nullptr;
		right = nullptr;
	}
};



struct AVL {
	Node* root = nullptr;


	void EraseTree(Node* cur) {
		if (cur == nullptr) {
			return;
		}
		EraseTree(cur->left);
		EraseTree(cur->right);
		delete cur;
	}


	~AVL() {
		EraseTree(root);
	}


	static int GetHeightByTheBeach(Node* cur) {
		return cur == nullptr ? 0 : cur->height;
	}


	static int GetBalanceFactor(Node* cur) {
		return GetHeightByTheBeach(cur->right) - GetHeightByTheBeach(cur->left);
	}


	static void Fix(Node* p) {
		p->height = std::max(GetHeightByTheBeach(p->right), GetHeightByTheBeach(p->left)) + 1;
	}


	Node* LL(Node* q) {
		Node* p = q->right;
		q->right = p->left;
		p->left = q;
		Fix(q);
		Fix(p);
		return p;
	}


	Node* RR(Node* q) {
		Node* p = q->left;
		q->left = p->right;
		p->right = q;
		Fix(q);
		Fix(p);
		return p;
	}


	Node* RL(Node* cur) {
		cur->right = RR(cur->right);
		return LL(cur);
	}


	Node* LR(Node* cur) {
		cur->left = LL(cur->left);
		return RR(cur);
	}


	Node* Balance(Node* cur) {
		if (cur == nullptr) { return cur; }
		Fix(cur);
		if (GetBalanceFactor(cur) == 2) {
			if (GetBalanceFactor(cur->right) < 0) {
				return RL(cur);
			}
			return LL(cur);
		}
		if (GetBalanceFactor(cur) == -2) {
			if (GetBalanceFactor(cur->left) > 0) {
				return LR(cur);
			}
			return RR(cur);
		}
		return cur;
	}


	Node* Insert(std::string x, Node* dir) {
		if (dir == nullptr) {
			return new Node(x);
		}
		if (x < dir->value) {
			dir->left = Insert(x, dir->left);
		}
		else if (x > dir->value) {
			dir->right = Insert(x, dir->right);
		}
		return Balance(dir);
	}


	void Insert(std::string x) {
		root = Insert(x, root);
	}


	bool Exists(std::string x) {
		return Search(x) != nullptr;
	}


	Node* Search(std::string x) {
		Node* cur = root;
		while (!(cur == nullptr || cur->value == x)) {
			if (x > cur->value) {
				cur = cur->right;
			}
			else {
				cur = cur->left;
			}
		}
		return cur;
	}
};



int main() {
	int n;
	std::cin >> n;

	AVL fella1;
	AVL fella2;
	AVL fella3;
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
