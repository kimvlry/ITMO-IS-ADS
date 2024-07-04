#include <iostream>
#include <vector>



struct Node {
	int value;
	Node* next;

	Node(int x) {
		value = x;
		next = nullptr;
	}
};



struct Stack {
	Node* top = nullptr;


	~Stack() {
		while (top != nullptr) {
			Node* temp = top;
			top = top->next;
			delete temp;
		}
	}


	bool Empty() {
		return (top == nullptr);
	}


	void Push(int value) {
		Node* temp = new Node(value);
		temp->next = top;
		top = temp;
	}


	void Pop() {
		if (Empty()) {
			std::cout << "underflow";
			return;
		}
		Node* temp = top;
		top = top->next;
		delete temp;
	}
};



void Merge(std::vector<int>& arr, int left, int mid, int right) {
	int result[right - left];
	int l = 0, r = 0;
	while ((left + l < mid) && (mid + r < right)) {
		if (arr[left + l] <= arr[mid + r]) {
			result[l + r] = arr[left + l];
			l++;
		}
		else {
			result[l + r] = arr[mid + r];
			r++;
		}
	}
	while (left + l < mid) {
		result[l + r] = arr[left + l];
		l++;
	}
	while (mid + r < right) {
		result[l + r] = arr[mid + r];
		r++;
	}
	for (int i = 0; i < r + l; i++) {
		arr[left + i] = result[i];
	}
}


void MergeSort(std::vector<int>& arr, int left, int right) {
	if (left + 1 >= right) {
		return;
	}
	int mid = (left + right) / 2;
	MergeSort(arr, left, mid);
	MergeSort(arr, mid, right);
	Merge(arr, left, mid, right);
}


bool ValidPostorder(std::vector<int>& arr, int n) {
	Stack s;
	int root = std::numeric_limits<int>::max();
	for (int i = n - 1; i >= 0; --i) {
		if (arr[i] > root) {
			return false;
		}
		while (!s.Empty() && s.top->value > arr[i]) {
			root = s.top->value;
			s.Pop();
		}
		s.Push(arr[i]);
	}
	return true;
}


bool ValidPreorder(std::vector<int>& arr, int n) {
	Stack s;
	int root = std::numeric_limits<int>::min();
	for (int i = 0; i < n; ++i) {
		if (arr[i] < root) {
			return false;
		}
		while (!s.Empty() && s.top->value < arr[i]) {
			root = s.top->value;
			s.Pop();
		}
		s.Push(arr[i]);
	}
	return true;
}


bool AreTheSameTree(std::vector<int>& first, std::vector<int>& second, std::vector<int>& third, int n) {
	MergeSort(first, 0, n);
	MergeSort(second, 0, n);
	MergeSort(third, 0, n);
	return (first == second) && (second == third);
}


int main() {
	int n;
	int val;
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;

	std::vector<int> pre;
	std::vector<int> in;
	std::vector<int> post;

	for (int i = 0; i < n; ++i) {
		std::cin >> val;
		pre.push_back(val);
	}
	for (int i = 0; i < n; ++i) {
		std::cin >> val;
		in.push_back(val);
		if (i > 0 && in[i] < in[i - 1]) {
			std::cout << "NO";
			return 0;
		}
	}
	for (int i = 0; i < n; ++i) {
		std::cin >> val;
		post.push_back(val);
	}

	if (!ValidPreorder(pre, n) || !ValidPostorder(post, n)) {
		std::cout << "NO";
		return 0;
	}

	if (!AreTheSameTree(pre, in, post, n)) {
		std::cout << "NO";
		return 0;
	}

	std::cout << "YES";
}
