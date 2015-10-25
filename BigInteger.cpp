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


struct BigInteger {

	string value;

	BigInteger(ll x) {
		value = to_string(x);
	}

	BigInteger(string x) {
		value = x;
	}

	// ”’l¨•¶š—ñ‚É•ÏŠ·
	string to_string(ll x) {
		string res = "";
		bool minus = x < 0;
		x = abs(x);
		do {
			char v  = '0' + (x % 10);
			res += v;
			x /= 10;
		} while (x != 0);
		if (minus) res += '-';
		reverse(res.begin(), res.end());
		return res;
	}

	// ©g‚Ì”‚Æˆø”‚Ì”‚Ì‘å¬‚ğ”äŠr
	int compare(string s, string t) {
		if (s.size() > t.size()) return 1;
		if (s.size() < t.size()) return -1;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] > t[i]) return 1;
			if (s[i] < t[i]) return -1;
		}
		return 0;
	}

	// “ª‚Ì0‚ğíœ
	string remove_leading_zeros(string x) {
		string res = "";
		int i = 0;
		while (i < x.size() && x[i] == '0') i++;
		while (i < x.size()) res += x[i++];
		if (res == "") res = "0";
		return res;
	}

	// “ª‚Éƒ}ƒCƒiƒX‚Â‚¯‚é
	string add_leading_minus(string x) {
		string res = '-' + x;
		return res;
	}

	// •‰”‚©ƒ`ƒFƒbƒN
	bool is_minus(string x) {
		return x[0] == '-';
	}

	// â‘Î’l
	string absolute(string x) {
		if (is_minus(x)) {
			return x.substr(1);
		} else {
			return x;
		}
	}

	// ’Pƒ‰ÁZ(‘æ‚Pˆø” + ‘æ‚Qˆø”)
	string simple_add(string s, string t) {
		string res = "";
		int carry = 0; // ŒJã‚°‚Í‚X1
		int s_size = s.size();
		int t_size = t.size();
		for (int i = s_size - 1, j = t_size - 1; i >= 0 || j >= 0;) {
			int x = carry;
			if (i >= 0) x += s[i--] - '0';
			if (j >= 0) x += t[j--] - '0';
			char c = '0' + x % 10;
			res += c;
			carry = x / 10;
		}
		if (carry > 0) res += carry + '0'; //2€‚Ì‘«‚µZ‚Ì‚½‚ß1‚Ì‚İ
		reverse(res.begin(), res.end());
		return res;
	}

	// ’PƒŒ¸Z(‘æ‚Pˆø” - ‘æ‚Qˆø”), ‘æ‚Pˆø”„‘æ‚Qˆø”
	string simple_subtract(string s, string t) {
		string res = "";
		int borrow = 0; // ŒJ‰º‚°‚Í‚X1
		int s_size = s.size();
		int t_size = t.size();
		for (int i = s_size - 1, j = t_size - 1; i >= 0 || j >= 0;) {
			int x = 0;
			int s_i = (i >= 0) ? s[i--] - '0' : 0;
			int t_j = (j >= 0) ? t[j--] - '0' : 0;
			if (s_i - borrow >= 0) {
				s_i -= borrow;
				borrow = 0;
			} else {
				s_i = 10 - s_i - borrow;
			}
			if (s_i >= t_j) x = s_i - t_j;
			if (s_i < t_j) {
				x = 10 - t_j + s_i;
				borrow += 1;
			}
			char c = x + '0';
			res += c;
		}
		reverse(res.begin(), res.end());
		res = remove_leading_zeros(res);
		return res;
	}

	// ‰ÁZ
	BigInteger add(BigInteger biginteger) {
		string res = "";
		string s = value;
		string t = biginteger.value;
		string ss = absolute(s);
		string tt = absolute(t);
		if (is_minus(s) == is_minus(t)) {
			// —¼•û³A—¼•û•‰‚Ìê‡‚Í‰ÁZ
			res = simple_add(ss, tt);
			if (is_minus(s)) res = add_leading_minus(res);
		} else {
			// •Ğ•û•‰‚Ìê‡‚ÍŒ¸Z
			if (compare(ss, tt) > 0 && is_minus(s)) res = '-';
			if (compare(ss, tt) < 0 && is_minus(t)) res = '-';
			if (compare(ss, tt) < 0) swap(ss, tt);
			res = res + simple_subtract(ss, tt);
		}
		return BigInteger(res);
	}

	// Œ¸Z
	BigInteger subtract(BigInteger biginteger) {
		string res = "";
		string s = value;
		string t = biginteger.value;
		t = is_minus(t) ? absolute(t) : add_leading_minus(t);
		return BigInteger(s).add(BigInteger(t));
	}

	// è—](Š„‚é”‚Ílong long)
	ll modulo(ll x) {
		ll res = 0;
		if (x <= 0) return -1;
		if (is_minus(value)) return -1;
		for (int i = 0; i < value.size(); i++) {
			res = 10 * res + (value[i] - '0');
			res = res % x;
		}
		return res;
	}
};

int main() {
	string a;
	ll b;
	while (cin >> a >> b) {
		BigInteger x(a), y(b);
		//BigInteger z = x.add(y);
		//BigInteger z = x.subtract(y);
		//cout << z.value << endl;
		ll z = x.modulo(b);
		cout << z << endl;
	}
	return 0;
}


