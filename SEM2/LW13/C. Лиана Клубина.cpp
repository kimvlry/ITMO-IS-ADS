#include <iostream>


int main() {
	int n, m;
	std::string text;
	std::cin >> n >> m >> text;

	int ans = 0;

	int i, j, k;
	for (int a = 0; a < m; ++a) {
		std::cin >> i >> j >> k;
		----i;
		----j;
		bool cool = true;
		while (k > 0) {
			if (text[++i] != text[++j]) {
				cool = false;
				break;
			}
			--k;
		}
		if (cool) {
			++ans;
		}
	}
	std::cout << ans;
}
