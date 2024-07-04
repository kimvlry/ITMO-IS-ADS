// #include <blazingio.hpp>
#include <iostream>
#include <vector>

int n;


int f(int x) {
	return x % (n * 2);
}


int h(int x, int attempt) {
	if (attempt == 1) {
		return f(x);
	}
	return (f(x) + attempt) % (n * 2);
}


int main() {
	std::cin >> n;
	std::vector<int> table;
	table.assign(n * 2, -1);

	int x;
	for (int i = 0; i < n; ++i) {
		std::cin >> x;
		int attempt = 1;
		while (true) {
			int hash = h(x, attempt);
			if (table[hash] == x) {
				break;
			}
			if (table[hash] == -1) {
				table[hash] = x;
				break;
			}
			++attempt;
		}
	}

	for (int i = 0; i < n; ++i) {
		std::cin >> x;
		int attempt = 1;
		while (true) {
			int hash = h(x, attempt);
			if (table[hash] == x) {
				break;
			}
			if (table[hash] == -1) {
				std::cout << "NO";
				return 0;
			}
			++attempt;
		}
	}

	std::cout << "YES";
}
