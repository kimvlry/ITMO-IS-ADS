#include <iostream>
using std::cout, std::cin;


void InsertionSortDescending(long long* arr, long long n, long long* film_no) {
	for (int j = 1; j < n; ++j) {
		long long key = arr[j];
		long long no_key = film_no[j];
		long long i = j - 1;

		while (i >= 0 && arr[i] < key) {
			arr[i + 1] = arr[i];
			film_no[i + 1] = film_no[i];
			--i;
		}
		arr[i + 1] = key;
		film_no[i + 1] = no_key;
	}
}


int main() {
	long long int n, m, k;
	cin >> n >> m >> k;

	auto* crit = new long long [n];
	auto* films = new long long[m];
	auto* film_no = new long long[m];

	for (long long i = 0; i < n; ++i) {
		cin >> crit[i];
	}
	for (long long i = 0; i < m; ++i) {
		films[i] = 0;
	}
	for (long long i = 0; i < m; ++i) {
		film_no[i] = i + 1;
	}

	for (long long i = 0; i < m; ++i) {
		for (long long j = 0; j < n; ++j) {
			long long score;
			cin >> score;
			films[i] += score * crit[j];
		}
		films[i] = films[i] % 1000000007;
	}

	InsertionSortDescending(films, m, film_no);
	for (long long i = 0; i < k; ++i) {
		cout << film_no[i] << " ";
	}
	delete[] crit;
	delete[] films;
	delete[] film_no;
}
