// 蟻本 p334
// ローリングハッシュを2次元的に使用する場合の例
//
// oooo
// oooo
// oooo
// oooo
//
// 上図のようなグリッドのハッシュを求めたいときは、
//
// oooo -> x
// oooo -> x
// oooo -> x
// oooo -> x
//
// 上図のように各行ごとにハッシュを求める(x)
// 得られたハッシュ列(x)からさらにハッシュを求める
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
// 上図のように単一のハッシュ値(y)が求まる
// ※ハッシュ値xを求めるときと、ハッシュ値yを求めるときは
// 　異なる基数を使用すること
// ※下のプログラムではmod数は十分に大きな値ということで省略している
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
	// 得られたハッシュ値の列から再度ハッシュ値を求めるため、
	// 基数はそれぞれの別の値を使用
	const ull B1 = 9973;
	const ull B2 = 1e+8 + 7;

	// 行方向
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

	// 列方向
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


