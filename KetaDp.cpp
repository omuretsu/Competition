//ABC007 D - �֎~���ꂽ����
//http://abc007.contest.atcoder.jp/tasks/abc007_4
/*

����DP
0�`N�̐��Ő�����4,9���܂܂�Ȃ������̌��͂������邩�H

e.g: N=1452

N�͕�����Ƃ��čl���A�Y�������L�ɂ悤�ɍl����

index | 3 2 1 0
----------------
  N   | 1 4 5 2

����dp���l����

dp[i][j]: 0�`i��i���ڂ�j�ɂ����Ƃ��́A4,9���܂܂�Ȃ����̌�

�����i���ڂɒ��ڂ��Ă���Ƃ��A�����Ă��鐔��0�`N[i]*10^i + N[i-1]*10^(i-1) + ...N[0]
��4,9���܂܂�Ȃ����̌����l���Ă��邱�Ƃɑ�������

e.g: i=2�̂Ƃ��Aj=0: 000�`099�͈̔͂ő�ӂ𖞂������̌��J�E���g
                j=1: 100�`199�͈̔͂ő�ӂ𖞂������̌��J�E���g
                j=2: 200�`299�͈̔͂ő�ӂ𖞂������̌��J�E���g
                j=3: 300�`399�͈̔͂ő�ӂ𖞂������̌��J�E���g
                j=4: 400�`452�͈̔͂ő�ӂ𖞂������̌��J�E���g(�ʓr�ꍇ�����Ōv�Z)

j���l����Ƃ��A�ꍇ�������K�v

(1) j < N[i]
j�����ڂ��錅���̐�N[i]��菬������Ή��ʂ̈ʂ̐��͉��ł��Ƃ��(0�`9)

    (1-1) j == 4 or j == 9
    j��4,9�ł���΁A�㑱����ʂ̐��͂��ׂđ�ӂ𖞂������ɂȂ�̂�
        dp[i][j] = 10^i
    �����藧��
    e.g i=2�ł����0����(�ŏ��͕֋X��0���ڂƂ���),1���ڂ�0�`9���ł��悢�̂�10^2
	����������

    (1-2) j != 4 and j != 9
    j��4,9�ȊO�ł���΁A�㑱����ʂ̐���4�܂���9�̂����ꂩ���܂܂�Ă��Ȃ���΂Ȃ�Ȃ�
    �����
        �S��(0�`9)�Ŏ��鐔�̌� - (4,9)��1���o�����Ȃ����̌�
    �ŁA�\���ł���̂�
        dp[i][j] = 10^i - 8^i
    ����������

(2) j == N[i]
j�����ڂ��鐔�̌���N[i]�̂Ƃ��́A�㑱����ʂ̐��ɐ������������邽�߁A�ʓr�ɍl����K�v������
e.g N=1452��i=2,j=4�ł���΁A400�ԑ��452�܂łł���A499�܂ł͍l�����Ă��͂����Ȃ�����

    (2-1) j == 4 or j == 9
    j��4,9�ł����N�̌㑱����ʂ̐������̂܂ܑ�ӂ𖞂������ƂȂ�
    �������A�㑱����ʂ̐������ׂ�0�ɂȂ�p�^�[�����l������K�v�����邽��+1����K�v������
    e.g N=1452, i=2, j=4�̂Ƃ��A�㑱����52����ӂ𖞂����p�^�[���ł��邪�A
        �����401�`452���w���Ă���A400���l������R��Ă���B���̂���,400�̕����l�����A
        +1���s��
        ����ɂ����
            dp[i][j] += slice(N, i-1) + 1
        �����藧��(N��i-1����0�܂ł𐔒l������1���Z)

    (2-2) j != 4 and j != 9
    j��4,9�ȊO�̐��ł���΁A�㑱����ʂ̐��ő�ӂ𖞂��������J�E���g����K�v������
    �����1�O�̌���dp�Ōv�Z�ς݂ł��邽�߁A���������Z����΃J�E���g���s����
    e.g 1352, i=2, j=3�̂Ƃ��A300�`352�Ԃɂ����ӂ𖞂������̌���
        i=1,j=0: 00�`09�͈̔͂ő�ӂ𖞂������̌�
        i=1,j=1: 10�`19�͈̔͂ő�ӂ𖞂������̌�
        i=1,j=2: 20�`29�͈̔͂ő�ӂ𖞂������̌�
        i=1,j=3: 30�`39�͈̔͂ő�ӂ𖞂������̌�
        i=1,j=4: 40�`49�͈̔͂ő�ӂ𖞂������̌�
        i=1,j=5: 50�`52�͈̔͂ő�ӂ𖞂������̌�
        �̘a�ł���
    �����
        for (int k = 0; k <= N[i]-'0', k++) dp[i][j] += dp[i - 1][k];
    �����藧��

����dp[N.size()-1][j]�ɏW�񂳂�Ă��邽�߁A���������Z���čŏI�I�ȉ������܂�
e.g N=1452�̏ꍇ�A
    i=N.size()-1,j=0: 0000�`0999�ő�ӂ𖞂������̌�
    i=N-size()-1,j=1: 1000�`1452�ő�ӂ𖞂������̌�
    �ł��������Z

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


