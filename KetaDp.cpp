//ABC007 D - 禁止された数字
//http://abc007.contest.atcoder.jp/tasks/abc007_4
/*

■桁DP
0～Nの数で数字に4,9が含まれない数字の個数はいくつあるか？

e.g: N=1452

Nは文字列として考え、添え字下記にように考える

index | 3 2 1 0
----------------
  N   | 1 4 5 2

次のdpを考える

dp[i][j]: 0～iでi桁目を数jにしたときの、4,9が含まれない数の個数

これはi桁目に着目しているとき、数えている数は0～N[i]*10^i + N[i-1]*10^(i-1) + ...N[0]
で4,9が含まれない数の個数を考えていることに相当する

e.g: i=2のとき、j=0: 000～099の範囲で題意を満たす数の個数カウント
                j=1: 100～199の範囲で題意を満たす数の個数カウント
                j=2: 200～299の範囲で題意を満たす数の個数カウント
                j=3: 300～399の範囲で題意を満たす数の個数カウント
                j=4: 400～452の範囲で題意を満たす数の個数カウント(別途場合分けで計算)

jを考えるとき、場合分けが必要

(1) j < N[i]
jが着目する桁数の数N[i]より小さければ下位の位の数は何でもとれる(0～9)

    (1-1) j == 4 or j == 9
    jが4,9であれば、後続する位の数はすべて題意を満たす数になるので
        dp[i][j] = 10^i
    が成り立つ
    e.g i=2であれば0桁目(最初は便宜上0桁目とする),1桁目は0～9何でもよいので10^2
	が成立する

    (1-2) j != 4 and j != 9
    jが4,9以外であれば、後続する位の数に4または9のいずれかが含まれていなければならない
    これは
        全体(0～9)で取れる数の個数 - (4,9)が1個も出現しない数の個数
    で、表現できるので
        dp[i][j] = 10^i - 8^i
    が成立する

(2) j == N[i]
jが着目する数の桁数N[i]のときは、後続する位の数に制限が発生するため、別途に考える必要がある
e.g N=1452でi=2,j=4であれば、400番台は452までであり、499までは考慮していはいけないため

    (2-1) j == 4 or j == 9
    jが4,9であればNの後続する位の数がそのまま題意を満たす個数となる
    だたし、後続する位の数がすべて0になるパターンも考慮する必要があるため+1する必要がある
    e.g N=1452, i=2, j=4のとき、後続する52個が題意を満たすパターンであるが、
        これは401～452を指しており、400が考慮から漏れている。そのため,400の分を考慮し、
        +1を行う
        これによって
            dp[i][j] += slice(N, i-1) + 1
        が成り立つ(Nのi-1から0までを数値化して1加算)

    (2-2) j != 4 and j != 9
    jが4,9以外の数であれば、後続する位の数で題意を満たす個数をカウントする必要がある
    これは1つ前の桁のdpで計算済みであるため、これらを加算すればカウントが行える
    e.g 1352, i=2, j=3のとき、300～352間にある題意を満たす数の個数は
        i=1,j=0: 00～09の範囲で題意を満たす数の個数
        i=1,j=1: 10～19の範囲で題意を満たす数の個数
        i=1,j=2: 20～29の範囲で題意を満たす数の個数
        i=1,j=3: 30～39の範囲で題意を満たす数の個数
        i=1,j=4: 40～49の範囲で題意を満たす数の個数
        i=1,j=5: 50～52の範囲で題意を満たす数の個数
        の和である
    よって
        for (int k = 0; k <= N[i]-'0', k++) dp[i][j] += dp[i - 1][k];
    が成り立つ

解はdp[N.size()-1][j]に集約されているため、これらを加算して最終的な解が求まる
e.g N=1452の場合、
    i=N.size()-1,j=0: 0000～0999で題意を満たす数の個数
    i=N-size()-1,j=1: 1000～1452で題意を満たす数の個数
    でこれらを加算

*/


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

ll A, B;
ll dp[30][15];
ll p8[25], p10[25];

ll slice(string s, int i) {
	ll res = 0;
	while (i >= 0) {
		res = 10 * res + (s[i] - '0');
		i--;
	}
	return res;
}

ll calc(string s) {
	memset(dp, 0, sizeof(dp));
	ll res = 0;
	reverse(s.begin(), s.end());
	for (int i = 0; i < s.size(); i++) {
		int x = s[i] - '0';
		for (int j = 0; j < x; j++) {
			if (j == 4 || j == 9) {
				dp[i][j] = p10[i];
			} else {
				dp[i][j] = p10[i] - p8[i];
			}
		}
		if (x == 4 || x == 9) {
			dp[i][x] = slice(s, i - 1) + 1;
		} else {
			for (int k = 0; i - 1 >= 0 && k < 10; k++) dp[i][x] += dp[i - 1][k];
		}
	}
	for (int i = 0; i < 10; i++) res += dp[s.size() - 1][i];
	return res;
}

string str(ll x) {
	string res = "";
	while (x != 0) {
		char c = x % 10 + '0';
		res = c + res;
		x /= 10;
	}
	if (res.size() == 0) res = "0";
	return res;
}

void init() {
	p8[0] = p10[0] = 1;
	rep(i, 20) {
		p8[i + 1] = 8 * p8[i];
		p10[i + 1] = 10 * p10[i];
	}
}

void solve() {
	init();
	cout << calc(str(B)) - calc(str(A-1)) << endl;
}

int main() {
	cin >> A >> B;
	solve();
	return 0;
}


