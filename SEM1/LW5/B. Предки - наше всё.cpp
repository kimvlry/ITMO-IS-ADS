#include <iostream>
#include <vector>



struct Node {
	int value;
	Node* left;
	Node* right;

	Node(int val) {
		value = val;
		left = nullptr;
		right = nullptr;
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
		return Search(x, root) != nullptr;
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


	Node* Delete(Node* v, int x) {
		if (v == nullptr) {
			return v;
		}
		if (x < v->value) {
			v->left = Delete(v->left, x);
			return v;
		}
		if (x > v->value) {
			v->right = Delete(v->right, x);
			return v;
		}
		if (v->left != nullptr && v->right != nullptr) {
			v->value = Min(v->right)->value;
			v->right = Delete(v->right, v->value);
		}
		else {
			if (v->left != nullptr) {
				v = v->left;
			}
			else if (v->right != nullptr) {
				v = v->right;
			}
			else {
				v = nullptr;
			}
		}
		return v;
	}


	void Delete(int x) {
		root = Delete(root, x);
	}
};



int main() {
	BST YaTree;

	std::string command;
	int val;

	while (std::cin >> command) {
		if (command == "insert") {
			std::cin >> val;
			YaTree.Insert(val);
		}
		else if (command == "delete") {
			std::cin >> val;
			YaTree.Delete(val);
		}
		else if (command == "exists") {
			std::cin >> val;
			if (YaTree.Search(val) == nullptr) {
				std::cout << "false" << '\n';
			}
			else {
				std::cout << "true" << '\n';
			}
		}
		else if (command == "next") {
			std::cin >> val;
			if (YaTree.Next(val) == nullptr) {
				std::cout << "none" << '\n';
			}
			else {
				std::cout << YaTree.Next(val)->value << '\n';
			}
		}
		else if (command == "prev") {
			std::cin >> val;
			if (YaTree.Prev(val) == nullptr) {
				std::cout << "none" << '\n';
			}
			else {
				std::cout << YaTree.Prev(val)->value << '\n';
			}
		}
	}
}
