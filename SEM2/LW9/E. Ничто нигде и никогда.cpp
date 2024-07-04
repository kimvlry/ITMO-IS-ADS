#include <iostream>
#include <vector>
#include <set>

int cur_time = 0;

std::vector<std::vector<int>> graph;
std::set<std::pair<int, int>> bridges;

std::vector<bool> visited;
std::vector<int> entry_time;
std::vector<int> entry_minimum;


void DFS(int v, int parent) {
	visited[v] = true;
	++cur_time;
	entry_time[v] = cur_time;
	entry_minimum[v] = cur_time;

	for (int to : graph[v]) {
		if (to != parent) {
			if (visited[to]) {
				entry_minimum[v] = std::min(entry_time[to], entry_minimum[v]);
			}
			else {
				DFS(to, v);
				entry_minimum[v] = std::min(entry_minimum[v], entry_minimum[to]);

				if (entry_time[v] < entry_minimum[to]) {
					bridges.emplace(std::min(v + 1, to + 1), std::max(v + 1, to + 1));
				}
			}
		}
	}
}


void FindBridges() {
	for (int i = 0; i < graph.size(); ++i) {
		if (!visited[i]) {
			DFS(i, -1);
		}
	}
}


int main() {
	int n, m;
	int a, b;

	std::cin >> n >> m;
	graph.assign(n, {});
	entry_time.assign(n, -1);
	entry_minimum.assign(n, -1);
	visited.assign(n, false);

	for (int i = 0; i < m; ++i) {
		std::cin >> a >> b;
		--a;
		--b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	FindBridges();

	for (const auto& it : bridges) {
		std::cout << it.first << ' ' << it.second << std::endl;
	}
}
