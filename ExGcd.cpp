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

int main() {
	ll a = 1124;
	ll b = 84;
	ll x, y;
	ll d = exgcd(a, b, x, y);
	printf("x = %lld\n", x);
	printf("y = %lld\n", y);
	printf("d = %lld\n", d);
	return 0;
}


