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

ll inv(ll x) {
	return powmod(x, MOD-2, MOD);
}

ll getmod(ll x) {
	return ((x % MOD) + MOD) % MOD;
}

int main() {
	return 0;
}


