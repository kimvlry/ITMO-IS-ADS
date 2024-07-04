#include <iostream>
#include <vector>
#include <stack>
#include <ranges>

#define graph std::vector<std::vector<int>>


void DFS(int v, graph& g, std::vector<bool>& visited, bool& odd_degree) {
	visited[v] = true;
	if (g[v].size() % 2 != 0) {
		odd_degree = true;
		return;
	}
	for (const auto u : g[v]) {
		if (!visited[u]) {
			DFS(u, g, visited, odd_degree);
		}
	}
}


bool IsEulerian(graph& g) {
	std::vector<bool> visited(g.size(), false);
	bool odd_degree = false;

	DFS(0, g, visited, odd_degree);
	if (odd_degree) {
		return false;
	}
	for (int i = 0; i < g.size(); ++i) {
		if (visited[i] == false && !g[i].empty()) {
			return false;
		}
	}
	return true;
}


std::optional<std::vector<int>> EulerCycle(graph& g) {
	std::stack<int> st;
	std::vector<int> cycle;

	if (!IsEulerian(g)) {
		return std::nullopt;
	}

	st.push(0);
	while (!st.empty()) {
		int v = st.top();
		if (g[v].size() == 0) {
			cycle.push_back(v);
			st.pop();
		}
		else {
			int u = g[v][0];
			st.push(u);
			auto it = std::ranges::find(g[v], u);
			g[v].erase(it);
			it = std::ranges::find(g[u], v);
			g[u].erase(it);
		}
	}
	return cycle;
}


int main() {
	int n, m, a, b;
	std::cin >> n >> m;

	graph g(n);
	for (int i = 0; i < m; ++i) {
		std::cin >> a >> b;
		--a;
		--b;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	auto ans = EulerCycle(g);
	if (ans) {
		for (auto i = ans.value().rbegin(); i != ans.value().rend(); ++i) {
			std::cout << *i + 1 << ' ';
		}
	}
	else {
		std::cout << ":(";
	}
}
