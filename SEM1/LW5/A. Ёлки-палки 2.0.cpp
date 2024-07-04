#include <iostream>
#include <vector>



struct Node {
	int val;
	int height;
	Node* left_subtree;
	Node* right_subtree;

	Node(int value) {
		val = value;
		left_subtree = nullptr;
		right_subtree = nullptr;
	}
};



Node* ArrToBST(std::vector<Node>& a, int first, int last) {
	if (first <= last) {
		int mid = (first + last) / 2;
		Node* root = &a[mid];
		root->left_subtree = ArrToBST(a, first, mid - 1);
		root->right_subtree = ArrToBST(a, mid + 1, last);
		return root;
	}
	return nullptr;
}


void PreOrderTraversal(Node* node) {
	if (node != nullptr) {
		std::cout << node->val << " ";
		PreOrderTraversal(node->left_subtree);
		PreOrderTraversal(node->right_subtree);
	}
}


int main() {
	int n;
	int data;
	std::cin >> n;
	std::vector<Node> Tree;
	for (int i = 0; i < n; ++i) {
		std::cin >> data;
		Tree.emplace_back(data);
	}
	Node* root = ArrToBST(Tree, 0, n - 1);
	PreOrderTraversal(root);
}
