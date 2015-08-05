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
 * ���[�N���b�h�̌ݏ��@
 *
 *
 * a��b�Ŋ������Ƃ��̏���p,���܂��r�Ƃ���
 * ���̂Ƃ�gcd(a,b)=gcd(b,r)
 *
 * <�ؖ�>
 *
 * gcd(a, b) = G1
 * gcd(b, r) = G2
 *
 * �Ƃ���
 * �ő���񐔂Ȃ̂�
 * a = G1A
 * b = G1B
 * �Ə�����
 *
 * a,b,p,r�̊֌W���
 * a = bp + r
 * r = bp - a
 *   = G1Bp - G1A
 *   = (Bp - A)G1
 * �Ə�����̂ŁAG1��r�̖񐔂ɂȂ�
 * G1��b�̖񐔂ł�����̂ŁAG1��r,b�̌��񐔂ł���
 * b,r�̍ő���񐔂�G2���ȉ������藧��
 * G1 <= G2 ----(1)
 *
 * G2��b,r�̍ő���񐔂Ȃ̂�
 * b = G2E
 * r = G2F
 * �Ə�����
 *
 * a = bp + r
 * a = G2Ep + G2F
 *   = (Ep + F)G2
 * �Ə�����̂�G2��a�̖񐔂ɂȂ�
 * G2��b�̖񐔂ł�����̂ŁAG2��a,b�̌��񐔂ɂȂ�
 *
 * G1��a,b�̍ő���񐔂Ȃ̂ŁAG1��G2�̊֌W��
 * G2 <= G1 ----(2)
 *
 * (1)��G1 <= G2
 * (2)��G2 <= G1
 * ���A���ꂪ�����ɐ��藧�̂�
 *
 * G1 = G2
 *
 */

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


