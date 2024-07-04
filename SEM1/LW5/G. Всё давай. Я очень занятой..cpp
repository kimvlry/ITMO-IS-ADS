#include <iostream>
#include <vector>



struct Node {
	int value;
	Node* left;
	Node* right;
	Node* prnt;

	bool valid_bst;
	int min;
	int max;
	long long subtree_sum;


	Node(bool valid_flag) {
		value = 0;
		left = nullptr;
		right = nullptr;
		prnt = nullptr;

		valid_bst = valid_flag;
		min = std::numeric_limits<int>::max();
		max = std::numeric_limits<int>::min();
		subtree_sum = 0;
	}


	Node(int val) {
		value = val;
		left = nullptr;
		right = nullptr;
		prnt = nullptr;

		valid_bst = false;
		min = std::numeric_limits<int>::max();
		max = std::numeric_limits<int>::min();
		subtree_sum = 0;
	}
};



long long ans = 0;



struct BST {
	Node* root = nullptr;
	Node* cur = nullptr;


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
};



Node* IsMaxValidBST(Node* cur) {
	if (cur == nullptr) {
		return new Node(true);
	}
	Node* l = IsMaxValidBST(cur->left);
	Node* r = IsMaxValidBST(cur->right);
	if (l->valid_bst && r->valid_bst) {
		if (l->max < cur->value && r->min > cur->value) {
			cur->valid_bst = true;

			cur->min = std::min(l->min, cur->value);
			cur->max = std::max(r->max, cur->value);
			cur->subtree_sum = cur->value + l->subtree_sum + r->subtree_sum;
		}
	}
	ans = std::max(ans, cur->subtree_sum);
	return cur;
}


int main() {
	BST days;
	char command;
	int key;
	int root_key;

	std::cin >> root_key;
	days.cur = new Node(root_key);
	days.root = days.cur;

	while (std::cin >> command) {
		if (command == 'l') {
			std::cin >> key;
			if (days.cur->left != nullptr) {
				days.cur = days.cur->left;
			}
			else {
				days.cur->left = new Node(key);
				days.cur->left->prnt = days.cur;
				days.cur = days.cur->left;
			}
		}
		else if (command == 'r') {
			std::cin >> key;
			if (days.cur->right != nullptr) {
				days.cur = days.cur->right;
			}
			else {
				days.cur->right = new Node(key);
				days.cur->right->prnt = days.cur;
				days.cur = days.cur->right;
			}
		}
		else if (command == 'u') {
			if (days.cur->prnt != nullptr) {
				days.cur = days.cur->prnt;
			}
		}
	}
	IsMaxValidBST(days.root);
	std::cout << ans;
}
