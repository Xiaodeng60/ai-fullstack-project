#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Job {
    int p; // profit
    int d; // deadline
    int index;
};

bool compare(const Job& a, const Job& b) {
    return a.p > b.p;
}

class UnionFind {
public:
    vector<int> parent;
    UnionFind(int size) {
        parent.resize(size + 1);
        for (int i = 0; i <= size; ++i) {
            parent[i] = i;
        }
    }
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootX] = rootY;
        }
    }
};

void jobScheduling(vector<Job>& jobs, int maxDeadline) {
    sort(jobs.begin(), jobs.end(), compare);
    UnionFind uf(maxDeadline);
    vector<int> scheduled;

    for (auto& job : jobs) {
        int slot = uf.find(job.d);
        if (slot > 0) {
            scheduled.push_back(job.index);
            uf.unite(slot, slot - 1);
        }
    }

    cout << "Scheduled jobs: ";
    for (int idx : scheduled) {
        cout << idx << " ";
    }
    cout << endl;
    cout << "Total jobs scheduled: " << scheduled.size() << endl;
}

int main() {
    // Fixed test case: 4 jobs
    vector<Job> jobs = {
        {35, 4, 1}, // p, d, index
        {30, 3, 2},
        {25, 2, 3},
        {20, 1, 4}
    };
    int maxDeadline = 4; // assume max d is 4

    jobScheduling(jobs, maxDeadline);

    return 0;
}