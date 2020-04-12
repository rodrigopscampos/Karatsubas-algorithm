#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;



int* tempA;
int* tempB;

void copy(int* dest, int* src, int size) {
    for (int i = 0; i < size; i++)
        dest[i] = src[i];
}

void merge(int* arr, int middle, int right) {

    copy(tempA, arr, middle );
    copy(tempB, arr + middle, (right - middle) );

    int l = 0, r = 0; int curr = 0;

    while (l < middle && r < right - middle) {
        if (tempA[l] > tempB[r]) {
            arr[curr] = tempB[r];
            r++;
        }
        else {
            arr[curr] = tempA[l];
            l++;
        }

        curr++;
    }

    while (l < middle) arr[curr++] = tempA[l++];
    while (r < right - middle) arr[curr++] = tempB[r++];
};

void sort(int* arr, int size) {
    if (size < 2) return;

    if (size == 2) {

        if (arr[0] > arr[1]) {
            swap(arr[0], arr[1]);
        }

        return;
    }

    int middle = size / 2;

    sort(arr, middle);
    sort(arr + middle, size - middle);

    merge(arr, middle, size);
}

int main() {

    int n;
    cin >> n;

    int* arr = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    tempA = new int[n / 2 + 1];
    tempB = new int[n / 2 + 1];

    sort(arr, n);

    free(tempA);
    free(tempB);

    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << arr[i];

        if (i != n - 1) cout << ",";
    }
    cout << "]";

    return 0;
}
