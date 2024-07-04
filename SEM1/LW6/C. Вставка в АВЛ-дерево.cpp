#include <iostream>
#include <vector>

int output = 0;


struct Node {
	int value;
	Node* left = nullptr;
	Node* right = nullptr;
	int height;
	int output_number;


	Node(int val, Node& l, Node& r) {
		value = val;
		left = &l;
		right = &r;
		height = 1;
	}


	Node(int val) {
		value = val;
		height = 1;
	}


	Node() {
	}
};



struct AVL {
	std::vector<Node> tree;
	Node* root = nullptr;


	AVL(int n) {
		for (int i = 0; i < n + 1; ++i) {
			tree.emplace_back();
		}
	}


	int CalculateHeights(Node* p, int cur_height) {
		if (p == nullptr) {
			return 0;
		}
		p->height = std::max(CalculateHeights(p->left, cur_height),
		                     CalculateHeights(p->right, cur_height)) + 1;
		return p->height;
	}


	static int GetHughtByTheBeach(Node* cur) {
		return cur == nullptr ? 0 : cur->height;
	}


	int BalanceFactor(Node* cur) {
		return (GetHughtByTheBeach(cur->right) - GetHughtByTheBeach(cur->left));
	}


	void Fix(Node* p) {
		p->height = std::max(GetHughtByTheBeach(p->right), GetHughtByTheBeach(p->left)) + 1;
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
		if (BalanceFactor(cur) == 2) {
			if (BalanceFactor(cur->right) < 0) {
				return RL(cur);
			}
			return LL(cur);
		}
		if (BalanceFactor(cur) == -2) {
			if (BalanceFactor(cur->left) > 0) {
				return LR(cur);
			}
			return RR(cur);
		}
		return cur;
	}


	Node* Insert(Node x, Node* dir) {
		if (dir == nullptr) {
			tree[tree.size() - 1] = x;
			return &tree[tree.size() - 1];
		}
		if (x.value < dir->value) {
			dir->left = Insert(x, dir->left);
		}
		else if (x.value > dir->value) {
			dir->right = Insert(x, dir->right);
		}
		return Balance(dir);
	}


	void Insert(int x) {
		root = Insert(Node(x), root);
	}


	void SetOutputLines(Node* cur) {
		if (cur == nullptr) {
			return;
		}
		cur->output_number = ++output;
		SetOutputLines(cur->left);
		SetOutputLines(cur->right);
	}


	void PreOrderTraversal(Node* head) {
		if (head == nullptr) {
			return;
		}
		std::cout << head->value << ' ';
		head->left != nullptr ? std::cout << head->left->output_number << ' ' : std::cout << 0 << ' ';
		head->right != nullptr ? std::cout << head->right->output_number << ' ' : std::cout << 0 << ' ';
		std::cout << '\n';

		if (head->left != nullptr) {
			PreOrderTraversal(head->left);
		}
		if (head->right != nullptr) {
			PreOrderTraversal(head->right);
		}
	}
};



int main() {
	int n;
	std::cin >> n;
	AVL supercool_avl(n);
	int val, l_index, r_index;

	for (int i = 0; i < n; ++i) {
		std::cin >> val >> l_index >> r_index;
		supercool_avl.tree[i] = Node(val, supercool_avl.tree[l_index - 1], supercool_avl.tree[r_index - 1]);
		if (l_index == 0) {
			supercool_avl.tree[i].left = nullptr;
		}
		if (r_index == 0) {
			supercool_avl.tree[i].right = nullptr;
		}
	}

	int x;
	std::cin >> x;
	std::cout << n + 1 << '\n';
	if (n == 0) {
		std::cout << x << ' ' << 0 << ' ' << 0;
	}
	else {
		supercool_avl.CalculateHeights(&supercool_avl.tree[0], 0);
		supercool_avl.root = supercool_avl.Balance(&supercool_avl.tree[0]);
		supercool_avl.Insert(x);
		supercool_avl.SetOutputLines(supercool_avl.root);
		supercool_avl.PreOrderTraversal(supercool_avl.root);
	}
}
