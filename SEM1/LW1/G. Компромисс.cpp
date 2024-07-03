#include <iostream>


int main() {
	int t, n;
	std::cin >> t;
	int* border = new int[2];
	for (int i = 0; i < t; ++i) {
		border[0] = 15;
		border[1] = 30;
		std::cin >> n;
		int number;
		char sign, trash;
		for (int j = 0; j < n; ++j) {
			std::cin >> sign >> trash >> number;
			if ((sign == '<' && number >= border[0]) || (sign == '>' && number <= border[1])) {
				if (sign == '>') {
					if (number > border[0]) {
						border[0] = number;
					}
				}
				if (sign == '<') {
					if (number < border[1]) {
						border[1] = number;
					}
				}
				std::cout << border[0] << "\n";
			}
			else {
				// vote doesn't fit borders
				std::cout << -1 << "\n";
				border[0] = 100;
				border[1] = -100;
			}
		}
	}
	delete[] border;
}
