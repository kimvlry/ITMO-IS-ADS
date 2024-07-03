#include <iostream>
using std::cin, std::cout;



struct Node {
	int val;
	Node* prev;
	Node* next;


	Node(int value) {
		val = value;
		prev = nullptr;
		next = nullptr;
	}
};



struct Stack {
	Node* top = nullptr;
	Node* bottom = nullptr;
	Node* ptr = nullptr;


	~Stack() {
		while (top != nullptr) {
			auto tmp = top;
			top = top->next;
			delete tmp;
		}
	}


	bool IsEmpty() {
		return top == nullptr && bottom == nullptr;
	}


	void Push(int value) {
		Node* temp = new Node(value);
		if (top == nullptr && bottom == nullptr) {
			bottom = temp;
		}
		else if (bottom != nullptr && top == nullptr) {
			top = temp;
			top->next = bottom;
			bottom->prev = top;
		}
		else if (bottom != nullptr) {
			temp->next = top;
			top->prev = temp;
			top = temp;
		}
		delete temp;
	}


	void PopTop() {
		if (!IsEmpty()) {
			Node* temp = top;
			top = top->next;
			top->prev = nullptr;
			delete temp;
		}
	}


	void PopBottom() {
		if (!IsEmpty()) {
			Node* temp = bottom;
			bottom = bottom->prev;
			bottom->next = nullptr;
			delete temp;
		}
	}


	int SkipDescending() {
		int to_skip = 0;
		ptr = top;
		while (ptr->next != nullptr) {
			if (ptr->val <= ptr->next->val) {
				++to_skip;
			}
			else {
				return to_skip;
			}
			ptr = ptr->next;
			PopTop();
		}
		return to_skip;
	}
};



int main() {
	int n;
	Stack Tasks;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int rate;
		cin >> rate;
		Tasks.Push(rate);
	}

	int to_skip = Tasks.SkipDescending();
	bool la_perfectly_beautiful_non_ascending_array = (to_skip == n - 1);
	if (la_perfectly_beautiful_non_ascending_array) {
		for (int i = 0; i < n - 1; ++i) {
			cout << "-1 ";
		}
	}
	else {
		for (int i = 0; i < n - 1 - to_skip; ++i) {
			Tasks.ptr = Tasks.bottom->prev;
			int counter = 1;
			while (Tasks.ptr != nullptr && Tasks.ptr->next != nullptr && Tasks.ptr->val <= Tasks.bottom->val) {
				++counter;
				Tasks.ptr = Tasks.ptr->prev;
			}
			if (Tasks.ptr != nullptr && Tasks.ptr->val > Tasks.bottom->val) {
				cout << counter << ' ';
			}
			else {
				cout << "-1 ";
			}
			Tasks.PopBottom();
		}
		for (int i = 0; i < to_skip; ++i) {
			cout << "-1 ";
		}
	}
	cout << "-1";
}
