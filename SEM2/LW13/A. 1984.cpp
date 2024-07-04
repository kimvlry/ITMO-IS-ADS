#include <iostream>
#include <vector>


auto PrefixFunction(std::string text) {
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
	return pi;
}


int main() {
	std::string text, pattern;
	std::cin >> text >> pattern;
	auto pi = PrefixFunction(pattern + "#" + text);
	std::vector<int> ans;
	for (int i = 0; i < pi.size(); ++i) {
		if (pi[i] == pattern.size()) {
			ans.push_back(i - pattern.size() * 2);
		}
	}
	std::cout << ans.size() << '\n';
	for (auto s : ans) {
		std::cout << s << ' ';
	}
}
