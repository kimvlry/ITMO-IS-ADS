#include <iostream>



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


	int CalculateHeights(Node* p, int cur_height) {
		if (p == nullptr) {
			return 0;
		}
		p->height = std::max(CalculateHeights(p->left, cur_height),
		                     CalculateHeights(p->right, cur_height)) + 1;
		return p->height;
	}


	static int GetHeightByTheBeach(Node* cur) {
		return cur == nullptr ? 0 : cur->height;
	}


	static int GetBalanceFactor(Node* cur) {
		return (GetHeightByTheBeach(cur->right) - GetHeightByTheBeach(cur->left));
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
	std::string contact;
	int ans = 0;

	AVL supercool_tree;

	for (int i = 0; i < n; ++i) {
		std::cin >> contact;
		std::string unique;

		if (supercool_tree.Search(contact) == nullptr) {
			supercool_tree.Insert(contact);
		}
		else {
			for (int j = 0; j < contact.length(); ++j) {
				if (unique.find(contact[j]) == std::string::npos) {
					unique.push_back(contact[j]);
				}
			}
			ans += unique.length();
		}
	}
	std::cout << ans;
}
