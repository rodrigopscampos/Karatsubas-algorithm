#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct MinHeap {
    int arr[1000000];
    int curr = -1;

    int INF = (int)1e9;

    int getParent(int n) {
        return arr[(n - 1) / 2];
    }

    int getLeftChildren(int n) {
        int index = (n * 2) + 1;
        if (index > curr) return INF;
        return arr[index];
    }

    int getRightChildren(int n) {
        int index = (n * 2) + 2;
        if (index > curr) return INF;
        return arr[index];
    }

    void add(int n) {
        arr[++curr] = n;

        n = curr;
        if (n >= 1) {
            while (arr[(n - 1) / 2] > arr[n]) {
                swap(arr[(n - 1) / 2], arr[n]);
                n = (n - 1) / 2;
            }
        }
    }

    int lookup(int n) {
        for(int i = 0; i <= curr; i++)
            if(arr[i] == n) return i;
        
        return -1;
    }
    
    void remove(int n) {
        n = lookup(n);

        arr[n] = 0;
        swap(arr[n], arr[curr]);
        curr--;

        while (arr[n] > getRightChildren(n) || arr[n] > getLeftChildren(n)) {
            if (getRightChildren(n) < getLeftChildren(n)) {
                swap(arr[n], arr[(n * 2) + 2]);
                n = (n * 2) + 2;
            }
            else {
                swap(arr[n], arr[(n * 2) + 1]);
                n = (n * 2) + 1;
            }
        }
    }

    void printMin() {
        cout << arr[0] << "\n";
    }

    void printArr() {
        return;
        cout << "print: ";
        for (int i = 0; i <= curr; i++)
            cout << arr[i] << " ";
        cout << "\n";
    }
};


int main() {
    
    int q, t, v;
    cin >> q;

    MinHeap heap;
    for(int i = 0; i < q; i++) {
        cin >> t;

        if(t == 1) { // add
            cin >> v;
            heap.add(v);
        } else if(t == 2) { // delete
            cin >> v;
            heap.remove(v);
        } else if(t == 3) { //print min
            heap.printMin();
        } else {
            cout << "invalid v: " << v;
        }

        heap.printArr();
    }

    return 0;
}
