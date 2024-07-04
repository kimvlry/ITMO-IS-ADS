#include <iostream>
#include <vector>

#define INF 1000000



struct edge {
	int from, to, weight;
};



bool BFNegativeCycle(const std::vector<edge>& edges, int k) {
	int n = edges.size();
	std::vector<int> distances(n, 0);
	std::vector<int> parents(n, -1);
	int changed = -1;

	for (int i = 0; i < n; ++i) {
		changed = -1;
		for (const auto& e : edges) {
			if (distances[e.from] < INF) {
				if (distances[e.from] + e.weight < distances[e.to]) {
					distances[e.to] = std::max(-INF, distances[e.from] + e.weight);
					parents[e.to] = e.from;
					changed = e.to;
				}
			}
		}
	}
	if (changed == -1) {
		return true;
	}
	for (int i = 0; i < n; ++i) {
		changed = parents[changed];
	}
	std::vector<int> cycle;

	for (int vertex = changed;; vertex = parents[vertex]) {
		cycle.push_back(vertex);
		if (vertex == changed && cycle.size() > 1) {
			break;
		}
	}
	return cycle.size() <= k;
}


int main() {
	int N, k;
	int n, m;
	int a, b, h;
	std::cin >> N >> k;

	for (int i = 0; i < N; ++i) {
		std::cin >> n >> m;
		std::vector<edge> edges(m);

		for (int j = 0; j < m; ++j) {
			std::cin >> a >> b >> h;
			--a;
			--b;
			edges[j] = {a, b, h};
		}
		BFNegativeCycle(edges, k) ? std::cout << "YES" << std::endl : std::cout << "NO" << std::endl;
		edges.clear();
	}
}
