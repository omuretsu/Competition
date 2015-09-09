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


const int MAX_V = 1005;

vector<int> G[MAX_V];
int vs[MAX_V * 2 - 1];

//
// 概要：オイラーツアー
// 　　：木に対して、訪問した順に頂点を列挙する
// 引数1：現在の頂点
// 引数2：一個前の頂点
// 引数3：訪問した頂点の個数(0-indexed)
//
void euler_tour(int u, int p, int &k) {
	vs[k++] = u;
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v == p) continue;
		euler_tour(v, u, k);
		vs[k++] = u;
	}
}

int main() {
	G[1].push_back(2);
	G[2].push_back(1);
	G[1].push_back(3);
	G[3].push_back(1);
	G[3].push_back(6);
	G[6].push_back(3);
	G[2].push_back(4);
	G[4].push_back(2);
	G[2].push_back(5);
	G[5].push_back(2);
	G[5].push_back(7);
	G[7].push_back(5);
	G[5].push_back(8);
	G[8].push_back(5);
	int k = 0;
	euler_tour(1, -1, k);


	for (int i = 0; i < k; i++) {
		cout << vs[i] << " ";
	} cout << endl;

	return 0;
}


