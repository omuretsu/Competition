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

// �T�v�F�􂱂݌v�Z�p
struct Convolution {
	// �T�v  : �t�[���G�ϊ����s��(FFT�ōs��)
	// ����1 : �t�[���G�ϊ����s���Ώ�
	// ����2 : �t�[���G�ϊ����s���Ώۂ̃T�C�Y(2�ׂ̂���ł��邱��)
	// ����3 : �t�[���G�t�ϊ����s����(true:�s��/false:�s��Ȃ�)
	// �Ԃ�l: �t�[���G�ϊ��̌���
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
			F[i] = F0[i % (n/2)] + pow_W * F1[i % (n/2)]; //�����͍l������Ă�
			pow_W *= W;
		}
		return F;
	}
	// �T�v  : �t�[���G�t�ϊ����s��
	// ����1 : �t�[���G�t�ϊ����s���Ώ�
	// ����2 : �t�[���G�t�ϊ����s���Ώۂ̃T�C�Y(2�ׂ̂���ł��邱��)
	// �Ԃ�l: �t�[���G�t�ϊ��̌���
	vector<Complex> idft(vector<Complex> &F, int n) {
		vector<Complex> f = dft(F, n, true);
		for (int i = 0; i < f.size(); i++) {
			f[i] /= n;
		}
		return f;
	}
	// �T�v  : ��ݍ��݂�����
	// �@�@  : ��ݍ��ݑΏۂ��t�[���G�ϊ�->�ϊ��������̓��m�̐ς��v�Z->�t�[���G�t�ϊ��ŏ�ݍ��݂��v�Z
	// ����1 : ��ݍ��ݑΏ�1 
	// ����2 : ��ݍ��ݑΏ�2
	// ����3 : ��ݍ��ݑΏۂ̃T�C�Y(2�ׂ̂���ł��邱��)
	// �Ԃ�l: ��ݍ��݂̌v�Z����
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


