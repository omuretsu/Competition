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
	//[0, x)‚Ì Rolling Hash ‚ðŒvŽZ
	ull hash(int i, int j) {
		ull res = (phash[i] * pow[j - i]) % mod;
		return (phash[j] + mod - res) % mod;
	}
	size_t size() {
		return s.size();
	}
};

RollingHash rh;

void solve() {
	string x = "hi";
	rh.init(x, 101);
	rh.build();
	for (int i = 0; i < rh.size(); i++) {
		cout << i << ": " << rh.phash[i + 1] << endl;
	}
	cout << "---" << endl;
	for (int i = 0; i < rh.size(); i++) {
		cout << i << ": " << rh.pow[i + 1] << endl;
	}
	for (int i = 0; i < rh.size(); i++) {
		cout << i << ": " << rh.hash(0, i+1) << endl;
	}
}

int main() {
	solve();
	return 0;
}


