#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

typedef long long ll;



struct edge {
	int a;
	int b;
	int weight;


	edge(int a, int b, int w)
		: a(a)
		, b(b)
		, weight(w) {
	}
};



bool comparator(edge& a, edge& b) {
	return a.weight < b.weight;
}



struct DSU {
	std::vector<int> presenters;
	std::vector<std::set<int>> united;


	DSU(int size) {
		presenters.assign(size, 0);
		united.assign(size, {});
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


	void Unite(int x, int y, int w, std::vector<int>& ans) {
		int x_root = Find(x);
		int y_root = Find(y);

		if (x_root != y_root) {
			int x_rank = united[x_root].size();
			int y_rank = united[y_root].size();
			if (x_rank < y_rank) {
				swap(united[x_root], united[y_root]);
			}
			presenters[y_root] = x_root;

			while (united[y_root].size() > 0) {
				int v = *united[y_root].begin();

				if (united[x_root].find(v) == united[x_root].end()) {
					united[x_root].insert(v);
				}
				else {
					ans[v] -= w;
				}

				united[y_root].erase(v);
			}
		}
	}


	bool AreConnected(int x, int y) {
		return Find(x) == Find(y);
	}
};



ll Kruskal(DSU& sets, std::vector<edge>& edges, int n, std::vector<int>& answer) {
	ll ans = 0;
	int cnt = 0;
	std::ranges::sort(edges, comparator);
	for (const auto cur : edges) {
		if (!sets.AreConnected(cur.a, cur.b)) {
			sets.Unite(cur.a, cur.b, cur.weight, answer);
			ans += cur.weight;
			++cnt;
			if (cnt == n - 1) {
				break;
			}
		}
	}
	return ans;
}


int main() {
	int n, m;
	std::cin >> n >> m;

	std::vector<edge> edges;
	DSU cool(n);

	std::vector<int> ans;
	ans.assign(m, -1);

	int a, b, weight;
	for (int i = 0; i < m; ++i) {
		std::cin >> a >> b >> weight;
		--a;
		--b;
		cool.united[a].insert(i);
		cool.united[b].insert(i);

		edges.emplace_back(a, b, weight);
		ans[i] = weight;
	}

	ll timing = Kruskal(cool, edges, n, ans);
	for (int i = 0; i < m; ++i) {
		std::cout << ans[i] + timing << '\n';
	}
}
