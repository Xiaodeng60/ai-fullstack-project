#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    double profit;
    double weight;
    double ratio; // profit / weight
};

bool compare(const Item& a, const Item& b) {
    return a.ratio > b.ratio;
}

void greedyKnapsack(vector<Item>& items, double capacity, vector<double>& x) {
    sort(items.begin(), items.end(), compare);
    x.assign(items.size(), 0.0);
    double cu = capacity;
    int n = items.size();
    for (int i = 0; i < n; ++i) {
        if (items[i].weight > cu) {
            break;
        }
        x[i] = 1.0;
        cu -= items[i].weight;
    }
    if (cu > 0 && !items.empty()) {
        int i = min_element(x.begin(), x.end()) - x.begin();
        if (i < n) {
            x[i] = cu / items[i].weight;
        }
    }
}

int main() {
    // Fixed test case
    vector<Item> items = {
        {60, 10, 0}, // profit, weight, ratio will be calculated
        {100, 20, 0},
        {120, 30, 0}
    };
    double capacity = 50.0;

    // Calculate ratios
    for (auto& item : items) {
        item.ratio = item.profit / item.weight;
    }

    cout << "Items:" << endl;
    for (size_t i = 0; i < items.size(); ++i) {
        cout << "Item " << i + 1 << ": profit=" << items[i].profit << ", weight=" << items[i].weight << ", ratio=" << items[i].ratio << endl;
    }

    vector<double> x;
    greedyKnapsack(items, capacity, x);

    double totalProfit = 0.0;
    cout << "\nSelected fractions:" << endl;
    for (size_t i = 0; i < items.size(); ++i) {
        if (x[i] > 0) {
            cout << "Item " << i + 1 << ": " << x[i] << endl;
            totalProfit += x[i] * items[i].profit;
        }
    }
    cout << "Total profit: " << totalProfit << endl;

    return 0;
}
