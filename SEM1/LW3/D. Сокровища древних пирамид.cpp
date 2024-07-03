#include <iostream>
using std::cin, std::cout, std::endl, std::ios_base;



struct Node {
	int val;
	Node* prev;
	Node* next;
};



struct Stack {
	Node* top = nullptr;
	Node* bottom = nullptr;


	~Stack() {
		while (top != nullptr) {
			auto tmp = top;
			top = top->next;
			delete tmp;
		}
	}


	bool Stack_Empty() {
		return top == nullptr && bottom == nullptr;
	}


	void Push(int value) {
		Node* temp = new Node;
		temp->prev = nullptr;
		temp->val = value;
		temp->next = top;
		if (top == nullptr && bottom == nullptr) {
			bottom = temp;
			top = temp;
		}
		else if (bottom != nullptr && top == nullptr) {
			top = temp;
			top->next = bottom;
			bottom->prev = top;
		}
		else if (bottom != nullptr) {
			top->prev = temp;
			top = temp;
		}
		delete temp;
	}


	void PopTop() {
		if (Stack_Empty()) {
			cout << "underflow";
			return;
		}
		Node* temp = top;
		top = top->next;
		top->prev = nullptr;
		delete temp;
	}


	void PopBottom() {
		if (Stack_Empty()) {
			cout << "underflow";
		}
		Node* temp = bottom;
		bottom = bottom->prev;
		bottom->next = nullptr;
		delete temp;
	}
};



void CmpThree(int a, int b, int c, int& max, int& mid, int& min) {
	if (a >= b && a >= c) {
		max = a;
		b > c ? min = c : min = b;
		mid = a + b + c - max - min;
	}
	else if (b >= a && b >= c) {
		max = b;
		a > c ? min = c : min = a;
		mid = a + b + c - max - min;
	}
	else if (c >= a && c >= b) {
		max = c;
		b > a ? min = a : min = b;
		mid = a + b + c - max - min;
	}
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;

	int treasure;
	Stack Backpack;

	if (n <= m) {
		for (int i = 0; i < n; ++i) {
			cin >> treasure;
			Backpack.Push(treasure);
		}
		for (int i = 0; i < n - 1; ++i) {
			cout << Backpack.bottom->val << " ";
			Backpack.PopBottom();
		}
		cout << Backpack.bottom->val;
	}
	else {
		for (int i = 0; i < m; ++i) {
			cin >> treasure;
			Backpack.Push(treasure);
		}
		for (int i = 0; i < n - m; ++i) {
			int a = Backpack.top->val;
			int b = Backpack.bottom->val;
			Backpack.PopTop();
			Backpack.PopBottom();
			int c;
			cin >> c;
			int heaviest = 0, middle = 0, lightest = 0;
			CmpThree(a, b, c, heaviest, middle, lightest);
			Backpack.Push(middle);
			Backpack.Push(heaviest);
		}
		for (int i = 0; i < m - 1; ++i) {
			cout << Backpack.bottom->val << " ";
			Backpack.PopBottom();
		}
		cout << Backpack.bottom->val;
	}
}
