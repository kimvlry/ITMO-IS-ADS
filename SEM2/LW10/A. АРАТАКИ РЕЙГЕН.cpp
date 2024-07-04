#include <iostream>
#include <vector>
// #include <blazingio.hpp>

#define graph std::vector<std::vector<int>>


void DFS(auto v, graph& g, std::vector<int>& parent) {
	for (const auto u : g[v]) {
		if (u != parent[v]) {
			parent[u] = v;
			DFS(u, g, parent);
		}
	}
}


std::vector<int> Pruefer(graph& g) {
	auto n = g.size();

	std::vector<int> deg(n);
	std::vector<int> preufer_code(n - 2);
	std::vector<int> parents;

	parents.assign(n, -1);
	int p = -1;

	DFS(n - 1, g, parents);

	for (int i = 0; i < n; ++i) {
		deg[i] = g[i].size();
		if (deg[i] == 1 && p == -1) {
			p = i;
		}
	}
	int current_leaf = p;

	for (int i = 0; i < n - 2; ++i) {
		int next = parents[current_leaf];
		preufer_code[i] = next + 1;

		if (--deg[next] == 1 && p > next) {
			current_leaf = next;
		}
		else {
			++p;
			while (deg[p] != 1) {
				++p;
			}
			current_leaf = p;
		}
	}
	return preufer_code;
}


int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, m;
	std::cin >> n >> m;

	graph cool(n);

	int a, b;
	for (int i = 0; i < m; ++i) {
		std::cin >> a >> b;
		--a;
		--b;
		cool[a].push_back(b);
		cool[b].push_back(a);
	}
	for (auto i : Pruefer(cool)) {
		std::cout << i << ' ';
	}
}
