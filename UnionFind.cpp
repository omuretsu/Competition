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
#define rep(x, to) for (int x = 0; x < (to); x++)
#define REP(x, a, to) for (int x = (a); x < (to); x++)
#define foreach(itr, x) for (typeof((x).begin()) itr = (x).begin(); itr != (x).end(); itr++)

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef pair<long, long> PLL;

const int MAX_V = 100005;

struct UnionFind {

	int n;
	int parent[MAX_V];

	void init(int m) {
		n = m;
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

int main() {
	UnionFind uf;
	uf.init(5);
	uf.unite(2, 4);
	rep(i, 5) {
		rep(j, 5) {
			printf("%d %d -> %d\n", i, j, uf.find(i) == uf.find(j));
		}
	}
	return 0;
}


