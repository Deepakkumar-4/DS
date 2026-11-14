
#include <bits/stdc++.h>
using namespace std;

// ============================================================
// 1. MATRIX CHAIN MULTIPLICATION - MEMOIZATION
// ============================================================

// arr = {10, 20, 30, 40}
// Matrices:
// A1 = 10 x 20
// A2 = 20 x 30
// A3 = 30 x 40
//
// dp[i][j] = minimum multiplication cost
//            for matrices from i to j.
//
// Recurrence:
// dp[i][j] = min(
//     dp[i][k] + dp[k+1][j]
//     + arr[i-1] * arr[k] * arr[j]
// )

int mcmMemo(int i, int j, vector<int>& arr,
            vector<vector<int>>& dp) {

    // Single matrix: no multiplication required
    if (i == j) return 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    int mini = INT_MAX;

    for (int k = i; k < j; k++) {

        int cost =
            mcmMemo(i, k, arr, dp) +
            mcmMemo(k + 1, j, arr, dp) +
            arr[i - 1] * arr[k] * arr[j];

        mini = min(mini, cost);
    }

    return dp[i][j] = mini;
}


// ============================================================
// 2. MATRIX CHAIN MULTIPLICATION - TABULATION
// ============================================================

int mcmTabulation(vector<int>& arr) {

    int n = arr.size();

    // Number of matrices = n - 1
    vector<vector<int>> dp(
        n, vector<int>(n, 0));

    // Start with smaller intervals
    for (int i = n - 1; i >= 1; i--) {

        for (int j = i + 1; j < n; j++) {

            int mini = INT_MAX;

            for (int k = i; k < j; k++) {

                int cost =
                    dp[i][k] +
                    dp[k + 1][j] +
                    arr[i - 1] * arr[k] * arr[j];

                mini = min(mini, cost);
            }

            dp[i][j] = mini;
        }
    }

    return dp[1][n - 1];
}


// ============================================================
// 3. PRINT OPTIMAL PARENTHESIZATION
// ============================================================

void printOptimal(int i, int j,
                  vector<vector<int>>& split) {

    if (i == j) {
        cout << "A" << i;
        return;
    }

    cout << "(";

    int k = split[i][j];

    printOptimal(i, k, split);

    cout << " x ";

    printOptimal(k + 1, j, split);

    cout << ")";
}

int mcmWithParenthesis(vector<int>& arr) {

    int n = arr.size();

    vector<vector<int>> dp(
        n, vector<int>(n, 0));

    vector<vector<int>> split(
        n, vector<int>(n, 0));

    for (int i = n - 1; i >= 1; i--) {

        for (int j = i + 1; j < n; j++) {

            int mini = INT_MAX;

            for (int k = i; k < j; k++) {

                int cost =
                    dp[i][k] +
                    dp[k + 1][j] +
                    arr[i - 1] * arr[k] * arr[j];

                if (cost < mini) {
                    mini = cost;
                    split[i][j] = k;
                }
            }

            dp[i][j] = mini;
        }
    }

    cout << "Optimal Parenthesization: ";
    printOptimal(1, n - 1, split);
    cout << endl;

    return dp[1][n - 1];
}


// ============================================================
// 4. MAXIMUM COST MATRIX CHAIN MULTIPLICATION
// ============================================================

// Variation: Instead of minimum cost,
// find the maximum multiplication cost.

int mcmMaximum(vector<int>& arr) {

    int n = arr.size();

    vector<vector<int>> dp(
        n, vector<int>(n, 0));

    for (int i = n - 1; i >= 1; i--) {

        for (int j = i + 1; j < n; j++) {

            int maxi = INT_MIN;

            for (int k = i; k < j; k++) {

                int cost =
                    dp[i][k] +
                    dp[k + 1][j] +
                    arr[i - 1] * arr[k] * arr[j];

                maxi = max(maxi, cost);
            }

            dp[i][j] = maxi;
        }
    }

    return dp[1][n - 1];
}


// ============================================================
// 5. MAIN FUNCTION
// ============================================================

int main() {

    // Three matrices:
    // A1 = 10 x 20
    // A2 = 20 x 30
    // A3 = 30 x 40

    vector<int> arr = {10, 20, 30, 40};

    int n = arr.size();

    // Memoization
    vector<vector<int>> dp(
        n, vector<int>(n, -1));

    cout << "MCM Memoization: "
         << mcmMemo(1, n - 1, arr, dp)
         << endl;

    // Tabulation
    cout << "MCM Tabulation: "
         << mcmTabulation(arr)
         << endl;

    // Optimal Parenthesization
    cout << "MCM with Parenthesization: "
         << mcmWithParenthesis(arr)
         << endl;

    // Maximum Cost Variation
    cout << "Maximum Multiplication Cost: "
         << mcmMaximum(arr)
         << endl;

    return 0;
}
