#include <iostream>


int main() {
	int n;
	std::cin >> n;
	int arr[n];

	int before = 0;
	int past = 0;
	int answer = -1;

	for (int i = 0; i < n; ++i) {
		std::cin >> arr[i];
		past += arr[i];
	}
	past -= arr[0];

	for (int i = 0; i < n; ++i) {
		if (before == past) {
			answer = i;
			break;
		}
		before += arr[i];
		past -= arr[i + 1];
	}
	std::cout << answer;
}
