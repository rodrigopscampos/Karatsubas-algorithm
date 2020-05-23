#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <iomanip>  

using namespace std;

priority_queue<int, vector<int>, std::less<int>> lowers;
priority_queue<int, vector<int>, std::greater<int>> highers;
vector<int> result;

void add(int n) {
	if (lowers.empty() || n < lowers.top()) {
		lowers.push(n);
	}
	else {
		highers.push(n);
	}
}

void rebalance() {
	if (lowers.size() > highers.size()) {
		while (lowers.size() - highers.size() > 1) {
			highers.push(lowers.top());
			lowers.pop();
		}
	}
	else {
		while (highers.size() - lowers.size() > 1) {
			lowers.push(highers.top());
			highers.pop();
		}
	}
}

void calcMedian() {
	if (lowers.size() == highers.size()) {
		float m = (lowers.top() + highers.top()) / 2.0;
		result.push_back(m);
	}
	else if (lowers.size() > highers.size()) {
		float m = lowers.top();
		result.push_back(m);
	}
	else {
		float m = highers.top();
		result.push_back(m);
	}
}

void median(int n) {

	add(n);
	rebalance();
	calcMedian();
}

int main() {

	int n;

	for (int i = 0; i < 10000; i++) {
		cin >> n;
		median(n);
	}

	std::cout << std::fixed;

	for (auto it : result)
		cout << std::setprecision(1) << it << "\n";

	return 0;
}
