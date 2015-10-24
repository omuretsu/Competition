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

ll gcd(ll a, ll b) {
	if (b == 0LL) return a;
	else return gcd(b, a % b);
}

ll lcm(ll a, ll b) {
	return a * b / gcd(a, b);
}

// •ïœŒ´—‚Ì—á
// 1`n‚Ì®”‚ÅA­‚È‚­‚Æ‚àa‚Ì—v‘f‚Ì‚Ç‚ê‚©‚ÅŠ„‚èØ‚ê‚é‚à‚Ì‚ÌŒÂ”
ll inclusion_exclusion(ll n, vector<int> &a) {
	ll res = 0;
	int m = a.size();
	for (int i = 1; i < (1 << m); i++) {
		int num = 0;
		for (int j = i; j != 0; j >>= 1) num += (j & 1);
		ll lc = 1;
		for (int j = 0; j < m; j++) {
			if (i & (1<<j)) {
				lc = lcm(lc, a[j]);
			}
		}
		if (num % 2 == 0) {
			res -= n / lc;
		} else {
			res += n / lc;
		}
	}
	return res;
}

int main() {
	ll n = 100;
	vector<int> a;
	a.push_back(2);
	a.push_back(3);
	a.push_back(7);
	ll ans = inclusion_exclusion(n, a);
	cout << ans << endl;
}


