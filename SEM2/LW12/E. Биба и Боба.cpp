#include <iostream>
#include <vector>

/*
 h[i] - h[j] == i - j
 <=> h[i] - i == h[j] - j
*/

void solve(std::vector<int>& h) {
	int c = 0;
	std::vector<int> freq(h.size() * 2, 0);

	for (int i = 0; i < h.size(); ++i) {
		int delta = h[i] - i + h.size();
		c += freq[delta];
		freq[delta] += 1;
	}
	std::cout << c;
}


int main() {
	int n;
	std::cin >> n;

	std::vector<int> heights;
	heights.resize(n);

	for (int i = 0; i < n; ++i)
		std::cin >> heights[i];

	solve(heights);
}
