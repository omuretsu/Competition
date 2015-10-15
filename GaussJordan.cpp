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

typedef vector<double> vec;
typedef vector< vec > mat;

//
// ガウス・ジョルダン法（掃きだし法）
// 連立一次方程式の左辺係数をA,右辺をbとして方程式を満たす解を求める
// 方程式に解が存在しない場合は、サイズ0のvecを返す
//
vec gauss_jordan(const mat &A, const vec &b) {
	int n = A.size();
	// n x (n+1)
	mat B(n, vec(n + 1));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			B[i][j] = A[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		B[i][n] = b[i];
	}

	// 列に着目
	for (int i = 0; i < n; i++) {
		int pivot = i;
		for (int j = i; j < n; j++) {
			if (abs(B[j][i]) > abs(B[pivot][i])) pivot = j;
		}
		swap(B[i], B[pivot]);
		if (abs(B[i][i]) < EPS) return vec();
		
		for (int j = i + 1; j <= n; j++) B[i][j] /= B[i][i];
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			for (int k = i + 1; k <= n; k++) B[j][k] -= B[j][i] * B[i][k];
		}
	}

	vec x(n);
	for (int i = 0; i < n; i++) x[i] = B[i][n];
	return x;
}


int main() {
	mat m(3, vec(3));
	m[0][0] = 1; m[0][1] = -2; m[0][2] = 3;
	m[1][0] = 4; m[1][1] = -5; m[1][2] = 6;
	m[2][0] = 7; m[2][1] = -8; m[2][2] = 10;

	vec b(3);
	b[0] = 6;
	b[1] = 12;
	b[2] = 21;

	vec c = gauss_jordan(m, b);
	rep(i, c.size()) {
		cout << c[i] << endl;
	}

	return 0;
}
