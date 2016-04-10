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

namespace SuffixArray {

	const int MAX_N = 1000005;

	int n;           //       n: 文字列のサイズ
	int k;           //       k: ダブリング用
	int rank[MAX_N]; // rank[i]: 先頭index iの接尾辞の順位
	int sa[MAX_N];   //   sa[i]: 順位iの接尾辞の先頭index
	int tmp[MAX_N];  //  tmp[i]: 作業用
	int lcp[MAX_N];  //  lcp[i]: 順位iの接尾辞と順位i+1の接尾辞のlcp(最長共通接頭辞)

	string t;

	bool compare_sa(int i, int j) {
		if (rank[i] != rank[j]) {
			return rank[i] < rank[j];
		} else {
			int ri = i + k <= n ? rank[i + k] : -1;
			int rj = j + k <= n ? rank[j + k] : -1;
			return ri < rj;
		}
	}

	void build_sa(string s) {
		t  = s;
		n = s.size();
		for (int i = 0; i <= s.size(); i++) {
			sa[i] = i;
			rank[i] = i < n ? s[i] : -1;
		}
		for (k = 1; k <= n; k *= 2) {
			sort(sa, sa + n + 1, compare_sa);
			tmp[sa[0]] = 0;
			for (int i = 1; i <= n; i++) {
				tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
			}
			for (int i = 0; i <= n; i++) {
				rank[i] = tmp[i];
			}
		}
	}

	// build_sa後に呼び出すること
	void build_lcp() {
		for (int i = 0; i <= n; i++) {
			rank[sa[i]] = i;
		}

		int h = 0;
		lcp[0] = 0;
		for (int i = 0; i < n; i++) {
			// rank[i]=0となるのはi=nだけどi<nなので問題なし
			int j = sa[rank[i] - 1];

			if (h > 0) h--;
			for (; j + h < n && i + h < n; h++) {
				if (t[j + h] != t[i + h]) break;
			}

			lcp[rank[i] - 1] = h;
		}

	}
}


int main() {
	string x = "abracadabra";
	SuffixArray::build_sa(x);
	SuffixArray::build_lcp();

	for (int i = 0; i <= SuffixArray::n; i++) {
		printf(
				"i:%3d sa:%3d lcp:%3d %s\n",
				i,
				SuffixArray::sa[i],
				SuffixArray::lcp[i],
				x.substr(SuffixArray::sa[i]).c_str()
		);
	}
	return 0;
}


