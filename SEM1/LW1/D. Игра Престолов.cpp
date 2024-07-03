#include <iostream>


int main() {
	int n, m, q;
	int ep, se, lost = 0;
	std::cin >> n >> m >> q;
	int complete_show[n][m];

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			complete_show[i][j] = 0;
		}
	}
	for (int i = 0; i < q; ++i) {
		std::cin >> ep >> se;
		complete_show[se - 1][ep - 1] = 1;
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (complete_show[i][j] == 0) {
				++lost;
			}
		}
	}
	std::cout << lost << "\n";
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (complete_show[i][j] == 0) {
				std::cout << j + 1 << " " << i + 1 << "\n";
			}
		}
	}
}
