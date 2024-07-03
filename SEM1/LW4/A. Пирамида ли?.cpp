#include <iostream>
using std::cin, std::cout;


int main() {
	int n;
	cin >> n;
	int arr[n + 1];
	for (int i = 1; i <= n; ++i) {
		cin >> arr[i];
	}
	for (int i = 1; i <= n / 2; ++i) {
		if ((2 * i <= n && arr[i] > arr[2 * i]) || (2 * i + 1 <= n && arr[i] > arr[2 * i + 1])) {
			cout << "NO";
			return 0;
		}
	}
	cout << "YES";
}
