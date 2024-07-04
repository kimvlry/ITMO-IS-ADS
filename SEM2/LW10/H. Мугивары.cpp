#include <iostream>
#include <vector>
#include <queue>

#define INF INT_MAX
#define ll long long



struct edge {
	int destination;
	int time;


	edge(int destination, int time)
		: destination(destination)
		, time(time) {
	}
};



void ParseHyperedge(std::vector<ll>& islands, std::vector<std::vector<edge>>& graph, ll t) {
	ll n = islands.size();
	for (ll i = 0; i < n - 1; ++i) {
		for (int j = i + 1; j < n; ++j) {
			ll a = islands[i];
			ll b = islands[j];
			graph[a].emplace_back(b, t);
			graph[b].emplace_back(a, t);
		}
	}
}


ll Dijkstra(std::vector<std::vector<edge>>& graph, ll k) {
	ll n = graph.size();
	std::vector<ll> timing(n, INF);
	std::vector<bool> visited(n, false);
	std::priority_queue<std::pair<ll, ll>, std::vector<std::pair<ll, ll>>, std::greater<>> pq;
	timing[0] = 0;

	pq.push({0, 0});
	while (!pq.empty()) {
		ll cur = pq.top().second;
		ll cur_time = pq.top().first;
		pq.pop();
		if (visited[cur]) {
			continue;
		}
		visited[cur] = true;
		for (const auto& neighbour : graph[cur]) {
			ll b = neighbour.destination;
			ll b_time = cur_time + neighbour.time;
			if (b_time < timing[b]) {
				timing[b] = b_time;
				pq.push({b_time, b});
			}
		}
	}
	ll time = timing[k - 1] == INF ? -1 : timing[k - 1];
	return time;
}


int main() {
	int n, m, k;
	std::cin >> n >> m >> k;

	std::vector<std::vector<edge>> graph;
	graph.assign(n, {});

	ll s, t;
	for (ll i = 0; i < m; ++i) {
		std::cin >> s >> t;
		std::vector<ll> islands;
		ll island;
		for (ll j = 0; j < s; ++j) {
			std::cin >> island;
			--island;
			islands.push_back(island);
		}
		ParseHyperedge(islands, graph, t);
	}

	std::cout << Dijkstra(graph, k);
}
