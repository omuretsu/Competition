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


int N, K;
vector<int> a;
int x[105];

// 今の状態から一手でいける状態のGrundy数に含まれていない最小の非負整数が、
// 今の状態のGrundy数
// grundy(x1) xor grundy(x2) xor grundy(x3) ...
// 0 -> 負け
// 0以外 -> 勝ち

int grundy[105];
int grundy_number(int x, vector<int> &a) {
	if (grundy[x] != -1) return grundy[x];
	set<int> S;
	for (int i = 0; i < a.size(); i++) {
		if (x - a[i] >= 0) {
			S.insert(grundy_number(x - a[i], a));
		}
	}
	int res = 0;
	foreach(itr, S) {
		if (res != *itr) break;
		res++;
	}
	return grundy[x] = res;
}

void solve() {
	memset(grundy, -1, sizeof(grundy));
	grundy[0] = 0;//負け
	int res = 0;
	for (int i = 0; i < N; i++) {
		int tmp = grundy_number(x[i], a);
		cout << x[i] << " " << tmp << endl;
		res ^= tmp;
	}
	if (res == 0) {
		cout << "Bob" << endl;
	} else {
		cout << "Alice" << endl;
	}
}


int main() {
	cin >> N >> K;
	rep(i, K) {
		int tmp;
		cin >> tmp;
		a.push_back(tmp);
	}
	rep(i, N) cin >> x[i];
	solve();
	return 0;
}


