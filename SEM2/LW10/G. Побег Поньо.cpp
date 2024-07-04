#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;



struct edge {
	int a;
	int b;
	int weight;
	bool lucky;


	edge(int a, int b, int w, bool l)
		: a(a)
		, b(b)
		, weight(w)
		, lucky(l) {
	}
};



bool comparator(edge& a, edge& b) {
	return a.weight < b.weight;
}



struct DSU {
	std::vector<int> presenters;
	std::vector<int> ranks;


	DSU(int size) {
		presenters.assign(size, 0);
		ranks.assign(size, 1);
		for (int i = 0; i < size; ++i) {
			presenters[i] = i;
		}
	}


	int Find(int x) {
		if (presenters[x] == x) {
			return x;
		}
		return (presenters[x] = Find(presenters[x]));
	}


	void Unite(int x, int y) {
		int x_root = Find(x);
		int y_root = Find(y);
		if (x_root != y_root) {
			if (ranks[x_root] < ranks[y_root]) {
				std::swap(x_root, y_root);
			}
			ranks[x_root] += ranks[y_root];
			presenters[y_root] = x_root;
		}
	}


	bool AreConnected(int x, int y) {
		return Find(x) == Find(y);
	}
};



ll Kruskal(DSU& sets, std::vector<edge>& edges, int n, ll& loot) {
	ll ans = 0;
	int cnt = 0;
	std::ranges::sort(edges, comparator);
	for (const auto cur : edges) {
		if (!sets.AreConnected(cur.a, cur.b)) {
			sets.Unite(cur.a, cur.b);
			if (cur.lucky) {
				loot -= cur.weight;
			}
			else {
				ans += cur.weight;
			}
			++cnt;
			if (cnt == n - 1) {
				break;
			}
		}
	}
	return ans;
}


int main() {
	ll n, m, k;
	std::cin >> n >> m >> k;

	std::vector<edge> edges;
	DSU sets(n);
	ll loot = 0;

	int a, b, weight;
	for (int i = 0; i < m; ++i) {
		std::cin >> a >> b >> weight;
		--a;
		--b;
		loot += weight;
		edges.emplace_back(a, b, weight, true);
	}

	for (int i = 0; i < k; ++i) {
		std::cin >> a >> b >> weight;
		--a;
		--b;
		edges.emplace_back(a, b, weight, false);
	}

	ll ans = Kruskal(sets, edges, n, loot) - loot;
	ans < 0 ? std::cout << 0 : std::cout << ans;
}
