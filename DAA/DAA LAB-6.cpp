#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>
using namespace std;

int main() {
    int n;

    cout << "Enter number of matrices: ";
    cin >> n;

    vector<int> p(n + 1);

    cout << "Enter " << n + 1 << " dimensions: ";
    for (int &x : p)
        cin >> x;

    vector<vector<long long>> m(n + 1, vector<long long>(n + 1, 0));
    vector<vector<int>> split(n + 1, vector<int>(n + 1, 0));

    // Matrix Chain Multiplication
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            m[i][j] = LLONG_MAX;

            for (int k = i; k < j; k++) {
                long long cost = m[i][k] + m[k + 1][j]
                    + (long long)p[i - 1] * p[k] * p[j];

                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    // Display DP Table
    cout << "\nDP Table:\n\n";
    cout << setw(8) << " ";

    for (int i = 1; i <= n; i++)
        cout << setw(12) << ("A" + to_string(i));

    cout << endl;

    for (int i = 1; i <= n; i++) {
        cout << setw(8) << ("A" + to_string(i));

        for (int j = 1; j <= n; j++) {
            if (j >= i)
                cout << setw(12) << m[i][j];
            else
                cout << setw(12) << "-";
        }

        cout << endl;
    }

    cout << "\nMinimum number of scalar multiplications: "
         << m[1][n] << endl;

    // Print optimal order
    cout << "Optimal Parenthesization: ";

    // Recursive function
    auto printOrder = [&](auto&& self, int i, int j) -> void {
        if (i == j) {
            cout << "A" << i;
            return;
        }

        int k = split[i][j];

        cout << "(";
        self(self, i, k);
        cout << " x ";
        self(self, k + 1, j);
        cout << ")";
    };

    printOrder(printOrder, 1, n);

    cout << endl;

    return 0;
}
