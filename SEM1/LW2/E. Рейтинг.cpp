#include <iostream>
long long ans = 0;


void Merge(int* arr, int left, int mid, int right) {
	int result[right - left];
	int l = 0;
	int r = 0;
	while ((left + l < mid) && (mid + r < right)) {
		if (arr[left + l] <= arr[mid + r]) {
			result[l + r] = arr[left + l];
			l++;
			ans += r;
		}
		else {
			result[l + r] = arr[mid + r];
			r++;
		}
	}
	while (left + l < mid) {
		result[l + r] = arr[left + l];
		l++;
		ans += r;
	}
	while (mid + r < right) {
		result[l + r] = arr[mid + r];
		r++;
	}
	for (int i = 0; i < r + l; i++) {
		arr[left + i] = result[i];
	}
}


void MergeSort(int* arr, int left, int right) {
	if (left + 1 >= right) {
		return;
	}
	int mid = (left + right) / 2;
	MergeSort(arr, left, mid);
	MergeSort(arr, mid, right);
	Merge(arr, left, mid, right);
}


int main() {
	int n;
	std::cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; ++i) {
		std::cin >> arr[i];
	}
	MergeSort(arr, 0, n);
	std::cout << ans;
	delete[] arr;
}
