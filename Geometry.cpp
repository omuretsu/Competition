// poj 1127
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
	double add(double a, double b) { // 誤差を考慮して加算
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
// 概要　：線分s1-e1と線分s2-e2が交差しているか判定する(線分はベクトル扱い)
// 引数１：ベクトル1の始点
// 引数２：ベクトル1の終点
// 引数３：ベクトル2の始点
// 引数４：ベクトル2の終点
// 戻り値：true  ベクトル1とベクトル2は交差している
// 　　　　false ベクトル1とベクトル2は交差していない
bool intersect(P s1, P e1, P s2, P e2) { // 線分交差
	//x座標的に離れて位置している
	if (max(s1.x, e1.x) < min(s2.x, e2.x) || max(s2.x, e2.x) < min(s1.x, e1.x)) return false;
	//y座標的に離れて位置している
	if (max(s1.y, e1.y) < min(s2.y, e2.y) || max(s2.y, e2.y) < min(s1.y, e1.y)) return false;
	//交差している
	double res1 = (e1 - s1).cross(s2 - s1) * (e1 - s1).cross(e2 - s1);
	double res2 = (e2 - s2).cross(e1 - s2) * (e2 - s2).cross(s1 - s2);
	return (res1 < EPS) && (res2 < EPS);
}
// 概要　：線分上にp1-p2上に点qが存在するか判定する
// 引数１：線分の端点１(p1)
// 引数２：線分の端点２(p2)
// 引数３：判定対象の点(q)
// 戻り値：true  線分上に点qが存在する
// 　　　　false 線分上に点qが存在しない
bool on_seg(P p1, P p2, P q) { // 線分p1-p2上にある点qがあるか判定
	return (p1 - q).cross(p2 - q) == 0 && (p1 - q).dot(p2 - q) <= 0;
}

const int MAX_V = 100005;

struct UnionFind {
	int n;
	int parent[MAX_V];
	UnionFind(int size) {
		n = size;
		for (int i = 0; i < n; i++) {
			parent[i] = i;
		}
	}
	int find(int i) {
		if (i == parent[i]) return i;
		else return parent[i] = find(parent[i]);
	}
	void unite(int x, int y) {
		int a = find(x);
		int b = find(y);
		if (a == b) return;
		else {
			parent[a] = b;
		}
	}
	bool is_same(int x, int y) {
		return find(x) == find(y);
	}
};

int N;
P p[15], q[15];

int main() {
	while (cin >> N, N) {
		rep(i, N) {
			cin >> p[i].x >> p[i].y >> q[i].x >> q[i].y;
		}
		UnionFind uf(15);
		REP(i, 0, N) {
			P vec1 = p[i] - q[i];//.(p[i].x - q[i].x, p[i].y - q[i].y);
			REP(j, i+1, N) {
				P vec2 = p[j] - q[j]; //(p[j].x - q[j].x, p[j].x - q[j].y);
#if 0
				// 平行である
				if (vec1.cross(vec2) == 0) {
					if (on_seg(p[i], q[i], p[j]) ||
							on_seg(p[i], q[i], q[j]) ||
							on_seg(p[j], q[j], p[i]) ||
							on_seg(p[j], q[j], q[i])) {
							uf.unite(i, j);
					}
				}
				// 平行でない
				// 交差だけではだめな理由：
				// --- ---
				// 上記のように直線上にあって、線分の交差がないものも
				// intersect = 0となって交差判定されてしまうため
				// 防ぐために、平行の判定を事前に入れる
				else {
					if (intersect(p[i], q[i], p[j], q[j])) {
						uf.unite(i, j);
					}
				}
#else
				if (intersect(p[i], q[i], p[j], q[j])) {
					uf.unite(i, j);
				}
			}
		}
#endif
		int a, b;
		while (cin >> a >> b, a|b) {
			a--; b--;
			if (uf.is_same(a, b)) {
				printf("CONNECTED\n");
			} else {
				printf("NOT CONNECTED\n");
			}
		}

	}
	return 0;
}
