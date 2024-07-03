#include <iostream>
using std::cin, std::cout, std::swap;


void MaxHeapify(int* arr, int n, int i) {
	int largest = i;
	int l_child = 2 * i + 1;
	int r_child = 2 * i + 2;

	if (l_child < n && arr[l_child] > arr[largest]) {
		largest = l_child;
	}
	if (r_child < n && arr[r_child] > arr[largest]) {
		largest = r_child;
	}
	if (largest != i) {
		swap(arr[i], arr[largest]);
		MaxHeapify(arr, n, largest);
	}
}


void BuildMaxHeap(int* arr, int n) {
	for (int i = n / 2 - 1; i >= 0; --i) {
		MaxHeapify(arr, n, i);
	}
}


void Heapsort(int* arr, int n) {
	BuildMaxHeap(arr, n);
	for (int i = n - 1; i >= 0; --i) {
		swap(arr[0], arr[i]);
		MaxHeapify(arr, i, 0);
	}
}


int main() {
	int n;
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
	}
	Heapsort(arr, n);
	for (int i = 0; i < n - 1; ++i) {
		cout << arr[i] << ' ';
	}
	cout << arr[n - 1];
	delete[] arr;
}
