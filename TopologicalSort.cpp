#include <bits/stdc++.h>
#define rep(x, to) for (int x = 0; x < (to); x++)
#define REP(x, a, to) for (int x = (a); x < (to); x++)
#define EPS (1e-14)
#define _PA(x,N) rep(i,N){cout<<x[i]<<" ";}cout<<endl;
#define _PA2(x,H,W) rep(i,(H)){rep(j,(W)){cout<<x[i][j]<<" ";}cout<<endl;}

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;
typedef complex<double> Complex;
typedef vector< vector<int> > Mat;

vector<int> edge[1005];		// �אڃ��X�g
int in_node[1005];			// ���_i�ɓ��͂��Ă���Ӑ�
queue<int> Q;
vector<int> L;				// �g�|���W�J���\�[�g�̌���

int N, M;

// �T�v  �FTopological Sort
// �Ԃ�l�F����(true) / ���s(false, DAG�łȂ�)
bool TopologicalSort() {
	// ���͕ӂ������Ȃ����_�W�����擾
	for (int i = 0; i < N; i++) {
		if (in_node[i] != 0) continue;
		Q.push(i);
	}
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		L.push_back(u);
		for (int i = 0; i < edge[u].size(); i++) {
			int v = edge[u][i];
			in_node[v]--;
			if (in_node[v] != 0) continue;
			Q.push(v);
		}
	}
	for (int i = 0; i < N; i++) {
		if (in_node[i] == 0) continue;
		return false;
	}
	return true;
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int u, v;
		cin >> u >> v;
		edge[u].push_back(v);
		in_node[v]++;
	}

	bool res = TopologicalSort();

	if (res) {
		cout << "true" << endl;
	} else {
		cout << "false" << endl;
	}

	for (int i = 0; i < L.size(); i++) {
		cout << L[i] << " ";
	} cout << endl;
	return 0;
}


