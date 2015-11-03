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

//
// �傫���Ȃ肻���ȑg�ݍ��킹�������߂�
// double�Ōv�Z����̂Ō덷������\����
// pCq = p!/((p-q)!q!)
// log(pCq) = log(p!) - (log((p-q)!) + log(q!))
// pCq = exp(log(pCq))
// ��pCq�����߂�
//
struct LogCombination {
	double log_fact[10005];
	LogCombination(int size) {
		for (int i = 1; i <= size; i++) {
			log_fact[i] = log(i) + log_fact[i-1];
		}
		log_fact[0] = log(1);
	}
	double log_pCq(int p, int q) {
		double x = log_fact[p] - (log_fact[q] + log_fact[p - q]);
		return x;
	}
	double pCq(int p, int q) {
		double x = log_pCq(p, q);
		return exp(x);
	}
};

LogCombination comb(1005);


// �T�v  �F�g�ݍ��킹�����߂�,mod�Ȃ���C[100][?]���炢��Overflow����H
// ����1 �F�g�ݍ��킹�Ώۂ̗v�f��
// �Ԃ�l�F�Ȃ�
ll C[1005][1005];
void combination(int size) {
	for (int i = 0; i < size; i++) C[i][0] = 1LL;
	for (int i = 1; i < size; i++) {
		for (int j = 1; j <= i; j++) {
			C[i][j] = (C[i-1][j-1] + C[i-1][j]) % (ll)(1e+9 + 7);
		}
	}
}


ll N, K;
int main() {
#if 0
	combination(1005);

	rep(i, 10) rep(j, 10) {
		printf("%lld%c", C[i][j], j == 9 ? '\n' : ' ');
	}
#else
	cout << comb.pCq(5, 2) << endl;
#endif
	return 0;
}


