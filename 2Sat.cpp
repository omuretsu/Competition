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

//
// 2-SAT
// a��b��(��a��b)�܂���(��b��a)�ɏ��������\
// ����𗘗p����
// a��b = (��a��b)��(��b��a)
// �ɂ���
// a��b��a,b�͒��_�A���͗L���ӂƂ��ăO���t���\�z
// �O���t�ɑ΂��āA���A��������K�p���A
// ���A����������a�Ɓ�a���������Ă�����A�[���s��
// �������Ă��Ȃ�������[���\
//
struct TwoSat {
	Scc sat; // ���A����������p
	int n; // �ϐ��̎��(�ے�܂܂Ȃ�)

	void init(int size) {
		n = size; 
		sat.V = 2 * size; // �ے���܂ނ̂�2�{
	}
	
	// �ے��n����ԍ��t�����邱��
	// ��)a,b,c��3�ϐ�����
	// a=0,b=1,c=2�Ƃ��A��a=3,��b=4,��c=5
	// �̂悤�ɂ���
	void add_edge(int from, int to) {
		sat.add_edge(from, to);
	}

	int scc() {
		return sat.scc();
	}

	// �[������
	bool is_satisfy() {
		for (int i = 0; i < n; i++) {
			// a �� ��a ���������A�������Ɋ܂܂�Ă�����
			if (sat.cmp[i] == sat.cmp[n + i]) {
				return false;
			}
			return true;
		}
	}

	// ���蓖��
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
	//(a�Ɂ�b)��(b��c)��(��c�Ɂ�a)
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


