#include <iostream>


int main() {
	int max_bin_len = 60;
	long long x, y;
	int answer = 0;
	std::cin >> x >> y;
	for (int left_ones = 1; left_ones <= (max_bin_len - 2); ++left_ones) {
		for (int middle_zeros = 1; middle_zeros <= (max_bin_len - left_ones) - 1; ++middle_zeros) {
			for (int right_ones = 1; right_ones <= (max_bin_len - left_ones - middle_zeros); ++right_ones) {
				long long pow_of_two = 1;
				long long number = 1;

				if (right_ones > 1) {
					for (int c = 1; c < right_ones; c++) {
						pow_of_two *= 2;
						number += pow_of_two;
					}
				}

				for (int i = right_ones; i < (middle_zeros + right_ones); ++i) {
					pow_of_two *= 2;
				}

				for (int i = (middle_zeros + right_ones); i < (left_ones + middle_zeros + right_ones); ++i) {
					pow_of_two *= 2;
					number += pow_of_two;
				}
				if ((number <= y) && (number >= x)) {
					++answer;
				}
			}
		}
	}
	std::cout << answer;
}
