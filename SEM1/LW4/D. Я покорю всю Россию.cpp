#include <iostream>
#include <vector>



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
			std::cout << "queue is empty" << '\n';
			return;
		}
		Node* tmp = head;
		head = head->next;
		if (head == nullptr) {
			tail = nullptr;
		}
		delete tmp;
	}
};



struct Event {
	long long ID;
	long long value;


	Event(long long id, long long val) {
		ID = id;
		value = val;
	}
};



void SiftDown(std::vector<Event>& a, int i) {
	int n = a.size();
	int largest = i;
	int l_child = 2 * i + 1;
	int r_child = 2 * i + 2;

	if (l_child < n && ((a[l_child].value > a[largest].value) || (a[l_child].value == a[largest].value && a[l_child]
		.ID > a[largest].ID))) {
		largest = l_child;
	}
	if (r_child < n && ((a[r_child].value > a[largest].value) || (a[r_child].value == a[largest].value && a[r_child]
		.ID > a[largest].ID))) {
		largest = r_child;
	}
	if (largest != i) {
		std::swap(a[i], a[largest]);
		SiftDown(a, largest);
	}
}


void BuildHeap(std::vector<Event>& a) {
	int n = a.size();
	for (int i = n / 2 - 1; i >= 0; --i) {
		SiftDown(a, i);
	}
}


void ExtractMax(std::vector<Event>& a) {
	int size = a.size();
	a[0] = a[size - 1];
	a.pop_back();
	SiftDown(a, 0);
}


int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	long long n, m, a, b, c;
	std::string v;
	std::cin >> n;
	std::vector<Event> Rate;
	std::vector<Event> Royalty;
	Queue Verdict;

	for (int i = 0; i < n; ++i) {
		std::cin >> a >> b >> c;
		Rate.emplace_back(a, b);
		Royalty.emplace_back(a, c);
	}
	std::cin >> m;
	for (int i = 0; i < m; ++i) {
		std::cin >> v;
		(v == "YES") ? Verdict.Enqueue(1) : Verdict.Enqueue(0);
	}
	BuildHeap(Rate);
	BuildHeap(Royalty);
	std::vector<long long> ans1;
	std::vector<long long> ans2;

	for (int i = 0; i < n; ++i) {
		long long city = Rate[0].ID;
		if (Royalty[0].ID == city) {
			ans2.push_back(Rate[0].ID);
			ExtractMax(Rate);
			ExtractMax(Royalty);
		}
		else {
			if (!Verdict.IsEmpty()) {
				ans1.push_back(city); // алло алло
				if (Verdict.head->val == 1) {
					ans2.push_back(city);
				}
				Verdict.Dequeue(); // до свидания

				int j = 0;
				while (Royalty[j].ID != city) {
					++j;
				}
				Royalty.erase(Royalty.begin() + j);
				SiftDown(Royalty, j);
				ExtractMax(Rate);
			}
			else { ExtractMax(Rate); }
		}
	}
	for (int i = 0; i < ans1.size(); ++i) {
		std::cout << ans1[i] << " ";
	}
	std::cout << '\n';
	for (int i = 0; i < ans2.size(); ++i) {
		std::cout << ans2[i] << " ";
	}
}
