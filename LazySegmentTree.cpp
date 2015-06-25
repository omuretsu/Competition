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

// 遅延評価SegmentTree
struct LazyPropagationSegmentTree {
	int n;						// 2のべき乗値
	ll lazy[500005];	// 2*nのサイズ以上を設定すること
	ll  dat[500005];	// 2*nのサイズ以上を設定すること
	void init(int m) {
		n = 1;
		while (n < m) n *= 2;
		memset(lazy, 0, sizeof(lazy));
		memset(dat, 0, sizeof(dat));
	}
	// ノードkの遅延評価を行う
	void lazy_evaluate(int k, int l, int r) {
		dat[k] += (r - l) * lazy[k];
		if (k < n - 1) {
			lazy[2 * k + 1] += lazy[k];
			lazy[2 * k + 2] += lazy[k];
		}
		lazy[k] = 0;
	}
	// 区間[a,b)にxを加える。
	// k,l,rは現在ノードkに着目し、ノードkは区間[l,r)を指すことを示す
	void add(int a, int b, int x, int k, int l, int r) {
		//再帰で帰ってきたとき、範囲外の領域のlazyも考慮する必要があるため
		//範囲外チェックの前に遅延評価を行う
		if (lazy[k] != 0) {
			lazy_evaluate(k, l, r);
		}
		if (b <= l || r <= a) return;
		if (a <= l && r <= b) {
			dat[k] += (r - l) * x;
			//葉じゃない
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
	// 区間[a,b)の値を参照する
	// k,l,rは現在ノードkに着目し、ノードkは区間[l,r)を指すことを示す
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


