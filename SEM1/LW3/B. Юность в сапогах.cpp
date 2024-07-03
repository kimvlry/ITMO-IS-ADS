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



struct Queue {
	Node* head = nullptr;
	Node* tail = nullptr;


	~Queue() {
		while (tail != nullptr) {
			auto tmp = tail;
			tail = tail->next;
			delete tmp;
		}
	}


	bool IsEmpty() {
		return (head == nullptr);
	}


	void Enqueue(int value) {
		Node* temp = new Node(value);
		if (IsEmpty()) {
			tail = temp;
			head = temp;
		}
		else {
			tail->next = temp;
			tail = temp;
		}
	}


	void Dequeue() {
		if (IsEmpty()) {
			std::cerr << "queue is empty";
			return;
		}
		Node* temp = head;
		head = head->next;
		if (head == nullptr) {
			tail = nullptr;
		}
		delete temp;
	}
};



int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	char command;
	int number;
	Queue Pervaki;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> command;
		if (command == '+') {
			cin >> number;
			Pervaki.Enqueue(number);
		}
		else if (command == '-') {
			if (!Pervaki.IsEmpty()) {
				cout << Pervaki.head->val << '\n';
				Pervaki.Dequeue();
			}
		}
	}
}
