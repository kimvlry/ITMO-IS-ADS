#include <iostream>
#include <vector>


int main() {
	std::string text;
	std::cin >> text;

	int n = text.size();
	std::vector<int> pi(n, 0);
	for (int i = 1; i < n; ++i) {
		int j = pi[i - 1];
		while (j > 0 && text[j] != text[i]) {
			j = pi[j - 1];
		}
		if (text[i] == text[j]) {
			++j;
		}
		pi[i] = j;
	}
	for (auto c : pi) {
		std::cout << c << ' ';
	}
}
