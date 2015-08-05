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

/*
 * ユークリッドの互除法
 *
 *
 * aをbで割ったときの商をp,あまりをrとする
 * このときgcd(a,b)=gcd(b,r)
 *
 * <証明>
 *
 * gcd(a, b) = G1
 * gcd(b, r) = G2
 *
 * とする
 * 最大公約数なので
 * a = G1A
 * b = G1B
 * と書ける
 *
 * a,b,p,rの関係より
 * a = bp + r
 * r = bp - a
 *   = G1Bp - G1A
 *   = (Bp - A)G1
 * と書けるので、G1はrの約数になる
 * G1はbの約数でもあるので、G1はr,bの公約数である
 * b,rの最大公約数はG2より以下が成り立つ
 * G1 <= G2 ----(1)
 *
 * G2はb,rの最大公約数なので
 * b = G2E
 * r = G2F
 * と書ける
 *
 * a = bp + r
 * a = G2Ep + G2F
 *   = (Ep + F)G2
 * と書けるのでG2はaの約数になる
 * G2はbの約数でもあるので、G2はa,bの公約数になる
 *
 * G1はa,bの最大公約数なので、G1とG2の関係は
 * G2 <= G1 ----(2)
 *
 * (1)のG1 <= G2
 * (2)のG2 <= G1
 * より、これが同時に成り立つのは
 *
 * G1 = G2
 *
 */

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


