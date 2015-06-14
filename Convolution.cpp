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
typedef pair<long, long> PLL;
typedef complex<double>  Complex;

// 概要：畳こみ計算用
struct Convolution {
	// 概要  : フーリエ変換を行う(FFTで行う)
	// 引数1 : フーリエ変換を行う対象
	// 引数2 : フーリエ変換を行う対象のサイズ(2のべき乗であること)
	// 引数3 : フーリエ逆変換を行うか(true:行う/false:行わない)
	// 返り値: フーリエ変換の結果
	vector<Complex> dft(vector<Complex> &f, int n, bool reverse = false) {
		vector<Complex> F(n);
		vector<Complex> f0(n/2);
		vector<Complex> f1(n/2);
		if (n == 1) {
			F[0] = f[0];
			return F;
		}
		for (int i = 0; i < n / 2; i++) {
			f0[i] = f[2 * i];
			f1[i] = f[2 * i + 1];
		}
		vector<Complex> F0 = dft(f0, n/2, reverse);
		vector<Complex> F1 = dft(f1, n/2, reverse);
		Complex  pow_W(1, 0);
		Complex W = Complex(cos(2 * M_PI / n), (reverse ? 1 : -1) * sin(2 * M_PI / n));
		for (int i = 0; i < n; i++) {
			F[i] = F0[i % (n/2)] + pow_W * F1[i % (n/2)]; //符号は考慮されてる
			pow_W *= W;
		}
		return F;
	}
	// 概要  : フーリエ逆変換を行う
	// 引数1 : フーリエ逆変換を行う対象
	// 引数2 : フーリエ逆変換を行う対象のサイズ(2のべき乗であること)
	// 返り値: フーリエ逆変換の結果
	vector<Complex> idft(vector<Complex> &F, int n) {
		vector<Complex> f = dft(F, n, true);
		for (int i = 0; i < f.size(); i++) {
			f[i] /= n;
		}
		return f;
	}
	// 概要  : 畳み込みをする
	// 　　  : 畳み込み対象をフーリエ変換->変換したもの同士の積を計算->フーリエ逆変換で畳み込みを計算
	// 引数1 : 畳み込み対象1 
	// 引数2 : 畳み込み対象2
	// 引数3 : 畳み込み対象のサイズ(2のべき乗であること)
	// 返り値: 畳み込みの計算結果
	vector<Complex> convolute(vector<Complex> &g, vector<Complex>& h, int n) {
		vector<Complex> gg = dft(g, n);
		vector<Complex> hh = dft(h, n);
		vector<Complex> ff(n);
		for (int i = 0; i < n; i++) {
			ff[i] = gg[i] * hh[i];
		}
		return idft(ff, n);
	}
};

int pow2_at_least(int n) {
	int res = 1;
	while (res < n) {
		res *= 2;
	}
	return res;
}

int N;
vector<Complex> A;
vector<Complex> B;
Convolution convolution;

int main() {
	cin >> N;
	int n = pow2_at_least(2 * N + 1);
	A.resize(n);
	B.resize(n);
	rep(i, N) {
		int a, b;
		cin >> a >> b;
		A[i + 1].real() = a;
		B[i + 1].real() = b;
	}
	vector<Complex> ans = convolution.convolute(A, B, n);
	rep(i, 2*N) {
		cout << (int)(ans[i+1].real()+0.1) << endl;
	}
	return 0;
}


