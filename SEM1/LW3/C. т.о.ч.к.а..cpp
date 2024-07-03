#include <iostream>
using std::cin, std::cout, std::string;


void CountSort(string* arr, int n, int pos) {
	int count[26]{0};
	string temp[n];
	for (int i = 0; i < n; ++i) {
		++count[int(arr[i][pos]) - 97];
	}
	for (int i = 1; i < 26; ++i) {
		count[i] += count[i - 1];
	}
	for (int i = n - 1; i >= 0; --i) {
		temp[count[int(arr[i][pos]) - 97] - 1] = arr[i];
		--count[int(arr[i][pos]) - 97];
	}
	for (int i = 0; i < n; ++i) {
		arr[i] = temp[i];
	}
}


void RadixSort(string* arr, int n, int k, int t) {
	for (int pos = k - 1; pos >= k - t; --pos) {
		CountSort(arr, n, pos);
	}
}


int main() {
	int n, k, t;
	cin >> n >> k >> t;
	string messages[n];
	for (int i = 0; i < n; ++i) {
		cin >> messages[i];
	}
	RadixSort(messages, n, k, t);
	for (int i = 0; i < n; ++i) {
		cout << messages[i] << '\n';
	}
}
