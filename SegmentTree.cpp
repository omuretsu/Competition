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
#define rep(x, to) for (int x = 0; x < (to); x++)
#define REP(x, a, to) for (int x = (a); x < (to); x++)
#define foreach(itr, x) for (typeof((x).begin()) itr = (x).begin(); itr != (x).end(); itr++)

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef pair<long, long> PLL;

//SegmentTree RMQ version
class SegmentTree {
	public:
		int n_;
		int dat_[100005]; //2 * n - 1ˆÈã‚Ì‘å‚«‚³‚ğŠm•Û‚·‚é‚±‚Æ
		void init(int n) {
			n_ = 1;
			while (n_ < n) {
				n_ *= 2;
			}
			for (int i = 0; i < 2 * n_ - 1; i++) {
				dat_[i] = (int)(1e+9 + 7);
			}
		}
		void update(int i, int value) {
			i += n_ - 1;
			dat_[i] = value;
			while (i > 0) {
				i = (i - 1) / 2;
				int chl = 2 * i + 1;
				int chr = 2 * i + 2;
				dat_[i] = min(dat_[chl], dat_[chr]);
			}
		}
		//[a, b) node-k [l, r)
		int query(int a, int b, int k, int l, int r) {
			if (a <= l && r <= b) return dat_[k];
			if (b <= l || r <= a) return (int)(1e+9 + 7);
			int chl = 2 * k + 1;
			int chr = 2 * k + 2;
			return min(query(a, b, chl, l, (l + r)/2), query(a, b, chr, (l + r)/2, r));
		}
};

int main() {
	int x[] = {4, 2, 19, 24, 11, -1, 100, 32};
	int size = sizeof(x) / sizeof(x[0]);

	SegmentTree seg;
	seg.init(size);

	rep(i, size) {
		seg.update(i, x[i]);
	}

	rep(i, 2 * seg.n_ - 1) {
		printf("%2d: %d\n", i, seg.dat_[i]);
	}

	rep(i, size) {
		rep(j, size + 1) {
			printf("[%d,%d) %d\n", i, j, seg.query(i, j, 0, 0, size));
		}
	}

	return 0;
}


