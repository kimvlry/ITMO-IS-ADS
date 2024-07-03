#include <iostream>
#include <vector>
using std::cin, std::cout, std::swap, std::string, std::vector, std::endl, std::ios_base;

vector<vector<int>> queues;

void Create() {
	vector<int> new_queue;
	queues.push_back(new_queue);
}


void SiftUp(int que_number, int i) {
	while (i != 0 && queues[que_number][i] < queues[que_number][(i - 1) / 2]) {
		swap(queues[que_number][i], queues[que_number][(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}


void Insert(int que_number, int x) {
	queues[que_number].push_back(x);
	SiftUp(que_number, queues[que_number].size() - 1);
}


void SiftDown(int que_number, int i) {
	auto size = queues[que_number].size();
	int minimal = i;
	int l_child = 2 * i + 1;
	int r_child = 2 * i + 2;

	if (l_child < size && queues[que_number][l_child] < queues[que_number][minimal]) {
		minimal = l_child;
	}
	if (r_child < size && queues[que_number][r_child] < queues[que_number][minimal]) {
		minimal = r_child;
	}
	if (minimal != i) {
		swap(queues[que_number][i], queues[que_number][minimal]);
		SiftDown(que_number, minimal);
	}
}


int ExtractMin(int que_number) {
	auto size = queues[que_number].size();
	int minimal = queues[que_number][0];
	queues[que_number][0] = queues[que_number][size - 1];
	queues[que_number].pop_back();
	SiftDown(que_number, 0);
	return minimal;
}


void IncreasePriority(int que_number, int old, int new_key) {
	for (int i = 0; i < queues[que_number].size(); ++i) {
		if (queues[que_number][i] == old) {
			queues[que_number][i] = new_key;
			SiftUp(que_number, i);
			break;
		}
	}
}


void Merge(int que_1, int que_2) {
	Create();
	auto que_3 = queues.size() - 1;
	queues[que_3] = queues[que_2];
	for (int i : queues[que_1]) {
		Insert(que_3, i);
	}
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	string command;
	int que_number, element, q1, q2, new_key;
	while (cin >> command) {
		if (command == "create") {
			Create();
		}
		else if (command == "insert") {
			cin >> que_number >> element;
			Insert(que_number, element);
		}
		else if (command == "extract-min") {
			cin >> que_number;
			if (queues[que_number].empty()) {
				cout << '*' << '\n';
			}
			else { cout << ExtractMin(que_number) << '\n'; }
		}
		else if (command == "merge") {
			cin >> q1 >> q2;
			Merge(q1, q2);
		}
		else if (command == "decrease-key") {
			cin >> que_number >> element >> new_key;
			IncreasePriority(que_number, element, new_key);
		}
	}
	return 0;
}
