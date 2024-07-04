// #include <blazingio.hpp>
#include <iostream>
#include <vector>
#include <ranges>

using std::vector;
using std::ranges::find;
typedef std::vector<std::vector<int>> graph;


void TrueLove(graph& m_preferences, graph& w_preferences) {
	int n = m_preferences.size();

	vector<int> m_partner(n, -1);
	vector<int> w_partner(n, -1);

	int cnt_single = n;
	while (cnt_single > 0) {
		auto single_it = find(w_partner, -1);
		if (single_it == w_partner.end()) {
			break;
		}
		int single = single_it - w_partner.begin();

		for (int i = 0; i < n; ++i) {
			if (w_partner[single] != -1) {
				break;
			}

			int potential_match = m_preferences[single][i];

			if (m_partner[potential_match] != -1) {
				int m = m_partner[potential_match];
				auto candidate = find(w_preferences[potential_match], single);
				auto current = find(w_preferences[potential_match], m);

				if (candidate < current) {
					m_partner[potential_match] = single;
					w_partner[single] = potential_match;
					w_partner[m] = -1;
				}
			}

			else {
				--cnt_single;
				m_partner[potential_match] = single;
				w_partner[single] = potential_match;
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		std::cout << i << " " << w_partner[i] << "\n";
	}
}


int main() {
	int n;
	std::cin >> n;

	graph m_preferences(n);
	graph w_preferences(n);

	int x;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			std::cin >> x;
			m_preferences[i].push_back(x);
		}
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			std::cin >> x;
			w_preferences[i].push_back(x);
		}
	}

	TrueLove(m_preferences, w_preferences);
}
