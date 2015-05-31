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

// imos法で二重辺連結成分分解を行う
const int MAX_V = 100005;

struct UnionFind {
	int n;
	int parent[MAX_V];
	UnionFind(int size) {
		n = size;
		for (int i = 0; i < n; i++) {
			parent[i] = i;
		}
	}
	int find(int i) {
		if (i == parent[i]) return i;
		else return parent[i] = find(parent[i]);
	}
	void unite(int x, int y) {
		int a = find(x);
		int b = find(y);
		if (a == b) return;
		else {
			parent[a] = b;
		}
	}
	bool is_same(int x, int y) {
		return find(x) == find(y);
	}
};

struct SccBi {

	UnionFind uf;
	vector<int> G[MAX_V];			// 初期のグラフ
	vector<int> SCC_G[MAX_V];	// 二重辺連結成分分解後のグラフ
	vector<PII> edges;
	int used[MAX_V];
	int depth[MAX_V];
	int imos[MAX_V];

	SccBi() : uf(MAX_V) {
		memset(used, 0, sizeof(used));
		memset(depth, 0, sizeof(depth));
		memset(imos, 0, sizeof(imos));
	}

	void dfs(int cur, int prev, int d) {
		used[cur] = 1;
		depth[cur] = d;
		rep(i, G[cur].size()) {
			int adj = G[cur][i];
			if (adj == prev) continue; // 直前にいた頂点は無視
			if (used[adj]) {
				if (depth[adj] < depth[cur]) { //後退辺発見
					imos[cur] += 1;
					imos[adj] -= 1;
				}
			} else {
				dfs(adj, cur, d + 1);
			}
		}
	}

	int paint(int cur) {
		int res = 0;
		used[cur] = 1;
		rep(i, G[cur].size()) {
			int adj = G[cur][i];
			if (used[adj]) continue;
			int tmp = paint(adj);
			res += tmp;
			if (tmp > 0) uf.unite(cur, adj);
		}
		return imos[cur] = res + imos[cur];
	}

	void add_edge(int i, int j) {
		G[i].push_back(j);
		G[j].push_back(i);
		edges.push_back(PII(i, j));
	}

	void build() {
		dfs(0, -1, 0);
		memset(used, 0, sizeof(used));
		paint(0);
		rep(i, edges.size()) {
			int u = edges[i].first;
			int v = edges[i].second;
			int x = uf.find(u);
			int y = uf.find(v);
			if (uf.is_same(x, y)) continue;
			SCC_G[x].push_back(y);
			SCC_G[y].push_back(x);
		}
	}

};

SccBi scc_bi;

int main() {

	scc_bi.add_edge(0, 1);
	scc_bi.add_edge(1, 2);
	scc_bi.add_edge(2, 3);
	scc_bi.add_edge(2, 4);
	scc_bi.add_edge(3, 4);

	scc_bi.build();

	rep(i, 5) {
		printf("%d: ", i);
		rep(j, scc_bi.SCC_G[i].size()) {
			printf("%d ", scc_bi.SCC_G[i][j]);
		}
		printf("\n");
	}

	return 0;
}


