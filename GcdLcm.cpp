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
#define rep(x, to) for (int x = 0; x < (to); x++)
#define REP(x, a, to) for (int x = (a); x < (to); x++)
#define foreach(itr, x) for (typeof((x).begin()) itr = (x).begin(); itr != (x).end(); itr++)

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef pair<long, long> PLL;

// 概要　：２つの数の最大公約数を求める
// 引数１：求める対象数１
// 引数２：求める対象数２
// 戻り値：引数１と引数２の最大公約数
ll gcd(ll a, ll b) {
	if (b == 0LL) return a;
	else return gcd(b, a % b);
}

// 概要　：２つの数の最小公倍数を求める
// 引数１：求める対象数１
// 引数２：求める対象数２
// 戻り値：引数１と引数２の最小公倍数
ll lcm(ll a, ll b) {
	return a * b / gcd(a, b);
}

int main() {

	cout << gcd(25, 15) << endl;
	cout << gcd(15, 25) << endl;
	cout << lcm(10, 15) << endl;
	cout << lcm(15, 10) << endl;

	return 0;
}


