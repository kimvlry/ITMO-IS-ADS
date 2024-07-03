#include <iostream>


void QuickSort(long long* arr, long long left, long long right) {
	long long i = left;
	long long j = right;
	long long mid = left + rand() % (right - left);
	long long pivot = *(arr + mid);

	while (i <= j) {
		while (*(arr + i) < pivot) {
			i++;
		}
		while (*(arr + j) > pivot) {
			j--;
		}
		if (i <= j) {
			std::swap(*(arr + i), *(arr + j));
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
	long long n;
	std::cin >> n;

	auto* duration = new long long[n];
	auto* ddl = new long long[n];
	long long max_score = 0;
	long long days = 0;

	for (long long i = 0; i < n; ++i) {
		std::cin >> duration[i] >> ddl[i];
	}

	QuickSort(duration, 0, n - 1);
	QuickSort(ddl, 0, n - 1);

	for (long long i = 0; i < n; ++i) {
		max_score += ddl[i];
	}
	long long cur = 0;
	for (long long i = 0; i < n; ++i) {
		days += cur + duration[i];
		cur += duration[i];
	}
	std::cout << max_score - days;
	delete[] duration;
	delete[] ddl;
}
