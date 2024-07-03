#include <iostream>


int main() {
	int n;
	std::cin >> n;
	int word_lenght = n;

	int to_remove_on_right = 0;
	int to_remove_on_left = 0;
	char* s = new char[n];
	char* reversed_s = new char[n];

	for (int i = 0; i < n; ++i) {
		std::cin >> s[i];
	}
	for (int i = 0; i < n; ++i) {
		reversed_s[i] = s[n - i - 1];
	}

	for (int i = 0; i < (n - (n % 2 != 0)) / 2; ++i) {
		// letter to remove is on the right?
		if (s[i] != s[n - i - 1]) {
			if (s[n - i - 2] == s[i]) {
				to_remove_on_right++;
				n = n - 1;
			}
			else {
				to_remove_on_right += 2;
			}
		}
	}
	n = word_lenght;

	for (int i = 0; i < ((n - (n % 2 != 0)) / 2); ++i) {
		// same for the reversed (letter to remove was on left)
		if (reversed_s[i] != reversed_s[n - i - 1]) {
			if (reversed_s[i] == reversed_s[n - i - 2]) {
				++to_remove_on_left;
				n = n - 1;
			}
			else {
				to_remove_on_left += 2;
			}
		}
	}

	if ((to_remove_on_right == 1) or (to_remove_on_left == 1) or (to_remove_on_right + to_remove_on_left == 0)) {
		std::cout << "YES";
	}
	else {
		std::cout << "NO";
	}
	delete[] s;
	delete[] reversed_s;
}
