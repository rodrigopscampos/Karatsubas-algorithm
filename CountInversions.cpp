#include <iostream>
#include <string>
#include <queue>

using namespace std;

int* tempA;
int* tempB;

void copy(int* dest, int* src, int size) {
	for (int i = 0; i < size; i++)
		dest[i] = src[i];
}

long long int merge(int* arr, int middle, int right) {

	copy(tempA, arr, middle);
	copy(tempB, arr + middle, (right - middle));

	int l = 0, r = 0; int curr = 0;

	long long int ret = 0;
	int i = 0, j = 0;

	while (i < middle && j < right - middle) {

		if (tempA[i] > tempB[j]) {
			arr[curr] = tempB[j];
			ret += middle - i;
			j++;
		}
		else {
			arr[curr] = tempA[i];
			i++;
		}

		curr++;
	}

	while (i < middle) arr[curr++] = tempA[i++];
	while (j < right - middle) arr[curr++] = tempB[j++];

	return ret;
};

long long int sort(int* arr, int size) {
	if (size < 2) return 0;

	if (size == 2) {

		if (arr[0] > arr[1]) {
			swap(arr[0], arr[1]);
			return 1;
		}

		return 0;
	}

	int middle = size / 2;

	long long int ret = 0;
	ret += sort(arr, middle);
	ret += sort(arr + middle, size - middle);
	ret += merge(arr, middle, size);
	return ret;
}

int main() {

	int n = 100000;
	int* arr = new int[n];

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	tempA = new int[n / 2 + 1];
	tempB = new int[n / 2 + 1];

	cout << sort(arr, n) << "\n";

	free(tempA);
	free(tempB);

	return 0;
}
