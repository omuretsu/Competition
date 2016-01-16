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

// Longest Common Prefix (DP”Å)
// Å’·‹¤’ÊÚ“ªŽ«
// lcp[i][j]‚Å•¶Žš—ñs‚Ìi•¶Žš–Ú`‚Æ•¶Žš—ñt‚Ìj•¶Žš–Ú`
// ‚ÅÅ’·‚Ì‹¤’Ê•¶Žš—ñ‚Ì’·‚³‚Í‰½•¶Žš‚©‚ð•ÛŽ
int lcp[5005][5005];
void LCP(string &s, string &t) {
	for (int i = (int)s.size() - 1; i >= 0; i--) {
		for (int j = (int)t.size() - 1; j >= 0; j--) {
			if (s[i] == t[j]) {
				lcp[i][j] = lcp[i+1][j+1] + 1;
			} else {
				lcp[i][j] = 0;
			}
		}
	}
}

// Longest Common Preffix (Rolling Hash”Å)
// RollingHash.cpp ‚É‚ ‚è

int main() {
	string s = "abcca";
	string t = "tabcabcs";
	LCP(s, t);
	rep(i, s.size()) {
		rep(j, t.size()) {
			printf("lcp[%d][%d]=%d %s => %s\n", i, j, lcp[i][j], s.c_str(), s.substr(i, lcp[i][j]).c_str());
			printf("lcp[%d][%d]=%d %s => %s\n", i, j, lcp[i][j], t.c_str(), t.substr(j, lcp[i][j]).c_str());
		}
	}
	return 0;
}


