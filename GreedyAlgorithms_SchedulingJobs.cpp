#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <iomanip>  

using namespace std;

struct Job {
	long long Length;
	long long Weight;

	long long PriorityDiff;
	long double PriorityRatio;

	Job(long long l, long long w) {
		Length = l;
		Weight = w;

		PriorityDiff = Weight - Length;
		PriorityRatio = (long double)Weight / (long double)Length;
	}
};

auto cmp_diff = [](Job left, Job right) {
	if (left.PriorityDiff == right.PriorityDiff) {
		return left.Weight < right.Weight;
	}
	else
		return left.PriorityDiff < right.PriorityDiff;
};

auto cmp_ratio = [](Job left, Job right) {
	if (left.PriorityRatio == right.PriorityRatio) {
		return left.Weight < right.Weight;
	}
	else
		return left.PriorityRatio < right.PriorityRatio;
};

priority_queue<Job, vector<Job>, decltype(cmp_diff)> jobs_diff(cmp_diff);
priority_queue<Job, vector<Job>, decltype(cmp_ratio)> jobs_ratio(cmp_ratio);

long long calc_diff() {
	long long ret = 0;
	long long t = 0;
	while (!jobs_diff.empty()) {
		auto j = jobs_diff.top(); jobs_diff.pop();
		t += j.Length;
		ret += (t * j.Weight);
	}

	return ret;
}

long long calc_ratio() {
	long long ret = 0;
	long long t = 0;
	while (!jobs_ratio.empty()) {
		auto j = jobs_ratio.top(); jobs_ratio.pop();
		t += j.Length;
		ret += (t * j.Weight);
	}

	return ret;
}

int main() {
	int n, l, w;

	cin >> n;

	for (int i = 0; i < n; i++) {

		cin >> w >> l;
		auto j = Job(l, w);
		jobs_diff.push(j);
		jobs_ratio.push(j);
	}

	cout << "by diff: " << calc_diff() << "\n";
	cout << "by ratio: " << calc_ratio() << "\n";
}
