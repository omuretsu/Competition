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
#define rep(x, to) for (int x = 0; x < (to); x++)
#define REP(x, a, to) for (int x = (a); x < (to); x++)
#define foreach(itr, x) for (typeof((x).begin()) itr = (x).begin(); itr != (x).end(); itr++)

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef pair<long, long> PLL;

struct Edge {
	int to;		// 行き先
	int cap;	// 要領
	int cost;	// コスト
	int rev;	// 逆辺のインデックスG[v][rev]
};

const int MAX_V = 105;
const int INF = (int)(1e+9 + 7);

int V;									// 頂点数 //設定すること
vector<Edge> G[MAX_V];	// 隣接リスト
int dist[MAX_V];				// 最短距離
int prevv[MAX_V];				// 最短路の直前の頂点
int preve[MAX_V];				// 最短路の直前の辺

void add_edge(int from, int to, int cap, int cost) {
	G[from].push_back((Edge){to, cap, cost, G[to].size()});
	G[to].push_back((Edge){from, 0, -cost, G[from].size() - 1});
}

// s -> t に f 流すときの最小費用流
// f流せないときは失敗(-1)
int min_cost_flow(int s, int t, int f) {
	int res = 0;
	while (f > 0) {
		// ベルマンフォードでコストに基づいた最短経路を求める
		fill(dist, dist + V, INF);
		dist[s] = 0;
		bool update = true;
		while (update) {
			update = false;
			for (int v = 0; v < V; v++) {
				if (dist[v] == INF) continue;
				for (int i = 0; i < G[v].size(); i++) {
					Edge &e = G[v][i];
					if (e.cap > 0 && dist[e.to] > dist[v] + e.cost) {
						dist[e.to] = dist[v] + e.cost;
						prevv[e.to] = v;
						preve[e.to] = i; // eはG[v][i]から来たことを示す
						update = true;
					}
				}
			}
		}

		// fはまだ残っているが、もう流せない
		if (dist[t] == INF) {
			return -1;
		}

		// 求めた最短路に目いっぱい流す
		int d = f; // 流す予定の流量
		for (int v = t; v != s; v = prevv[v]) {
			d = min(d, G[prevv[v]][preve[v]].cap);
		}
		f -= d; // 流す分だけ減らす
		res += d * dist[t]; // dist[t]はs->tの最短路上のcostをすべて含んでいる
		for (int v = t; v != s; v = prevv[v]) {
			Edge &e = G[prevv[v]][preve[v]];
			e.cap -= d;
			G[v][e.rev].cap += d;
		}
	}
	return res;
}

void init() {
	for (int i = 0; i < V; i++) {
		G[i].clear();
	}
	V = 5;
	add_edge(0, 1, 10, 2);
	add_edge(0, 2, 2, 4);
	add_edge(1, 2, 6, 6);
	add_edge(1, 3, 6, 2);
	add_edge(3, 2, 3, 3);
	add_edge(2, 4, 5, 2);
	add_edge(3, 4, 8, 6);
}


int main() {
#if 0
	for (int i = 0; i < 20; i++) {
		init();
		int res = min_cost_flow(0, 4, i);
		cout << res << endl;
	}
#endif
	init();
	cout << min_cost_flow(0, 4, 9) << endl;
	


	return 0;
}


