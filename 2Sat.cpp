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

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;
typedef complex<double> Complex;
typedef vector< vector<int> > Mat;

const int MAX_V = 100005;

// 強連結成分分解
struct Scc {
	int V; // 頂点数
	vector<int> G[MAX_V];	// グラフの隣接リスト
	vector<int> rG[MAX_V];	// 辺の向きが逆の隣接リスト
	vector<int> vs; // 帰りがけの順の並び(dfsで最深頂点の順に入る)
	bool used[MAX_V];
	int cmp[MAX_V]; // 頂点が何番目のトポロジカル順序に属しているか？

	void add_edge(int from, int to) {
		G[from].push_back(to);
		rG[to].push_back(from);
	}

	void dfs(int v) {
		used[v] = true;
		for (int i = 0; i < G[v].size(); i++) {
			if (!used[G[v][i]]) dfs(G[v][i]);
		}
		vs.push_back(v);
	}

	void rdfs(int v, int k) {
		used[v] = true;
		cmp[v] = k;
		for (int i = 0; i < rG[v].size(); i++) {
			if (!used[rG[v][i]]) rdfs(rG[v][i], k);
		}
	}

	int scc() {
		memset(used, 0, sizeof(used));
		vs.clear();
		// トポロジカルソート
		for (int i = 0; i < V; i++) {
			if (!used[i]) dfs(i);
		}
		memset(used, 0, sizeof(used));
		int k = 0;
		// 強連結成分ごとに番号付け
		for (int i = vs.size() - 1; i >= 0; i--) {
			if (!used[vs[i]]) rdfs(vs[i], k++);
		}
		return k;
	}
};

//
// 2-SAT
// a∨bは(￢a→b)または(￢b→a)に書き換え可能
// これを利用して
// a∨b = (￢a→b)∧(￢b→a)
// にする
// a→bをa,bは頂点、→は有向辺としてグラフを構築
// グラフに対して、強連結成分を適用し、
// 強連結成分内にaと￢aが共存していたら、充足不可
// 共存していなかったら充足可能
//
struct TwoSat {
	Scc sat; // 強連結成分分解用
	int n; // 変数の種類(否定含まない)

	void init(int size) {
		n = size; 
		sat.V = 2 * size; // 否定を含むので2倍
	}
	
	// 否定はnから番号付けすること
	// 例)a,b,cの3変数扱う
	// a=0,b=1,c=2とし、￢a=3,￢b=4,￢c=5
	// のようにする
	void add_edge(int from, int to) {
		sat.add_edge(from, to);
	}

	int scc() {
		return sat.scc();
	}

	// 充足判定
	bool is_satisfy() {
		for (int i = 0; i < n; i++) {
			// a と ￢a が同じ強連結成分に含まれていたら
			if (sat.cmp[i] == sat.cmp[n + i]) {
				return false;
			}
			return true;
		}
	}

	// 割り当て
	vector<int> assign() {
		vector<int> res;
		if (!is_satisfy()) {
			return res;
		}
		for (int i = 0; i < n; i++) { 
			if (sat.cmp[i] < sat.cmp[i + n]) {
				res.push_back(0);
			} else {
				res.push_back(1);
			}
		}
		return res;
	}

};

TwoSat sat;

int main() {
#if 0
	//(a∨￢b)∧(b∨c)∧(￢c∨￢a)
	int N = 3;
	sat.init(N);
	sat.add_edge(0, 5);
	sat.add_edge(1, 0);
	sat.add_edge(2, 3);
	sat.add_edge(3, 4);
	sat.add_edge(4, 2);
	sat.add_edge(5, 1);
#else
	//
	int N = 2;
	sat.init(N);
	sat.add_edge(0, 1);
	sat.add_edge(0, 3);
	sat.add_edge(1, 0);
	sat.add_edge(1, 2);
	sat.add_edge(2, 1);
	sat.add_edge(2, 3);
	sat.add_edge(3, 0);
	sat.add_edge(3, 2);
#endif

	sat.scc();

	if (sat.is_satisfy()) {
		cout << "true" << endl;
		vector<int> assign = sat.assign();
		for (int i = 0; i < N; i++) {
			printf("%d : %d\n", i, assign[i]);
		}
	} else {
		cout << "no" << endl;
	}


	return 0;
}


