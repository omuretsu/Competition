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
#define rep(x, to) for (int x = 0; x < (to); x++)
#define REP(x, a, to) for (int x = (a); x < (to); x++)
#define foreach(itr, x) for (typeof((x).begin()) itr = (x).begin(); itr != (x).end(); itr++)

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef pair<long, long> PLL;

const ll MOD =(ll)(1e+9+7);

// aのp乗を求める
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

// xの逆元を求める(法はMOD=1e+9 + 7とする)
ll inv(ll x) {
	return powmod(x, MOD-2, MOD);
}

// xのmodを求める(法はMOD=1e+9 + 7とする)
ll getmod(ll x) {
	return ((x % MOD) + MOD) % MOD;
}


// 拡張ユークリッドの互除法
// ax + by = gcd(a,b)を満たすx,yを求める
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

// mを法とするaの逆元を求める
ll mod_inverse(ll a, ll m) {
	ll x, y;
	exgcd(a, m, x, y);
	return (m + x % m) % m;
}

int main() {
	ll a = 1124;
	ll b = 84;
	ll x, y;
	ll d = exgcd(a, b, x, y);
	printf("x = %lld\n", x);
	printf("y = %lld\n", y);
	printf("d = %lld\n", d);

	printf("mod_inverse\n");
	a = 24;
	b = 13;
	x = mod_inverse(a, b);
	printf("x = %lld\n", x);

	return 0;
}


