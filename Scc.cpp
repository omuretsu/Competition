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

// ���A����������
struct Scc {
	int V; // ���_��
	vector<int> G[MAX_V];	// �O���t�̗אڃ��X�g
	vector<int> rG[MAX_V];	// �ӂ̌������t�̗אڃ��X�g
	vector<int> vs; // �A�肪���̏��̕���(dfs�ōŐ[���_�̏��ɓ���)
	bool used[MAX_V];
	int cmp[MAX_V]; // ���_�����Ԗڂ̃g�|���W�J�������ɑ����Ă��邩�H

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
		// �g�|���W�J���\�[�g
		for (int i = 0; i < V; i++) {
			if (!used[i]) dfs(i);
		}
		memset(used, 0, sizeof(used));
		int k = 0;
		// ���A���������Ƃɔԍ��t��
		for (int i = vs.size() - 1; i >= 0; i--) {
			if (!used[vs[i]]) rdfs(vs[i], k++);
		}
		return k;
	}
};

Scc scc;

int main() {
	scc.V = 12;
	scc.add_edge(0, 10);
	scc.add_edge(0, 3);
	scc.add_edge(1, 10);
	scc.add_edge(2, 0);
	scc.add_edge(3, 2);
	scc.add_edge(4, 2);
	scc.add_edge(4, 3);
	scc.add_edge(6, 7);
	scc.add_edge(7, 8);
	scc.add_edge(8, 7);
	scc.add_edge(9, 1);
	scc.add_edge(10, 9);
	scc.add_edge(11, 4);

	scc.scc();

	rep(i, scc.V) {
		printf("%d: %d\n", i, scc.cmp[i]);
	}

	return 0;
}


