// ABC26 D
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

int a, b, c;

double f(double t) {
	return a * t + b * sin(c * t * M_PI);
}

// 概要：中間値の定理
// 　　：関数fの連続性を利用してf(p)=xとなるpを求める
double intermediate_value_theorem(int x) {
	double mn = 0;
	double mx = 300;
	rep(i, 100) {
		double mid = (mx + mn) / 2;
		if (f(mid) < x) {
			mn = mid;
		} else {
			mx = mid;
		}
	}
	return mn;
}

int main() {
	cin >> a >> b >> c;
	printf("%.12f\n", intermediate_value_theorem(100));
	return 0;
}


