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

typedef vector< vector<int> > Mat;

//A * Bの行列積を計算
Mat mul(Mat &A, Mat &B) {
	Mat C(A.size(), vector<int>(B[0].size()));
	rep(i, A.size()) {
		rep(j, B[0].size()) {
			rep(k, A[0].size()) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	return C;
}

//A^xの行列積を計算する(行数=列数であること)
Mat pow(Mat A, int x) {
	Mat B(A.size(), vector<int>(A.size()));
	rep(i, A.size()) B[i][i] = 1; //単位行列
	while (x > 0) {
		if (x & 1) {
			B = mul(B, A);
		}
		A = mul(A, A);
		x = x >> 1;
	}
	return B;
}


int main() {
	Mat A(2, vector<int>(3)); //2 x 3
	Mat B(3, vector<int>(2)); //3 x 2

	A[0][0] = 1; A[0][1] = 2; A[0][2] = 3;
	A[1][0] = 3; A[1][1] = 2; A[1][2] = 1;

	B[0][0] = 3; B[0][1] = 7;
	B[1][0] = 5; B[1][1] = 1;
	B[2][0] = 1; B[2][1] = 2;

	Mat C = mul(A, B);
	rep(i, C.size()) {
		rep(j, C[0].size()) {
			printf("%d%c", C[i][j], j == C[0].size() - 1 ? '\n' : ' ');
		}
	}
	return 0;
}


