#include <iostream>
#include <vector>

/*
   alternative solution

   int main() {
		int n, m, a, b;
		std::cin >> n >> m;

		std::vector<bool> pushed(n, false);
		std::vector<int> q;

		for (int i = 0; i < m; ++i) {
			std::cin >> a >> b;
			if (!pushed[a]) {
				q.push_back(a);
				pushed[a] = true;
			}
			if (!pushed[b]) {
				q.push_back(b);
				pushed[b] = true;
			}
		}

		for (auto what_the_fuck_problem_G_is : q) {
			std::cout << what_the_fuck_problem_G_is << ' ';
		}
   }
*/


typedef std::vector<std::vector<int>> graph;


void HamiltonianCycle(const graph& g, std::vector<int>& q) {
	int n = g.size();

	for (int step = 0; step < n; ++step) {
		if (g[q[0]][q[1]]) {
			q.push_back(q[0]);
			q.erase(q.begin());
		}
		else {
			int i = 2;
			while (!g[q[0]][q[i]] || !g[q[1]][q[i + 1]]) {
				++i;
			}
			int j = 0;
			while (2 + j < i - j) {
				std::swap(q[1 + j], q[i - j]);
				++j;
			}
			q.push_back(q[0]);
			q.erase(q.begin());
		}
	}
}


int main() {
	int n, m;
	int a, b;
	std::cin >> n >> m;

	graph g(n, std::vector<int>(n, 0));
	std::vector<bool> pushed(n, false);
	std::vector<int> q;

	for (int i = 0; i < m; ++i) {
		std::cin >> a >> b;
		if (!pushed[a]) {
			q.push_back(a);
			pushed[a] = true;
		}
		if (!pushed[b]) {
			q.push_back(b);
			pushed[b] = true;
		}
		g[a][b] = 1;
		g[b][a] = 1;
	}

	HamiltonianCycle(g, q);

	for (auto v : q) {
		std::cout << v << " ";
	}
}
