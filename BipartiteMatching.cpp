#include <bits/stdc++.h>
#define rep(x, to) for (int x = 0; x < (to); x++)
#define REP(x, a, to) for (int x = (a); x < (to); x++)
#define foreach(itr, x) for (typeof((x).begin()) itr = (x).begin(); itr != (x).end(); itr++)
#define EPS (1e-14)
#define _PA(x,N) rep(i,N){cout<<x[i]<<" ";}cout<<endl;
#define _PA2(x,H,W) rep(i,(H)){rep(j,(W)){cout<<x[i][j]<<" ";}cout<<endl;}

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;
typedef complex<double> Complex;
typedef vector< vector<int> > Mat;

const int MAX_V = 1005;

//
//  2部グラフのマッチング
//
struct Graph {
	vector<int> G[MAX_V];
	int match[MAX_V];
	int used[MAX_V];

	void add_edge(int u, int v) {
		G[u].push_back(v);
		G[v].push_back(v);
	}

	bool dfs(int v) {
		used[v] = true;
		for (int i = 0; i < G[v].size(); i++) {
			int u = G[v][i];
			int w = match[u];
			if (w < 0 || (!used[w] && dfs(w))) {
				match[v] = u;
				match[u] = v;
				return true;
			}
		}
		return false;
	}

	int biparate_matching(int V) {
		int res = 0;
		memset(match, -1, sizeof(match));
		for (int v = 0; v < V; v++) {
			if (match[v] >= 0) continue;
			memset(used, 0, sizeof(used));
			if (dfs(v)) {
				res++;
			}
		}
		return res;
	}

};

Graph bi;

void solve() {
/*
 [0]---[3]
   ＼ /
     x
    / ＼
 [1]   [4]
   ＼ /
     x
    / ＼
 [2]    [5]

 上図の2部グラフの場合、最大マッチングは、
 [0]-[3],[1]-[5],[2]-[4]
 になる
*/

	bi.add_edge(0, 3);
	bi.add_edge(0, 4);
	bi.add_edge(1, 3);
	bi.add_edge(1, 5);
	bi.add_edge(2, 4);


	int res = bi.biparate_matching(6);
	printf("matching: %d\n", res);
	for (int i = 0; i < 6; i++) {
		if (bi.match[i] < 0) continue;
		printf("[%d] - [%d]\n", i, bi.match[i]);
	}

}

int main() {
	solve();
	return 0;
}


