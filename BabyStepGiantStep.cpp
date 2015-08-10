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

ll exgcd(ll a, ll b, ll &x, ll &y) {
	ll d = a;
	if (b != 0) {
		d = exgcd(b, a % b, y, x);
	y -= (a / b) * x;
	} else {
		x = 1;
		y = 0;
	}
	return d;
}

ll powmod(ll a, ll p, ll mod) {
	ll res = 1;
	while (p > 0) {
		if (p & 1) {
			res *= a;
			res %= mod;
		}
		a *= a;
		a %= mod;
		p >>= 1;
	}
	return res;
}

// baby step giant step
// h �� g^x (mod p)
// �ƂȂ�悤��x��x=mq+r�ƒu����(m=sqrt(p)+1�Ƃ���)
// h �� g^(mq+r) (mod p)
// h �� g^(mq)g^(r) (mod p)
// h (g^(-m))^(q) �� g^(r) (mod p)
// �ō����Ɍv�Z����
ll baby_step_giant_step(ll h, ll g, ll p) {
	set<PLL> G;
	ll m = sqrt(p) + 1;
	for (ll r = 0, v = 1; r < m; r++) {
		G.insert(PLL(v, r));
		v *= g;
		v %= p;
	}
	ll x = 0, y = 0;
	exgcd(powmod(g, m, p), p, x, y); // g^m�̋t�����߂�(x�ɓ���)
	ll ig = (x + p) % p;
	ll res = -1;
	for (ll q = 0, v = h; q < m; q++) {
		set<PLL>::iterator itr = G.lower_bound(PLL(v, 0));
		if (itr != G.end() && itr->first == v) {
			res = itr -> second + m * q;
			break;
		}
		v *= ig;
		v %= p;
	}
	return res;
}

int main() {
	ll p = 31;
	ll g = 3;
	ll h = 6;
	ll x = baby_step_giant_step(h, g, p);
	cout << x << endl;
	return 0;
}


