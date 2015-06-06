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
	double add(double a, double b) { // �덷���l�����ĉ��Z
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
	double dot(P p) { // ����
		return add(x * p.x, y * p.y);
	}
	double cross(P p) { // �O��
		return add(x * p.y, -y * p.x);
	}
};
// �T�v�@�F����s1-e1�Ɛ���s2-e2���������Ă��邩���肷��(�����̓x�N�g������)
// �����P�F�x�N�g��1�̎n�_
// �����Q�F�x�N�g��1�̏I�_
// �����R�F�x�N�g��2�̎n�_
// �����S�F�x�N�g��2�̏I�_
// �߂�l�Ftrue  �x�N�g��1�ƃx�N�g��2�͌������Ă���
// �@�@�@�@false �x�N�g��1�ƃx�N�g��2�͌������Ă��Ȃ�
bool intersect(P s1, P e1, P s2, P e2) { // ��������
	//x���W�I�ɗ���Ĉʒu���Ă���
	if (max(s1.x, e1.x) < min(s2.x, e2.x) || max(s2.x, e2.x) < min(s1.x, e1.x)) return false;
	//y���W�I�ɗ���Ĉʒu���Ă���
	if (max(s1.y, e1.y) < min(s2.y, e2.y) || max(s2.y, e2.y) < min(s1.y, e1.y)) return false;
	//�������Ă���
	double res1 = (e1 - s1).cross(s2 - s1) * (e1 - s1).cross(e2 - s1);
	double res2 = (e2 - s2).cross(e1 - s2) * (e2 - s2).cross(s1 - s2);
	return (res1 < EPS) && (res2 < EPS);
}
// �T�v�@�F�������p1-p2��ɓ_q�����݂��邩���肷��
// �����P�F�����̒[�_�P(p1)
// �����Q�F�����̒[�_�Q(p2)
// �����R�F����Ώۂ̓_(q)
// �߂�l�Ftrue  ������ɓ_q�����݂���
// �@�@�@�@false ������ɓ_q�����݂��Ȃ�
bool on_seg(P p1, P p2, P q) { // ����p1-p2��ɂ���_q�����邩����
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
				// ���s�ł���
				if (vec1.cross(vec2) == 0) {
					if (on_seg(p[i], q[i], p[j]) ||
							on_seg(p[i], q[i], q[j]) ||
							on_seg(p[j], q[j], p[i]) ||
							on_seg(p[j], q[j], q[i])) {
							uf.unite(i, j);
					}
				}
				// ���s�łȂ�
				// ���������ł͂��߂ȗ��R�F
				// --- ---
				// ��L�̂悤�ɒ�����ɂ����āA�����̌������Ȃ����̂�
				// intersect = 0�ƂȂ��Č������肳��Ă��܂�����
				// �h�����߂ɁA���s�̔�������O�ɓ����
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
