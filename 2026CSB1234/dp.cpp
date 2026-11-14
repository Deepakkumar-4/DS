


//------ Longest Common Subsequence

#include <bits/stdc++.h>
using namespace std;

int dp[1005][1005];

int LCS(string s, string t, int n, int m)
{
    if(n == 0 || m == 0)
        return 0;

    if(dp[n][m] != -1)
        return dp[n][m];

    if(s[n-1] == t[m-1])
        return dp[n][m] = 1 + LCS(s, t, n-1, m-1);

    else
        return dp[n][m] = max(LCS(s, t, n-1, m),
                              LCS(s, t, n, m-1));
}

int main()
{
    string s, t;
    cin >> s >> t;

    memset(dp, -1, sizeof(dp));

    cout << LCS(s, t, s.length(), t.length());

    return 0;
    /*
    Main Logic
1. Base Condition: If either string becomes empty (n == 0 || m == 0), return 0.
2. Memoization: If dp[n][m] != -1, return the already calculated answer.
3. If characters match: Add 1 and move both strings backwards.
4. If characters don't match: Try two possibilities:
   - Exclude the last character of the first string.
   - Exclude the last character of the second string.
   Take the maximum of both results.
Sample Input:
abcdgh
abedfhq


Output:
4


Longest Common Subsequence = abdh.
3. Recurrence Relation
\[
LCS(n,m)=
\begin{cases}
0 & n=0 \text{ or } m=0\\
1+LCS(n-1,m-1) & s[n-1]=t[m-1]\\
\max(LCS(n-1,m),LCS(n,m-1)) & \text{otherwise}
\end{cases}
\]

4. Complexity
- Time Complexity: \(O(n\times m)\)
- Space Complexity: \(O(n\times m)\) for DP array, plus recursion stack \(O(n+m)\).*/
}
//----------------maximun length of subarray

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n;

    vector<int> nums1(n);
    for(int i = 0; i < n; i++)
        cin >> nums1[i];

    cin >> m;

    vector<int> nums2(m);
    for(int i = 0; i < m; i++)
        cin >> nums2[i];

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    int ans = 0;

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            if(nums1[i-1] == nums2[j-1])
            {
                dp[i][j] = 1 + dp[i-1][j-1];
                ans = max(ans, dp[i][j]);
            }
            else
            {
                dp[i][j] = 0;
            }
        }
    }

    cout << ans;

    return 0;
    /*Main Logic
1. Initialize a 2D DP array with zeros.
2. Compare each element of nums1 with each element of nums2.
3. If elements match: Add 1 to the previous diagonal value (dp[i-1][j-1]).
4. If elements don't match: Set dp[i][j] = 0 because the continuous subarray breaks.
5. Maintain a variable ans to store the maximum value found in the DP table.
6. Finally, return ans.
Sample Input:
5
1 2 3 2 1
5
3 2 1 4 7


Output:
3


Explanation: The longest common continuous subarray is [3, 2, 1], having length 3.
3. Recurrence Relation
Let dp[i][j] represent the length of the longest common subarray ending at nums1[i-1] and nums2[j-1].
\[
dp[i][j]=
\begin{cases}
1+dp[i-1][j-1] & nums1[i-1]=nums2[j-1]\\
0 & \text{otherwise}
\end{cases}
\]

Final Answer:
\[
\boxed{ans=\max(dp[i][j])}
\]

4. Complexity
- Time Complexity: \(O(n\times m)\)
- Space Complexity: \(O(n\times m)\)
Important: Unlike LCS, when elements do not match, we set DP to zero because a subarray must be continuous.*/
}
//---------------longest palindromic subsequence's

#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    cin >> s;

    string t = s;
    reverse(t.begin(), t.end());

    int n = s.length();

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(s[i-1] == t[j-1])
            {
                dp[i][j] = 1 + dp[i-1][j-1];
            }
            else
            {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    cout << dp[n][n];

    return 0;
    /*Main Logic
1. Take the input string s.
2. Create another string t by reversing s.
3. Initialize a 2D DP array with zeros.
4. Compare characters of both strings:
   - If characters match: dp[i][j] = 1 + dp[i-1][j-1].
   - If characters don't match: Take the maximum of the top and left DP values.
5. The final answer is dp[n][n].
Sample Input:
bbbab


Output:
4


Explanation: The longest palindromic subsequence is bbbb, having length 4.
3. Recurrence Relation
Let dp[i][j] represent the LCS length of the first i characters of s and first j characters of its reverse t.
\[
dp[i][j]=
\begin{cases}
1+dp[i-1][j-1] & s[i-1]=t[j-1]\\
\max(dp[i-1][j],dp[i][j-1]) & \text{otherwise}
\end{cases}
\]

Base Condition:
\[
dp[0][j]=dp[i][0]=0
\]

Final Answer:
\[
\boxed{LPS=dp[n][n]}
\]

4. Complexity
- Time Complexity: \(O(n^2)\)
- Space Complexity: \(O(n^2)\)
Important: LPS can be solved by simply finding LCS between the original string and its reverse.*/
}
//-------------Minimum Insertion Steps to Make a String Palindrome

#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    cin >> s;

    string t = s;
    reverse(t.begin(), t.end());

    int n = s.length();

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(s[i-1] == t[j-1])
            {
                dp[i][j] = 1 + dp[i-1][j-1];
            }
            else
            {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    int lps = dp[n][n];

    int ans = n - lps;

    cout << ans;

    return 0;
    /*Main Logic
1. Take the input string s.
2. Reverse the string and store it in t.
3. Calculate LCS of s and t using a 2D DP table.
4. Store the LCS result as lps.
5. Calculate minimum insertions using:
\[
\boxed{Answer=n-LPS}
\]

Sample Input:
mbadm


Output:
2


Explanation:
- Original string = mbadm
- Longest Palindromic Subsequence = mam
- LPS length = 3
- Minimum insertions = 5 − 3 = 2.
One possible palindrome is mbdadbm.
3. Recurrence Relation
First, calculate LPS using LCS:
\[
dp[i][j]=
\begin{cases}
1+dp[i-1][j-1] & s[i-1]=t[j-1]\\
\max(dp[i-1][j],dp[i][j-1]) & \text{otherwise}
\end{cases}
\]

Base Condition:
\[
dp[0][j]=dp[i][0]=0
\]

Final formula:
\[
\boxed{Minimum\ Insertions=n-dp[n][n]}
\]

4. Complexity
- Time Complexity: \(O(n^2)\)
- Space Complexity: \(O(n^2)\)
Important: Minimum insertions required to make a string palindrome = String Length − Longest Palindromic Subsequence.*/
}
///-------------Is Subsequence

#include <bits/stdc++.h>
using namespace std;

bool isSubsequence(string s, string t)
{
    int n = s.size();
    int m = t.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            if(s[i-1] == t[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    return dp[n][m] == n;
}

int main()
{
    string s, t;
    cin >> s >> t;

    if(isSubsequence(s, t))
        cout << "true";
    else
        cout << "false";

    return 0;
    /*Main Logic
1. Take two input strings s and t.
2. Initialize a 2D DP array with zeros.
3. Compare characters of both strings:
   - If characters match: Add 1 to the diagonal value.
   - If characters don't match: Take the maximum of the top and left values.
4. After filling the DP table, check whether dp[n][m] == n.
5. If true, return true; otherwise, return false.
Sample Input:
abc
ahbgdc


Output:
true


Explanation: The characters a, b, and c appear in the same order in ahbgdc. Therefore, abc is a subsequence of ahbgdc.
3. Recurrence Relation
Let dp[i][j] represent the LCS length of the first i characters of s and first j characters of t.
\[
dp[i][j]=
\begin{cases}
1+dp[i-1][j-1] & s[i-1]=t[j-1]\\
\max(dp[i-1][j],dp[i][j-1]) & \text{otherwise}
\end{cases}
\]

Base Condition:
\[
dp[0][j]=dp[i][0]=0
\]

Final Condition:
\[
\boxed{dp[n][m]==n}
\]

If true, s is a subsequence of t.
4. Complexity
- Time Complexity: \(O(n\times m)\)
- Space Complexity: \(O(n\times m)\)
Important: A string s is a subsequence of t if and only if LCS(s,t) == length(s).*/
}
//---------------Delete Operation for Two Strings

#include <bits/stdc++.h>
using namespace std;

int minDistance(string word1, string word2)
{
    int n = word1.size();
    int m = word2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            if(word1[i-1] == word2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    int lcs = dp[n][m];

    return (n - lcs) + (m - lcs);
}

int main()
{
    string word1, word2;
    cin >> word1 >> word2;

    cout << minDistance(word1, word2);

    return 0;
    /*1. Take two input strings word1 and word2.
2. Calculate the LCS of both strings using a 2D DP table.
3. Store the LCS length in lcs.
4. Calculate the remaining characters in each string:
   - Deletions from word1 = n - lcs.
   - Deletions from word2 = m - lcs.
5. Add both deletion counts to get the minimum operations.
Formula:
\[
\boxed{Answer=(n-LCS)+(m-LCS)}
\]

Sample Input:
sea
eat


Output:
2


Explanation:
- LCS of sea and eat = ea.
- LCS length = 2.
- Delete s from sea and t from eat.
- Both strings become ea.
Total deletions = 1 + 1 = 2.
3. Recurrence Relation
Let dp[i][j] represent the LCS length of the first i characters of word1 and first j characters of word2.
\[
dp[i][j]=
\begin{cases}
1+dp[i-1][j-1] & word1[i-1]=word2[j-1]\\
\max(dp[i-1][j],dp[i][j-1]) & \text{otherwise}
\end{cases}
\]

Base Condition:
\[
dp[0][j]=dp[i][0]=0
\]

Final Answer:
\[
\boxed{(n-dp[n][m])+(m-dp[n][m])}
\]

4. Complexity
- Time Complexity: \(O(n\times m)\)
- Space Complexity: \(O(n\times m)\)
Important: Whenever two strings must be made identical using only deletion operations, think of LCS. Keep the common subsequence and delete all remaining characters.*/
}
//----------------Shortest Common Supersequence

#include <bits/stdc++.h>
using namespace std;

int main()
{
    string str1, str2;
    cin >> str1 >> str2;

    int n = str1.size();
    int m = str2.size();

    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            if(str1[i-1] == str2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    int i = n, j = m;
    string ans = "";

    while(i > 0 && j > 0)
    {
        if(str1[i-1] == str2[j-1])
        {
            ans += str1[i-1];
            i--;
            j--;
        }
        else if(dp[i-1][j] > dp[i][j-1])
        {
            ans += str1[i-1];
            i--;
        }
        else
        {
            ans += str2[j-1];
            j--;
        }
    }

    while(i > 0)
    {
        ans += str1[i-1];
        i--;
    }

    while(j > 0)
    {
        ans += str2[j-1];
        j--;
    }

    reverse(ans.begin(), ans.end());

    cout << ans;

    return 0;
}
/*1. Create a DP table to calculate LCS.
2. If characters match, take diagonal value + 1.
3. If characters don't match, take maximum of top and left values.
4. Start traversing the DP table backwards:
   - If characters match, add the character once and move diagonally.
   - Otherwise, add the character from the direction with the larger DP value.
5. Add any remaining characters.
6. Reverse the answer because we built it backwards.
3. Sample Input and Output
Input:
abac
cab


Output:
cabac


Explanation:
- String 1 = abac
- String 2 = cab
- LCS = ab
- The common characters are included only once.
Therefore, the shortest common supersequence is cabac, with length 5.
4. Recurrence Relation
The DP table uses the standard LCS recurrence:
\[
dp[i][j]=
\begin{cases}
1+dp[i-1][j-1] & \text{if characters match}\\
\max(dp[i-1][j],dp[i][j-1]) & \text{otherwise}
\end{cases}
\]

Base Case:
\[
dp[0][j]=dp[i][0]=0
\]

Length of SCS:
\[
\boxed{SCS=n+m-LCS}
\]

Here, the program reconstructs the actual SCS string, not just its length.
5. Complexity
- Time Complexity: \(O(n \times m)\)
- Space Complexity: \(O(n \times m)\)
Where \(n\) and \(m\) are the lengths of the two strings.*/
///--------  palindrome valid after at most one deletion

#include <bits/stdc++.h>
using namespace std;

bool checkPalindrome(string s, int left, int right)
{
    while(left < right)
    {
        if(s[left] != s[right])
        {
            return false;
        }

        left++;
        right--;
    }

    return true;
}

bool validPalindrome(string s)
{
    int left = 0;
    int right = s.length() - 1;

    while(left < right)
    {
        if(s[left] != s[right])
        {
            return checkPalindrome(s, left + 1, right) ||
                   checkPalindrome(s, left, right - 1);
        }

        left++;
        right--;
    }

    return true;
}

int main()
{
    string s;
    cin >> s;

    if(validPalindrome(s))
        cout << "true";
    else
        cout << "false";

    return 0;
}

/*
MAIN LOGIC:
1. Take two pointers: left = 0 and right = n-1.
2. Compare characters at both positions.
3. If characters match, move left forward and right backward.
4. If characters do not match, try two possibilities:
   a) Delete the left character.
   b) Delete the right character.
5. Check whether either remaining substring is a palindrome.
6. If any one possibility works, return true.
   Otherwise, return false.

SAMPLE INPUT:
abca

SAMPLE OUTPUT:
true

EXPLANATION:
Compare first and last characters:
a == a (Match)

Now compare:
b != c (Mismatch)

Try deleting b:
aca -> Palindrome (TRUE)

Therefore, output is true.

RECURRENCE RELATION:
Let P(i,j) represent whether substring from
index i to j is a palindrome.

If s[i] == s[j]:
    P(i,j) = P(i+1,j-1)

If s[i] != s[j] and deletion is available:
    P(i,j) = P(i+1,j) OR P(i,j-1)

NOTE:
This is a conceptual recurrence, not a DP
implementation. We use Two Pointers + Greedy.

TIME COMPLEXITY:
O(n)

A maximum of two linear scans are performed.

SPACE COMPLEXITY:
O(1) auxiliary space.
*/
//--------------burst Balloons

#include <bits/stdc++.h>
using namespace std;

int maxCoins(vector<int>& nums)
{
    int n = nums.size();

    // Add 1 at the beginning and end
    vector<int> a(n + 2, 1);

    for(int i = 0; i < n; i++)
    {
        a[i + 1] = nums[i];
    }

    // DP table
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

    // Length of current range
    for(int len = 1; len <= n; len++)
    {
        for(int i = 1; i <= n - len + 1; i++)
        {
            int j = i + len - 1;

            // Try every balloon as the last balloon
            for(int k = i; k <= j; k++)
            {
                int coins = a[i - 1] * a[k] * a[j + 1]
                          + dp[i][k - 1]
                          + dp[k + 1][j];

                dp[i][j] = max(dp[i][j], coins);
            }
        }
    }

    return dp[1][n];
}

int main()
{
    int n;
    cin >> n;

    vector<int> nums(n);

    for(int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    cout << maxCoins(nums);

    return 0;
}

/*
MAIN LOGIC:

1. Add 1 at the beginning and end of the array.
   Example: [3,1,5,8] becomes [1,3,1,5,8,1].

2. Create a 2D DP table.

3. dp[i][j] represents the maximum coins
   obtained by bursting all balloons from i to j.

4. Try every balloon k from i to j as the LAST
   balloon to burst.

5. Coins obtained by bursting k last:

   a[i-1] * a[k] * a[j+1]

6. Add the maximum coins from the left and
   right subproblems.

7. Take the maximum among all possible choices.

SAMPLE INPUT:
4
3 1 5 8

SAMPLE OUTPUT:
167

EXPLANATION:

One optimal bursting order:

[3,1,5,8]

Burst 1:
3 * 1 * 5 = 15

Remaining: [3,5,8]

Burst 5:
3 * 5 * 8 = 120

Remaining: [3,8]

Burst 3:
1 * 3 * 8 = 24

Remaining: [8]

Burst 8:
1 * 8 * 1 = 8

Total coins:
15 + 120 + 24 + 8 = 167

RECURRENCE RELATION:

Let dp[i][j] = maximum coins obtained
by bursting all balloons from i to j.

dp[i][j] = max over all k from i to j:

dp[i][k-1] + dp[k+1][j]
+ a[i-1] * a[k] * a[j+1]

BASE CASE:

dp[i][j] = 0 when i > j

TIME COMPLEXITY:
O(n^3)

Three nested loops are used.

SPACE COMPLEXITY:
O(n^2)

A 2D DP table is used.

PATTERN:
Dynamic Programming - Matrix Chain Multiplication (MCM)

IMPORTANT TRICK:
Think about which element to choose LAST,
not which element to choose FIRST.
*/
///-----------Minimum Score Triangulation of Polygon

#include <bits/stdc++.h>
using namespace std;

int minScoreTriangulation(vector<int>& values)
{
    int n = values.size();

    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Length of current polygon section
    for(int len = 3; len <= n; len++)
    {
        for(int i = 0; i <= n - len; i++)
        {
            int j = i + len - 1;

            dp[i][j] = INT_MAX;

            // Try every possible middle vertex
            for(int k = i + 1; k < j; k++)
            {
                int score = values[i] * values[k] * values[j]
                          + dp[i][k]
                          + dp[k][j];

                dp[i][j] = min(dp[i][j], score);
            }
        }
    }

    return dp[0][n - 1];
}

int main()
{
    int n;
    cin >> n;

    vector<int> values(n);

    for(int i = 0; i < n; i++)
    {
        cin >> values[i];
    }

    cout << minScoreTriangulation(values);

    return 0;
}

/*
MAIN LOGIC:

1. Create a 2D DP table.
2. dp[i][j] stores the minimum score needed
   to triangulate the polygon section from i to j.
3. Start with sections of length 3 because
   the smallest polygon section is a triangle.
4. Choose every possible middle vertex k.
5. Form a triangle using vertices i, k and j.
6. Calculate its weight:
   values[i] * values[k] * values[j]
7. Add the minimum scores of left and right
   polygon sections.
8. Take the minimum among all possibilities.

SAMPLE INPUT:
4
3 7 4 5

SAMPLE OUTPUT:
144

EXPLANATION:

First triangulation:
3*7*5 + 4*5*7 = 245

Second triangulation:
3*4*5 + 3*4*7 = 144

Minimum score = 144.

RECURRENCE RELATION:

dp[i][j] = min for all k from i+1 to j-1:

dp[i][k] + dp[k][j]
+ values[i] * values[k] * values[j]

BASE CASE:

dp[i][j] = 0 when j-i < 2

Because fewer than 3 vertices cannot
form a triangle.

TIME COMPLEXITY:
O(n^3)

SPACE COMPLEXITY:
O(n^2)

PATTERN:
Dynamic Programming - Matrix Chain Multiplication

IMPORTANT TRICK:
Choose a middle vertex k and form a triangle
with i, k and j.

Try every possible k and take the minimum.
*/
//----------------Minimum Cost Tree From Leaf Values.

#include <bits/stdc++.h>
using namespace std;

int mctFromLeafValues(vector<int>& arr)
{
    int n = arr.size();

    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Length of current range
    for(int len = 2; len <= n; len++)
    {
        for(int i = 0; i <= n - len; i++)
        {
            int j = i + len - 1;

            dp[i][j] = INT_MAX;

            // Try every possible partition
            for(int k = i; k < j; k++)
            {
                int leftMax = 0;
                int rightMax = 0;

                // Find maximum in left part
                for(int x = i; x <= k; x++)
                {
                    leftMax = max(leftMax, arr[x]);
                }

                // Find maximum in right part
                for(int x = k + 1; x <= j; x++)
                {
                    rightMax = max(rightMax, arr[x]);
                }

                int cost = dp[i][k] + dp[k + 1][j]
                         + leftMax * rightMax;

                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    return dp[0][n - 1];
}

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n);

    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << mctFromLeafValues(arr);

    return 0;
}

/*
MAIN LOGIC:

1. Create a 2D DP table.
2. dp[i][j] stores the minimum cost of
   constructing a tree using arr[i...j].
3. Start with ranges of length 2 because
   at least two leaves are needed to form a parent.
4. Try every possible partition k.
5. Find the maximum value in the left part.
6. Find the maximum value in the right part.
7. Calculate the new parent node value:

   leftMax * rightMax

8. Add left subtree cost and right subtree cost.
9. Take the minimum among all partitions.

SAMPLE INPUT:
3
6 2 4

SAMPLE OUTPUT:
32

EXPLANATION:

Possible tree 1:
6*2 + 6*4 = 12 + 24 = 36

Possible tree 2:
2*4 + 6*4 = 8 + 24 = 32

Minimum cost = 32.

RECURRENCE RELATION:

dp[i][j] = min over k from i to j-1:

dp[i][k] + dp[k+1][j]
+ max(arr[i...k]) * max(arr[k+1...j])

BASE CASE:

dp[i][i] = 0

A single leaf does not need a parent node.

TIME COMPLEXITY:
O(n^4)

Three nested DP loops plus the loops
used to calculate the maximum values.

SPACE COMPLEXITY:
O(n^2)

PATTERN:
Dynamic Programming - Matrix Chain Multiplication

IMPORTANT TRICK:
Split the array into left and right parts.
Multiply the maximum element of each part.
Add the costs of both subtrees.
Take the minimum.
*/
//---------------Guess Number Higher or Lower II

#include <bits/stdc++.h>
using namespace std;

int getMoneyAmount(int n)
{
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

    // Length of current range
    for(int len = 2; len <= n; len++)
    {
        for(int i = 1; i <= n - len + 1; i++)
        {
            int j = i + len - 1;

            dp[i][j] = INT_MAX;

            // Try every possible guess
            for(int k = i; k <= j; k++)
            {
                int cost = k + max(dp[i][k - 1],
                                   dp[k + 1][j]);

                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    return dp[1][n];
}

int main()
{
    int n;
    cin >> n;

    cout << getMoneyAmount(n);

    return 0;
}

/*
MAIN LOGIC:

1. Create a 2D DP table.
2. dp[i][j] represents the minimum money needed
   to guarantee winning between numbers i and j.
3. Try every possible guess k from i to j.
4. If the guess is wrong, we pay k dollars.
5. There are two possibilities:

   Lower number:
   dp[i][k-1]

   Higher number:
   dp[k+1][j]

6. Take MAX of both because we need to
   handle the worst possible case.
7. Add the cost of current guess k.
8. Take MIN among all possible guesses.

SAMPLE INPUT:
10

SAMPLE OUTPUT:
16

EXPLANATION:

For n = 10, one optimal first guess is 7.

If the number is higher:
Guess 9, then guess 8 or 10.

Worst cost = 7 + 9 = 16.

If the number is lower:
Guess 3 and continue optimally.

Worst cost = 7 + 5 + 3 = 15.

Overall minimum guaranteed money = 16.

RECURRENCE RELATION:

dp[i][j] = min over k from i to j:

k + max(dp[i][k-1], dp[k+1][j])

BASE CASE:

dp[i][j] = 0 when i >= j.

TIME COMPLEXITY:
O(n^3)

Three nested loops are used.

SPACE COMPLEXITY:
O(n^2)

A 2D DP table is used.

PATTERN:
Dynamic Programming - Matrix Chain Multiplication

IMPORTANT TRICK:

MIN of MAX:

1. MAX because we consider the worst case.
2. MIN because we choose the best first guess.

This is called minimax DP.
*/
//---------coin change problem

#include <bits/stdc++.h>
using namespace std;

long long getWays(int n, vector<int>& coins)
{
    vector<long long> dp(n + 1, 0);

    dp[0] = 1;

    for(int coin : coins)
    {
        for(int i = coin; i <= n; i++)
        {
            dp[i] = dp[i] + dp[i - coin];
        }
    }

    return dp[n];
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> coins(m);

    for(int i = 0; i < m; i++)
    {
        cin >> coins[i];
    }

    cout << getWays(n, coins);

    return 0;
}

/*
MAIN LOGIC:

1. Create a 1D DP array of size n+1.
2. dp[i] represents the number of ways to
   make amount i.
3. Initialize dp[0] = 1 because there is
   one way to make zero amount.
4. Traverse each coin denomination.
5. For every coin, traverse amounts from
   coin to n.
6. Update:

   dp[i] = dp[i] + dp[i-coin]

7. Finally, dp[n] gives the total number
   of ways to make the required amount.

SAMPLE INPUT:
4 3
1 2 3

SAMPLE OUTPUT:
4

EXPLANATION:

Using coins [1,2,3], amount = 4.

Possible combinations:

1. 1 + 1 + 1 + 1
2. 1 + 1 + 2
3. 2 + 2
4. 1 + 3

Total ways = 4.

RECURRENCE RELATION:

dp[i] = dp[i] + dp[i-coin]

BASE CASE:

dp[0] = 1

All other dp values initially = 0.

TIME COMPLEXITY:
O(n * m)

n = Amount
m = Number of coin denominations

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming - Unbounded Knapsack

IMPORTANT TRICK:

Outer loop = Coins
Inner loop = Amount (Forward direction)

Forward traversal allows unlimited use
of the same coin.

Use long long because the number of ways
can exceed the int range.
*/
