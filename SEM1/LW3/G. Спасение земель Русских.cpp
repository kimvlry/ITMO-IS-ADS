#include <iostream>
using std::cin, std::cout;


int main() {
	int n, k;
	cin >> n >> k;
	int seats[n];
	for (int i = 0; i < n; ++i) {
		cin >> seats[i];
	}

	int l = 0;
	int r = seats[n - 1] - seats[0] + 1;
	while (l < r) {
		int mid = (l + r) / 2;
		int cows = 1;
		int last = seats[0];
		for (int i = 1; i < n; ++i) {
			if (seats[i] - last > mid) {
				++cows;
				last = seats[i];
			}
		}
		if (cows >= k) {
			l = mid + 1;
		}
		else {
			r = mid;
		}
	}
	cout << l;
}
