#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, capacity;

    cout << "Enter number of items: ";
    cin >> n;

    vector<int> weight(n), profit(n);

    cout << "Enter weights: ";
    for (int &x : weight)
        cin >> x;

    cout << "Enter profits: ";
    for (int &x : profit)
        cin >> x;

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    // DP table
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {

            if (weight[i - 1] <= w)
                dp[i][w] = max(dp[i - 1][w],
                               profit[i - 1] +
                               dp[i - 1][w - weight[i - 1]]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    cout << "\nMaximum profit: " << dp[n][capacity] << endl;

    // Find selected items
    vector<int> selected(n, 0);
    int w = capacity;

    for (int i = n; i >= 1; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            selected[i - 1] = 1;
            w -= weight[i - 1];
        }
    }

    cout << "\n0/1 Selection:\n";
    for (int i = 0; i < n; i++)
        cout << "Item " << i + 1 << ": " << selected[i] << endl;

    // Calculate total weight
    int totalWeight = 0;

    for (int i = 0; i < n; i++)
        if (selected[i])
            totalWeight += weight[i];

    cout << "\nTotal weight: " << totalWeight << endl;
    cout << "Maximum profit: " << dp[n][capacity] << endl;

    return 0;
}
