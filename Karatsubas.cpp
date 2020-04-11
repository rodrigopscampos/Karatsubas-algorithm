#include <iostream>
#include <string>
#include <queue>

using namespace std;

string trimLeft0(string str) {
	auto p = str.begin();
	for (; *p == '0' && p != str.end() - 1; p++);
	str = string(p, str.end());
	return str;
}

void fixLen(string& x, string& y) {
	if (y.size() % 2 != 0)
		y = '0' + y;
	if (x.size() % 2 != 0)
		x = '0' + x;

	if (x.size() > y.size()) {
		y = string(x.size() - y.size(), '0') + y;
	}
	else if (y.size() > x.size()) {
		x = string(y.size() - x.size(), '0') + x;
	}
}


string sub(string x, string y) {

	fixLen(x, y);

	int aux = 0;
	deque<char> result;
	for (int i = x.size() - 1; i >= 0; i--) {
		int a = x[i] - '0';
		int b = y[i] - '0';

		if (a >= b) {
			string a_minus_b = to_string(a - b);
			result.push_front(a_minus_b[0]);
		}
		else {
			a += 10;
			x[i - 1] -= 1;

			string a_minus_b = to_string(a - b);
			result.push_front(a_minus_b[0]);
		}
	}

	auto ret = string(result.begin(), result.end());
	return trimLeft0(ret);
}

string sum(string x, string y) {

	fixLen(x, y);

	int aux = 0;
	deque<char> result;
	for (int i = x.size() - 1; i >= 0; i--) {
		int a = x[i] - '0';
		int b = y[i] - '0';

		string a_plus_b = to_string(a + b + aux);
		aux = 0;

		if (a_plus_b.size() > 1) {
			result.push_front(a_plus_b[1]);
			aux = a_plus_b[0] - '0';
		}
		else {
			result.push_front(a_plus_b[0]);
		}
	}

	if (aux > 0) result.push_front('0' + aux);

	auto ret = string(result.begin(), result.end());
	return trimLeft0(ret);
}

string pow10x(int exp, string n) {
	return n + string(exp, '0');
}

string multiply(string x, string y) {

	fixLen(x, y);

	if (x.size() <= 3 || y.size() <= 3)
		return to_string(stoi(x) * (stoi(y)));

	auto n = x.size();
	auto n2 = n / 2;

	auto a = trimLeft0(x.substr(0, n2));
	auto b = trimLeft0(x.substr(n2, n - n2));

	auto c = trimLeft0(y.substr(0, n2));
	auto d = trimLeft0(y.substr(n2, n - n2));

	auto ac = multiply(a, c);
	auto db = multiply(d, b);

	auto a_plus_b = sum(a, b);
	auto c_plus_d = sum(c, d);
	auto ac_plus_db = sum(ac, db);
	auto a_plus_b_x_c_plus_d = multiply(a_plus_b, c_plus_d);

	auto ad_plus_bc = sub(a_plus_b_x_c_plus_d, ac_plus_db);

	auto ten_exp_ac = pow10x(n, ac);
	auto ten_half_exp_ad_plus_bc = pow10x(n2, ad_plus_bc);

	auto ret = sum(sum(ten_exp_ac, ten_half_exp_ad_plus_bc), db);
	return trimLeft0(ret);
}

int main() {

	string x = "3141592653589793238462643383279502884197169399375105820974944592";
	string y = "2718281828459045235360287471352662497757247093699959574966967627";
	cout << multiply(x, y) << "\n";
	cout << multiply(y, x) << "\n";

	return 0;
}
