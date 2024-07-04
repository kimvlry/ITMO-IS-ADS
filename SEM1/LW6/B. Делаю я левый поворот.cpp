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
		height = 0;
	}


	Node() = default;
};



struct AVL {
	std::vector<Node> tree;


	AVL(int n) {
		for (int i = 0; i < n; ++i) {
			tree.emplace_back();
		}
	}


	int CalculateHeights(Node* cur) {
		if (cur == nullptr) {
			return 0;
		}
		cur->height = std::max(CalculateHeights(cur->left),
		                       CalculateHeights(cur->right)) + 1;
		return cur->height;
	}


	int GetHeightByTheBeach(Node* cur) {
		return cur == nullptr ? 0 : cur->height;
	}


	Node* LL(Node* q) {
		Node* p = q->right;
		q->right = p->left;
		p->left = q;
		CalculateHeights(q);
		CalculateHeights(p);
		return p;
	}


	Node* RR(Node* q) {
		Node* p = q->left;
		q->left = p->right;
		p->right = q;
		CalculateHeights(q);
		CalculateHeights(p);
		return p;
	}


	Node* RL(Node* cur) {
		cur->right = RR(cur->right);
		return LL(cur);
	};


	Node* Balance(Node* cur) {
		if (cur->right != nullptr) {
			if (GetHeightByTheBeach(cur->right->right) - GetHeightByTheBeach(cur->right->left) < 0) {
				return RL(cur);
			}
			return LL(cur);
		}
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
	AVL my_tree(n);
	int val, l_index, r_index;

	for (int i = 0; i < n; ++i) {
		std::cin >> val >> l_index >> r_index;
		my_tree.tree[i] = Node(val, my_tree.tree[l_index - 1], my_tree.tree[r_index - 1]);
		if (l_index == 0) {
			my_tree.tree[i].left = nullptr;
		}
		if (r_index == 0) {
			my_tree.tree[i].right = nullptr;
		}
	}
	my_tree.CalculateHeights(&my_tree.tree[0]);
	Node* head = my_tree.Balance(&my_tree.tree[0]);
	my_tree.SetOutputLines(head);

	std::cout << n << '\n';
	my_tree.PreOrderTraversal(head);
}
