#include <iostream>


void QuickSortDescending(int* arr, int left, int right) {
	int i = left;
	int j = right;
	int key = left + rand() % (right - left);
	int pivot = arr[key];
	while (i <= j) {
		while (arr[i] > pivot) {
			i++;
		}
		while (arr[j] < pivot) {
			j--;
		}
		if (i <= j) {
			std::swap(arr[i], arr[j]);
			i++;
			j--;
		}
	}
	if (left < j) {
		QuickSortDescending(arr, left, j);
	}
	if (right > i) {
		QuickSortDescending(arr, i, right);
	}
}


int main() {
	int n;
	long long ans = 0;
	int ab[2] = {0, 0};
	std::cin >> n;
	int* sticks = new int[n];
	for (int k = 0; k < n; ++k) {
		std::cin >> sticks[k];
	}

	QuickSortDescending(sticks, 0, n - 1);

	int j = 0;
	for (int i = 0; i < n - 1; ++i) {
		if (sticks[i] == sticks[i + 1] || sticks[i] - 1 == sticks[i + 1]) {
			ab[j] = sticks[i + 1];
			j++;
			if (j == 2) {
				ans += (long long)ab[0] * (long long)ab[1];
				j = 0;
				ab[0] = 0;
				ab[1] = 0;
			}
			++i;
		}
	}
	std::cout << ans;
}
