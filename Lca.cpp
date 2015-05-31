#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <numeric>
#include <bitset>
#define rep(x, to) for (int x = 0; x < (to); x++)
#define REP(x, a, to) for (int x = (a); x < (to); x++)
#define foreach(itr, x) for (typeof((x).begin()) itr = (x).begin(); itr != (x).end(); itr++)

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef pair<long, long> PLL;

const int MAX_V = 100005;
const int MAX_LOG_V = 30;

struct Lca {
	vector<int> G[MAX_V];
	int parent[MAX_LOG_V+5][MAX_V];
	int depth[MAX_V];
	int root;
	Lca() {
		memset(parent, 0, sizeof(parent));
		memset(depth, 0, sizeof(depth));
		root = 0;	//設定すること
	}
	void add_edge(int i, int j) {
		G[i].push_back(j);
		G[j].push_back(i);
	}
	// 木であることが前提
	void dfs(int cur, int prev, int d) {
		parent[0][cur] = prev;
		depth[cur] = d;
		for (int i = 0; i < G[cur].size(); i++) {
			int adj = G[cur][i];
			if (adj == prev) continue;
			dfs(adj, cur, d + 1);
		}
	}
	void build(int V) {
		dfs(root, -1, 0);
		for (int k = 0; k + 1 < MAX_LOG_V; k++) {
			for (int v = 0; v < V; v++) {
				if (parent[k][v] < 0) parent[k + 1][v] = -1;
				else parent[k + 1][v] = parent[k][parent[k][v]];
			}
		}
	}
	int query(int u, int v) {
		if (depth[u] > depth[v]) swap(u, v);
		// 同じ深さに調節する
		for (int k = 0; k < MAX_LOG_V; k++) {
			if (((depth[v] - depth[u]) >> k) & 1) {
				v = parent[k][v];
			}
		}
		if (u == v) return v;
		// 最近の共通祖先を求める
		for (int k = MAX_LOG_V - 1; k >= 0; k--) {
			if (parent[k][v] != parent[k][u]) {
				v = parent[k][v];
				u = parent[k][u];
			}
		}
		return parent[0][u];
	}
};

Lca lca; // サイズ大きいのでスタック領域には作成不可

int main() {


	lca.add_edge(0, 1);
	lca.add_edge(0, 2);
	lca.add_edge(2, 5);
	lca.add_edge(1, 3);
	lca.add_edge(1, 4);
	lca.add_edge(4, 6);
	lca.add_edge(4, 7);
	lca.root = 0;
	lca.build(8);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 8; j++) {
			printf("%d%c", lca.parent[i][j], j == 7 ? '\n' : ' ');
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = i + 1; j < 8; j++) {
			printf("lca(%d,%d) = %d\n", i, j, lca.query(i, j));
		}
	}
	return 0;
}


