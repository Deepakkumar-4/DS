


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


//====================================================================
// SECTION: DP PROBLEMS ON SUBSEQUENCE
//====================================================================

//---------Longest Repeated Subsequence

#include <bits/stdc++.h>
using namespace std;

int longestRepeatedSubsequence(string s)
{
    int n = s.length();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(s[i - 1] == s[j - 1] && i != j)
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[n][n];
}

int main()
{
    string s;
    if(cin >> s)
    {
        cout << longestRepeatedSubsequence(s) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. Longest Repeated Subsequence is a variation of LCS of string s with itself.
2. The key condition is that matching characters must have different indices (i != j)
   so that a character at index i is not matched with itself.
3. If s[i-1] == s[j-1] and i != j:
   dp[i][j] = 1 + dp[i-1][j-1]
   Otherwise:
   dp[i][j] = max(dp[i-1][j], dp[i][j-1])
4. dp[n][n] gives the length of the longest repeated subsequence.

SAMPLE INPUT:
AABEBCDD

SAMPLE OUTPUT:
3

EXPLANATION:
The longest repeated subsequence is "ABD" of length 3.

RECURRENCE RELATION:
dp[i][j] = 1 + dp[i-1][j-1]                if s[i-1] == s[j-1] and i != j
dp[i][j] = max(dp[i-1][j], dp[i][j-1])      otherwise

BASE CASE:
dp[0][j] = dp[i][0] = 0

TIME COMPLEXITY:
O(n^2)

SPACE COMPLEXITY:
O(n^2) (can be optimized to O(n))

PATTERN:
Dynamic Programming - LCS Variant
*/

//---------Maximum Sum Increasing Subsequence

#include <bits/stdc++.h>
using namespace std;

int maxSumIS(vector<int>& arr)
{
    int n = arr.size();
    if(n == 0) return 0;

    vector<int> dp = arr;
    int ans = arr[0];

    for(int i = 1; i < n; i++)
    {
        for(int j = 0; j < i; j++)
        {
            if(arr[j] < arr[i])
            {
                dp[i] = max(dp[i], dp[j] + arr[i]);
            }
        }
        ans = max(ans, dp[i]);
    }

    return ans;
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> arr(n);
        for(int i = 0; i < n; i++) cin >> arr[i];
        cout << maxSumIS(arr) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[i] represents the maximum sum of an increasing subsequence ending at arr[i].
2. Initialize dp[i] = arr[i] because an element alone forms an increasing subsequence.
3. For each element i from 1 to n-1:
   - Check all previous elements j from 0 to i-1.
   - If arr[j] < arr[i], arr[i] can extend the subsequence ending at j:
     dp[i] = max(dp[i], dp[j] + arr[i])
4. The maximum value in dp array is the answer.

SAMPLE INPUT:
7
1 101 2 3 100 4 5

SAMPLE OUTPUT:
106

EXPLANATION:
The subsequence [1, 2, 3, 100] yields the maximum sum: 1 + 2 + 3 + 100 = 106.

RECURRENCE RELATION:
dp[i] = arr[i] + max({dp[j] : 0 <= j < i and arr[j] < arr[i]} U {0})

BASE CASE:
dp[i] = arr[i] for all 0 <= i < n

TIME COMPLEXITY:
O(n^2)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming - LIS Variant
*/

//---------Count all subsequences having product less than K

#include <bits/stdc++.h>
using namespace std;

int countSubsequencesProductLessThanK(vector<int>& arr, int k)
{
    int n = arr.size();
    // dp[i][j] = count of non-empty subsequences using first j elements with product <= i
    vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));

    for(int i = 1; i <= k; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            // Option 1: Do not include arr[j-1]
            dp[i][j] = dp[i][j - 1];

            // Option 2: Include arr[j-1]
            if(arr[j - 1] <= i && arr[j - 1] > 0)
            {
                // dp[i / arr[j-1]][j-1] + 1 (the 1 is for the singleton subsequence {arr[j-1]})
                dp[i][j] += dp[i / arr[j - 1]][j - 1] + 1;
            }
        }
    }

    // Number of subsequences with product STRICTLY less than k: product <= k - 1
    return dp[k - 1][n];
}

int main()
{
    int n, k;
    if(cin >> n >> k)
    {
        vector<int> arr(n);
        for(int i = 0; i < n; i++) cin >> arr[i];
        cout << countSubsequencesProductLessThanK(arr, k) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[i][j] stores the count of subsequences from the first j elements with product <= i.
2. For each element arr[j-1]:
   - Subsequences not taking arr[j-1]: dp[i][j-1].
   - Subsequences taking arr[j-1]: Combine with earlier subsequences having product <= i / arr[j-1],
     plus 1 for the new single-element subsequence {arr[j-1]}.
3. dp[i][j] = dp[i][j-1] + (dp[i / arr[j-1]][j-1] + 1) if arr[j-1] <= i.
4. For strictly less than k, query dp[k-1][n].

SAMPLE INPUT:
4 10
1 2 3 4

SAMPLE OUTPUT:
11

EXPLANATION:
Subsequences with product < 10:
{1}, {2}, {3}, {4}, {1,2}, {1,3}, {1,4}, {2,3}, {2,4}, {1,2,3}, {1,2,4} -> Total 11.

RECURRENCE RELATION:
dp[i][j] = dp[i][j-1] + (arr[j-1] <= i ? dp[floor(i / arr[j-1])][j-1] + 1 : 0)

BASE CASE:
dp[i][0] = 0 for all i

TIME COMPLEXITY:
O(k * n)

SPACE COMPLEXITY:
O(k * n)

PATTERN:
Dynamic Programming - 0/1 Knapsack with Product Constraint
*/

//---------Longest Increasing Subsequence

#include <bits/stdc++.h>
using namespace std;

// O(n log n) Binary Search (Patience Sorting)
int lengthOfLIS(vector<int>& nums)
{
    if(nums.empty()) return 0;
    vector<int> tails;

    for(int x : nums)
    {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if(it == tails.end())
        {
            tails.push_back(x);
        }
        else
        {
            *it = x; // Replace to maintain smallest tail value
        }
    }

    return tails.size();
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> nums(n);
        for(int i = 0; i < n; i++) cin >> nums[i];
        cout << lengthOfLIS(nums) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. Maintain a vector 'tails' where tails[i] stores the smallest tail of all increasing
   subsequences of length i+1 found so far.
2. For each number x in nums:
   - Use lower_bound to find the first element in tails >= x.
   - If no such element exists, x extends the largest subsequence: tails.push_back(x).
   - If found, replace that element with x (keeps subsequence length same with a smaller tail).
3. The length of tails gives the length of the Longest Increasing Subsequence.

SAMPLE INPUT:
6
10 9 2 5 3 7

SAMPLE OUTPUT:
3

EXPLANATION:
LIS is [2, 3, 7] or [2, 5, 7], length = 3.

RECURRENCE (O(n^2) alternative):
dp[i] = 1 + max({dp[j] : 0 <= j < i and nums[j] < nums[i]} U {0})

TIME COMPLEXITY:
O(n log n)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming + Binary Search / Patience Sorting
*/

//---------Longest Bitonic Subsequence

#include <bits/stdc++.h>
using namespace std;

int longestBitonicSubsequence(int n, vector<int>& nums)
{
    if(n == 0) return 0;

    // lis[i] = length of LIS ending at nums[i]
    vector<int> lis(n, 1);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < i; j++)
        {
            if(nums[j] < nums[i])
            {
                lis[i] = max(lis[i], 1 + lis[j]);
            }
        }
    }

    // lds[i] = length of LDS starting at nums[i] (LIS from right to left)
    vector<int> lds(n, 1);
    for(int i = n - 1; i >= 0; i--)
    {
        for(int j = n - 1; j > i; j--)
        {
            if(nums[j] < nums[i])
            {
                lds[i] = max(lds[i], 1 + lds[j]);
            }
        }
    }

    int maxLen = 0;
    for(int i = 0; i < n; i++)
    {
        maxLen = max(maxLen, lis[i] + lds[i] - 1);
    }

    return maxLen;
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> nums(n);
        for(int i = 0; i < n; i++) cin >> nums[i];
        cout << longestBitonicSubsequence(n, nums) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. A bitonic sequence first increases then decreases.
2. Calculate lis[i]: Longest Increasing Subsequence ending at index i from left to right.
3. Calculate lds[i]: Longest Decreasing Subsequence starting at index i from right to left.
4. For each element i as the peak, the bitonic length is lis[i] + lds[i] - 1
   (subtract 1 because nums[i] is counted in both).
5. The maximum over all indices gives the result.

SAMPLE INPUT:
8
1 11 2 10 4 5 2 1

SAMPLE OUTPUT:
6

EXPLANATION:
The longest bitonic subsequence is [1, 2, 4, 5, 2, 1] or [1, 2, 10, 5, 2, 1], length = 6.

RECURRENCE RELATION:
LBS = max_{0 <= i < n} (lis[i] + lds[i] - 1)

BASE CASE:
lis[i] = 1, lds[i] = 1 for all i

TIME COMPLEXITY:
O(n^2)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming - Bidirectional LIS
*/

//---------Longest Arithmetic Subsequence

#include <bits/stdc++.h>
using namespace std;

int longestArithSeqLength(vector<int>& nums)
{
    int n = nums.size();
    if(n <= 2) return n;

    // dp[i][diff] = length of arithmetic sequence ending at index i with common difference diff
    vector<unordered_map<int, int>> dp(n);
    int maxLen = 2;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < i; j++)
        {
            int diff = nums[i] - nums[j];
            int count = dp[j].count(diff) ? dp[j][diff] + 1 : 2;
            dp[i][diff] = max(dp[i][diff], count);
            maxLen = max(maxLen, dp[i][diff]);
        }
    }

    return maxLen;
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> nums(n);
        for(int i = 0; i < n; i++) cin >> nums[i];
        cout << longestArithSeqLength(nums) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. An arithmetic progression has constant difference diff = nums[i] - nums[j].
2. Let dp[i][diff] be the length of the AP ending at index i with common difference diff.
3. For every pair of indices (j, i) where j < i:
   - Compute diff = nums[i] - nums[j].
   - If an AP ended at index j with difference diff, extend it: dp[j][diff] + 1.
   - Otherwise, the two numbers form a new AP of length 2.
4. Track the maximum length across all states.

SAMPLE INPUT:
6
3 6 9 12 15 18

SAMPLE OUTPUT:
6

EXPLANATION:
The entire sequence is an AP with common difference 3, length = 6.

RECURRENCE RELATION:
dp[i][diff] = (dp[j].count(diff) ? dp[j][diff] : 1) + 1  for 0 <= j < i

BASE CASE:
Any two numbers form an AP of length 2.

TIME COMPLEXITY:
O(n^2)

SPACE COMPLEXITY:
O(n^2)

PATTERN:
Dynamic Programming - State with Transition Parameter
*/


//====================================================================
// SECTION: DP ON ARRAYS
//====================================================================

//---------Max Sum Subarray (Kadane's Algorithm)

#include <bits/stdc++.h>
using namespace std;

long long maxSubarraySum(vector<int>& arr)
{
    long long maxEndingHere = arr[0];
    long long maxSoFar = arr[0];

    for(size_t i = 1; i < arr.size(); i++)
    {
        // Either extend the previous subarray or start a new subarray at current element
        maxEndingHere = max((long long)arr[i], maxEndingHere + arr[i]);
        maxSoFar = max(maxSoFar, maxEndingHere);
    }

    return maxSoFar;
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> arr(n);
        for(int i = 0; i < n; i++) cin >> arr[i];
        cout << maxSubarraySum(arr) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[i] represents the maximum sum of a contiguous subarray ending at index i.
2. At index i, we have two choices:
   - Add arr[i] to the running sum: dp[i-1] + arr[i]
   - Start a fresh subarray at arr[i]: arr[i]
3. Update maxEndingHere = max(arr[i], maxEndingHere + arr[i]).
4. Maintain maxSoFar as the maximum of maxEndingHere encountered so far.
5. Handled entirely in O(1) space using two variables.

SAMPLE INPUT:
8
-2 -3 4 -1 -2 1 5 -3

SAMPLE OUTPUT:
7

EXPLANATION:
The contiguous subarray [4, -1, -2, 1, 5] gives the largest sum = 7.

RECURRENCE RELATION:
dp[i] = max(arr[i], dp[i-1] + arr[i])
Base Case: dp[0] = arr[0]

TIME COMPLEXITY:
O(n)

SPACE COMPLEXITY:
O(1)

PATTERN:
Dynamic Programming - Kadane's Algorithm
*/

//---------Max Sum Without Adjacent (House Robber)

#include <bits/stdc++.h>
using namespace std;

int findMaxSum(vector<int>& arr)
{
    int n = arr.size();
    if(n == 0) return 0;
    if(n == 1) return arr[0];

    int prev2 = arr[0];
    int prev1 = max(arr[0], arr[1]);

    for(int i = 2; i < n; i++)
    {
        // Pick current element arr[i] + prev2, or don't pick current (prev1)
        int curr = max(prev1, prev2 + arr[i]);
        prev2 = prev1;
        prev1 = curr;
    }

    return prev1;
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> arr(n);
        for(int i = 0; i < n; i++) cin >> arr[i];
        cout << findMaxSum(arr) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[i] represents the maximum sum possible using a subset of elements from 0 to i
   with no two selected elements being adjacent.
2. At index i, we can:
   - Exclude arr[i]: sum is dp[i-1].
   - Include arr[i]: sum is dp[i-2] + arr[i].
3. dp[i] = max(dp[i-1], dp[i-2] + arr[i]).
4. We only need the last two states (prev1, prev2), achieving O(1) space.

SAMPLE INPUT:
6
5 5 10 100 10 5

SAMPLE OUTPUT:
110

EXPLANATION:
Pick 5, 100, 5 -> Sum = 110.

RECURRENCE RELATION:
dp[i] = max(dp[i-1], dp[i-2] + arr[i])
Base Cases: dp[0] = arr[0], dp[1] = max(arr[0], arr[1])

TIME COMPLEXITY:
O(n)

SPACE COMPLEXITY:
O(1)

PATTERN:
Dynamic Programming - Pick / Don't Pick with State Reduction
*/

//---------Min Jumps to Reach End

#include <bits/stdc++.h>
using namespace std;

int minJumps(vector<int>& arr)
{
    int n = arr.size();
    if(n <= 1) return 0;
    if(arr[0] == 0) return -1;

    // dp[i] = minimum jumps to reach index i from index 0
    vector<int> dp(n, INT_MAX);
    dp[0] = 0;

    for(int i = 1; i < n; i++)
    {
        for(int j = 0; j < i; j++)
        {
            if(j + arr[j] >= i && dp[j] != INT_MAX)
            {
                dp[i] = min(dp[i], dp[j] + 1);
            }
        }
    }

    return (dp[n - 1] == INT_MAX) ? -1 : dp[n - 1];
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> arr(n);
        for(int i = 0; i < n; i++) cin >> arr[i];
        cout << minJumps(arr) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[i] stores the minimum jumps needed to reach index i from index 0.
2. Base case: dp[0] = 0, and all other dp[i] = INT_MAX.
3. For every index i from 1 to n-1:
   - Check all previous indices j (0 <= j < i).
   - If index i is reachable from j (j + arr[j] >= i) and dp[j] != INT_MAX:
     dp[i] = min(dp[i], dp[j] + 1).
4. If dp[n-1] remains INT_MAX, the end is unreachable, return -1.
(Note: A greedy BFS approach can also solve this in O(n) time).

SAMPLE INPUT:
11
1 3 5 8 9 2 6 7 6 8 9

SAMPLE OUTPUT:
3

EXPLANATION:
Jump from 0 -> 1 -> 4 -> 10. Total 3 jumps.

RECURRENCE RELATION:
dp[i] = min_{0 <= j < i, j + arr[j] >= i} (dp[j] + 1)

BASE CASE:
dp[0] = 0

TIME COMPLEXITY:
O(n^2) for DP (O(n) for greedy jump intervals)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming - 1D Reachability Minimization
*/

//---------Max Sum Subarray with K Concatenations

#include <bits/stdc++.h>
using namespace std;

long long kadane(vector<int>& arr)
{
    long long curr = 0, maxSoFar = 0;
    for(int x : arr)
    {
        curr = max((long long)x, curr + x);
        maxSoFar = max(maxSoFar, curr);
    }
    return maxSoFar;
}

long long kConcatenationMaxSum(vector<int>& arr, int k)
{
    const int MOD = 1e9 + 7;
    int n = arr.size();

    long long totalSum = 0;
    for(int x : arr) totalSum += x;

    if(k == 1)
    {
        return kadane(arr) % MOD;
    }

    // Concatenate arr twice to find max subarray spanning boundary
    vector<int> doubleArr = arr;
    for(int x : arr) doubleArr.push_back(x);

    long long maxSub2 = kadane(doubleArr);

    if(totalSum > 0)
    {
        // Positive total sum can be accumulated across (k - 2) intermediate copies
        long long ans = (maxSub2 + (long long)(k - 2) * totalSum) % MOD;
        return max(0LL, ans);
    }
    else
    {
        // Total sum is non-positive; intermediate copies would only decrease sum
        return max(0LL, maxSub2 % MOD);
    }
}

int main()
{
    int n, k;
    if(cin >> n >> k)
    {
        vector<int> arr(n);
        for(int i = 0; i < n; i++) cin >> arr[i];
        cout << kConcatenationMaxSum(arr, k) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. When array is repeated k times:
   - For k = 1: standard Kadane's algorithm.
   - For k >= 2: The maximum subarray may lie entirely in one copy or span across two copies.
2. Run Kadane on arr repeated 2 times (doubleArr) to get maxSub2.
3. Compute totalSum of one array copy:
   - If totalSum > 0: All (k - 2) copies in the middle can be fully included to maximize sum:
     ans = maxSub2 + (k - 2) * totalSum.
   - If totalSum <= 0: Middle copies do not contribute positively, so maxSub2 is sufficient.
4. Return answer modulo 1e9 + 7 (empty subarray gives sum 0).

SAMPLE INPUT:
3 3
1 -2 1

SAMPLE OUTPUT:
2

EXPLANATION:
Array is [1, -2, 1, 1, -2, 1, 1, -2, 1].
Max subarray sum is 2 (e.g. [1, 1] across the boundaries).

RECURRENCE RELATION:
If totalSum > 0: ans = maxSub2 + (k - 2) * totalSum
If totalSum <= 0: ans = maxSub2

TIME COMPLEXITY:
O(n)

SPACE COMPLEXITY:
O(n) for 2x concatenation

PATTERN:
Dynamic Programming - Kadane + Periodicity
*/

//---------Max Sum Circular (Maximum Sum Circular Subarray)

#include <bits/stdc++.h>
using namespace std;

int maxSubarraySumCircular(vector<int>& nums)
{
    int totalSum = 0;
    int currMax = 0, maxSum = nums[0];
    int currMin = 0, minSum = nums[0];

    for(int x : nums)
    {
        totalSum += x;

        // Kadane for maximum subarray
        currMax = max(x, currMax + x);
        maxSum = max(maxSum, currMax);

        // Kadane for minimum subarray
        currMin = min(x, currMin + x);
        minSum = min(minSum, currMin);
    }

    // If all numbers are negative, totalSum == minSum, so circular wrapping is invalid
    if(totalSum == minSum)
    {
        return maxSum;
    }

    // Maximum circular sum is either non-wrapping (maxSum) or wrapping (totalSum - minSum)
    return max(maxSum, totalSum - minSum);
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> nums(n);
        for(int i = 0; i < n; i++) cin >> nums[i];
        cout << maxSubarraySumCircular(nums) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. In a circular array, the maximum contiguous subarray has two possibilities:
   - Case 1 (Non-wrapping): Lies completely inside the array without wrap-around.
     Found via standard Kadane's max subarray.
   - Case 2 (Wrapping): Takes elements from the beginning and end, wrapping around.
     This is equivalent to totalSum - minSubarraySum.
2. Track both maxSum and minSum in a single pass using Kadane's logic.
3. Edge case: If all numbers are negative, totalSum - minSum = 0 (empty array),
   which is not allowed; return maxSum in this case.
4. Otherwise, return max(maxSum, totalSum - minSum).

SAMPLE INPUT:
4
5 -3 5 5

SAMPLE OUTPUT:
12

EXPLANATION:
Circular subarray [5, 5, 5] (wrapping around index 0) gives sum = 15 - 3 = 12.

RECURRENCE RELATION:
maxCircular = max(maxSubarray, totalSum - minSubarray)

TIME COMPLEXITY:
O(n)

SPACE COMPLEXITY:
O(1)

PATTERN:
Dynamic Programming - Inverted Kadane / Circular Array
*/

//---------Max Product Subarray

#include <bits/stdc++.h>
using namespace std;

int maxProduct(vector<int>& nums)
{
    int n = nums.size();
    if(n == 0) return 0;

    int maxProd = nums[0];
    int minProd = nums[0];
    int result = nums[0];

    for(int i = 1; i < n; i++)
    {
        // When multiplied by a negative number, max product and min product swap
        if(nums[i] < 0)
        {
            swap(maxProd, minProd);
        }

        maxProd = max(nums[i], maxProd * nums[i]);
        minProd = min(nums[i], minProd * nums[i]);

        result = max(result, maxProd);
    }

    return result;
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> nums(n);
        for(int i = 0; i < n; i++) cin >> nums[i];
        cout << maxProduct(nums) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. A negative number can turn a very small negative product into a large positive product.
2. Therefore, at each step we must track BOTH:
   - maxProd: maximum product ending at current index.
   - minProd: minimum product ending at current index.
3. When nums[i] < 0, swap maxProd and minProd before multiplying.
4. Update:
   maxProd = max(nums[i], maxProd * nums[i])
   minProd = min(nums[i], minProd * nums[i])
5. Update global result with maxProd.

SAMPLE INPUT:
4
2 3 -2 4

SAMPLE OUTPUT:
6

EXPLANATION:
Subarray [2, 3] gives maximum product = 6.

RECURRENCE RELATION:
maxProd[i] = max(nums[i], max(maxProd[i-1] * nums[i], minProd[i-1] * nums[i]))
minProd[i] = min(nums[i], min(maxProd[i-1] * nums[i], minProd[i-1] * nums[i]))

TIME COMPLEXITY:
O(n)

SPACE COMPLEXITY:
O(1)

PATTERN:
Dynamic Programming - Kadane's with Sign Flip Tracking
*/


//====================================================================
// SECTION: DP PROBLEMS ON GRID
//====================================================================

//---------Min Cost Path in a Grid

#include <bits/stdc++.h>
using namespace std;

int minCostPath(vector<vector<int>>& grid)
{
    int m = grid.size();
    int n = grid[0].size();

    vector<vector<int>> dp(m, vector<int>(n, 0));

    dp[0][0] = grid[0][0];

    // Initialize first row (can only come from left)
    for(int j = 1; j < n; j++)
    {
        dp[0][j] = dp[0][j - 1] + grid[0][j];
    }

    // Initialize first column (can only come from top)
    for(int i = 1; i < m; i++)
    {
        dp[i][0] = dp[i - 1][0] + grid[i][0];
    }

    // Fill remaining cells considering Right, Down, and Diagonal-Down moves
    for(int i = 1; i < m; i++)
    {
        for(int j = 1; j <= n - 1; j++)
        {
            dp[i][j] = grid[i][j] + min({dp[i - 1][j],       // from top
                                         dp[i][j - 1],       // from left
                                         dp[i - 1][j - 1]}); // from diagonal top-left
        }
    }

    return dp[m - 1][n - 1];
}

int main()
{
    int m, n;
    if(cin >> m >> n)
    {
        vector<vector<int>> grid(m, vector<int>(n));
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++) cin >> grid[i][j];
        }
        cout << minCostPath(grid) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[i][j] represents the minimum cost to reach cell (i, j) from (0, 0).
2. The allowed moves to reach (i, j) are:
   - From top: (i-1, j)
   - From left: (i, j-1)
   - From diagonal: (i-1, j-1)
3. Transition:
   dp[i][j] = grid[i][j] + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]})
4. First row and first column have only 1 predecessor direction, serving as base boundaries.

SAMPLE INPUT:
3 3
1 2 3
4 8 2
1 5 3

SAMPLE OUTPUT:
8

EXPLANATION:
Path: (0,0) -> (0,1) -> (1,2) -> (2,2) with cost 1 + 2 + 2 + 3 = 8.

RECURRENCE RELATION:
dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])

TIME COMPLEXITY:
O(m * n)

SPACE COMPLEXITY:
O(m * n) (can be optimized to O(n))

PATTERN:
Dynamic Programming - 2D Grid Path Optimization
*/

//---------Min Path Sum in Triangle

#include <bits/stdc++.h>
using namespace std;

int minimumTotal(vector<vector<int>>& triangle)
{
    int n = triangle.size();
    // Start from the bottom row and move upwards
    vector<int> dp = triangle[n - 1];

    for(int i = n - 2; i >= 0; i--)
    {
        for(int j = 0; j <= i; j++)
        {
            // Pick minimum of the two adjacent numbers in the row below
            dp[j] = triangle[i][j] + min(dp[j], dp[j + 1]);
        }
    }

    return dp[0];
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<vector<int>> triangle(n);
        for(int i = 0; i < n; i++)
        {
            triangle[i].resize(i + 1);
            for(int j = 0; j <= i; j++) cin >> triangle[i][j];
        }
        cout << minimumTotal(triangle) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. Moving top-down requires checking boundaries, but bottom-up is simpler and cleaner.
2. Initialize dp array with the bottom row of the triangle.
3. For each row from bottom-2 up to 0:
   - For each index j: dp[j] = triangle[i][j] + min(dp[j], dp[j+1]).
4. At the end, dp[0] holds the minimum path sum from top to bottom.

SAMPLE INPUT:
4
2
3 4
6 5 7
4 1 8 3

SAMPLE OUTPUT:
11

EXPLANATION:
Path: 2 -> 3 -> 5 -> 1 with minimum total sum = 11.

RECURRENCE RELATION:
dp[i][j] = triangle[i][j] + min(dp[i+1][j], dp[i+1][j+1])
Base Case: dp[n-1][j] = triangle[n-1][j]

TIME COMPLEXITY:
O(n^2)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming - Bottom-Up Tree/Triangle
*/

//---------Grid Unique Paths

#include <bits/stdc++.h>
using namespace std;

int uniquePaths(int m, int n)
{
    // dp[j] stores number of ways to reach column j in current row
    vector<int> dp(n, 1);

    for(int i = 1; i < m; i++)
    {
        for(int j = 1; j < n; j++)
        {
            // dp[j] (from top) + dp[j-1] (from left)
            dp[j] = dp[j] + dp[j - 1];
        }
    }

    return dp[n - 1];
}

int main()
{
    int m, n;
    if(cin >> m >> n)
    {
        cout << uniquePaths(m, n) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[i][j] represents the number of unique paths from (0, 0) to (i, j).
2. From each cell, you can only move Right or Down.
3. Therefore, to reach (i, j), you must come from either (i-1, j) or (i, j-1):
   dp[i][j] = dp[i-1][j] + dp[i][j-1].
4. Base case: First row and first column have only 1 way (moving straight right or down).
5. Space optimization: We only need the previous row value and current left value.

SAMPLE INPUT:
3 7

SAMPLE OUTPUT:
28

EXPLANATION:
Total paths from (0,0) to (2,6) in a 3x7 grid is 28.

RECURRENCE RELATION:
dp[i][j] = dp[i-1][j] + dp[i][j-1]
Base Case: dp[0][j] = dp[i][0] = 1

TIME COMPLEXITY:
O(m * n)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming - 2D Counting Combinations
*/

//---------Paths in a Grid with Obstacles

#include <bits/stdc++.h>
using namespace std;

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid)
{
    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();

    // If start or destination is an obstacle, no path exists
    if(obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1)
        return 0;

    vector<long long> dp(n, 0);
    dp[0] = 1;

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(obstacleGrid[i][j] == 1)
            {
                dp[j] = 0; // Obstacle blocks all paths through this cell
            }
            else if(j > 0)
            {
                dp[j] = dp[j] + dp[j - 1];
            }
        }
    }

    return dp[n - 1];
}

int main()
{
    int m, n;
    if(cin >> m >> n)
    {
        vector<vector<int>> grid(m, vector<int>(n));
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++) cin >> grid[i][j];
        }
        cout << uniquePathsWithObstacles(grid) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. Similar to Grid Unique Paths, but when obstacleGrid[i][j] == 1,
   no paths can pass through it, so dp[i][j] = 0.
2. If cell is free (obstacleGrid[i][j] == 0):
   dp[i][j] = dp[i-1][j] + dp[i][j-1].
3. Space optimization reduces 2D table to 1D vector of size n.

SAMPLE INPUT:
3 3
0 0 0
0 1 0
0 0 0

SAMPLE OUTPUT:
2

EXPLANATION:
Only 2 paths reach the bottom-right corner without touching cell (1, 1).

RECURRENCE RELATION:
dp[i][j] = 0                               if obstacleGrid[i][j] == 1
dp[i][j] = dp[i-1][j] + dp[i][j-1]         otherwise

TIME COMPLEXITY:
O(m * n)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming - Grid Path with Constraints
*/

//---------Max Rectangular Area with all 1s (Maximal Rectangle)

#include <bits/stdc++.h>
using namespace std;

// Monotonic stack subroutine to find maximum rectangle area in a histogram
int largestRectangleArea(vector<int>& heights)
{
    stack<int> st;
    int maxArea = 0;
    int n = heights.size();

    for(int i = 0; i <= n; i++)
    {
        int h = (i == n) ? 0 : heights[i];
        while(!st.empty() && heights[st.top()] > h)
        {
            int height = heights[st.top()];
            st.pop();
            int width = st.empty() ? i : (i - st.top() - 1);
            maxArea = max(maxArea, height * width);
        }
        st.push(i);
    }

    return maxArea;
}

int maximalRectangle(vector<vector<char>>& matrix)
{
    if(matrix.empty() || matrix[0].empty()) return 0;
    int m = matrix.size();
    int n = matrix[0].size();

    vector<int> heights(n, 0);
    int maxRect = 0;

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            // Cumulative height of consecutive 1s in column j
            if(matrix[i][j] == '1')
                heights[j]++;
            else
                heights[j] = 0;
        }
        maxRect = max(maxRect, largestRectangleArea(heights));
    }

    return maxRect;
}

int main()
{
    int m, n;
    if(cin >> m >> n)
    {
        vector<vector<char>> matrix(m, vector<char>(n));
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++) cin >> matrix[i][j];
        }
        cout << maximalRectangle(matrix) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. Treat each row as the base of a histogram where bar height represents
   consecutive 1s extending upwards.
2. For each row:
   - If matrix[i][j] == '1': heights[j] += 1
   - If matrix[i][j] == '0': heights[j] = 0 (base is reset)
3. For each updated histogram row, calculate largest rectangular area using
   a monotonic increasing stack in O(n) time.
4. The maximum area encountered across all rows is the maximal rectangle.

SAMPLE INPUT:
4 5
1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

SAMPLE OUTPUT:
6

EXPLANATION:
The maximal rectangle of all 1s has height 2 and width 3, area = 6.

TIME COMPLEXITY:
O(m * n)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming - Row-wise Histogram + Monotonic Stack
*/

//---------Count Rectangular Areas with all 1s

#include <bits/stdc++.h>
using namespace std;

int numSubmat(vector<vector<int>>& mat)
{
    int m = mat.size();
    int n = mat[0].size();

    // heights[i][j] = number of consecutive 1s ending at (i, j) moving upwards
    vector<vector<int>> heights(m, vector<int>(n, 0));

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(mat[i][j] == 1)
            {
                heights[i][j] = (i == 0) ? 1 : heights[i - 1][j] + 1;
            }
        }
    }

    int totalRectangles = 0;

    // For every cell (i, j), count rectangles having bottom-right corner at (i, j)
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(mat[i][j] == 1)
            {
                int minHeight = heights[i][j];
                // Expand leftwards to columns k <= j
                for(int k = j; k >= 0 && mat[i][k] == 1; k--)
                {
                    minHeight = min(minHeight, heights[i][k]);
                    totalRectangles += minHeight;
                }
            }
        }
    }

    return totalRectangles;
}

int main()
{
    int m, n;
    if(cin >> m >> n)
    {
        vector<vector<int>> mat(m, vector<int>(n));
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++) cin >> mat[i][j];
        }
        cout << numSubmat(mat) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. First, preprocess consecutive 1s in each column:
   heights[i][j] = (mat[i][j] == 1) ? heights[i-1][j] + 1 : 0.
2. To count all submatrices (rectangles) of all 1s:
   - For each bottom-right corner at (i, j), expand horizontally to the left (column k from j down to 0).
   - The number of rectangles of width (j - k + 1) with bottom at row i is bounded by the
     minimum height among columns from k to j: minHeight = min(heights[i][k..j]).
   - Add minHeight to total count.

SAMPLE INPUT:
3 3
1 0 1
1 1 0
1 1 0

SAMPLE OUTPUT:
13

EXPLANATION:
Total submatrices containing only 1s:
1x1: 8
1x2: 3
2x1: 2
Total = 13.

RECURRENCE RELATION:
rectanglesEndingAt(i, j) = sum_{k=0..j} min_{c=k..j}(heights[i][c])

TIME COMPLEXITY:
O(m * n^2) (can be optimized to O(m * n) with monotonic stack)

SPACE COMPLEXITY:
O(m * n)

PATTERN:
Dynamic Programming - 2D Submatrix Counting
*/


//====================================================================
// SECTION: DP PROBLEMS ON SUBSET
//====================================================================

//---------Subset Sum

#include <bits/stdc++.h>
using namespace std;

bool isSubsetSum(vector<int>& arr, int target)
{
    // dp[j] indicates whether a subset with sum j is possible
    vector<bool> dp(target + 1, false);
    dp[0] = true; // Sum of 0 is always possible with an empty subset

    for(int num : arr)
    {
        // Traverse backwards to use each element at most once
        for(int j = target; j >= num; j--)
        {
            if(dp[j - num])
            {
                dp[j] = true;
            }
        }
    }

    return dp[target];
}

int main()
{
    int n, target;
    if(cin >> n >> target)
    {
        vector<int> arr(n);
        for(int i = 0; i < n; i++) cin >> arr[i];
        cout << (isSubsetSum(arr, target) ? "true" : "false") << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[j] is true if a subset with sum j can be formed.
2. Initialize dp[0] = true (empty set has sum 0), all others false.
3. For each element num in arr:
   - Iterate sum j backwards from target down to num.
   - If sum (j - num) was achievable without current element, then sum j
     is achievable by including num: dp[j] = dp[j] || dp[j - num].
4. Backward traversal ensures 0/1 knapsack behavior (each element used once).

SAMPLE INPUT:
6 9
3 34 4 12 5 2

SAMPLE OUTPUT:
true

EXPLANATION:
Subset [4, 5] or [3, 4, 2] has sum = 9.

RECURRENCE RELATION:
dp[j] = dp[j] || dp[j - num]

BASE CASE:
dp[0] = true

TIME COMPLEXITY:
O(n * target)

SPACE COMPLEXITY:
O(target)

PATTERN:
Dynamic Programming - 0/1 Knapsack Decision
*/

//---------Count Subsets with Given Sum

#include <bits/stdc++.h>
using namespace std;

int findWays(vector<int>& num, int tar)
{
    const int MOD = 1e9 + 7;
    // dp[j] = number of subsets having sum j
    vector<int> dp(tar + 1, 0);
    dp[0] = 1;

    for(int x : num)
    {
        for(int j = tar; j >= x; j--)
        {
            dp[j] = (dp[j] + dp[j - x]) % MOD;
        }
    }

    return dp[tar];
}

int main()
{
    int n, tar;
    if(cin >> n >> tar)
    {
        vector<int> arr(n);
        for(int i = 0; i < n; i++) cin >> arr[i];
        cout << findWays(arr, tar) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[j] stores the count of subsets that sum to j.
2. Initialize dp[0] = 1 (1 way to achieve sum 0: empty set).
3. For each number x:
   - Traverse j from tar down to x:
     dp[j] = (dp[j] + dp[j - x]) % MOD.
4. If the array contains zeros, each zero doubles the number of valid subsets
   since including or excluding 0 does not change the subset sum.

SAMPLE INPUT:
4 5
1 4 4 5

SAMPLE OUTPUT:
3

EXPLANATION:
Subsets summing to 5: {1, 4}, {1, 4}, {5}. Total = 3.

RECURRENCE RELATION:
dp[j] = dp[j] + dp[j - x]

TIME COMPLEXITY:
O(n * tar)

SPACE COMPLEXITY:
O(tar)

PATTERN:
Dynamic Programming - 0/1 Knapsack Counting
*/

//---------Partition a Set into 2 Equal Sum (Equal Partition)

#include <bits/stdc++.h>
using namespace std;

bool canPartition(vector<int>& nums)
{
    int totalSum = 0;
    for(int x : nums) totalSum += x;

    // Odd sum cannot be partitioned into two equal integer halves
    if(totalSum % 2 != 0) return false;

    int target = totalSum / 2;
    vector<bool> dp(target + 1, false);
    dp[0] = true;

    for(int num : nums)
    {
        for(int j = target; j >= num; j--)
        {
            dp[j] = dp[j] || dp[j - num];
        }
    }

    return dp[target];
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> nums(n);
        for(int i = 0; i < n; i++) cin >> nums[i];
        cout << (canPartition(nums) ? "true" : "false") << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. Two subsets with equal sum must each sum to totalSum / 2.
2. If totalSum is odd, equal partition is impossible; return false immediately.
3. If totalSum is even, the problem reduces directly to the Subset Sum problem
   with target = totalSum / 2.
4. Solve via 1D boolean DP table with backward traversal.

SAMPLE INPUT:
4
1 5 11 5

SAMPLE OUTPUT:
true

EXPLANATION:
Array can be partitioned as [1, 5, 5] and [11], each with sum = 11.

RECURRENCE RELATION:
canPartition(nums) = isSubsetSum(nums, totalSum / 2)

TIME COMPLEXITY:
O(n * totalSum)

SPACE COMPLEXITY:
O(totalSum)

PATTERN:
Dynamic Programming - Reduction to Subset Sum
*/

//---------Largest Divisible Subset

#include <bits/stdc++.h>
using namespace std;

vector<int> largestDivisibleSubset(vector<int>& nums)
{
    int n = nums.size();
    if(n == 0) return {};

    // Sorting is crucial: if a % b == 0 and b % c == 0, then a % c == 0
    sort(nums.begin(), nums.end());

    vector<int> dp(n, 1);       // Length of largest divisible subset ending at i
    vector<int> parent(n, -1);  // To reconstruct the subset
    int maxLen = 1;
    int maxIdx = 0;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < i; j++)
        {
            if(nums[i] % nums[j] == 0 && dp[j] + 1 > dp[i])
            {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        if(dp[i] > maxLen)
        {
            maxLen = dp[i];
            maxIdx = i;
        }
    }

    // Reconstruct subset using parent pointers
    vector<int> result;
    int curr = maxIdx;
    while(curr != -1)
    {
        result.push_back(nums[curr]);
        curr = parent[curr];
    }
    reverse(result.begin(), result.end());

    return result;
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> nums(n);
        for(int i = 0; i < n; i++) cin >> nums[i];
        vector<int> ans = largestDivisibleSubset(nums);
        for(int x : ans) cout << x << " ";
        cout << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. Sort nums in ascending order.
2. By sorting, if nums[i] % nums[j] == 0 (where j < i), then nums[i] is divisible
   by all elements in the subset ending at nums[j] due to transitivity of divisibility.
3. Similar to LIS:
   dp[i] = 1 + max({dp[j] : 0 <= j < i and nums[i] % nums[j] == 0} U {0}).
4. Use parent array to trace back and reconstruct the largest subset.

SAMPLE INPUT:
4
1 2 4 8

SAMPLE OUTPUT:
1 2 4 8

EXPLANATION:
Every pair in [1, 2, 4, 8] satisfies a % b == 0 or b % a == 0.

RECURRENCE RELATION:
dp[i] = max(dp[i], dp[j] + 1)  for all 0 <= j < i where nums[i] % nums[j] == 0

TIME COMPLEXITY:
O(n^2)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming - LIS Variant with Divisibility & Path Reconstruction
*/

//---------Count Subsets with Given XOR

#include <bits/stdc++.h>
using namespace std;

int subsetXOR(vector<int>& arr, int k)
{
    int n = arr.size();
    if(n == 0) return (k == 0) ? 1 : 0;

    // Find maximum element to determine maximum possible XOR value
    int maxEle = *max_element(arr.begin(), arr.end());
    int maxXOR = 1;
    while(maxXOR <= maxEle)
    {
        maxXOR <<= 1;
    }
    maxXOR = max(maxXOR * 2, 1024);

    // dp[j] = number of subsets having XOR sum equal to j
    vector<int> dp(maxXOR, 0);
    dp[0] = 1; // Empty subset has XOR sum 0

    for(int x : arr)
    {
        vector<int> nextDp = dp;
        for(int j = 0; j < maxXOR; j++)
        {
            if(dp[j] > 0)
            {
                // Including element x creates XOR state (j ^ x)
                nextDp[j ^ x] += dp[j];
            }
        }
        dp = move(nextDp);
    }

    return (k < maxXOR) ? dp[k] : 0;
}

int main()
{
    int n, k;
    if(cin >> n >> k)
    {
        vector<int> arr(n);
        for(int i = 0; i < n; i++) cin >> arr[i];
        cout << subsetXOR(arr, k) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[j] represents the number of subsets with XOR sum equal to j.
2. Base condition: dp[0] = 1 (empty set XOR sum is 0).
3. For each element x in arr:
   - Every existing subset with XOR sum j can be augmented with x,
     producing a new subset with XOR sum (j ^ x).
   - Update: nextDp[j ^ x] += dp[j].
4. After processing all elements, dp[k] is the count of subsets with XOR sum equal to k.

SAMPLE INPUT:
4 6
4 2 2 6

SAMPLE OUTPUT:
4

EXPLANATION:
Subsets with XOR = 6:
{4, 2}, {4, 2}, {6}, {4, 2, 2, 6} -> Total = 4.

RECURRENCE RELATION:
dp[i][j] = dp[i-1][j] + dp[i-1][j ^ arr[i-1]]

TIME COMPLEXITY:
O(n * maxXOR) where maxXOR <= 2^(ceil(log2(max_val)) + 1)

SPACE COMPLEXITY:
O(maxXOR)

PATTERN:
Dynamic Programming - 0/1 Knapsack with XOR Operation
*/

//---------Minimum Subset Difference

#include <bits/stdc++.h>
using namespace std;

int minSubsetSumDifference(vector<int>& arr)
{
    int n = arr.size();
    int totalSum = 0;
    for(int x : arr) totalSum += x;

    // Run subset sum DP up to totalSum / 2
    int target = totalSum / 2;
    vector<bool> dp(target + 1, false);
    dp[0] = true;

    for(int num : arr)
    {
        for(int j = target; j >= num; j--)
        {
            dp[j] = dp[j] || dp[j - num];
        }
    }

    // Find the largest subset sum s <= totalSum / 2 that is achievable
    int s1 = 0;
    for(int j = target; j >= 0; j--)
    {
        if(dp[j])
        {
            s1 = j;
            break;
        }
    }

    // Difference between the two subset sums: (totalSum - s1) - s1
    return totalSum - 2 * s1;
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> arr(n);
        for(int i = 0; i < n; i++) cin >> arr[i];
        cout << minSubsetSumDifference(arr) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. Divide array into two subsets S1 and S2 such that |sum(S1) - sum(S2)| is minimized.
2. Since sum(S1) + sum(S2) = totalSum, difference is:
   |totalSum - 2 * sum(S1)|.
3. To minimize this difference, sum(S1) should be as close as possible to totalSum / 2.
4. Run subset sum DP up to totalSum / 2.
5. The largest achievable sum s1 <= totalSum / 2 minimizes the difference:
   minDiff = totalSum - 2 * s1.

SAMPLE INPUT:
4
1 6 11 5

SAMPLE OUTPUT:
1

EXPLANATION:
Subset 1: [1, 5, 6] (sum = 12)
Subset 2: [11] (sum = 11)
Difference = |12 - 11| = 1.

RECURRENCE RELATION:
minDiff = min_{0 <= s <= totalSum / 2, dp[s] == true} (totalSum - 2 * s)

TIME COMPLEXITY:
O(n * totalSum)

SPACE COMPLEXITY:
O(totalSum)

PATTERN:
Dynamic Programming - 0/1 Knapsack Partition Optimization
*/


//====================================================================
// SECTION: ROD CUTTING & STICK CUTTING PROBLEMS
//====================================================================

//---------Classic Rod Cutting Problem (Unbounded Knapsack)

#include <bits/stdc++.h>
using namespace std;

int cutRod(vector<int>& price, int n)
{
    // dp[i] represents the maximum revenue obtainable by cutting a rod of length i
    vector<int> dp(n + 1, 0);

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= i; j++)
        {
            // Cut a piece of length j with price[j-1], remaining rod has length (i - j)
            dp[i] = max(dp[i], price[j - 1] + dp[i - j]);
        }
    }

    return dp[n];
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> price(n);
        for(int i = 0; i < n; i++) cin >> price[i];
        cout << cutRod(price, n) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[i] represents the maximum revenue obtainable by cutting a rod of length i.
2. For a rod of length i, we can make the first cut at length j (where 1 <= j <= i).
3. The revenue from this cut is price[j-1] + dp[i-j] (optimal solution for the remainder).
4. Take the maximum over all possible cut lengths j from 1 to i:
   dp[i] = max_{1 <= j <= i} (price[j-1] + dp[i-j]).
5. Base case: A rod of length 0 yields 0 revenue (dp[0] = 0).

SAMPLE INPUT:
8
1 5 8 9 10 17 17 20

SAMPLE OUTPUT:
22

EXPLANATION:
Cut the rod of length 8 into two pieces of length 2 and 6.
Value = price[1] + price[5] = 5 + 17 = 22.

RECURRENCE RELATION:
dp[i] = max_{1 <= j <= i} (price[j - 1] + dp[i - j])
Base Case: dp[0] = 0

TIME COMPLEXITY:
O(n^2)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming - Unbounded Knapsack
*/

//---------Minimum Cost to Cut a Stick (LeetCode 1547)

#include <bits/stdc++.h>
using namespace std;

int minCost(int n, vector<int>& cuts)
{
    // Add boundaries 0 and n to the cut positions
    cuts.push_back(0);
    cuts.push_back(n);
    sort(cuts.begin(), cuts.end());

    int m = cuts.size();
    // dp[i][j] stores the minimum cost to make all cuts between cuts[i] and cuts[j]
    vector<vector<int>> dp(m, vector<int>(m, 0));

    // Length of the interval in cuts array
    for(int len = 2; len < m; len++)
    {
        for(int i = 0; i < m - len; i++)
        {
            int j = i + len;
            dp[i][j] = INT_MAX;

            // Try each cut position k strictly between i and j
            for(int k = i + 1; k < j; k++)
            {
                int cost = (cuts[j] - cuts[i]) + dp[i][k] + dp[k][j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    return dp[0][m - 1];
}

int main()
{
    int n, c;
    if(cin >> n >> c)
    {
        vector<int> cuts(c);
        for(int i = 0; i < c; i++) cin >> cuts[i];
        cout << minCost(n, cuts) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. Whenever we make a cut at position k on a stick between cuts[i] and cuts[j],
   the cost incurred is the current stick's length: cuts[j] - cuts[i].
2. The cut splits the stick into two sub-problems:
   - Stick between cuts[i] and cuts[k] (cost = dp[i][k])
   - Stick between cuts[k] and cuts[j] (cost = dp[k][j])
3. Append 0 and n to cuts and sort them.
4. dp[i][j] = (cuts[j] - cuts[i]) + min_{i < k < j} (dp[i][k] + dp[k][j]).
5. Base case: When j == i + 1, no cuts remain between them, so dp[i][j] = 0.

SAMPLE INPUT:
7 4
1 3 4 5

SAMPLE OUTPUT:
16

EXPLANATION:
Cuts sorted with boundaries: [0, 1, 3, 4, 5, 7].
Optimal sequence: Cut at 3 (cost 7), then 1 (cost 3), then 4 (cost 4), then 5 (cost 2).
Total cost = 7 + 3 + 4 + 2 = 16.

RECURRENCE RELATION:
dp[i][j] = (cuts[j] - cuts[i]) + min_{i < k < j} (dp[i][k] + dp[k][j])

TIME COMPLEXITY:
O(m^3) where m is number of cuts + 2

SPACE COMPLEXITY:
O(m^2)

PATTERN:
Dynamic Programming - Matrix Chain Multiplication (Interval DP)
*/

//---------Maximize The Cut Segments (Cut into lengths x, y, z)

#include <bits/stdc++.h>
using namespace std;

int maximizeTheCuts(int n, int x, int y, int z)
{
    // dp[i] = maximum segments a rod of length i can be cut into
    vector<int> dp(n + 1, -1);
    dp[0] = 0; // 0 length requires 0 cuts

    for(int i = 1; i <= n; i++)
    {
        if(i >= x && dp[i - x] != -1) dp[i] = max(dp[i], dp[i - x] + 1);
        if(i >= y && dp[i - y] != -1) dp[i] = max(dp[i], dp[i - y] + 1);
        if(i >= z && dp[i - z] != -1) dp[i] = max(dp[i], dp[i - z] + 1);
    }

    return (dp[n] == -1) ? 0 : dp[n];
}

int main()
{
    int n, x, y, z;
    if(cin >> n >> x >> y >> z)
    {
        cout << maximizeTheCuts(n, x, y, z) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[i] stores the maximum number of cut segments of a rod of length i
   using only lengths x, y, and z.
2. Initialize dp[0] = 0 and all other dp[i] = -1 (unreachable).
3. At length i:
   - Try cutting a segment of length x: dp[i - x] + 1
   - Try cutting a segment of length y: dp[i - y] + 1
   - Try cutting a segment of length z: dp[i - z] + 1
   Take the maximum among valid previous states.
4. If dp[n] is -1, it's impossible to cut the rod completely into given segments.

SAMPLE INPUT:
4 2 1 1

SAMPLE OUTPUT:
4

EXPLANATION:
Cut into 4 segments of length 1 each.

RECURRENCE RELATION:
dp[i] = 1 + max({dp[i - x], dp[i - y], dp[i - z]}) where dp state != -1

TIME COMPLEXITY:
O(n)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming - 1D Unbounded Knapsack Maximization
*/

//---------Integer Break (LeetCode 343)

#include <bits/stdc++.h>
using namespace std;

int integerBreak(int n)
{
    // dp[i] stores the maximum product achievable by splitting integer i into at least 2 parts
    vector<int> dp(n + 1, 0);
    dp[1] = 1;

    for(int i = 2; i <= n; i++)
    {
        for(int j = 1; j < i; j++)
        {
            // Either don't break (i - j) further: j * (i - j)
            // Or break (i - j) further: j * dp[i - j]
            dp[i] = max({dp[i], j * (i - j), j * dp[i - j]});
        }
    }

    return dp[n];
}

int main()
{
    int n;
    if(cin >> n)
    {
        cout << integerBreak(n) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. Analogous to rod cutting where length n is cut into integers, but we maximize the PRODUCT.
2. For number i, split off a piece of size j (1 <= j < i).
3. The remaining piece (i - j) can either:
   - Not be broken further: product = j * (i - j)
   - Be broken further into sub-pieces: product = j * dp[i - j]
4. dp[i] = max_{1 <= j < i} (max(j * (i - j), j * dp[i - j])).

SAMPLE INPUT:
10

SAMPLE OUTPUT:
36

EXPLANATION:
10 = 3 + 3 + 4, product = 3 * 3 * 4 = 36.

RECURRENCE RELATION:
dp[i] = max_{1 <= j < i} (max(j * (i - j), j * dp[i - j]))

TIME COMPLEXITY:
O(n^2)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming - Rod Cutting with Multiplicative Values
*/

//====================================================================
// SECTION: CLIMBING STAIRS PROBLEMS
//====================================================================

//---------Climbing Stairs (LeetCode 70)

#include <bits/stdc++.h>
using namespace std;

int climbStairs(int n)
{
    if(n <= 2) return n;

    int prev2 = 1; // ways to reach 1st step
    int prev1 = 2; // ways to reach 2nd step

    for(int i = 3; i <= n; i++)
    {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }

    return prev1;
}

int main()
{
    int n;
    if(cin >> n)
    {
        cout << climbStairs(n) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. You can climb 1 or 2 steps at a time.
2. To reach the n-th step, you can:
   - Come from the (n-1)-th step by taking 1 step.
   - Come from the (n-2)-th step by taking 2 steps.
3. Total ways: dp[n] = dp[n-1] + dp[n-2].
4. Space optimized to O(1) by maintaining only the last two values (Fibonacci sequence).

SAMPLE INPUT:
3

SAMPLE OUTPUT:
3

EXPLANATION:
Ways to reach step 3:
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step

RECURRENCE RELATION:
dp[n] = dp[n - 1] + dp[n - 2]
Base Cases: dp[1] = 1, dp[2] = 2

TIME COMPLEXITY:
O(n)

SPACE COMPLEXITY:
O(1)

PATTERN:
Dynamic Programming - Fibonacci Sequence / Step Transition
*/

//---------Min Cost Climbing Stairs (LeetCode 746)

#include <bits/stdc++.h>
using namespace std;

int minCostClimbingStairs(vector<int>& cost)
{
    int n = cost.size();
    int prev2 = 0; // Cost to reach step 0
    int prev1 = 0; // Cost to reach step 1

    for(int i = 2; i <= n; i++)
    {
        // Pay cost of leaving (i-1) or leaving (i-2)
        int curr = min(prev1 + cost[i - 1], prev2 + cost[i - 2]);
        prev2 = prev1;
        prev1 = curr;
    }

    return prev1;
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> cost(n);
        for(int i = 0; i < n; i++) cin >> cost[i];
        cout << minCostClimbingStairs(cost) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. You can start at index 0 or index 1 with 0 initial cost.
2. dp[i] represents the minimum cost to reach step i (where n is the top of the floor).
3. To reach step i:
   - Step from (i-1), paying cost[i-1]: dp[i-1] + cost[i-1]
   - Step from (i-2), paying cost[i-2]: dp[i-2] + cost[i-2]
4. dp[i] = min(dp[i-1] + cost[i-1], dp[i-2] + cost[i-2]).
5. Space optimized to O(1).

SAMPLE INPUT:
3
10 15 20

SAMPLE OUTPUT:
15

EXPLANATION:
Start at index 1 (cost 15), take 2 steps to reach the top. Total cost = 15.

RECURRENCE RELATION:
dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2])
Base Cases: dp[0] = 0, dp[1] = 0

TIME COMPLEXITY:
O(n)

SPACE COMPLEXITY:
O(1)

PATTERN:
Dynamic Programming - Minimum Cost Step Path
*/

//---------Climbing Stairs with K Steps

#include <bits/stdc++.h>
using namespace std;

int climbStairsKSteps(int n, int k)
{
    const int MOD = 1e9 + 7;
    // dp[i] = number of ways to reach step i using at most k steps
    vector<int> dp(n + 1, 0);
    dp[0] = 1;

    long long windowSum = 1; // Running sum of previous k steps

    for(int i = 1; i <= n; i++)
    {
        dp[i] = windowSum % MOD;
        windowSum = (windowSum + dp[i]) % MOD;

        // Slide the window: remove dp[i - k] when i >= k
        if(i >= k)
        {
            windowSum = (windowSum - dp[i - k] + MOD) % MOD;
        }
    }

    return dp[n];
}

int main()
{
    int n, k;
    if(cin >> n >> k)
    {
        cout << climbStairsKSteps(n, k) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. From step i, you can jump to step (i + 1), (i + 2), ..., (i + k).
2. Conversely, to reach step i, you could have arrived from any step j where
   max(0, i - k) <= j < i:
   dp[i] = sum_{j = 1}^{k} dp[i - j].
3. Naive summation takes O(n * k).
4. Using a sliding window sum of size k reduces the transition to O(1),
   making overall time O(n).

SAMPLE INPUT:
4 2

SAMPLE OUTPUT:
5

EXPLANATION:
With k = 2, it is standard Fibonacci: 1, 2, 3, 5 -> 5 ways to reach step 4.

RECURRENCE RELATION:
dp[i] = sum_{j=1}^{min(i, k)} dp[i - j]
Base Case: dp[0] = 1

TIME COMPLEXITY:
O(n) with sliding window

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming + Sliding Window Optimization
*/

//---------Frog Jump (LeetCode 403)

#include <bits/stdc++.h>
using namespace std;

bool canCross(vector<int>& stones)
{
    int n = stones.size();
    // stoneMap maps stone position to its index in stones array
    unordered_map<int, int> stoneMap;
    for(int i = 0; i < n; i++)
    {
        stoneMap[stones[i]] = i;
    }

    // dp[i] stores all valid last jump sizes that reached stones[i]
    vector<unordered_set<int>> dp(n);
    dp[0].insert(0); // At starting stone 0, initial jump speed is 0

    for(int i = 0; i < n; i++)
    {
        for(int k : dp[i])
        {
            // From stones[i], the next jump can be k-1, k, or k+1
            for(int step = k - 1; step <= k + 1; step++)
            {
                if(step > 0)
                {
                    int nextPos = stones[i] + step;
                    if(stoneMap.count(nextPos))
                    {
                        int nextIdx = stoneMap[nextPos];
                        dp[nextIdx].insert(step);
                    }
                }
            }
        }
    }

    // Frog can cross if the last stone can be reached with any jump size
    return !dp[n - 1].empty();
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> stones(n);
        for(int i = 0; i < n; i++) cin >> stones[i];
        cout << (canCross(stones) ? "true" : "false") << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. A frog starts at stone 0. Its first jump must be of length 1 (if stone 1 exists).
2. If the last jump was k units, the next jump can be k-1, k, or k+1 units (where jump > 0).
3. State: dp[i] contains a set of jump sizes that landed on stones[i].
4. For each stone i and each jump k in dp[i]:
   - Try jumps of size step in {k-1, k, k+1} with step > 0.
   - Next stone position = stones[i] + step.
   - If nextPos contains a stone at index nextIdx, insert 'step' into dp[nextIdx].
5. If dp[n-1] is not empty, the frog can reach the destination stone.

SAMPLE INPUT:
8
0 1 3 5 6 8 12 17

SAMPLE OUTPUT:
true

EXPLANATION:
Jumps: 0 -> 1 (k=1), 1 -> 3 (k=2), 3 -> 5 (k=2), 5 -> 8 (k=3),
       8 -> 12 (k=4), 12 -> 17 (k=5). All jumps valid, reached end.

RECURRENCE RELATION:
If k in dp[i] and (stones[i] + step == stones[j]) for step in {k-1, k, k+1}:
dp[j].insert(step)

TIME COMPLEXITY:
O(n^2)

SPACE COMPLEXITY:
O(n^2)

PATTERN:
Dynamic Programming - State Reachability with Variable Speed / Jump Tracking
*/


//====================================================================
// SECTION: DP PROBLEMS ON SUBSEQUENCE
//====================================================================

//---------Longest Repeated Subsequence

#include <bits/stdc++.h>
using namespace std;

int longestRepeatedSubsequence(string s)
{
    int n = s.length();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(s[i - 1] == s[j - 1] && i != j)
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[n][n];
}

int main()
{
    string s;
    if(cin >> s)
    {
        cout << longestRepeatedSubsequence(s) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. Longest Repeated Subsequence is a variation of LCS of string s with itself.
2. The key condition is that matching characters must have different indices (i != j)
   so that a character at index i is not matched with itself.
3. If s[i-1] == s[j-1] and i != j:
   dp[i][j] = 1 + dp[i-1][j-1]
   Otherwise:
   dp[i][j] = max(dp[i-1][j], dp[i][j-1])
4. dp[n][n] gives the length of the longest repeated subsequence.

SAMPLE INPUT:
AABEBCDD

SAMPLE OUTPUT:
3

EXPLANATION:
The longest repeated subsequence is "ABD" of length 3.

RECURRENCE RELATION:
dp[i][j] = 1 + dp[i-1][j-1]                if s[i-1] == s[j-1] and i != j
dp[i][j] = max(dp[i-1][j], dp[i][j-1])      otherwise

BASE CASE:
dp[0][j] = dp[i][0] = 0

TIME COMPLEXITY:
O(n^2)

SPACE COMPLEXITY:
O(n^2) (can be optimized to O(n))

PATTERN:
Dynamic Programming - LCS Variant
*/

//---------Maximum Sum Increasing Subsequence

#include <bits/stdc++.h>
using namespace std;

int maxSumIS(vector<int>& arr)
{
    int n = arr.size();
    if(n == 0) return 0;

    vector<int> dp = arr;
    int ans = arr[0];

    for(int i = 1; i < n; i++)
    {
        for(int j = 0; j < i; j++)
        {
            if(arr[j] < arr[i])
            {
                dp[i] = max(dp[i], dp[j] + arr[i]);
            }
        }
        ans = max(ans, dp[i]);
    }

    return ans;
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> arr(n);
        for(int i = 0; i < n; i++) cin >> arr[i];
        cout << maxSumIS(arr) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[i] represents the maximum sum of an increasing subsequence ending at arr[i].
2. Initialize dp[i] = arr[i] because an element alone forms an increasing subsequence.
3. For each element i from 1 to n-1:
   - Check all previous elements j from 0 to i-1.
   - If arr[j] < arr[i], arr[i] can extend the subsequence ending at j:
     dp[i] = max(dp[i], dp[j] + arr[i])
4. The maximum value in dp array is the answer.

SAMPLE INPUT:
7
1 101 2 3 100 4 5

SAMPLE OUTPUT:
106

EXPLANATION:
The subsequence [1, 2, 3, 100] yields the maximum sum: 1 + 2 + 3 + 100 = 106.

RECURRENCE RELATION:
dp[i] = arr[i] + max({dp[j] : 0 <= j < i and arr[j] < arr[i]} U {0})

BASE CASE:
dp[i] = arr[i] for all 0 <= i < n

TIME COMPLEXITY:
O(n^2)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming - LIS Variant
*/

//---------Count all subsequences having product less than K

#include <bits/stdc++.h>
using namespace std;

int countSubsequencesProductLessThanK(vector<int>& arr, int k)
{
    int n = arr.size();
    // dp[i][j] = count of non-empty subsequences using first j elements with product <= i
    vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));

    for(int i = 1; i <= k; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            // Option 1: Do not include arr[j-1]
            dp[i][j] = dp[i][j - 1];

            // Option 2: Include arr[j-1]
            if(arr[j - 1] <= i && arr[j - 1] > 0)
            {
                // dp[i / arr[j-1]][j-1] + 1 (the 1 is for the singleton subsequence {arr[j-1]})
                dp[i][j] += dp[i / arr[j - 1]][j - 1] + 1;
            }
        }
    }

    // Number of subsequences with product STRICTLY less than k: product <= k - 1
    return dp[k - 1][n];
}

int main()
{
    int n, k;
    if(cin >> n >> k)
    {
        vector<int> arr(n);
        for(int i = 0; i < n; i++) cin >> arr[i];
        cout << countSubsequencesProductLessThanK(arr, k) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[i][j] stores the count of subsequences from the first j elements with product <= i.
2. For each element arr[j-1]:
   - Subsequences not taking arr[j-1]: dp[i][j-1].
   - Subsequences taking arr[j-1]: Combine with earlier subsequences having product <= i / arr[j-1],
     plus 1 for the new single-element subsequence {arr[j-1]}.
3. dp[i][j] = dp[i][j-1] + (dp[i / arr[j-1]][j-1] + 1) if arr[j-1] <= i.
4. For strictly less than k, query dp[k-1][n].

SAMPLE INPUT:
4 10
1 2 3 4

SAMPLE OUTPUT:
11

EXPLANATION:
Subsequences with product < 10:
{1}, {2}, {3}, {4}, {1,2}, {1,3}, {1,4}, {2,3}, {2,4}, {1,2,3}, {1,2,4} -> Total 11.

RECURRENCE RELATION:
dp[i][j] = dp[i][j-1] + (arr[j-1] <= i ? dp[floor(i / arr[j-1])][j-1] + 1 : 0)

BASE CASE:
dp[i][0] = 0 for all i

TIME COMPLEXITY:
O(k * n)

SPACE COMPLEXITY:
O(k * n)

PATTERN:
Dynamic Programming - 0/1 Knapsack with Product Constraint
*/

//---------Longest Increasing Subsequence

#include <bits/stdc++.h>
using namespace std;

// O(n log n) Binary Search (Patience Sorting)
int lengthOfLIS(vector<int>& nums)
{
    if(nums.empty()) return 0;
    vector<int> tails;

    for(int x : nums)
    {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if(it == tails.end())
        {
            tails.push_back(x);
        }
        else
        {
            *it = x; // Replace to maintain smallest tail value
        }
    }

    return tails.size();
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> nums(n);
        for(int i = 0; i < n; i++) cin >> nums[i];
        cout << lengthOfLIS(nums) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. Maintain a vector 'tails' where tails[i] stores the smallest tail of all increasing
   subsequences of length i+1 found so far.
2. For each number x in nums:
   - Use lower_bound to find the first element in tails >= x.
   - If no such element exists, x extends the largest subsequence: tails.push_back(x).
   - If found, replace that element with x (keeps subsequence length same with a smaller tail).
3. The length of tails gives the length of the Longest Increasing Subsequence.

SAMPLE INPUT:
6
10 9 2 5 3 7

SAMPLE OUTPUT:
3

EXPLANATION:
LIS is [2, 3, 7] or [2, 5, 7], length = 3.

RECURRENCE (O(n^2) alternative):
dp[i] = 1 + max({dp[j] : 0 <= j < i and nums[j] < nums[i]} U {0})

TIME COMPLEXITY:
O(n log n)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming + Binary Search / Patience Sorting
*/

//---------Longest Bitonic Subsequence

#include <bits/stdc++.h>
using namespace std;

int longestBitonicSubsequence(int n, vector<int>& nums)
{
    if(n == 0) return 0;

    // lis[i] = length of LIS ending at nums[i]
    vector<int> lis(n, 1);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < i; j++)
        {
            if(nums[j] < nums[i])
            {
                lis[i] = max(lis[i], 1 + lis[j]);
            }
        }
    }

    // lds[i] = length of LDS starting at nums[i] (LIS from right to left)
    vector<int> lds(n, 1);
    for(int i = n - 1; i >= 0; i--)
    {
        for(int j = n - 1; j > i; j--)
        {
            if(nums[j] < nums[i])
            {
                lds[i] = max(lds[i], 1 + lds[j]);
            }
        }
    }

    int maxLen = 0;
    for(int i = 0; i < n; i++)
    {
        maxLen = max(maxLen, lis[i] + lds[i] - 1);
    }

    return maxLen;
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> nums(n);
        for(int i = 0; i < n; i++) cin >> nums[i];
        cout << longestBitonicSubsequence(n, nums) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. A bitonic sequence first increases then decreases.
2. Calculate lis[i]: Longest Increasing Subsequence ending at index i from left to right.
3. Calculate lds[i]: Longest Decreasing Subsequence starting at index i from right to left.
4. For each element i as the peak, the bitonic length is lis[i] + lds[i] - 1
   (subtract 1 because nums[i] is counted in both).
5. The maximum over all indices gives the result.

SAMPLE INPUT:
8
1 11 2 10 4 5 2 1

SAMPLE OUTPUT:
6

EXPLANATION:
The longest bitonic subsequence is [1, 2, 4, 5, 2, 1] or [1, 2, 10, 5, 2, 1], length = 6.

RECURRENCE RELATION:
LBS = max_{0 <= i < n} (lis[i] + lds[i] - 1)

BASE CASE:
lis[i] = 1, lds[i] = 1 for all i

TIME COMPLEXITY:
O(n^2)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming - Bidirectional LIS
*/

//---------Longest Arithmetic Subsequence

#include <bits/stdc++.h>
using namespace std;

int longestArithSeqLength(vector<int>& nums)
{
    int n = nums.size();
    if(n <= 2) return n;

    // dp[i][diff] = length of arithmetic sequence ending at index i with common difference diff
    vector<unordered_map<int, int>> dp(n);
    int maxLen = 2;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < i; j++)
        {
            int diff = nums[i] - nums[j];
            int count = dp[j].count(diff) ? dp[j][diff] + 1 : 2;
            dp[i][diff] = max(dp[i][diff], count);
            maxLen = max(maxLen, dp[i][diff]);
        }
    }

    return maxLen;
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> nums(n);
        for(int i = 0; i < n; i++) cin >> nums[i];
        cout << longestArithSeqLength(nums) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. An arithmetic progression has constant difference diff = nums[i] - nums[j].
2. Let dp[i][diff] be the length of the AP ending at index i with common difference diff.
3. For every pair of indices (j, i) where j < i:
   - Compute diff = nums[i] - nums[j].
   - If an AP ended at index j with difference diff, extend it: dp[j][diff] + 1.
   - Otherwise, the two numbers form a new AP of length 2.
4. Track the maximum length across all states.

SAMPLE INPUT:
6
3 6 9 12 15 18

SAMPLE OUTPUT:
6

EXPLANATION:
The entire sequence is an AP with common difference 3, length = 6.

RECURRENCE RELATION:
dp[i][diff] = (dp[j].count(diff) ? dp[j][diff] : 1) + 1  for 0 <= j < i

BASE CASE:
Any two numbers form an AP of length 2.

TIME COMPLEXITY:
O(n^2)

SPACE COMPLEXITY:
O(n^2)

PATTERN:
Dynamic Programming - State with Transition Parameter
*/


//====================================================================
// SECTION: DP ON ARRAYS
//====================================================================

//---------Max Sum Subarray (Kadane's Algorithm)

#include <bits/stdc++.h>
using namespace std;

long long maxSubarraySum(vector<int>& arr)
{
    long long maxEndingHere = arr[0];
    long long maxSoFar = arr[0];

    for(size_t i = 1; i < arr.size(); i++)
    {
        // Either extend the previous subarray or start a new subarray at current element
        maxEndingHere = max((long long)arr[i], maxEndingHere + arr[i]);
        maxSoFar = max(maxSoFar, maxEndingHere);
    }

    return maxSoFar;
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> arr(n);
        for(int i = 0; i < n; i++) cin >> arr[i];
        cout << maxSubarraySum(arr) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[i] represents the maximum sum of a contiguous subarray ending at index i.
2. At index i, we have two choices:
   - Add arr[i] to the running sum: dp[i-1] + arr[i]
   - Start a fresh subarray at arr[i]: arr[i]
3. Update maxEndingHere = max(arr[i], maxEndingHere + arr[i]).
4. Maintain maxSoFar as the maximum of maxEndingHere encountered so far.
5. Handled entirely in O(1) space using two variables.

SAMPLE INPUT:
8
-2 -3 4 -1 -2 1 5 -3

SAMPLE OUTPUT:
7

EXPLANATION:
The contiguous subarray [4, -1, -2, 1, 5] gives the largest sum = 7.

RECURRENCE RELATION:
dp[i] = max(arr[i], dp[i-1] + arr[i])
Base Case: dp[0] = arr[0]

TIME COMPLEXITY:
O(n)

SPACE COMPLEXITY:
O(1)

PATTERN:
Dynamic Programming - Kadane's Algorithm
*/

//---------Max Sum Without Adjacent (House Robber)

#include <bits/stdc++.h>
using namespace std;

int findMaxSum(vector<int>& arr)
{
    int n = arr.size();
    if(n == 0) return 0;
    if(n == 1) return arr[0];

    int prev2 = arr[0];
    int prev1 = max(arr[0], arr[1]);

    for(int i = 2; i < n; i++)
    {
        // Pick current element arr[i] + prev2, or don't pick current (prev1)
        int curr = max(prev1, prev2 + arr[i]);
        prev2 = prev1;
        prev1 = curr;
    }

    return prev1;
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> arr(n);
        for(int i = 0; i < n; i++) cin >> arr[i];
        cout << findMaxSum(arr) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[i] represents the maximum sum possible using a subset of elements from 0 to i
   with no two selected elements being adjacent.
2. At index i, we can:
   - Exclude arr[i]: sum is dp[i-1].
   - Include arr[i]: sum is dp[i-2] + arr[i].
3. dp[i] = max(dp[i-1], dp[i-2] + arr[i]).
4. We only need the last two states (prev1, prev2), achieving O(1) space.

SAMPLE INPUT:
6
5 5 10 100 10 5

SAMPLE OUTPUT:
110

EXPLANATION:
Pick 5, 100, 5 -> Sum = 110.

RECURRENCE RELATION:
dp[i] = max(dp[i-1], dp[i-2] + arr[i])
Base Cases: dp[0] = arr[0], dp[1] = max(arr[0], arr[1])

TIME COMPLEXITY:
O(n)

SPACE COMPLEXITY:
O(1)

PATTERN:
Dynamic Programming - Pick / Don't Pick with State Reduction
*/

//---------Min Jumps to Reach End

#include <bits/stdc++.h>
using namespace std;

int minJumps(vector<int>& arr)
{
    int n = arr.size();
    if(n <= 1) return 0;
    if(arr[0] == 0) return -1;

    // dp[i] = minimum jumps to reach index i from index 0
    vector<int> dp(n, INT_MAX);
    dp[0] = 0;

    for(int i = 1; i < n; i++)
    {
        for(int j = 0; j < i; j++)
        {
            if(j + arr[j] >= i && dp[j] != INT_MAX)
            {
                dp[i] = min(dp[i], dp[j] + 1);
            }
        }
    }

    return (dp[n - 1] == INT_MAX) ? -1 : dp[n - 1];
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> arr(n);
        for(int i = 0; i < n; i++) cin >> arr[i];
        cout << minJumps(arr) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[i] stores the minimum jumps needed to reach index i from index 0.
2. Base case: dp[0] = 0, and all other dp[i] = INT_MAX.
3. For every index i from 1 to n-1:
   - Check all previous indices j (0 <= j < i).
   - If index i is reachable from j (j + arr[j] >= i) and dp[j] != INT_MAX:
     dp[i] = min(dp[i], dp[j] + 1).
4. If dp[n-1] remains INT_MAX, the end is unreachable, return -1.
(Note: A greedy BFS approach can also solve this in O(n) time).

SAMPLE INPUT:
11
1 3 5 8 9 2 6 7 6 8 9

SAMPLE OUTPUT:
3

EXPLANATION:
Jump from 0 -> 1 -> 4 -> 10. Total 3 jumps.

RECURRENCE RELATION:
dp[i] = min_{0 <= j < i, j + arr[j] >= i} (dp[j] + 1)

BASE CASE:
dp[0] = 0

TIME COMPLEXITY:
O(n^2) for DP (O(n) for greedy jump intervals)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming - 1D Reachability Minimization
*/

//---------Max Sum Subarray with K Concatenations

#include <bits/stdc++.h>
using namespace std;

long long kadane(vector<int>& arr)
{
    long long curr = 0, maxSoFar = 0;
    for(int x : arr)
    {
        curr = max((long long)x, curr + x);
        maxSoFar = max(maxSoFar, curr);
    }
    return maxSoFar;
}

long long kConcatenationMaxSum(vector<int>& arr, int k)
{
    const int MOD = 1e9 + 7;
    int n = arr.size();

    long long totalSum = 0;
    for(int x : arr) totalSum += x;

    if(k == 1)
    {
        return kadane(arr) % MOD;
    }

    // Concatenate arr twice to find max subarray spanning boundary
    vector<int> doubleArr = arr;
    for(int x : arr) doubleArr.push_back(x);

    long long maxSub2 = kadane(doubleArr);

    if(totalSum > 0)
    {
        // Positive total sum can be accumulated across (k - 2) intermediate copies
        long long ans = (maxSub2 + (long long)(k - 2) * totalSum) % MOD;
        return max(0LL, ans);
    }
    else
    {
        // Total sum is non-positive; intermediate copies would only decrease sum
        return max(0LL, maxSub2 % MOD);
    }
}

int main()
{
    int n, k;
    if(cin >> n >> k)
    {
        vector<int> arr(n);
        for(int i = 0; i < n; i++) cin >> arr[i];
        cout << kConcatenationMaxSum(arr, k) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. When array is repeated k times:
   - For k = 1: standard Kadane's algorithm.
   - For k >= 2: The maximum subarray may lie entirely in one copy or span across two copies.
2. Run Kadane on arr repeated 2 times (doubleArr) to get maxSub2.
3. Compute totalSum of one array copy:
   - If totalSum > 0: All (k - 2) copies in the middle can be fully included to maximize sum:
     ans = maxSub2 + (k - 2) * totalSum.
   - If totalSum <= 0: Middle copies do not contribute positively, so maxSub2 is sufficient.
4. Return answer modulo 1e9 + 7 (empty subarray gives sum 0).

SAMPLE INPUT:
3 3
1 -2 1

SAMPLE OUTPUT:
2

EXPLANATION:
Array is [1, -2, 1, 1, -2, 1, 1, -2, 1].
Max subarray sum is 2 (e.g. [1, 1] across the boundaries).

RECURRENCE RELATION:
If totalSum > 0: ans = maxSub2 + (k - 2) * totalSum
If totalSum <= 0: ans = maxSub2

TIME COMPLEXITY:
O(n)

SPACE COMPLEXITY:
O(n) for 2x concatenation

PATTERN:
Dynamic Programming - Kadane + Periodicity
*/

//---------Max Sum Circular (Maximum Sum Circular Subarray)

#include <bits/stdc++.h>
using namespace std;

int maxSubarraySumCircular(vector<int>& nums)
{
    int totalSum = 0;
    int currMax = 0, maxSum = nums[0];
    int currMin = 0, minSum = nums[0];

    for(int x : nums)
    {
        totalSum += x;

        // Kadane for maximum subarray
        currMax = max(x, currMax + x);
        maxSum = max(maxSum, currMax);

        // Kadane for minimum subarray
        currMin = min(x, currMin + x);
        minSum = min(minSum, currMin);
    }

    // If all numbers are negative, totalSum == minSum, so circular wrapping is invalid
    if(totalSum == minSum)
    {
        return maxSum;
    }

    // Maximum circular sum is either non-wrapping (maxSum) or wrapping (totalSum - minSum)
    return max(maxSum, totalSum - minSum);
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> nums(n);
        for(int i = 0; i < n; i++) cin >> nums[i];
        cout << maxSubarraySumCircular(nums) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. In a circular array, the maximum contiguous subarray has two possibilities:
   - Case 1 (Non-wrapping): Lies completely inside the array without wrap-around.
     Found via standard Kadane's max subarray.
   - Case 2 (Wrapping): Takes elements from the beginning and end, wrapping around.
     This is equivalent to totalSum - minSubarraySum.
2. Track both maxSum and minSum in a single pass using Kadane's logic.
3. Edge case: If all numbers are negative, totalSum - minSum = 0 (empty array),
   which is not allowed; return maxSum in this case.
4. Otherwise, return max(maxSum, totalSum - minSum).

SAMPLE INPUT:
4
5 -3 5 5

SAMPLE OUTPUT:
12

EXPLANATION:
Circular subarray [5, 5, 5] (wrapping around index 0) gives sum = 15 - 3 = 12.

RECURRENCE RELATION:
maxCircular = max(maxSubarray, totalSum - minSubarray)

TIME COMPLEXITY:
O(n)

SPACE COMPLEXITY:
O(1)

PATTERN:
Dynamic Programming - Inverted Kadane / Circular Array
*/

//---------Max Product Subarray

#include <bits/stdc++.h>
using namespace std;

int maxProduct(vector<int>& nums)
{
    int n = nums.size();
    if(n == 0) return 0;

    int maxProd = nums[0];
    int minProd = nums[0];
    int result = nums[0];

    for(int i = 1; i < n; i++)
    {
        // When multiplied by a negative number, max product and min product swap
        if(nums[i] < 0)
        {
            swap(maxProd, minProd);
        }

        maxProd = max(nums[i], maxProd * nums[i]);
        minProd = min(nums[i], minProd * nums[i]);

        result = max(result, maxProd);
    }

    return result;
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> nums(n);
        for(int i = 0; i < n; i++) cin >> nums[i];
        cout << maxProduct(nums) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. A negative number can turn a very small negative product into a large positive product.
2. Therefore, at each step we must track BOTH:
   - maxProd: maximum product ending at current index.
   - minProd: minimum product ending at current index.
3. When nums[i] < 0, swap maxProd and minProd before multiplying.
4. Update:
   maxProd = max(nums[i], maxProd * nums[i])
   minProd = min(nums[i], minProd * nums[i])
5. Update global result with maxProd.

SAMPLE INPUT:
4
2 3 -2 4

SAMPLE OUTPUT:
6

EXPLANATION:
Subarray [2, 3] gives maximum product = 6.

RECURRENCE RELATION:
maxProd[i] = max(nums[i], max(maxProd[i-1] * nums[i], minProd[i-1] * nums[i]))
minProd[i] = min(nums[i], min(maxProd[i-1] * nums[i], minProd[i-1] * nums[i]))

TIME COMPLEXITY:
O(n)

SPACE COMPLEXITY:
O(1)

PATTERN:
Dynamic Programming - Kadane's with Sign Flip Tracking
*/


//====================================================================
// SECTION: DP PROBLEMS ON GRID
//====================================================================

//---------Min Cost Path in a Grid

#include <bits/stdc++.h>
using namespace std;

int minCostPath(vector<vector<int>>& grid)
{
    int m = grid.size();
    int n = grid[0].size();

    vector<vector<int>> dp(m, vector<int>(n, 0));

    dp[0][0] = grid[0][0];

    // Initialize first row (can only come from left)
    for(int j = 1; j < n; j++)
    {
        dp[0][j] = dp[0][j - 1] + grid[0][j];
    }

    // Initialize first column (can only come from top)
    for(int i = 1; i < m; i++)
    {
        dp[i][0] = dp[i - 1][0] + grid[i][0];
    }

    // Fill remaining cells considering Right, Down, and Diagonal-Down moves
    for(int i = 1; i < m; i++)
    {
        for(int j = 1; j <= n - 1; j++)
        {
            dp[i][j] = grid[i][j] + min({dp[i - 1][j],       // from top
                                         dp[i][j - 1],       // from left
                                         dp[i - 1][j - 1]}); // from diagonal top-left
        }
    }

    return dp[m - 1][n - 1];
}

int main()
{
    int m, n;
    if(cin >> m >> n)
    {
        vector<vector<int>> grid(m, vector<int>(n));
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++) cin >> grid[i][j];
        }
        cout << minCostPath(grid) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[i][j] represents the minimum cost to reach cell (i, j) from (0, 0).
2. The allowed moves to reach (i, j) are:
   - From top: (i-1, j)
   - From left: (i, j-1)
   - From diagonal: (i-1, j-1)
3. Transition:
   dp[i][j] = grid[i][j] + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]})
4. First row and first column have only 1 predecessor direction, serving as base boundaries.

SAMPLE INPUT:
3 3
1 2 3
4 8 2
1 5 3

SAMPLE OUTPUT:
8

EXPLANATION:
Path: (0,0) -> (0,1) -> (1,2) -> (2,2) with cost 1 + 2 + 2 + 3 = 8.

RECURRENCE RELATION:
dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])

TIME COMPLEXITY:
O(m * n)

SPACE COMPLEXITY:
O(m * n) (can be optimized to O(n))

PATTERN:
Dynamic Programming - 2D Grid Path Optimization
*/

//---------Min Path Sum in Triangle

#include <bits/stdc++.h>
using namespace std;

int minimumTotal(vector<vector<int>>& triangle)
{
    int n = triangle.size();
    // Start from the bottom row and move upwards
    vector<int> dp = triangle[n - 1];

    for(int i = n - 2; i >= 0; i--)
    {
        for(int j = 0; j <= i; j++)
        {
            // Pick minimum of the two adjacent numbers in the row below
            dp[j] = triangle[i][j] + min(dp[j], dp[j + 1]);
        }
    }

    return dp[0];
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<vector<int>> triangle(n);
        for(int i = 0; i < n; i++)
        {
            triangle[i].resize(i + 1);
            for(int j = 0; j <= i; j++) cin >> triangle[i][j];
        }
        cout << minimumTotal(triangle) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. Moving top-down requires checking boundaries, but bottom-up is simpler and cleaner.
2. Initialize dp array with the bottom row of the triangle.
3. For each row from bottom-2 up to 0:
   - For each index j: dp[j] = triangle[i][j] + min(dp[j], dp[j+1]).
4. At the end, dp[0] holds the minimum path sum from top to bottom.

SAMPLE INPUT:
4
2
3 4
6 5 7
4 1 8 3

SAMPLE OUTPUT:
11

EXPLANATION:
Path: 2 -> 3 -> 5 -> 1 with minimum total sum = 11.

RECURRENCE RELATION:
dp[i][j] = triangle[i][j] + min(dp[i+1][j], dp[i+1][j+1])
Base Case: dp[n-1][j] = triangle[n-1][j]

TIME COMPLEXITY:
O(n^2)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming - Bottom-Up Tree/Triangle
*/

//---------Grid Unique Paths

#include <bits/stdc++.h>
using namespace std;

int uniquePaths(int m, int n)
{
    // dp[j] stores number of ways to reach column j in current row
    vector<int> dp(n, 1);

    for(int i = 1; i < m; i++)
    {
        for(int j = 1; j < n; j++)
        {
            // dp[j] (from top) + dp[j-1] (from left)
            dp[j] = dp[j] + dp[j - 1];
        }
    }

    return dp[n - 1];
}

int main()
{
    int m, n;
    if(cin >> m >> n)
    {
        cout << uniquePaths(m, n) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[i][j] represents the number of unique paths from (0, 0) to (i, j).
2. From each cell, you can only move Right or Down.
3. Therefore, to reach (i, j), you must come from either (i-1, j) or (i, j-1):
   dp[i][j] = dp[i-1][j] + dp[i][j-1].
4. Base case: First row and first column have only 1 way (moving straight right or down).
5. Space optimization: We only need the previous row value and current left value.

SAMPLE INPUT:
3 7

SAMPLE OUTPUT:
28

EXPLANATION:
Total paths from (0,0) to (2,6) in a 3x7 grid is 28.

RECURRENCE RELATION:
dp[i][j] = dp[i-1][j] + dp[i][j-1]
Base Case: dp[0][j] = dp[i][0] = 1

TIME COMPLEXITY:
O(m * n)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming - 2D Counting Combinations
*/

//---------Paths in a Grid with Obstacles

#include <bits/stdc++.h>
using namespace std;

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid)
{
    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();

    // If start or destination is an obstacle, no path exists
    if(obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1)
        return 0;

    vector<long long> dp(n, 0);
    dp[0] = 1;

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(obstacleGrid[i][j] == 1)
            {
                dp[j] = 0; // Obstacle blocks all paths through this cell
            }
            else if(j > 0)
            {
                dp[j] = dp[j] + dp[j - 1];
            }
        }
    }

    return dp[n - 1];
}

int main()
{
    int m, n;
    if(cin >> m >> n)
    {
        vector<vector<int>> grid(m, vector<int>(n));
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++) cin >> grid[i][j];
        }
        cout << uniquePathsWithObstacles(grid) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. Similar to Grid Unique Paths, but when obstacleGrid[i][j] == 1,
   no paths can pass through it, so dp[i][j] = 0.
2. If cell is free (obstacleGrid[i][j] == 0):
   dp[i][j] = dp[i-1][j] + dp[i][j-1].
3. Space optimization reduces 2D table to 1D vector of size n.

SAMPLE INPUT:
3 3
0 0 0
0 1 0
0 0 0

SAMPLE OUTPUT:
2

EXPLANATION:
Only 2 paths reach the bottom-right corner without touching cell (1, 1).

RECURRENCE RELATION:
dp[i][j] = 0                               if obstacleGrid[i][j] == 1
dp[i][j] = dp[i-1][j] + dp[i][j-1]         otherwise

TIME COMPLEXITY:
O(m * n)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming - Grid Path with Constraints
*/

//---------Max Rectangular Area with all 1s (Maximal Rectangle)

#include <bits/stdc++.h>
using namespace std;

// Monotonic stack subroutine to find maximum rectangle area in a histogram
int largestRectangleArea(vector<int>& heights)
{
    stack<int> st;
    int maxArea = 0;
    int n = heights.size();

    for(int i = 0; i <= n; i++)
    {
        int h = (i == n) ? 0 : heights[i];
        while(!st.empty() && heights[st.top()] > h)
        {
            int height = heights[st.top()];
            st.pop();
            int width = st.empty() ? i : (i - st.top() - 1);
            maxArea = max(maxArea, height * width);
        }
        st.push(i);
    }

    return maxArea;
}

int maximalRectangle(vector<vector<char>>& matrix)
{
    if(matrix.empty() || matrix[0].empty()) return 0;
    int m = matrix.size();
    int n = matrix[0].size();

    vector<int> heights(n, 0);
    int maxRect = 0;

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            // Cumulative height of consecutive 1s in column j
            if(matrix[i][j] == '1')
                heights[j]++;
            else
                heights[j] = 0;
        }
        maxRect = max(maxRect, largestRectangleArea(heights));
    }

    return maxRect;
}

int main()
{
    int m, n;
    if(cin >> m >> n)
    {
        vector<vector<char>> matrix(m, vector<char>(n));
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++) cin >> matrix[i][j];
        }
        cout << maximalRectangle(matrix) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. Treat each row as the base of a histogram where bar height represents
   consecutive 1s extending upwards.
2. For each row:
   - If matrix[i][j] == '1': heights[j] += 1
   - If matrix[i][j] == '0': heights[j] = 0 (base is reset)
3. For each updated histogram row, calculate largest rectangular area using
   a monotonic increasing stack in O(n) time.
4. The maximum area encountered across all rows is the maximal rectangle.

SAMPLE INPUT:
4 5
1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

SAMPLE OUTPUT:
6

EXPLANATION:
The maximal rectangle of all 1s has height 2 and width 3, area = 6.

TIME COMPLEXITY:
O(m * n)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming - Row-wise Histogram + Monotonic Stack
*/

//---------Count Rectangular Areas with all 1s

#include <bits/stdc++.h>
using namespace std;

int numSubmat(vector<vector<int>>& mat)
{
    int m = mat.size();
    int n = mat[0].size();

    // heights[i][j] = number of consecutive 1s ending at (i, j) moving upwards
    vector<vector<int>> heights(m, vector<int>(n, 0));

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(mat[i][j] == 1)
            {
                heights[i][j] = (i == 0) ? 1 : heights[i - 1][j] + 1;
            }
        }
    }

    int totalRectangles = 0;

    // For every cell (i, j), count rectangles having bottom-right corner at (i, j)
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(mat[i][j] == 1)
            {
                int minHeight = heights[i][j];
                // Expand leftwards to columns k <= j
                for(int k = j; k >= 0 && mat[i][k] == 1; k--)
                {
                    minHeight = min(minHeight, heights[i][k]);
                    totalRectangles += minHeight;
                }
            }
        }
    }

    return totalRectangles;
}

int main()
{
    int m, n;
    if(cin >> m >> n)
    {
        vector<vector<int>> mat(m, vector<int>(n));
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++) cin >> mat[i][j];
        }
        cout << numSubmat(mat) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. First, preprocess consecutive 1s in each column:
   heights[i][j] = (mat[i][j] == 1) ? heights[i-1][j] + 1 : 0.
2. To count all submatrices (rectangles) of all 1s:
   - For each bottom-right corner at (i, j), expand horizontally to the left (column k from j down to 0).
   - The number of rectangles of width (j - k + 1) with bottom at row i is bounded by the
     minimum height among columns from k to j: minHeight = min(heights[i][k..j]).
   - Add minHeight to total count.

SAMPLE INPUT:
3 3
1 0 1
1 1 0
1 1 0

SAMPLE OUTPUT:
13

EXPLANATION:
Total submatrices containing only 1s:
1x1: 8
1x2: 3
2x1: 2
Total = 13.

RECURRENCE RELATION:
rectanglesEndingAt(i, j) = sum_{k=0..j} min_{c=k..j}(heights[i][c])

TIME COMPLEXITY:
O(m * n^2) (can be optimized to O(m * n) with monotonic stack)

SPACE COMPLEXITY:
O(m * n)

PATTERN:
Dynamic Programming - 2D Submatrix Counting
*/


//====================================================================
// SECTION: DP PROBLEMS ON SUBSET
//====================================================================

//---------Subset Sum

#include <bits/stdc++.h>
using namespace std;

bool isSubsetSum(vector<int>& arr, int target)
{
    // dp[j] indicates whether a subset with sum j is possible
    vector<bool> dp(target + 1, false);
    dp[0] = true; // Sum of 0 is always possible with an empty subset

    for(int num : arr)
    {
        // Traverse backwards to use each element at most once
        for(int j = target; j >= num; j--)
        {
            if(dp[j - num])
            {
                dp[j] = true;
            }
        }
    }

    return dp[target];
}

int main()
{
    int n, target;
    if(cin >> n >> target)
    {
        vector<int> arr(n);
        for(int i = 0; i < n; i++) cin >> arr[i];
        cout << (isSubsetSum(arr, target) ? "true" : "false") << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[j] is true if a subset with sum j can be formed.
2. Initialize dp[0] = true (empty set has sum 0), all others false.
3. For each element num in arr:
   - Iterate sum j backwards from target down to num.
   - If sum (j - num) was achievable without current element, then sum j
     is achievable by including num: dp[j] = dp[j] || dp[j - num].
4. Backward traversal ensures 0/1 knapsack behavior (each element used once).

SAMPLE INPUT:
6 9
3 34 4 12 5 2

SAMPLE OUTPUT:
true

EXPLANATION:
Subset [4, 5] or [3, 4, 2] has sum = 9.

RECURRENCE RELATION:
dp[j] = dp[j] || dp[j - num]

BASE CASE:
dp[0] = true

TIME COMPLEXITY:
O(n * target)

SPACE COMPLEXITY:
O(target)

PATTERN:
Dynamic Programming - 0/1 Knapsack Decision
*/

//---------Count Subsets with Given Sum

#include <bits/stdc++.h>
using namespace std;

int findWays(vector<int>& num, int tar)
{
    const int MOD = 1e9 + 7;
    // dp[j] = number of subsets having sum j
    vector<int> dp(tar + 1, 0);
    dp[0] = 1;

    for(int x : num)
    {
        for(int j = tar; j >= x; j--)
        {
            dp[j] = (dp[j] + dp[j - x]) % MOD;
        }
    }

    return dp[tar];
}

int main()
{
    int n, tar;
    if(cin >> n >> tar)
    {
        vector<int> arr(n);
        for(int i = 0; i < n; i++) cin >> arr[i];
        cout << findWays(arr, tar) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[j] stores the count of subsets that sum to j.
2. Initialize dp[0] = 1 (1 way to achieve sum 0: empty set).
3. For each number x:
   - Traverse j from tar down to x:
     dp[j] = (dp[j] + dp[j - x]) % MOD.
4. If the array contains zeros, each zero doubles the number of valid subsets
   since including or excluding 0 does not change the subset sum.

SAMPLE INPUT:
4 5
1 4 4 5

SAMPLE OUTPUT:
3

EXPLANATION:
Subsets summing to 5: {1, 4}, {1, 4}, {5}. Total = 3.

RECURRENCE RELATION:
dp[j] = dp[j] + dp[j - x]

TIME COMPLEXITY:
O(n * tar)

SPACE COMPLEXITY:
O(tar)

PATTERN:
Dynamic Programming - 0/1 Knapsack Counting
*/

//---------Partition a Set into 2 Equal Sum (Equal Partition)

#include <bits/stdc++.h>
using namespace std;

bool canPartition(vector<int>& nums)
{
    int totalSum = 0;
    for(int x : nums) totalSum += x;

    // Odd sum cannot be partitioned into two equal integer halves
    if(totalSum % 2 != 0) return false;

    int target = totalSum / 2;
    vector<bool> dp(target + 1, false);
    dp[0] = true;

    for(int num : nums)
    {
        for(int j = target; j >= num; j--)
        {
            dp[j] = dp[j] || dp[j - num];
        }
    }

    return dp[target];
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> nums(n);
        for(int i = 0; i < n; i++) cin >> nums[i];
        cout << (canPartition(nums) ? "true" : "false") << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. Two subsets with equal sum must each sum to totalSum / 2.
2. If totalSum is odd, equal partition is impossible; return false immediately.
3. If totalSum is even, the problem reduces directly to the Subset Sum problem
   with target = totalSum / 2.
4. Solve via 1D boolean DP table with backward traversal.

SAMPLE INPUT:
4
1 5 11 5

SAMPLE OUTPUT:
true

EXPLANATION:
Array can be partitioned as [1, 5, 5] and [11], each with sum = 11.

RECURRENCE RELATION:
canPartition(nums) = isSubsetSum(nums, totalSum / 2)

TIME COMPLEXITY:
O(n * totalSum)

SPACE COMPLEXITY:
O(totalSum)

PATTERN:
Dynamic Programming - Reduction to Subset Sum
*/

//---------Largest Divisible Subset

#include <bits/stdc++.h>
using namespace std;

vector<int> largestDivisibleSubset(vector<int>& nums)
{
    int n = nums.size();
    if(n == 0) return {};

    // Sorting is crucial: if a % b == 0 and b % c == 0, then a % c == 0
    sort(nums.begin(), nums.end());

    vector<int> dp(n, 1);       // Length of largest divisible subset ending at i
    vector<int> parent(n, -1);  // To reconstruct the subset
    int maxLen = 1;
    int maxIdx = 0;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < i; j++)
        {
            if(nums[i] % nums[j] == 0 && dp[j] + 1 > dp[i])
            {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        if(dp[i] > maxLen)
        {
            maxLen = dp[i];
            maxIdx = i;
        }
    }

    // Reconstruct subset using parent pointers
    vector<int> result;
    int curr = maxIdx;
    while(curr != -1)
    {
        result.push_back(nums[curr]);
        curr = parent[curr];
    }
    reverse(result.begin(), result.end());

    return result;
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> nums(n);
        for(int i = 0; i < n; i++) cin >> nums[i];
        vector<int> ans = largestDivisibleSubset(nums);
        for(int x : ans) cout << x << " ";
        cout << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. Sort nums in ascending order.
2. By sorting, if nums[i] % nums[j] == 0 (where j < i), then nums[i] is divisible
   by all elements in the subset ending at nums[j] due to transitivity of divisibility.
3. Similar to LIS:
   dp[i] = 1 + max({dp[j] : 0 <= j < i and nums[i] % nums[j] == 0} U {0}).
4. Use parent array to trace back and reconstruct the largest subset.

SAMPLE INPUT:
4
1 2 4 8

SAMPLE OUTPUT:
1 2 4 8

EXPLANATION:
Every pair in [1, 2, 4, 8] satisfies a % b == 0 or b % a == 0.

RECURRENCE RELATION:
dp[i] = max(dp[i], dp[j] + 1)  for all 0 <= j < i where nums[i] % nums[j] == 0

TIME COMPLEXITY:
O(n^2)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming - LIS Variant with Divisibility & Path Reconstruction
*/

//---------Count Subsets with Given XOR

#include <bits/stdc++.h>
using namespace std;

int subsetXOR(vector<int>& arr, int k)
{
    int n = arr.size();
    if(n == 0) return (k == 0) ? 1 : 0;

    // Find maximum element to determine maximum possible XOR value
    int maxEle = *max_element(arr.begin(), arr.end());
    int maxXOR = 1;
    while(maxXOR <= maxEle)
    {
        maxXOR <<= 1;
    }
    maxXOR = max(maxXOR * 2, 1024);

    // dp[j] = number of subsets having XOR sum equal to j
    vector<int> dp(maxXOR, 0);
    dp[0] = 1; // Empty subset has XOR sum 0

    for(int x : arr)
    {
        vector<int> nextDp = dp;
        for(int j = 0; j < maxXOR; j++)
        {
            if(dp[j] > 0)
            {
                // Including element x creates XOR state (j ^ x)
                nextDp[j ^ x] += dp[j];
            }
        }
        dp = move(nextDp);
    }

    return (k < maxXOR) ? dp[k] : 0;
}

int main()
{
    int n, k;
    if(cin >> n >> k)
    {
        vector<int> arr(n);
        for(int i = 0; i < n; i++) cin >> arr[i];
        cout << subsetXOR(arr, k) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[j] represents the number of subsets with XOR sum equal to j.
2. Base condition: dp[0] = 1 (empty set XOR sum is 0).
3. For each element x in arr:
   - Every existing subset with XOR sum j can be augmented with x,
     producing a new subset with XOR sum (j ^ x).
   - Update: nextDp[j ^ x] += dp[j].
4. After processing all elements, dp[k] is the count of subsets with XOR sum equal to k.

SAMPLE INPUT:
4 6
4 2 2 6

SAMPLE OUTPUT:
4

EXPLANATION:
Subsets with XOR = 6:
{4, 2}, {4, 2}, {6}, {4, 2, 2, 6} -> Total = 4.

RECURRENCE RELATION:
dp[i][j] = dp[i-1][j] + dp[i-1][j ^ arr[i-1]]

TIME COMPLEXITY:
O(n * maxXOR) where maxXOR <= 2^(ceil(log2(max_val)) + 1)

SPACE COMPLEXITY:
O(maxXOR)

PATTERN:
Dynamic Programming - 0/1 Knapsack with XOR Operation
*/

//---------Minimum Subset Difference

#include <bits/stdc++.h>
using namespace std;

int minSubsetSumDifference(vector<int>& arr)
{
    int n = arr.size();
    int totalSum = 0;
    for(int x : arr) totalSum += x;

    // Run subset sum DP up to totalSum / 2
    int target = totalSum / 2;
    vector<bool> dp(target + 1, false);
    dp[0] = true;

    for(int num : arr)
    {
        for(int j = target; j >= num; j--)
        {
            dp[j] = dp[j] || dp[j - num];
        }
    }

    // Find the largest subset sum s <= totalSum / 2 that is achievable
    int s1 = 0;
    for(int j = target; j >= 0; j--)
    {
        if(dp[j])
        {
            s1 = j;
            break;
        }
    }

    // Difference between the two subset sums: (totalSum - s1) - s1
    return totalSum - 2 * s1;
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> arr(n);
        for(int i = 0; i < n; i++) cin >> arr[i];
        cout << minSubsetSumDifference(arr) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. Divide array into two subsets S1 and S2 such that |sum(S1) - sum(S2)| is minimized.
2. Since sum(S1) + sum(S2) = totalSum, difference is:
   |totalSum - 2 * sum(S1)|.
3. To minimize this difference, sum(S1) should be as close as possible to totalSum / 2.
4. Run subset sum DP up to totalSum / 2.
5. The largest achievable sum s1 <= totalSum / 2 minimizes the difference:
   minDiff = totalSum - 2 * s1.

SAMPLE INPUT:
4
1 6 11 5

SAMPLE OUTPUT:
1

EXPLANATION:
Subset 1: [1, 5, 6] (sum = 12)
Subset 2: [11] (sum = 11)
Difference = |12 - 11| = 1.

RECURRENCE RELATION:
minDiff = min_{0 <= s <= totalSum / 2, dp[s] == true} (totalSum - 2 * s)

TIME COMPLEXITY:
O(n * totalSum)

SPACE COMPLEXITY:
O(totalSum)

PATTERN:
Dynamic Programming - 0/1 Knapsack Partition Optimization
*/


//====================================================================
// SECTION: ROD CUTTING & STICK CUTTING PROBLEMS
//====================================================================

//---------Classic Rod Cutting Problem (Unbounded Knapsack)

#include <bits/stdc++.h>
using namespace std;

int cutRod(vector<int>& price, int n)
{
    // dp[i] represents the maximum revenue obtainable by cutting a rod of length i
    vector<int> dp(n + 1, 0);

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= i; j++)
        {
            // Cut a piece of length j with price[j-1], remaining rod has length (i - j)
            dp[i] = max(dp[i], price[j - 1] + dp[i - j]);
        }
    }

    return dp[n];
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> price(n);
        for(int i = 0; i < n; i++) cin >> price[i];
        cout << cutRod(price, n) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[i] represents the maximum revenue obtainable by cutting a rod of length i.
2. For a rod of length i, we can make the first cut at length j (where 1 <= j <= i).
3. The revenue from this cut is price[j-1] + dp[i-j] (optimal solution for the remainder).
4. Take the maximum over all possible cut lengths j from 1 to i:
   dp[i] = max_{1 <= j <= i} (price[j-1] + dp[i-j]).
5. Base case: A rod of length 0 yields 0 revenue (dp[0] = 0).

SAMPLE INPUT:
8
1 5 8 9 10 17 17 20

SAMPLE OUTPUT:
22

EXPLANATION:
Cut the rod of length 8 into two pieces of length 2 and 6.
Value = price[1] + price[5] = 5 + 17 = 22.

RECURRENCE RELATION:
dp[i] = max_{1 <= j <= i} (price[j - 1] + dp[i - j])
Base Case: dp[0] = 0

TIME COMPLEXITY:
O(n^2)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming - Unbounded Knapsack
*/

//---------Minimum Cost to Cut a Stick (LeetCode 1547)

#include <bits/stdc++.h>
using namespace std;

int minCost(int n, vector<int>& cuts)
{
    // Add boundaries 0 and n to the cut positions
    cuts.push_back(0);
    cuts.push_back(n);
    sort(cuts.begin(), cuts.end());

    int m = cuts.size();
    // dp[i][j] stores the minimum cost to make all cuts between cuts[i] and cuts[j]
    vector<vector<int>> dp(m, vector<int>(m, 0));

    // Length of the interval in cuts array
    for(int len = 2; len < m; len++)
    {
        for(int i = 0; i < m - len; i++)
        {
            int j = i + len;
            dp[i][j] = INT_MAX;

            // Try each cut position k strictly between i and j
            for(int k = i + 1; k < j; k++)
            {
                int cost = (cuts[j] - cuts[i]) + dp[i][k] + dp[k][j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    return dp[0][m - 1];
}

int main()
{
    int n, c;
    if(cin >> n >> c)
    {
        vector<int> cuts(c);
        for(int i = 0; i < c; i++) cin >> cuts[i];
        cout << minCost(n, cuts) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. Whenever we make a cut at position k on a stick between cuts[i] and cuts[j],
   the cost incurred is the current stick's length: cuts[j] - cuts[i].
2. The cut splits the stick into two sub-problems:
   - Stick between cuts[i] and cuts[k] (cost = dp[i][k])
   - Stick between cuts[k] and cuts[j] (cost = dp[k][j])
3. Append 0 and n to cuts and sort them.
4. dp[i][j] = (cuts[j] - cuts[i]) + min_{i < k < j} (dp[i][k] + dp[k][j]).
5. Base case: When j == i + 1, no cuts remain between them, so dp[i][j] = 0.

SAMPLE INPUT:
7 4
1 3 4 5

SAMPLE OUTPUT:
16

EXPLANATION:
Cuts sorted with boundaries: [0, 1, 3, 4, 5, 7].
Optimal sequence: Cut at 3 (cost 7), then 1 (cost 3), then 4 (cost 4), then 5 (cost 2).
Total cost = 7 + 3 + 4 + 2 = 16.

RECURRENCE RELATION:
dp[i][j] = (cuts[j] - cuts[i]) + min_{i < k < j} (dp[i][k] + dp[k][j])

TIME COMPLEXITY:
O(m^3) where m is number of cuts + 2

SPACE COMPLEXITY:
O(m^2)

PATTERN:
Dynamic Programming - Matrix Chain Multiplication (Interval DP)
*/

//---------Maximize The Cut Segments (Cut into lengths x, y, z)

#include <bits/stdc++.h>
using namespace std;

int maximizeTheCuts(int n, int x, int y, int z)
{
    // dp[i] = maximum segments a rod of length i can be cut into
    vector<int> dp(n + 1, -1);
    dp[0] = 0; // 0 length requires 0 cuts

    for(int i = 1; i <= n; i++)
    {
        if(i >= x && dp[i - x] != -1) dp[i] = max(dp[i], dp[i - x] + 1);
        if(i >= y && dp[i - y] != -1) dp[i] = max(dp[i], dp[i - y] + 1);
        if(i >= z && dp[i - z] != -1) dp[i] = max(dp[i], dp[i - z] + 1);
    }

    return (dp[n] == -1) ? 0 : dp[n];
}

int main()
{
    int n, x, y, z;
    if(cin >> n >> x >> y >> z)
    {
        cout << maximizeTheCuts(n, x, y, z) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. dp[i] stores the maximum number of cut segments of a rod of length i
   using only lengths x, y, and z.
2. Initialize dp[0] = 0 and all other dp[i] = -1 (unreachable).
3. At length i:
   - Try cutting a segment of length x: dp[i - x] + 1
   - Try cutting a segment of length y: dp[i - y] + 1
   - Try cutting a segment of length z: dp[i - z] + 1
   Take the maximum among valid previous states.
4. If dp[n] is -1, it's impossible to cut the rod completely into given segments.

SAMPLE INPUT:
4 2 1 1

SAMPLE OUTPUT:
4

EXPLANATION:
Cut into 4 segments of length 1 each.

RECURRENCE RELATION:
dp[i] = 1 + max({dp[i - x], dp[i - y], dp[i - z]}) where dp state != -1

TIME COMPLEXITY:
O(n)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming - 1D Unbounded Knapsack Maximization
*/

//---------Integer Break (LeetCode 343)

#include <bits/stdc++.h>
using namespace std;

int integerBreak(int n)
{
    // dp[i] stores the maximum product achievable by splitting integer i into at least 2 parts
    vector<int> dp(n + 1, 0);
    dp[1] = 1;

    for(int i = 2; i <= n; i++)
    {
        for(int j = 1; j < i; j++)
        {
            // Either don't break (i - j) further: j * (i - j)
            // Or break (i - j) further: j * dp[i - j]
            dp[i] = max({dp[i], j * (i - j), j * dp[i - j]});
        }
    }

    return dp[n];
}

int main()
{
    int n;
    if(cin >> n)
    {
        cout << integerBreak(n) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. Analogous to rod cutting where length n is cut into integers, but we maximize the PRODUCT.
2. For number i, split off a piece of size j (1 <= j < i).
3. The remaining piece (i - j) can either:
   - Not be broken further: product = j * (i - j)
   - Be broken further into sub-pieces: product = j * dp[i - j]
4. dp[i] = max_{1 <= j < i} (max(j * (i - j), j * dp[i - j])).

SAMPLE INPUT:
10

SAMPLE OUTPUT:
36

EXPLANATION:
10 = 3 + 3 + 4, product = 3 * 3 * 4 = 36.

RECURRENCE RELATION:
dp[i] = max_{1 <= j < i} (max(j * (i - j), j * dp[i - j]))

TIME COMPLEXITY:
O(n^2)

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming - Rod Cutting with Multiplicative Values
*/

//====================================================================
// SECTION: CLIMBING STAIRS PROBLEMS
//====================================================================

//---------Climbing Stairs (LeetCode 70)

#include <bits/stdc++.h>
using namespace std;

int climbStairs(int n)
{
    if(n <= 2) return n;

    int prev2 = 1; // ways to reach 1st step
    int prev1 = 2; // ways to reach 2nd step

    for(int i = 3; i <= n; i++)
    {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }

    return prev1;
}

int main()
{
    int n;
    if(cin >> n)
    {
        cout << climbStairs(n) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. You can climb 1 or 2 steps at a time.
2. To reach the n-th step, you can:
   - Come from the (n-1)-th step by taking 1 step.
   - Come from the (n-2)-th step by taking 2 steps.
3. Total ways: dp[n] = dp[n-1] + dp[n-2].
4. Space optimized to O(1) by maintaining only the last two values (Fibonacci sequence).

SAMPLE INPUT:
3

SAMPLE OUTPUT:
3

EXPLANATION:
Ways to reach step 3:
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step

RECURRENCE RELATION:
dp[n] = dp[n - 1] + dp[n - 2]
Base Cases: dp[1] = 1, dp[2] = 2

TIME COMPLEXITY:
O(n)

SPACE COMPLEXITY:
O(1)

PATTERN:
Dynamic Programming - Fibonacci Sequence / Step Transition
*/

//---------Min Cost Climbing Stairs (LeetCode 746)

#include <bits/stdc++.h>
using namespace std;

int minCostClimbingStairs(vector<int>& cost)
{
    int n = cost.size();
    int prev2 = 0; // Cost to reach step 0
    int prev1 = 0; // Cost to reach step 1

    for(int i = 2; i <= n; i++)
    {
        // Pay cost of leaving (i-1) or leaving (i-2)
        int curr = min(prev1 + cost[i - 1], prev2 + cost[i - 2]);
        prev2 = prev1;
        prev1 = curr;
    }

    return prev1;
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> cost(n);
        for(int i = 0; i < n; i++) cin >> cost[i];
        cout << minCostClimbingStairs(cost) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. You can start at index 0 or index 1 with 0 initial cost.
2. dp[i] represents the minimum cost to reach step i (where n is the top of the floor).
3. To reach step i:
   - Step from (i-1), paying cost[i-1]: dp[i-1] + cost[i-1]
   - Step from (i-2), paying cost[i-2]: dp[i-2] + cost[i-2]
4. dp[i] = min(dp[i-1] + cost[i-1], dp[i-2] + cost[i-2]).
5. Space optimized to O(1).

SAMPLE INPUT:
3
10 15 20

SAMPLE OUTPUT:
15

EXPLANATION:
Start at index 1 (cost 15), take 2 steps to reach the top. Total cost = 15.

RECURRENCE RELATION:
dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2])
Base Cases: dp[0] = 0, dp[1] = 0

TIME COMPLEXITY:
O(n)

SPACE COMPLEXITY:
O(1)

PATTERN:
Dynamic Programming - Minimum Cost Step Path
*/

//---------Climbing Stairs with K Steps

#include <bits/stdc++.h>
using namespace std;

int climbStairsKSteps(int n, int k)
{
    const int MOD = 1e9 + 7;
    // dp[i] = number of ways to reach step i using at most k steps
    vector<int> dp(n + 1, 0);
    dp[0] = 1;

    long long windowSum = 1; // Running sum of previous k steps

    for(int i = 1; i <= n; i++)
    {
        dp[i] = windowSum % MOD;
        windowSum = (windowSum + dp[i]) % MOD;

        // Slide the window: remove dp[i - k] when i >= k
        if(i >= k)
        {
            windowSum = (windowSum - dp[i - k] + MOD) % MOD;
        }
    }

    return dp[n];
}

int main()
{
    int n, k;
    if(cin >> n >> k)
    {
        cout << climbStairsKSteps(n, k) << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. From step i, you can jump to step (i + 1), (i + 2), ..., (i + k).
2. Conversely, to reach step i, you could have arrived from any step j where
   max(0, i - k) <= j < i:
   dp[i] = sum_{j = 1}^{k} dp[i - j].
3. Naive summation takes O(n * k).
4. Using a sliding window sum of size k reduces the transition to O(1),
   making overall time O(n).

SAMPLE INPUT:
4 2

SAMPLE OUTPUT:
5

EXPLANATION:
With k = 2, it is standard Fibonacci: 1, 2, 3, 5 -> 5 ways to reach step 4.

RECURRENCE RELATION:
dp[i] = sum_{j=1}^{min(i, k)} dp[i - j]
Base Case: dp[0] = 1

TIME COMPLEXITY:
O(n) with sliding window

SPACE COMPLEXITY:
O(n)

PATTERN:
Dynamic Programming + Sliding Window Optimization
*/

//---------Frog Jump (LeetCode 403)

#include <bits/stdc++.h>
using namespace std;

bool canCross(vector<int>& stones)
{
    int n = stones.size();
    // stoneMap maps stone position to its index in stones array
    unordered_map<int, int> stoneMap;
    for(int i = 0; i < n; i++)
    {
        stoneMap[stones[i]] = i;
    }

    // dp[i] stores all valid last jump sizes that reached stones[i]
    vector<unordered_set<int>> dp(n);
    dp[0].insert(0); // At starting stone 0, initial jump speed is 0

    for(int i = 0; i < n; i++)
    {
        for(int k : dp[i])
        {
            // From stones[i], the next jump can be k-1, k, or k+1
            for(int step = k - 1; step <= k + 1; step++)
            {
                if(step > 0)
                {
                    int nextPos = stones[i] + step;
                    if(stoneMap.count(nextPos))
                    {
                        int nextIdx = stoneMap[nextPos];
                        dp[nextIdx].insert(step);
                    }
                }
            }
        }
    }

    // Frog can cross if the last stone can be reached with any jump size
    return !dp[n - 1].empty();
}

int main()
{
    int n;
    if(cin >> n)
    {
        vector<int> stones(n);
        for(int i = 0; i < n; i++) cin >> stones[i];
        cout << (canCross(stones) ? "true" : "false") << "\n";
    }
    return 0;
}

/*
MAIN LOGIC:
1. A frog starts at stone 0. Its first jump must be of length 1 (if stone 1 exists).
2. If the last jump was k units, the next jump can be k-1, k, or k+1 units (where jump > 0).
3. State: dp[i] contains a set of jump sizes that landed on stones[i].
4. For each stone i and each jump k in dp[i]:
   - Try jumps of size step in {k-1, k, k+1} with step > 0.
   - Next stone position = stones[i] + step.
   - If nextPos contains a stone at index nextIdx, insert 'step' into dp[nextIdx].
5. If dp[n-1] is not empty, the frog can reach the destination stone.

SAMPLE INPUT:
8
0 1 3 5 6 8 12 17

SAMPLE OUTPUT:
true

EXPLANATION:
Jumps: 0 -> 1 (k=1), 1 -> 3 (k=2), 3 -> 5 (k=2), 5 -> 8 (k=3),
       8 -> 12 (k=4), 12 -> 17 (k=5). All jumps valid, reached end.

RECURRENCE RELATION:
If k in dp[i] and (stones[i] + step == stones[j]) for step in {k-1, k, k+1}:
dp[j].insert(step)

TIME COMPLEXITY:
O(n^2)

SPACE COMPLEXITY:
O(n^2)

PATTERN:
Dynamic Programming - State Reachability with Variable Speed / Jump Tracking
*/
