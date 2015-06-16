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
typedef pair<long, long> PLL;
typedef complex<double> Complex;
typedef vector< vector<int> > Mat;

// �T�v  : �G���g�X�e�l�X��⿂őf�������߂�
// ����1 : ���ʂ��i�[����z��(1:�f���ł���/0:�f���łȂ�)
// ����2 : �z��̃T�C�Y
// �Ԃ�l: �Ȃ�
void sieve_of_eratosthenes(int *a, int n) {
	fill(a, a+n, 1);
	a[0] = a[1] = 0;
	for (int i = 2; i * i < n; i++) {
		if (a[i] == 0) continue;
		for (int j = i + i; j < n; j += i) {
			a[j] = 0;
		}
	}
}

int n;
int prime[100005];

int main() {
	cin >> n;
	sieve_of_eratosthenes(prime, 100005);
	for (int i = max(3, n - 100); i <= n + 100; i++) {
		if (prime[i]) continue;
		cout << i << endl;
		break;
	}
	return 0;
}


