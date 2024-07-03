#include <iostream>


void InsertionSort(int* arr, int n) {
	for (int j = 1; j < n; ++j) {
		int key = arr[j];
		int i = j - 1;
		while (i >= 0 && arr[i] > key) {
			arr[i + 1] = arr[i];
			--i;
		}
		arr[i + 1] = key;
	}
}


int main() {
	int n;
	std::cin >> n;
	int a[n];

	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}
	InsertionSort(a, n);
	for (int i = 0; i < n - 1; ++i) {
		std::cout << a[i] << " ";
	}
	std::cout << a[n - 1];
}
