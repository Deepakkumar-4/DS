//====================================================================
// FILE: dp2.cpp
// COMPREHENSIVE ADVANCED DYNAMIC PROGRAMMING REPOSITORY
// Covers:
// 1. DP on Stocks (All Variations)
// 2. String DP & Edit Distance (Edit Distance, Wildcard, Regex, Distinct Subsequences)
// 3. Partition DP / Matrix Chain Multiplication (MCM, Palindrome Partitioning II, Boolean Parenthesization)
// 4. 0/1 Knapsack & Target Sum (0/1 Knapsack, Coin Change Min Coins, Target Sum)
// 5. Tree DP (House Robber III, Binary Tree Maximum Path Sum)
// 6. Bitmask DP (Traveling Salesperson Problem)
//====================================================================

//====================================================================
// SECTION 1: DP ON STOCKS (BUY & SELL STOCKS)
//====================================================================

//---------Best Time to Buy and Sell Stock II (Infinite Transactions)

#include <bits/stdc++.h>
using namespace std;

int maxProfitStock2(vector<int>& prices)
{
    int n = prices.size();
    if(n == 0) return 0;

    // dp[0]: max profit when not holding a stock
    // dp[1]: max profit when holding a stock
    int notHolding = 0;
    int holding = -prices[0];

    for(int i = 1; i < n; i++)
    {
        int prevNotHolding = notHolding;
        // Either stay not holding, or sell the stock held
        notHolding = max(notHolding, holding + prices[i]);
        // Either stay holding, or buy a new stock
        holding = max(holding, prevNotHolding - prices[i]);
    }

    return notHolding;
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> prices(n);
        for(int i = 0; i < n; i++) cin >> prices[i];
        cout << maxProfitStock2(prices) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. You may complete as many transactions as you like (buy one and sell one multiple times).
2. Maintain two states at day i:
   - notHolding: maximum cash without holding any stock on day i.
   - holding: maximum cash while holding a stock on day i.
3. Transitions:
   notHolding = max(notHolding, holding + prices[i]) (sell)
   holding = max(holding, prevNotHolding - prices[i]) (buy)
4. Space optimized to O(1) using two variables.

SAMPLE INPUT:
6
7 1 5 3 6 4

SAMPLE OUTPUT:
7

EXPLANATION:
Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 4.
Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 3.
Total profit = 4 + 3 = 7.

RECURRENCE RELATION:
notHolding[i] = max(notHolding[i-1], holding[i-1] + prices[i])
holding[i]    = max(holding[i-1], notHolding[i-1] - prices[i])

TIME COMPLEXITY:
O(n)

SPACE COMPLEXITY:
O(1)

PATTERN:
Dynamic Programming - State Machine DP (Buy / Sell)
*/

//---------Best Time to Buy and Sell Stock with Cooldown (LeetCode 309)

#include <bits/stdc++.h>
using namespace std;

int maxProfitWithCooldown(vector<int>& prices)
{
    int n = prices.size();
    if(n <= 1) return 0;

    int hold = -prices[0]; // Holding a stock
    int sold = 0;          // Just sold today (must cooldown tomorrow)
    int rest = 0;          // In rest/cooldown state (free to buy)

    for(int i = 1; i < n; i++)
    {
        int prevHold = hold;
        int prevSold = sold;
        int prevRest = rest;

        hold = max(prevHold, prevRest - prices[i]); // Buy from rest state
        sold = prevHold + prices[i];                // Sell currently held stock
        rest = max(prevRest, prevSold);             // Stay in rest or cooldown from sold
    }

    return max(sold, rest);
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> prices(n);
        for(int i = 0; i < n; i++) cin >> prices[i];
        cout << maxProfitWithCooldown(prices) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. After selling a stock, you cannot buy on the next day (1 day cooldown).
2. Three states for each day:
   - hold: You own a stock. You can either keep holding or buy after rest.
   - sold: You sold a stock today. Next day must rest.
   - rest: You did not hold or sell stock today. Free to buy next day.
3. Transitions:
   hold = max(prevHold, prevRest - prices[i])
   sold = prevHold + prices[i]
   rest = max(prevRest, prevSold)
4. Result is max(sold, rest) on the final day.

SAMPLE INPUT:
5
1 2 3 0 2

SAMPLE OUTPUT:
3

EXPLANATION:
Transactions: [buy, sell, cooldown, buy, sell] -> profit = (2-1) + (2-0) = 3.

TIME COMPLEXITY:
O(n)

SPACE COMPLEXITY:
O(1)

PATTERN:
Dynamic Programming - 3-State Machine
*/

//---------Best Time to Buy and Sell Stock with Transaction Fee (LeetCode 714)

#include <bits/stdc++.h>
using namespace std;

int maxProfitWithFee(vector<int>& prices, int fee)
{
    int n = prices.size();
    if(n == 0) return 0;

    int notHolding = 0;
    int holding = -prices[0];

    for(int i = 1; i < n; i++)
    {
        int prevNotHolding = notHolding;
        // Deduct transaction fee when selling
        notHolding = max(notHolding, holding + prices[i] - fee);
        holding = max(holding, prevNotHolding - prices[i]);
    }

    return notHolding;
}

int main()
{
    int n, fee;
    if(cin >> n >> fee)
    {
        vector<int> prices(n);
        for(int i = 0; i < n; i++) cin >> prices[i];
        cout << maxProfitWithFee(prices, fee) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. You may complete unlimited transactions, but must pay a fee for each transaction.
2. We pay fee either upon buying or upon selling (here, upon selling).
3. Transitions:
   notHolding = max(notHolding, holding + prices[i] - fee)
   holding    = max(holding, notHolding - prices[i])
4. Space complexity is O(1).

SAMPLE INPUT:
6 2
1 3 2 8 4 9

SAMPLE OUTPUT:
8

EXPLANATION:
Buy at 1, sell at 8 (profit = 8 - 1 - 2 = 5).
Buy at 4, sell at 9 (profit = 9 - 4 - 2 = 3).
Total profit = 5 + 3 = 8.

TIME COMPLEXITY:
O(n)

SPACE COMPLEXITY:
O(1)

PATTERN:
Dynamic Programming - State Machine with Cost Penalty
*/

//---------Best Time to Buy and Sell Stock III (At most 2 transactions) (LeetCode 123)

#include <bits/stdc++.h>
using namespace std;

int maxProfitStock3(vector<int>& prices)
{
    int buy1 = INT_MIN, sell1 = 0;
    int buy2 = INT_MIN, sell2 = 0;

    for(int price : prices)
    {
        buy1  = max(buy1, -price);
        sell1 = max(sell1, buy1 + price);
        buy2  = max(buy2, sell1 - price);
        sell2 = max(sell2, buy2 + price);
    }

    return sell2;
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> prices(n);
        for(int i = 0; i < n; i++) cin >> prices[i];
        cout << maxProfitStock3(prices) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. Maximum of 2 transactions allowed.
2. Track 4 states representing the maximum balance after each stage:
   - buy1:  Max balance after 1st buy: max(buy1, -price)
   - sell1: Max balance after 1st sell: max(sell1, buy1 + price)
   - buy2:  Max balance after 2nd buy: max(buy2, sell1 - price)
   - sell2: Max balance after 2nd sell: max(sell2, buy2 + price)
3. sell2 gives the final maximum profit.

SAMPLE INPUT:
8
3 3 5 0 0 3 1 4

SAMPLE OUTPUT:
6

EXPLANATION:
Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3.
Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 3.
Total profit = 3 + 3 = 6.

TIME COMPLEXITY:
O(n)

SPACE COMPLEXITY:
O(1)

PATTERN:
Dynamic Programming - Constant-Transaction Unrolling
*/

//---------Best Time to Buy and Sell Stock IV (At most K transactions) (LeetCode 188)

#include <bits/stdc++.h>
using namespace std;

int maxProfitStockK(int k, vector<int>& prices)
{
    int n = prices.size();
    if(n <= 1 || k == 0) return 0;

    // If k >= n/2, equivalent to unlimited transactions
    if(k >= n / 2)
    {
        int maxProfit = 0;
        for(int i = 1; i < n; i++)
        {
            if(prices[i] > prices[i - 1])
                maxProfit += prices[i] - prices[i - 1];
        }
        return maxProfit;
    }

    // dp[t][d] = max profit on day d with at most t transactions
    vector<vector<int>> dp(k + 1, vector<int>(n, 0));

    for(int t = 1; t <= k; t++)
    {
        int maxDiff = -prices[0]; // max(dp[t-1][d] - prices[d])
        for(int d = 1; d < n; d++)
        {
            dp[t][d] = max(dp[t][d - 1], prices[d] + maxDiff);
            maxDiff = max(maxDiff, dp[t - 1][d] - prices[d]);
        }
    }

    return dp[k][n - 1];
}

int main()
{
    int k, n;
    if(cin >> k >> n)
    {
        vector<int> prices(n);
        for(int i = 0; i < n; i++) cin >> prices[i];
        cout << maxProfitStockK(k, prices) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[t][d] = max profit on day d with at most t transactions.
2. Choices on day d:
   - Do no transaction on day d: dp[t][d-1]
   - Sell on day d: buy on some day m (0 <= m < d), profit is prices[d] - prices[m] + dp[t-1][m].
3. dp[t][d] = max(dp[t][d-1], prices[d] + max_{0 <= m < d}(dp[t-1][m] - prices[m])).
4. Maintain running maxDiff = max_{m < d}(dp[t-1][m] - prices[m]) to optimize inner loop from O(n) to O(1).

SAMPLE INPUT:
2 6
3 2 6 5 0 3

SAMPLE OUTPUT:
7

EXPLANATION:
Buy day 2 (price 2), sell day 3 (price 6) -> 4.
Buy day 5 (price 0), sell day 6 (price 3) -> 3. Total = 7.

TIME COMPLEXITY:
O(k * n)

SPACE COMPLEXITY:
O(k * n) (can be optimized to O(n))

PATTERN:
Dynamic Programming - Multi-transaction with Pre-computed Maxima
*/


//====================================================================
// SECTION 2: STRING DP & EDIT DISTANCE
//====================================================================

//---------Edit Distance (LeetCode 72)

#include <bits/stdc++.h>
using namespace std;

int minDistance(string word1, string word2)
{
    int m = word1.size();
    int n = word2.size();

    // dp[i][j] = minimum operations to convert word1[0..i-1] to word2[0..j-1]
    vector<int> prev(n + 1, 0), curr(n + 1, 0);

    for(int j = 0; j <= n; j++) prev[j] = j;

    for(int i = 1; i <= m; i++)
    {
        curr[0] = i;
        for(int j = 1; j <= n; j++)
        {
            if(word1[i - 1] == word2[j - 1])
            {
                curr[j] = prev[j - 1]; // No operation needed
            }
            else
            {
                curr[j] = 1 + min({prev[j],      // Delete from word1
                                   curr[j - 1],  // Insert into word1
                                   prev[j - 1]});// Replace character
            }
        }
        prev = curr;
    }

    return prev[n];
}

int main()
{
    string w1, w2;
    if(cin >> w1 >> w2)
    {
        cout << minDistance(w1, w2) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[i][j] represents the minimum operations to convert word1[0..i-1] into word2[0..j-1].
2. Operations:
   - Match: word1[i-1] == word2[j-1] -> dp[i-1][j-1]
   - Insert: 1 + dp[i][j-1]
   - Delete: 1 + dp[i-1][j]
   - Replace: 1 + dp[i-1][j-1]
3. If characters don't match, take 1 + min of insert, delete, and replace.
4. Base case: Converting to/from empty string costs the length of the other string.

SAMPLE INPUT:
horse
ros

SAMPLE OUTPUT:
3

EXPLANATION:
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')
Total = 3 operations.

RECURRENCE RELATION:
dp[i][j] = dp[i-1][j-1]                               if word1[i-1] == word2[j-1]
dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]}) otherwise

TIME COMPLEXITY:
O(m * n)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming - 2D String Alignment
*/

//---------Distinct Subsequences (LeetCode 115)

#include <bits/stdc++.h>
using namespace std;

int numDistinct(string s, string t)
{
    int m = s.size();
    int n = t.size();

    // dp[j] = count of distinct occurrences of t[0..j-1] in s
    vector<unsigned long long> dp(n + 1, 0);
    dp[0] = 1; // Empty string t is formed 1 way (empty subsequence)

    for(int i = 1; i <= m; i++)
    {
        // Backward traversal to use results from previous row
        for(int j = n; j >= 1; j--)
        {
            if(s[i - 1] == t[j - 1])
            {
                dp[j] = dp[j] + dp[j - 1];
            }
        }
    }

    return dp[n];
}

int main()
{
    string s, t;
    if(cin >> s >> t)
    {
        cout << numDistinct(s, t) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[i][j] counts the number of times t[0..j-1] appears as a subsequence in s[0..i-1].
2. If s[i-1] == t[j-1]:
   - Match s[i-1] with t[j-1]: dp[i-1][j-1]
   - Skip s[i-1]: dp[i-1][j]
   - dp[i][j] = dp[i-1][j-1] + dp[i-1][j]
3. If s[i-1] != t[j-1]:
   - Must skip s[i-1]: dp[i][j] = dp[i-1][j].
4. Space optimized to 1D array of size n+1 traversing backwards.

SAMPLE INPUT:
rabbbit
rabbit

SAMPLE OUTPUT:
3

EXPLANATION:
There are 3 ways to form "rabbit" by deleting one of the three 'b's in "rabbbit".

TIME COMPLEXITY:
O(m * n)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming - Subsequence Counting
*/

//---------Wildcard Matching (LeetCode 44)

#include <bits/stdc++.h>
using namespace std;

bool isMatchWildcard(string s, string p)
{
    int m = s.size();
    int n = p.size();

    vector<bool> prev(n + 1, false), curr(n + 1, false);
    prev[0] = true;

    // Pattern matching empty string: only '*' can match empty
    for(int j = 1; j <= n; j++)
    {
        if(p[j - 1] == '*') prev[j] = prev[j - 1];
    }

    for(int i = 1; i <= m; i++)
    {
        curr[0] = false; // Non-empty string cannot match empty pattern
        for(int j = 1; j <= n; j++)
        {
            if(p[j - 1] == s[i - 1] || p[j - 1] == '?')
            {
                curr[j] = prev[j - 1];
            }
            else if(p[j - 1] == '*')
            {
                // '*' matches empty sequence (curr[j-1]) OR one/more characters (prev[j])
                curr[j] = curr[j - 1] || prev[j];
            }
            else
            {
                curr[j] = false;
            }
        }
        prev = curr;
    }

    return prev[n];
}

int main()
{
    string s, p;
    if(cin >> s >> p)
    {
        cout << (isMatchWildcard(s, p) ? "true" : "false") << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. '?' matches any single character.
2. '*' matches any sequence of characters (including empty).
3. If p[j-1] == s[i-1] or p[j-1] == '?':
   dp[i][j] = dp[i-1][j-1].
4. If p[j-1] == '*':
   - '*' matches empty string: dp[i][j-1]
   - '*' matches current char and can match more: dp[i-1][j]
   - dp[i][j] = dp[i][j-1] || dp[i-1][j].
5. Space optimized to O(n).

SAMPLE INPUT:
adceb
*a*b

SAMPLE OUTPUT:
true

EXPLANATION:
First '*' matches empty, second '*' matches "dce". Entire pattern matches.

TIME COMPLEXITY:
O(m * n)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming - 2D Pattern Matching with Wildcards
*/

//---------Regular Expression Matching (LeetCode 10)

#include <bits/stdc++.h>
using namespace std;

bool isMatchRegex(string s, string p)
{
    int m = s.size();
    int n = p.size();

    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
    dp[0][0] = true;

    // Deals with patterns like a*, a*b*, a*b*c* matching empty string
    for(int j = 2; j <= n; j += 2)
    {
        if(p[j - 1] == '*')
        {
            dp[0][j] = dp[0][j - 2];
        }
    }

    for(int i = 1; i <= m; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(p[j - 1] == '.' || p[j - 1] == s[i - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else if(p[j - 1] == '*')
            {
                // Option 1: 0 occurrences of character preceding '*'
                dp[i][j] = dp[i][j - 2];

                // Option 2: 1 or more occurrences if preceding char matches
                char prevChar = p[j - 2];
                if(prevChar == '.' || prevChar == s[i - 1])
                {
                    dp[i][j] = dp[i][j] || dp[i - 1][j];
                }
            }
        }
    }

    return dp[m][n];
}

int main()
{
    string s, p;
    if(cin >> s >> p)
    {
        cout << (isMatchRegex(s, p) ? "true" : "false") << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. '.' matches any single character.
2. '*' matches zero or more of the PRECEDING element.
3. If p[j-1] == '.' or p[j-1] == s[i-1]:
   dp[i][j] = dp[i-1][j-1].
4. If p[j-1] == '*':
   - 0 occurrences of preceding element p[j-2]: dp[i][j-2].
   - 1 or more occurrences (if p[j-2] matches s[i-1]): dp[i-1][j].
5. Base case: empty string matches empty pattern (dp[0][0] = true).

SAMPLE INPUT:
aab
c*a*b

SAMPLE OUTPUT:
true

EXPLANATION:
'c*' counts as 0 'c', 'a*' counts as two 'a', and 'b' matches 'b'.

TIME COMPLEXITY:
O(m * n)

SPACE COMPLEXITY:
O(m * n)

PATTERN:
Dynamic Programming - Regex Kleene Star State Machine
*/

//====================================================================
// SECTION 3: PARTITION DP & MATRIX CHAIN MULTIPLICATION
//====================================================================

//---------Matrix Chain Multiplication (MCM)

#include <bits/stdc++.h>
using namespace std;

int matrixMultiplication(vector<int>& arr)
{
    int n = arr.size(); // n elements means (n - 1) matrices
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // len is the length of matrix chain
    for(int len = 2; len < n; len++)
    {
        for(int i = 1; i < n - len + 1; i++)
        {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;

            for(int k = i; k < j; k++)
            {
                int cost = dp[i][k] + dp[k + 1][j] + arr[i - 1] * arr[k] * arr[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    return dp[1][n - 1];
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> arr(n);
        for(int i = 0; i < n; i++) cin >> arr[i];
        cout << matrixMultiplication(arr) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. Matrix Ai has dimensions arr[i-1] x arr[i].
2. dp[i][j] is the minimum operations to multiply matrices from Ai to Aj.
3. For any split point k (i <= k < j):
   cost = dp[i][k] + dp[k+1][j] + arr[i-1] * arr[k] * arr[j].
4. dp[i][j] = min_{i <= k < j} (cost).
5. Chain length len goes from 2 to n-1.

SAMPLE INPUT:
5
40 20 30 10 30

SAMPLE OUTPUT:
26000

EXPLANATION:
4 matrices: (40x20), (20x30), (30x10), (10x30).
Optimal parenthesization: ((A(BC))D) -> cost = 26000 operations.

RECURRENCE RELATION:
dp[i][j] = min_{i <= k < j} (dp[i][k] + dp[k+1][j] + arr[i-1] * arr[k] * arr[j])

TIME COMPLEXITY:
O(n^3)

SPACE COMPLEXITY:
O(n^2)

PATTERN:
Dynamic Programming - Matrix Chain Multiplication / Interval DP
*/

//---------Palindrome Partitioning II (Min Cuts) (LeetCode 132)

#include <bits/stdc++.h>
using namespace std;

int minCut(string s)
{
    int n = s.size();
    if(n <= 1) return 0;

    // isPal[i][j] = true if s[i..j] is a palindrome
    vector<vector<bool>> isPal(n, vector<bool>(n, false));

    for(int i = n - 1; i >= 0; i--)
    {
        for(int j = i; j < n; j++)
        {
            if(s[i] == s[j] && (j - i <= 2 || isPal[i + 1][j - 1]))
            {
                isPal[i][j] = true;
            }
        }
    }

    // dp[i] = minimum cuts needed for substring s[0..i]
    vector<int> dp(n, 0);

    for(int i = 0; i < n; i++)
    {
        if(isPal[0][i])
        {
            dp[i] = 0; // Entire prefix is already palindrome, 0 cuts needed
        }
        else
        {
            dp[i] = i; // Worst case: cut every character
            for(int j = 0; j < i; j++)
            {
                if(isPal[j + 1][i])
                {
                    dp[i] = min(dp[i], dp[j] + 1);
                }
            }
        }
    }

    return dp[n - 1];
}

int main()
{
    string s;
    if(cin >> s)
    {
        cout << minCut(s) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. Precompute isPal[i][j] in O(n^2) time:
   isPal[i][j] is true if s[i] == s[j] and isPal[i+1][j-1] is true.
2. dp[i] is the minimum cuts needed for s[0..i].
3. If s[0..i] is already a palindrome: dp[i] = 0.
4. Otherwise, test all potential cuts at position j (0 <= j < i):
   If s[j+1..i] is a palindrome, cut after j: dp[i] = min(dp[i], dp[j] + 1).

SAMPLE INPUT:
aab

SAMPLE OUTPUT:
1

EXPLANATION:
Cut after 'aa' to produce palindromes ["aa", "b"]. 1 cut.

TIME COMPLEXITY:
O(n^2)

SPACE COMPLEXITY:
O(n^2)

PATTERN:
Dynamic Programming - 1D Partition DP with 2D Palindrome Lookup
*/

//---------Boolean Parenthesization / Evaluate Expression to True

#include <bits/stdc++.h>
using namespace std;

int countWaysBoolean(string exp)
{
    int n = exp.length();
    const int MOD = 1003;

    // dpT[i][j] = ways exp[i..j] evaluates to True
    // dpF[i][j] = ways exp[i..j] evaluates to False
    vector<vector<int>> dpT(n, vector<int>(n, 0));
    vector<vector<int>> dpF(n, vector<int>(n, 0));

    // Base cases: single boolean operands at even indices
    for(int i = 0; i < n; i += 2)
    {
        dpT[i][i] = (exp[i] == 'T') ? 1 : 0;
        dpF[i][i] = (exp[i] == 'F') ? 1 : 0;
    }

    // Interval length of operands (step by 2)
    for(int len = 3; len <= n; len += 2)
    {
        for(int i = 0; i <= n - len; i += 2)
        {
            int j = i + len - 1;

            // Try each operator at odd index k between i and j
            for(int k = i + 1; k < j; k += 2)
            {
                char op = exp[k];

                int lT = dpT[i][k - 1], lF = dpF[i][k - 1];
                int rT = dpT[k + 1][j], rF = dpF[k + 1][j];

                if(op == '&')
                {
                    dpT[i][j] = (dpT[i][j] + lT * rT) % MOD;
                    dpF[i][j] = (dpF[i][j] + lF * rT + lT * rF + lF * rF) % MOD;
                }
                else if(op == '|')
                {
                    dpT[i][j] = (dpT[i][j] + lT * rT + lT * rF + lF * rT) % MOD;
                    dpF[i][j] = (dpF[i][j] + lF * rF) % MOD;
                }
                else if(op == '^')
                {
                    dpT[i][j] = (dpT[i][j] + lT * rF + lF * rT) % MOD;
                    dpF[i][j] = (dpF[i][j] + lT * rT + lF * rF) % MOD;
                }
            }
        }
    }

    return dpT[0][n - 1];
}

int main()
{
    string exp;
    if(cin >> exp)
    {
        cout << countWaysBoolean(exp) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. Expression contains operands ('T', 'F') at even indices and operators ('&', '|', '^') at odd indices.
2. Track both True count (dpT) and False count (dpF) for each subexpression [i..j].
3. For operator at index k:
   - '&': True = lT * rT; False = lF * rT + lT * rF + lF * rF
   - '|': True = lT * rT + lT * rF + lF * rT; False = lF * rF
   - '^': True = lT * rF + lF * rT; False = lT * rT + lF * rF
4. dpT[0][n-1] holds total parenthesizations evaluating to True.

SAMPLE INPUT:
T|T&F^T

SAMPLE OUTPUT:
4

TIME COMPLEXITY:
O(n^3)

SPACE COMPLEXITY:
O(n^2)

PATTERN:
Dynamic Programming - Matrix Chain Multiplication with Truth Tables
*/


//====================================================================
// SECTION 4: 0/1 KNAPSACK & TARGET SUM
//====================================================================

//---------0/1 Knapsack Problem (Standard)

#include <bits/stdc++.h>
using namespace std;

int knapSack01(int W, vector<int>& wt, vector<int>& val, int n)
{
    // dp[w] = maximum value achievable with weight limit w
    vector<int> dp(W + 1, 0);

    for(int i = 0; i < n; i++)
    {
        // Traverse backwards so each item is used at most once
        for(int w = W; w >= wt[i]; w--)
        {
            dp[w] = max(dp[w], val[i] + dp[w - wt[i]]);
        }
    }

    return dp[W];
}

int main()
{
    int n, W;
    if(cin >> n >> W)
    {
        vector<int> val(n), wt(n);
        for(int i = 0; i < n; i++) cin >> val[i];
        for(int i = 0; i < n; i++) cin >> wt[i];
        cout << knapSack01(W, wt, val, n) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[w] stores the maximum value attainable with capacity w.
2. For each item with weight wt[i] and value val[i]:
   - Iterate weight w backwards from W down to wt[i].
   - Either take the item: val[i] + dp[w - wt[i]]
   - Or don't take it: dp[w]
3. dp[w] = max(dp[w], val[i] + dp[w - wt[i]]).
4. Backward loop avoids multiple inclusions of the same item.

SAMPLE INPUT:
3 4
1 2 3
4 5 1

SAMPLE OUTPUT:
3

TIME COMPLEXITY:
O(n * W)

SPACE COMPLEXITY:
O(W)

PATTERN:
Dynamic Programming - Classic 0/1 Knapsack
*/

//---------Coin Change (Minimum Coins to make sum) (LeetCode 322)

#include <bits/stdc++.h>
using namespace std;

int coinChangeMin(vector<int>& coins, int amount)
{
    // dp[i] = minimum coins needed to make amount i
    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;

    for(int coin : coins)
    {
        for(int i = coin; i <= amount; i++)
        {
            dp[i] = min(dp[i], dp[i - coin] + 1);
        }
    }

    return (dp[amount] > amount) ? -1 : dp[amount];
}

int main()
{
    int n, amount;
    if(cin >> n >> amount)
    {
        vector<int> coins(n);
        for(int i = 0; i < n; i++) cin >> coins[i];
        cout << coinChangeMin(coins, amount) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[i] stores the minimum number of coins needed for amount i.
2. Initialize dp with amount + 1 (representing infinity) and dp[0] = 0.
3. For each coin, iterate amount i forwards from coin to amount:
   dp[i] = min(dp[i], dp[i - coin] + 1).
4. Forward traversal allows using each coin denomination infinitely.
5. If dp[amount] remains > amount, amount cannot be formed; return -1.

SAMPLE INPUT:
3 11
1 2 5

SAMPLE OUTPUT:
3

EXPLANATION:
11 = 5 + 5 + 1 (3 coins).

TIME COMPLEXITY:
O(n * amount)

SPACE COMPLEXITY:
O(amount)

PATTERN:
Dynamic Programming - Unbounded Knapsack Minimization
*/

//---------Target Sum (LeetCode 494)

#include <bits/stdc++.h>
using namespace std;

int findTargetSumWays(vector<int>& nums, int target)
{
    int totalSum = 0;
    for(int x : nums) totalSum += x;

    // Subsets P (positive) and N (negative): sum(P) - sum(N) = target
    // Also: sum(P) + sum(N) = totalSum
    // Adding both: 2 * sum(P) = target + totalSum
    // => sum(P) = (target + totalSum) / 2
    if((target + totalSum) % 2 != 0 || totalSum < abs(target))
        return 0;

    int s1 = (target + totalSum) / 2;
    vector<int> dp(s1 + 1, 0);
    dp[0] = 1;

    for(int num : nums)
    {
        for(int j = s1; j >= num; j--)
        {
            dp[j] += dp[j - num];
        }
    }

    return dp[s1];
}

int main()
{
    int n, target;
    if(cin >> n >> target)
    {
        vector<int> nums(n);
        for(int i = 0; i < n; i++) cin >> nums[i];
        cout << findTargetSumWays(nums, target) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. Assign '+' or '-' to each element to reach target.
2. Partition into two subsets: P (with '+') and N (with '-').
   sum(P) - sum(N) = target
   sum(P) + sum(N) = totalSum
   2 * sum(P) = target + totalSum  => sum(P) = (target + totalSum) / 2.
3. Problem reduces to finding number of subsets with sum = (target + totalSum) / 2.
4. If (target + totalSum) is odd or totalSum < abs(target), return 0.

SAMPLE INPUT:
5 3
1 1 1 1 1

SAMPLE OUTPUT:
5

EXPLANATION:
-1+1+1+1+1 = 3 (and 4 other combinations). Total = 5.

TIME COMPLEXITY:
O(n * s1)

SPACE COMPLEXITY:
O(s1)

PATTERN:
Dynamic Programming - Target Sum Reduction to Subset Sum
*/

//====================================================================
// SECTION 5: TREE DYNAMIC PROGRAMMING
//====================================================================

//---------House Robber III (Tree DP) (LeetCode 337)

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Returns pair: {max if root is robbed, max if root is NOT robbed}
pair<int, int> robDFS(TreeNode* root)
{
    if(!root) return {0, 0};

    auto left = robDFS(root->left);
    auto right = robDFS(root->right);

    // If we rob root: cannot rob immediate children
    int robThis = root->val + left.second + right.second;

    // If we don't rob root: we can either rob or not rob each child
    int notRobThis = max(left.first, left.second) + max(right.first, right.second);

    return {robThis, notRobThis};
}

int robTree(TreeNode* root)
{
    auto res = robDFS(root);
    return max(res.first, res.second);
}

int main()
{
    // Demonstration on simple tree: [3, 2, 3, null, 3, null, 1]
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(3);
    root->right->right = new TreeNode(1);

    cout << robTree(root) << "\n";
    return 0;
}

/*
MAIN LOGIC:
1. Cannot rob two directly-linked nodes in a binary tree.
2. For each node, return a pair of values:
   - robThis: Maximum money if this node is robbed.
   - notRobThis: Maximum money if this node is NOT robbed.
3. If node is robbed:
   robThis = node->val + left.notRobThis + right.notRobThis.
4. If node is not robbed:
   notRobThis = max(left.robThis, left.notRobThis) + max(right.robThis, right.notRobThis).
5. Post-order DFS visits children first, computing optimal values bottom-up.

SAMPLE OUTPUT:
7

EXPLANATION:
Rob root (3), left child's child (3), and right child's child (1) -> 3 + 3 + 1 = 7.

TIME COMPLEXITY:
O(V) where V is number of tree nodes

SPACE COMPLEXITY:
O(H) recursion stack where H is tree height

PATTERN:
Dynamic Programming on Trees - State Pair Post-Order Traversal
*/

//---------Binary Tree Maximum Path Sum (LeetCode 124)

#include <bits/stdc++.h>
using namespace std;

int maxPathSumDFS(TreeNode* node, int& globalMax)
{
    if(!node) return 0;

    // Ignore paths with negative contributions by taking max with 0
    int leftGain = max(0, maxPathSumDFS(node->left, globalMax));
    int rightGain = max(0, maxPathSumDFS(node->right, globalMax));

    // Path turning through this node
    int currentPathSum = node->val + leftGain + rightGain;
    globalMax = max(globalMax, currentPathSum);

    // Return maximum contribution this node can give to its parent
    return node->val + max(leftGain, rightGain);
}

int maxPathSum(TreeNode* root)
{
    int globalMax = INT_MIN;
    maxPathSumDFS(root, globalMax);
    return globalMax;
}

int main()
{
    TreeNode* root = new TreeNode(-10);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    cout << maxPathSum(root) << "\n";
    return 0;
}

/*
MAIN LOGIC:
1. A path can turn through any node as the root of the path:
   pathSum = node->val + max(0, leftGain) + max(0, rightGain).
2. Update globalMax with this sum.
3. To return to the parent node, the path can only continue down ONE branch:
   return node->val + max(leftGain, rightGain).
4. Negative subtree sums are pruned using max(0, subtreeSum).

SAMPLE OUTPUT:
42

EXPLANATION:
Optimal path is 15 -> 20 -> 7, sum = 15 + 20 + 7 = 42.

TIME COMPLEXITY:
O(V)

SPACE COMPLEXITY:
O(H)

PATTERN:
Dynamic Programming on Trees - Path Decomposition & Branch Selection
*/

//====================================================================
// SECTION 6: BITMASK DYNAMIC PROGRAMMING
//====================================================================

//---------Traveling Salesperson Problem (TSP) / Shortest Hamiltonian Cycle

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int tsp(int mask, int u, int n, vector<vector<int>>& dist, vector<vector<int>>& dp)
{
    // All cities visited: return distance back to starting city 0
    if(mask == (1 << n) - 1)
    {
        return dist[u][0];
    }

    if(dp[mask][u] != -1)
        return dp[mask][u];

    int ans = INF;

    // Try visiting all unvisited cities v
    for(int v = 0; v < n; v++)
    {
        if(!(mask & (1 << v)))
        {
            int newCost = dist[u][v] + tsp(mask | (1 << v), v, n, dist, dp);
            ans = min(ans, newCost);
        }
    }

    return dp[mask][u] = ans;
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<vector<int>> dist(n, vector<int>(n));
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++) cin >> dist[i][j];
        }

        // dp[mask][u]: min cost to visit remaining unvisited cities starting at u
        vector<vector<int>> dp(1 << n, vector<int>(n, -1));

        // Start at city 0 with mask containing only city 0 (1 << 0)
        cout << tsp(1, 0, n, dist, dp) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. State: (mask, u)
   - mask: bitmask of length n where i-th bit = 1 indicates city i has been visited.
   - u: current city.
2. Base case: When mask == (1 << n) - 1 (all bits set), all cities are visited;
   return distance from u back to origin (dist[u][0]).
3. Transition:
   For each unvisited city v (where !(mask & (1 << v))):
   dp(mask, u) = min(dp(mask, u), dist[u][v] + dp(mask | (1 << v), v)).
4. Total states = 2^n * n, each taking O(n) transitions.

SAMPLE INPUT:
4
0 10 15 20
10 0 35 25
15 35 0 30
20 25 30 0

SAMPLE OUTPUT:
80

EXPLANATION:
Path: 0 -> 1 -> 3 -> 2 -> 0: cost 10 + 25 + 30 + 15 = 80.

RECURRENCE RELATION:
dp(mask, u) = min_{v not in mask} (dist[u][v] + dp(mask | {v}, v))

TIME COMPLEXITY:
O(2^n * n^2)

SPACE COMPLEXITY:
O(2^n * n)

PATTERN:
Dynamic Programming with Bitmasking (Held-Karp Algorithm)
*/
