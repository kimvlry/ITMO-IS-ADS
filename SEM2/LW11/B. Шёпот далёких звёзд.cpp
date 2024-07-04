#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> graph;
#define INF INT_MAX


int DFS(int v, int sink, graph& c_graph, graph& f_graph, int bottleneck, std::vector<bool>& visited) {
	if (v == sink) {
		return bottleneck;
	}
	visited[v] = true;
	for (int i = 0; i < c_graph.size(); ++i) {
		if (!visited[i] && f_graph[v][i] < c_graph[v][i]) {
			int minim = std::min(bottleneck, c_graph[v][i] - f_graph[v][i]);
			int delta = DFS(i, sink, c_graph, f_graph, minim, visited);
			if (delta > 0) {
				f_graph[v][i] += delta;
				f_graph[i][v] -= delta;
				return delta;
			}
		}
	}
	return 0;
}


int FordFulkerson(graph& g, graph& flow, int source, int sink) {
	int max_flow = 0;
	std::vector<bool> visited(g.size(), false);
	while (int cur = DFS(source, sink, g, flow, INF, visited)) {
		max_flow += cur;
		visited.assign(g.size(), false);
	}
	return max_flow;
}


int main() {
	int n, m;
	int a, b, capacity;
	std::cin >> n >> m;

	graph g(n, std::vector<int>(n, 0));
	graph flow(n, std::vector<int>(n, 0));

	for (int i = 0; i < m; i++) {
		std::cin >> a >> b >> capacity;
		--a;
		--b;
		g[a][b] = capacity;
	}

	std::cout << FordFulkerson(g, flow, 0, n - 1);
}
