#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

vector<int> A;
vector<int> Link;

void merge(int q, int r, int &p) {
    int i = q, j = r, k = 0;
    while (i != 0 && j != 0) {
        if (A[i] <= A[j]) {
            Link[k] = i;
            k = i;
            i = Link[i];
        } else {
            Link[k] = j;
            k = j;
            j = Link[j];
        }
    }
    Link[k] = (i == 0) ? j : i;
    p = Link[0];
}

void insertsort(int low, int high, int &p) {
    p = 0;
    for (int i = low; i <= high; i++) {
        int j = p, k = 0;
        while (j != 0 && A[j] <= A[i]) {
            k = j;
            j = Link[j];
        }
        Link[k] = i;
        Link[i] = j;
        if (k == 0) p = i;
    }
}

void mergesort(int low, int high, int &p) {
    if (high - low + 1 < 16) {
        insertsort(low, high, p);
        return;
    }
    int mid = low + (high - low) / 2;
    int q, r;
    mergesort(low, mid, q);
    mergesort(mid + 1, high, r);
    merge(q, r, p);
}

int main() {
    A.push_back(0);
    Link.push_back(0);

    srand((unsigned int)time(NULL));
    clock_t start, end;
    start = clock();

    for (int i = 1; i <= 500000; i++) {
        A.push_back(rand() % 1000000);
        Link.push_back(0);
    }

    // 输出原始前100个
    cout << "Original array: ";
    for (int i = 1; i <= 100; i++) {
        cout << A[i] << " ";
    }
    cout << endl << endl;

    int p;
    mergesort(1, 500000, p);

    // 输出排序后前100个
    cout << "Sorted array: ";
    int count = 0;
    while (p != 0 && count < 100) {
        cout << A[p] << " ";
        p = Link[p];
        count++;
    }

    end = clock();
    cout << "\nTime taken: " << (double)(end - start) / CLOCKS_PER_SEC << "s\n";
    return 0;
}