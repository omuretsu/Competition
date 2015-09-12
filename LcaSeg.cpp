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
#include <complex>
#define rep(x, to) for (int x = 0; x < (to); x++)
#define REP(x, a, to) for (int x = (a); x < (to); x++)
#define foreach(itr, x) for (typeof((x).begin()) itr = (x).begin(); itr != (x).end(); itr++)
#define EPS (1e-14)
#define INF (1e+9 + 7)

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;
typedef complex<double> Complex;
typedef vector< vector<int> > Mat;

struct SegmentTree {
	int n;
	int dat[100005]; //2 * n - 1以上の大きさを確保すること
	int depth[100005];// 頂点の深さ
	int vs[100005]; // オイラーツアーによる頂点順序
	int id[100005]; // id[i]で頂点iが最初にvsに出現するインデックス
	void init(int m) {
		n = 1;
		while (n < m) {
			n *= 2;
		}
		for (int i = 0; i < 2 * n - 1; i++) {
			dat[i] = (int)(1e+9 + 7);
		}
	}
	void update(int i, int value) {
		i += n - 1;
		dat[i] = value;
		while (i > 0) {
			i = (i - 1) / 2;
			int chl = 2 * i + 1;
			int chr = 2 * i + 2;
			if (dat[chl] == INF) {
				dat[i] = dat[chr];
			} else if (dat[chr] == INF) {
				dat[i] = dat[chl];
			} else if (depth[dat[chl]] < depth[dat[chr]]) {
				dat[i] = dat[chl];
			} else {
				dat[i] = dat[chr];
			}
		}
	}
	//[a, b) node-k [l, r)
	int query(int a, int b, int k, int l, int r) {
		if (a <= l && r <= b) return dat[k];
		if (b <= l || r <= a) return INF;
		int chl = 2 * k + 1;
		int chr = 2 * k + 2;
		int res1 = query(a, b, chl, l, (l + r)/2);
		int res2 = query(a, b, chr, (l + r)/2, r);
		if (res1 == INF) return res2;
		if (res2 == INF) return res1;
		if (depth[res1] < depth[res2]) return res1;
		else return res2;
	}
};



// LCAをSegmentTree,RMQで解く
const int MAX_V = 1000005;
SegmentTree seg;
vector<int> G[1005];

void add_edge(int u, int v) {
	G[u].push_back(v);
	G[v].push_back(u);
}

void euler_tour(int u, int p, int d, int &k) {
	seg.vs[k] = u;
	seg.id[u] = k;
	seg.depth[k++] = d;
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v == p) continue;
		euler_tour(v, u, d + 1, k);
		seg.vs[k] = u;
		seg.depth[k++] = d;
	}
}

void init(int root) {
	int k = 0;
	euler_tour(root, -1, 0, k);
	seg.init(k);
	for (int i = 0; i < k; i++) {
		seg.update(i, i);
	}
}

int lca(int u, int v) {
	printf("seg.query(%d, %d, 0, 0, %d)\n",
			min(seg.id[u], seg.id[v]),
			max(seg.id[u], seg.id[v]) + 1,
			seg.n);
	return seg.vs[seg.query(min(seg.id[u], seg.id[v]), max(seg.id[u], seg.id[v]) + 1, 0, 0, seg.n)];
}


int main() {
	add_edge(1, 2);
	add_edge(1, 3);
	add_edge(3, 6);
	add_edge(2, 4);
	add_edge(2, 5);
	add_edge(5, 7);
	add_edge(5, 8);
	init(1);

	for (int i = 0; i <= 8; i++) {
		printf("id[%d]=%d\n", i, seg.id[i]);
	}

	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			int x = lca(i, j);
			printf("%d=lca(%d, %d)\n", x, i, j);
		}
	}

	return 0;
}


