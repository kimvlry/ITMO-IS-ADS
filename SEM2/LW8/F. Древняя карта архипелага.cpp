#include <iostream>
#include <queue>
#include <vector>
#include <set>

using namespace std;


set<int> BFS(vector<vector<int>> graph, set<int>& valid, int k) {
	int start = 0;
	vector<int> distances(graph.size(), -1);
	queue<int> q;
	q.push(start);
	distances[0] = 0;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int neighbor : graph[cur]) {
			if (distances[neighbor] == -1) {
				distances[neighbor] = distances[cur] + 1;
				q.push(neighbor);
				if (distances[neighbor] == k) {
					valid.insert(neighbor + 1);
				}
			}
		}
	}
	return valid;
}


int main() {
	int n, m, k;
	cin >> n >> m >> k;

	vector<vector<int>> graph;
	graph.assign(n, {});

	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a;
		--b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	set<int> valid;
	BFS(graph, valid, k);
	if (valid.size() == 0) {
		cout << "NO";
		return 0;
	}
	for (const auto& it : valid) {
		cout << it << endl;
	}
}
