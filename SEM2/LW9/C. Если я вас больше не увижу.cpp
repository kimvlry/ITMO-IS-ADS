#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

#define INF LLONG_MAX



struct neuronode {
	long long destination;
	long long time;


	neuronode(long long d, long long t) {
		destination = d;
		time = t;
	}
};



long long Dijkstra(vector<vector<neuronode>>& graph) {
	long long n = graph.size();
	vector<long long> dists(n, INF);
	vector<bool> visited(n, false);
	priority_queue<pair<long long, long long>,
	               vector<pair<long long, long long>>,
	               greater<pair<long long, long long>>> pq;

	pq.push({0, 0});
	while (!pq.empty()) {
		long long cur = pq.top().second;
		long long cur_time = pq.top().first;
		pq.pop();
		if (visited[cur]) {
			continue;
		}
		visited[cur] = true;
		for (const auto& neighbour : graph[cur]) {
			long long b = neighbour.destination;
			long long to_time = cur_time + neighbour.time;
			if (to_time < dists[b]) {
				dists[b] = to_time;
				pq.push({to_time, b});
			}
		}
	}
	long long time = dists[n - 1] == INF ? -1 : dists[n - 1];
	return time;
}


int main() {
	long long n, m;
	cin >> n >> m;

	vector<vector<neuronode>> graph(n);
	for (long long i = 0; i < m; ++i) {
		long long a, b, t;
		cin >> a >> b >> t;
		--a;
		--b;
		graph[a].push_back(neuronode(b, t));
	}

	long long time_before_existential_crisis = Dijkstra(graph);
	cout << time_before_existential_crisis;
}
