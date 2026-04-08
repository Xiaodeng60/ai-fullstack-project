///Quick Sort
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

void quickSort(vector<int>& a, int left, int right) {
    if (left >= right) return;
    int pivot = a[left + (right - left) / 2];
    int i = left;
    int j = right;
    while (i <= j) {
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;
        if (i <= j) {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }
    if (left < j) quickSort(a, left, j);
    if (i < right) quickSort(a, i, right);
}

int main() {
    const int n = 20;
    vector<int> data;
    data.reserve(n);

    // Generate test cases
    mt19937 rng((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dist(0, 999);
    for (int i = 0; i < n; ++i) {
        data.push_back(dist(rng));
    }

    cout << "Original array: ";
    for (int x : data) {
        cout << x << " ";
    }
    cout << endl;

    auto start = chrono::high_resolution_clock::now();
    quickSort(data, 0, (int)data.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed = end - start;

    cout << "Sorted array: ";
    for (int x : data) {
        cout << x << " ";
    }
    cout << endl;
    cout << "Time taken: " << elapsed.count() << " milliseconds" << endl;

    return 0;
}
