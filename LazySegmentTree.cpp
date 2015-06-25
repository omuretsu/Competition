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

// �x���]��SegmentTree
struct LazyPropagationSegmentTree {
	int n;						// 2�ׂ̂���l
	ll lazy[500005];	// 2*n�̃T�C�Y�ȏ��ݒ肷�邱��
	ll  dat[500005];	// 2*n�̃T�C�Y�ȏ��ݒ肷�邱��
	void init(int m) {
		n = 1;
		while (n < m) n *= 2;
		memset(lazy, 0, sizeof(lazy));
		memset(dat, 0, sizeof(dat));
	}
	// �m�[�hk�̒x���]�����s��
	void lazy_evaluate(int k, int l, int r) {
		dat[k] += (r - l) * lazy[k];
		if (k < n - 1) {
			lazy[2 * k + 1] += lazy[k];
			lazy[2 * k + 2] += lazy[k];
		}
		lazy[k] = 0;
	}
	// ���[a,b)��x��������B
	// k,l,r�͌��݃m�[�hk�ɒ��ڂ��A�m�[�hk�͋��[l,r)���w�����Ƃ�����
	void add(int a, int b, int x, int k, int l, int r) {
		//�ċA�ŋA���Ă����Ƃ��A�͈͊O�̗̈��lazy���l������K�v�����邽��
		//�͈͊O�`�F�b�N�̑O�ɒx���]�����s��
		if (lazy[k] != 0) {
			lazy_evaluate(k, l, r);
		}
		if (b <= l || r <= a) return;
		if (a <= l && r <= b) {
			dat[k] += (r - l) * x;
			//�t����Ȃ�
			if (k < n - 1) {
				lazy[2 * k + 1] += x;
				lazy[2 * k + 2] += x;
			}
			return;
		}
		int m = (l + r) / 2;
		int chl = 2 * k + 1;
		int chr = 2 * k + 2;
		add(a, b, x, chl, l, m);
		add(a, b, x, chr, m, r);
		dat[k] = dat[chl] + dat[chr];
	}
	// ���[a,b)�̒l���Q�Ƃ���
	// k,l,r�͌��݃m�[�hk�ɒ��ڂ��A�m�[�hk�͋��[l,r)���w�����Ƃ�����
	ll query(int a, int b, int k, int l, int r) {
		if (lazy[k] != 0) {
			lazy_evaluate(k, l, r);
		}
		if (b <= l || r <= a) return 0;
		if (a <= l && r <= b) return dat[k];
		int m = (l + r) / 2;
		int chl = 2 * k + 1;
		int chr = 2 * k + 2;
		return query(a, b, chl, l, m) + query(a, b, chr, m, r);
	}
};

int main() {
	return 0;
}


