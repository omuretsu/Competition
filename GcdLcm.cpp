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

// �T�v�@�F�Q�̐��̍ő���񐔂����߂�
// �����P�F���߂�Ώې��P
// �����Q�F���߂�Ώې��Q
// �߂�l�F�����P�ƈ����Q�̍ő����
ll gcd(ll a, ll b) {
	if (b == 0LL) return a;
	else return gcd(b, a % b);
}

// �T�v�@�F�Q�̐��̍ŏ����{�������߂�
// �����P�F���߂�Ώې��P
// �����Q�F���߂�Ώې��Q
// �߂�l�F�����P�ƈ����Q�̍ŏ����{��
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


