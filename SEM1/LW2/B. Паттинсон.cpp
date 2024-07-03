#include <iostream>
using std::cout, std::cin, std::swap;


void QuickSort(int* arr, int left, int right) {
	int i = left;
	int j = right;
	int key = left + rand() % (right - left);
	int pivot = arr[key];
	while (i <= j) {
		while (arr[i] < pivot) {
			i++;
		}
		while (arr[j] > pivot) {
			j--;
		}
		if (i <= j) {
			swap(arr[i], arr[j]);
			i++;
			j--;
		}
	}
	if (left < j) {
		QuickSort(arr, left, j);
	}
	if (right > i) {
		QuickSort(arr, i, right);
	}
}


int main() {
	int n;
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
	}

	QuickSort(arr, 0, n - 1);
	for (int i = 0; i < n - 1; ++i) {
		cout << arr[i] << " ";
	}
	cout << arr[n - 1];
	delete[] arr;
}
