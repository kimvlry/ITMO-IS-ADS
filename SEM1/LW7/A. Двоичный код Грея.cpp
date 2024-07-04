#include <iostream>
#include <string>
#include <vector>
#include <cmath>


void BrrBrrBrrGreyCoding(int n) {
	if (n <= 0)
		return;

	std::vector<std::string> codes;
	codes.emplace_back("0");
	codes.emplace_back("1");

	int i;
	int j;
	for (i = 2; i < pow(2, n); i = i * 2) {
		for (j = i - 1; j >= 0; --j) {
			codes.push_back(codes[j]);
		}
		for (j = 0; j < i; ++j) {
			codes[j] = "0" + codes[j];
		}
		for (j = i; j < 2 * i; ++j) {
			codes[j] = "1" + codes[j];
		}
	}
	for (i = 0; i < codes.size(); i++) {
		std::cout << codes[i] << '\n';
	}
}


int main() {
	int n;
	std::cin >> n;
	BrrBrrBrrGreyCoding(n);
}
