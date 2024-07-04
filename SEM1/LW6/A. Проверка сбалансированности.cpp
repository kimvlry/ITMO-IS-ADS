#include <iostream>
#include <vector>



struct Node {
	int left_ix;
	int right_ix;
	int height;

	Node(int l, int r) {
		left_ix = l;
		right_ix = r;
	}
};



int main() {
	int n;
	int val, l, r;
	std::cin >> n;
	std::vector<Node> tree;

	for (int i = 0; i < n; ++i) {
		std::cin >> val >> l >> r;
		tree.emplace_back(l - 1, r - 1);
	}

	for (int i = n - 1; i >= 0; --i) {
		tree[i].height = std::max(tree[tree[i].left_ix].height, tree[tree[i].right_ix].height) + 1;
	}

	for (int i = 0; i < n; ++i) {
		if (tree[i].left_ix == -1 && tree[i].right_ix == -1) {
			std::cout << 0 << '\n';
		}
		else if (tree[i].left_ix == -1) {
			std::cout << tree[tree[i].right_ix].height << '\n';
		}
		else if (tree[i].right_ix == -1) {
			std::cout << 0 - tree[tree[i].left_ix].height << '\n';
		}
		else {
			std::cout << tree[tree[i].right_ix].height - tree[tree[i].left_ix].height << '\n';
		}
	}
}
