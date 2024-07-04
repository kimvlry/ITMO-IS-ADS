#include <iostream>
#include <vector>

#define INF ULONG_LONG_MAX
using namespace std;


void FloydWarshall(vector<vector<unsigned long long>>& dist) {
	int n = dist.size();
	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (dist[i][k] != INF && dist[k][j] != INF) {
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
				}
			}
		}
	}
}


int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<unsigned long long>> distances;
	distances.assign(n, vector<unsigned long long>(n, INF));

	for (int i = 0; i < n; ++i) {
		distances[i][i] = 0;
	}
	for (int i = 0; i < m; ++i) {
		int x, y;
		unsigned long long l;
		cin >> x >> y >> l;
		--x;
		--y;
		if (x != y) {
			distances[x][y] = min(distances[x][y], l);
			distances[y][x] = min(distances[y][x], l);
		}
	}

	FloydWarshall(distances);

	unsigned long long min_sum = INF;
	int crystal_castle;

	for (int i = 0; i < n; ++i) {
		unsigned long long sum = 0;
		for (int j = 0; j < n; ++j) {
			sum += distances[i][j];
		}
		if (sum < min_sum) {
			min_sum = sum;
			crystal_castle = i + 1;
		}
	}
	cout << crystal_castle;
}
