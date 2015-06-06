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
typedef pair<long, long> PLL;

struct P {
	double x, y;
	P() : x(0), y(0) {}
	P(double x, double y) : x(x), y(y) {};
	// 誤差を考慮して加算
	double add(double a, double b) {
		if (abs(a + b) < EPS * (abs(a) + abs(b))) return 0;
		return a + b;
	}
	P operator+(P p) {
		return P(add(x, p.x), add(y, p.y));
	}
	P operator-(P p) {
		return P(add(x, -p.x), add(y, -p.y));
	}
	P operator*(double d) {
		return P(x * d, y * d);
	}
	double dot(P p) { // 内積
		return add(x * p.x, y * p.y);
	}
	double cross(P p) { // 外積
		return add(x * p.y, -y * p.x);
	}
};

int N;
P ps[50005];

// 概要　：グラハムスキャンで多角形の外周頂点を求める
// 引数１：頂点の配列
// 引数２：頂点の配列のサイズ
// 戻り値：外周の頂点リスト
bool cmp_x(const P &s, const P &t) {
	if (s.x != t.x) return s.x < t.x;
	return s.y < t.y;
}
vector<P> convex_hull(P *ps, int n) {
	sort(ps, ps + n, cmp_x);
	int k = 0;
	vector<P> qs(n * 2);
	for (int i = 0; i < n; i++) {
		while (k > 1 && (qs[k-1] - qs[k-2]).cross(ps[i] - qs[k-1]) <= 0) k--;
		qs[k++] = ps[i];
	}
	for (int i = n - 2, t = k; i >= 0; i--) {
		while (k > t && (qs[k-1] - qs[k-2]).cross(ps[i] - qs[k-1]) <= 0) k--;
		qs[k++] = ps[i];
	}
	qs.resize(k-1);
	return qs;
}

double dist(P s, P t) {
	return (s - t).dot(s - t);
}

int main() {
	scanf("%d", &N);
	int x, y;
	rep(i, N) {
		scanf("%lf %lf", &ps[i].x, &ps[i].y);
	}
	vector<P> qs = convex_hull(ps, N);
	double res = 0;
	for (int i = 0; i < qs.size(); i++) {
		for (int j = 0; j < i; j++) {
			res = max(res, dist(qs[i], qs[j]));
		}
	}
	printf("%.0f\n", res);
	return 0;
}

