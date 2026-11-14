
#include <bits/stdc++.h>
using namespace std;

// ============================================================
// 1. ROD CUTTING
// ============================================================

// Standard Rod Cutting
// dp[i] = maximum profit for rod of length i
// Recurrence: dp[i] = max(price[j-1] + dp[i-j])

int rodCutting(vector<int>& price, int n) {
    vector<int> dp(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            dp[i] = max(dp[i],
                        price[j - 1] + dp[i - j]);
        }
    }
    return dp[n];
}

// Rod Cutting - Memoization
int rodMemo(int i, vector<int>& price,
            vector<int>& dp) {
    if (i == 0) return 0;
    if (dp[i] != -1) return dp[i];

    int ans = 0;
    for (int j = 1; j <= i; j++) {
        ans = max(ans,
                  price[j - 1] +
                  rodMemo(i - j, price, dp));
    }
    return dp[i] = ans;
}

// Rod Cutting - Number of ways to obtain length n
// Each piece length can be used unlimited times.
// Counts unordered combinations.

long long rodWays(int n) {
    vector<long long> dp(n + 1, 0);
    dp[0] = 1;

    for (int len = 1; len <= n; len++) {
        for (int j = len; j <= n; j++) {
            dp[j] += dp[j - len];
        }
    }
    return dp[n];
}


// ============================================================
// 2. LONGEST COMMON SUBSEQUENCE (LCS)
// ============================================================

// Standard LCS - Tabulation
// dp[i][j] = LCS length of first i and first j characters

int LCS(string a, string b) {
    int n = a.size(), m = b.size();

    vector<vector<int>> dp(
        n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j],
                               dp[i][j - 1]);
        }
    }
    return dp[n][m];
}

// Print the actual LCS string

string printLCS(string a, string b) {
    int n = a.size(), m = b.size();

    vector<vector<int>> dp(
        n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j],
                               dp[i][j - 1]);
        }
    }

    string ans = "";
    int i = n, j = m;

    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            ans += a[i - 1];
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
            i--;
        else
            j--;
    }

    reverse(ans.begin(), ans.end());
    return ans;
}

// Longest Common Substring
// Unlike LCS, characters must be continuous.

int longestCommonSubstring(string a, string b) {
    int n = a.size(), m = b.size();
    int ans = 0;

    vector<vector<int>> dp(
        n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
                ans = max(ans, dp[i][j]);
            }
            else {
                dp[i][j] = 0;
            }
        }
    }
    return ans;
}

// Shortest Common Supersequence length
// SCS = len(a) + len(b) - LCS

int shortestCommonSupersequence(string a, string b) {
    return a.size() + b.size() - LCS(a, b);
}


// ============================================================
// 3. 0/1 KNAPSACK
// ============================================================

// Standard 0/1 Knapsack
// Each item can be selected at most once.

int knapsack(vector<int>& wt, vector<int>& val,
             int W) {
    int n = wt.size();

    vector<vector<int>> dp(
        n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            dp[i][w] = dp[i - 1][w];

            if (wt[i - 1] <= w) {
                dp[i][w] = max(
                    dp[i][w],
                    val[i - 1] +
                    dp[i - 1][w - wt[i - 1]]
                );
            }
        }
    }
    return dp[n][W];
}

// 0/1 Knapsack - Space Optimized
// Iterate capacity backwards to avoid reusing items.

int knapsackOptimized(vector<int>& wt,
                      vector<int>& val, int W) {
    int n = wt.size();
    vector<int> dp(W + 1, 0);

    for (int i = 0; i < n; i++) {
        for (int w = W; w >= wt[i]; w--) {
            dp[w] = max(dp[w],
                        val[i] + dp[w - wt[i]]);
        }
    }
    return dp[W];
}

// Subset Sum
// Can we form sum K using array elements?

bool subsetSum(vector<int>& arr, int K) {
    vector<bool> dp(K + 1, false);
    dp[0] = true;

    for (int x : arr) {
        for (int j = K; j >= x; j--) {
            dp[j] = dp[j] || dp[j - x];
        }
    }
    return dp[K];
}

// Equal Subset Partition
// Can array be divided into two equal-sum subsets?

bool canPartition(vector<int>& arr) {
    int sum = accumulate(arr.begin(), arr.end(), 0);

    if (sum % 2 != 0) return false;

    return subsetSum(arr, sum / 2);
}

// Count subsets with given sum K

long long countSubsets(vector<int>& arr, int K) {
    vector<long long> dp(K + 1, 0);
    dp[0] = 1;

    for (int x : arr) {
        for (int j = K; j >= x; j--) {
            dp[j] += dp[j - x];
        }
    }
    return dp[K];
}

// Minimum Subset Sum Difference

int minSubsetDifference(vector<int>& arr) {
    int sum = accumulate(arr.begin(), arr.end(), 0);

    vector<bool> dp(sum + 1, false);
    dp[0] = true;

    for (int x : arr) {
        for (int j = sum; j >= x; j--) {
            dp[j] = dp[j] || dp[j - x];
        }
    }

    int ans = INT_MAX;

    for (int s1 = 0; s1 <= sum / 2; s1++) {
        if (dp[s1]) {
            ans = min(ans, sum - 2 * s1);
        }
    }
    return ans;
}


// ============================================================
// 4. FROG JUMP
// ============================================================

// Standard Frog Jump
// Frog can jump either 1 or 2 steps.
// Cost = absolute difference in heights.

int frogJump(vector<int>& h) {
    int n = h.size();

    if (n <= 1) return 0;

    vector<int> dp(n, 0);
    dp[0] = 0;

    for (int i = 1; i < n; i++) {
        int one = dp[i - 1] +
                  abs(h[i] - h[i - 1]);

        int two = INT_MAX;

        if (i > 1) {
            two = dp[i - 2] +
                  abs(h[i] - h[i - 2]);
        }

        dp[i] = min(one, two);
    }

    return dp[n - 1];
}

// Frog Jump - Space Optimized

int frogJumpOptimized(vector<int>& h) {
    int n = h.size();

    if (n <= 1) return 0;

    int prev2 = 0, prev1 = 0;

    for (int i = 1; i < n; i++) {
        int one = prev1 + abs(h[i] - h[i - 1]);

        int two = INT_MAX;

        if (i > 1)
            two = prev2 + abs(h[i] - h[i - 2]);

        int curr = min(one, two);

        prev2 = prev1;
        prev1 = curr;
    }

    return prev1;
}

// Frog Jump - K Distance
// Frog can jump 1, 2, ... K steps.

int frogJumpK(vector<int>& h, int K) {
    int n = h.size();

    if (n <= 1) return 0;

    vector<int> dp(n, INT_MAX);
    dp[0] = 0;

    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= K && j <= i; j++) {
            dp[i] = min(
                dp[i],
                dp[i - j] + abs(h[i] - h[i - j])
            );
        }
    }

    return dp[n - 1];
}


// ============================================================
// MAIN FUNCTION - TEST ALL PROBLEMS
// ============================================================

int main() {

    // 1. Rod Cutting
    vector<int> price = {2, 5, 7, 8, 10};
    int n = 5;

    cout << "Rod Cutting: "
         << rodCutting(price, n) << endl;

    cout << "Rod Cutting Ways: "
         << rodWays(n) << endl;


    // 2. LCS
    string a = "abcde";
    string b = "ace";

    cout << "\nLCS Length: "
         << LCS(a, b) << endl;

    cout << "LCS String: "
         << printLCS(a, b) << endl;

    cout << "Longest Common Substring: "
         << longestCommonSubstring(a, b) << endl;

    cout << "Shortest Common Supersequence: "
         << shortestCommonSupersequence(a, b) << endl;


    // 3. 0/1 Knapsack
    vector<int> wt = {1, 2, 4, 5};
    vector<int> val = {5, 4, 8, 6};
    int W = 5;

    cout << "\nKnapsack: "
         << knapsack(wt, val, W) << endl;

    cout << "Optimized Knapsack: "
         << knapsackOptimized(wt, val, W) << endl;

    vector<int> arr = {1, 5, 11, 5};

    cout << "Subset Sum (11): "
         << subsetSum(arr, 11) << endl;

    cout << "Equal Partition: "
         << canPartition(arr) << endl;

    cout << "Count Subsets (11): "
         << countSubsets(arr, 11) << endl;

    cout << "Minimum Subset Difference: "
         << minSubsetDifference(arr) << endl;


    // 4. Frog Jump
    vector<int> heights = {10, 20, 30, 10};

    cout << "\nFrog Jump: "
         << frogJump(heights) << endl;

    cout << "Optimized Frog Jump: "
         << frogJumpOptimized(heights) << endl;

    cout << "Frog Jump K=3: "
         << frogJumpK(heights, 3) << endl;

    return 0;
}
