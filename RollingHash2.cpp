// �a�{ p334
// ���[�����O�n�b�V����2�����I�Ɏg�p����ꍇ�̗�
//
// oooo
// oooo
// oooo
// oooo
//
// ��}�̂悤�ȃO���b�h�̃n�b�V�������߂����Ƃ��́A
//
// oooo -> x
// oooo -> x
// oooo -> x
// oooo -> x
//
// ��}�̂悤�Ɋe�s���ƂɃn�b�V�������߂�(x)
// ����ꂽ�n�b�V����(x)���炳��Ƀn�b�V�������߂�
//
// oooo -> x
// oooo -> x
// oooo -> x
// oooo -> x
//
//         |
//         v
//
//         y
//
// ��}�̂悤�ɒP��̃n�b�V���l(y)�����܂�
// ���n�b�V���lx�����߂�Ƃ��ƁA�n�b�V���ly�����߂�Ƃ���
// �@�قȂ����g�p���邱��
// �����̃v���O�����ł�mod���͏\���ɑ傫�Ȓl�Ƃ������Ƃŏȗ����Ă���
//
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
#define _PA(x,N) rep(i,N){cout<<x[i]<<" ";}cout<<endl;
#define _PA2(x,H,W) rep(i,(H)){rep(j,(W)){cout<<x[i][j]<<" ";}cout<<endl;}

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;
typedef complex<double> Complex;
typedef vector< vector<int> > Mat;

int N, M, P, Q, T;
string field[105];
string pattern[105][105];

ull tmp[105][105], hash[105][105];

void compute_hash(string s[105], int n, int m) {
	// ����ꂽ�n�b�V���l�̗񂩂�ēx�n�b�V���l�����߂邽�߁A
	// ��͂��ꂼ��̕ʂ̒l���g�p
	const ull B1 = 9973;
	const ull B2 = 1e+8 + 7;

	// �s����
	ull t1 = 1;
	for (int j = 0; j < Q; j++) t1 *= B1;

	for (int i = 0; i < n; i++) {
		ull e = 0;
		for (int j = 0; j < Q; j++) {
			e = e * B1 + s[i][j];
		}
		
		for (int j = 0; j + Q <= m; j++) {
			tmp[i][j] = e;
			if (j + Q < m) {
				e = e * B1 + s[i][j + Q] - s[i][j] * t1;
			}
		}
	}

	// �����
	ull t2 = 1;
	for (int i = 0; i < P; i++) t2 *= B2;

	for (int i = 0; i + Q <= m; i++) {
		ull e = 0;
		for (int j = 0; j < P; j++) {
			e = e * B2 + tmp[j][i];
		}

		for (int j = 0; j + P <= n; j++) {
			hash[j][i] = e;
			if (j + P < n) {
				e = e * B2 + tmp[j + P][i] - tmp[j][i] * t2;
			}
		}
	}

}

void solve() {
	multiset<ull> unseen;
	for (int i = 0; i < T; i++) {
		compute_hash(pattern[i], P, Q);
		cout << hash[0][0] << endl;
		unseen.insert(hash[0][0]);
	}
	cout << "---" << endl;

	compute_hash(field, N, M);
	for (int i = 0; i + P <= N; i++) {
		for (int j = 0; j + Q <= M; j++) {
			cout << hash[i][j] << endl;
			unseen.erase(hash[i][j]);
		}
	}

	cout << T - unseen.size() << endl;
}

int main() {
	cin >> N >> M;
	rep(i, N) {
		cin >> field[i];
	}
	cin >> P >> Q;
	cin >> T;
	rep(i, T) {
		rep(j, P) {
			cin >> pattern[i][j];
		}
	}
	solve();
	return 0;
}


