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


// �T�v  �F�g�ݍ��킹�����߂�
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
	combination(1005);

	rep(i, 10) rep(j, 10) {
		printf("%lld%c", C[i][j], j == 9 ? '\n' : ' ');
	}

	cin >> N >> K;
	if (K >= N) {
		cout << C[N][K%N] << endl;
	} else {
		cout << C[N+K-1][K] << endl;
	}
	return 0;
}


