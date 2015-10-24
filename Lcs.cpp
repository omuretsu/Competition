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

const int INF = 1e+9 + 7;
const int MAX_N = 30005;

int N;
int C[MAX_N];
int dp[MAX_N];

// Å’·‘‰Á•”•ª—ñ
// dp: ’·‚³‚ªi+1‚Å‚ ‚é‚æ‚¤‚È‘‰Á•”•ª—ñ‚É‚¨‚¯‚éÅI—v‘f‚ÌÅ¬’l(‘¶İ‚µ‚È‚¢ê‡‚ÍINF)
void lcs() {
	fill(dp, dp + MAX_N, INF);
	for (int i = 0; i < N; i++) {
		*lower_bound(dp, dp + N, C[i]) = C[i];
	}
	int mx = lower_bound(dp, dp + N, INF) - dp;
	cout << mx << endl;
}

int main() {
	N = 5;
	C[0] = 4;
	C[1] = 2;
	C[2] = 3;
	C[3] = 1;
	C[4] = 5;
	lcs();
	return 0;
}


