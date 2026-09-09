#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, amount;

    cout << "Enter number of coins: ";
    cin >> n;

    vector<int> coins(n);

    cout << "Enter the coin values: ";
    for (int &x : coins)
        cin >> x;

    cout << "Enter the amount: ";
    cin >> amount;

    vector<int> dp(amount + 1, amount + 1);
    vector<int> usedCoin(amount + 1, -1);

    dp[0] = 0;

    // Find minimum coins
    for (int i = 1; i <= amount; i++) {
        for (int coin : coins) {
            if (coin <= i && dp[i - coin] + 1 < dp[i]) {
                dp[i] = dp[i - coin] + 1;
                usedCoin[i] = coin;
            }
        }
    }

    // Check result
    if (dp[amount] > amount) {
        cout << "Amount cannot be made using the given coins." << endl;
    }
    else {
        cout << "Minimum number of coins required: "
             << dp[amount] << endl;

        cout << "Coins used: ";

        int current = amount;

        while (current > 0) {
            int coin = usedCoin[current];
            cout << coin << " ";
            current -= coin;
        }

        cout << endl;
    }

    return 0;
}
