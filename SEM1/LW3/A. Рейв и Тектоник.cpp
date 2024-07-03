#include <iostream>
using std::cin, std::cout, std::ios_base;



struct Node {
	int val;
	Node* next;


	Node(int value) {
		val = value;
		next = nullptr;
	}
};



struct Stack {
	Node* top = nullptr;


	~Stack() {
		while (top != nullptr) {
			auto tmp = top;
			top = top->next;
			delete tmp;
		}
	}


	bool Stack_Empty() {
		return top == nullptr;
	}


	void Push(int value) {
		Node* temp = new Node(value);
		temp->next = top;
		top = temp;
	}


	void Pop() {
		if (Stack_Empty()) {
			std::cerr << "stack is empty";
			return;
		}
		Node* temp = top;
		top = top->next;
		delete temp;
	}
};



int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	char command;
	int message;
	Stack Chat;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> command;
		if (command == '+') {
			cin >> message;
			Chat.Push(message);
		}
		else if (command == '-') {
			if (!Chat.Stack_Empty()) {
				cout << Chat.top->val << '\n';
				Chat.Pop();
			}
		}
	}
}
