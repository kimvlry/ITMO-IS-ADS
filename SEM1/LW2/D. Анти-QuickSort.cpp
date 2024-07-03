#include <iostream>
using std::cout, std::cin, std::swap;


int main() {
	int n;
	cin >> n;
	int* arr = new int[n];
	for (int i = 1; i < n + 1; ++i) {
		arr[i - 1] = i;
	}
	for (int i = 2; i < n; ++i) {
		swap(arr[i], arr[i / 2]);
	}
	for (int i = 0; i < n - 1; ++i) {
		cout << arr[i] << " ";
	}
	cout << arr[n - 1];
	delete[] arr;
}
