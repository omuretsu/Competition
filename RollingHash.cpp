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

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;
typedef complex<double> Complex;
typedef vector< vector<int> > Mat;

// RollingHash
// �����񂩂�n�b�V���l�����߂�
// ������̌����Ƃ�����Ƃ��ɗL��
// q��m�݂͌��ɑf�ł��鐔�l���w��
struct RollingHash {
	string s;
	ull p;
	ull mod;
	ull phash[int(1e+6) + 5];
	ull pow[int(1e+6) + 5];
	void init(string t, ull q=1e+9 + 7, ull m=(1ULL<<30)) {
		s = t;
		p = q;
		mod = m;
	}
	void build() {
		phash[0] = 0; //1-indexed
		pow[0] = 1;// 0-indexed
		for (int i = 0; i < (int)s.size(); i++) {
			phash[i + 1] = s[i] + phash[i] * p;
			phash[i + 1] %= mod;
			pow[i + 1] = p * pow[i];
			pow[i + 1] %= mod;
		}
	}
	//[0, x)�� Rolling Hash ���v�Z
	ull hash(int i, int j) {
		ull res = (phash[i] * pow[j - i]) % mod;
		return (phash[j] + mod - res) % mod;
	}
	size_t size() {
		return s.size();
	}
};

// Longest Common Prefix(�Œ����ʐړ���)
// rh1�ŊǗ����镶����̃C���f�b�N�Xi��rh2�ŊǗ����镶����̃C���f�b�N�Xj
// ����Œ��ŋ��ʂ��镶����̒����͉������������߂�
int LCP(RollingHash &rh1, int i, RollingHash &rh2, int j) {
	int l = 0, r = min(rh1.size() - i, rh2.size() - j) + 1;
	while (r - l > 1) {
		int m = (l + r) / 2;
		if (rh1.hash(i, i + m) == rh2.hash(j, j + m)) {
			l = m;
		} else {
			r = m;
		}
	}
	int length = l;
	return length;
}

RollingHash rh1, rh2;

void solve() {
	string x = "application";
	rh1.init(x);
	rh1.build();

	string y = "appliance";
	rh2.init(y);
	rh2.build();

	printf("%s\n", x.c_str());
	printf("%s\n", y.c_str());
	int start = 0;
	int lcp = LCP(rh1, start, rh2, start);
	printf("index:%d�����LCP: %d����\n", start, lcp);
	printf("%s\n", x.substr(start, lcp).c_str());
}

int main() {
	solve();
	return 0;
}


