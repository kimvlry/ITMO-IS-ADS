#include <iostream>


int main() {
	int n, k, border = 0;
	std::cin >> n >> k;
	int arr[n];
	for (int i = 0; i < n; ++i) {
		std::cin >> arr[i];
	}

	if (k % n == 0) {
		for (int i = 0; i < n - 1; ++i) {
			std::cout << arr[i] << " ";
		}
		std::cout << arr[n - 1];
	}

	else {
		if (k > 0) {
			border = n - (k % n);
		}
		if (k < 0) {
			if (abs(k) > n) {
				border = (abs(k)) % n;
			}
			else {
				border = abs(k);
			}
		}

		for (int i = border; i < n; ++i) {
			std::cout << arr[i] << " ";
		}
		for (int i = 0; i < border - 1; ++i) {
			std::cout << arr[i] << " ";
		}
		std::cout << arr[border - 1];
	}
}
