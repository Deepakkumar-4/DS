#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <climits>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>

using namespace std;

// ============================================================
// 1. Reverse a String
// ============================================================
string reverseString(string s) {
    int start = 0, end = (int)s.length() - 1;
    while (start < end) {
        swap(s[start++], s[end--]);
    }
    return s;
}

// ============================================================
// 2. Check whether a String is Palindrome or not
// ============================================================
bool isPalindrome(string s) {
    int l = 0, r = (int)s.length() - 1;
    while (l < r) {
        if (s[l++] != s[r--]) return false;
    }
    return true;
}

// ============================================================
// 3. Find Duplicate characters in a string
// ============================================================
void printDuplicates(string s) {
    int count[256] = {0};
    for (char c : s) count[(unsigned char)c]++;
    for (int i = 0; i < 256; i++) {
        if (count[i] > 1) {
            cout << (char)i << " : " << count[i] << "\n";
        }
    }
}

/*
// ============================================================
// 4. Why strings are immutable in Java?
// - String Constant Pool (Memory efficiency): Reuses identical strings.
// - Security: Used in class loaders, network sockets, DB credentials.
// - Thread Safety: Read-only instances can be shared without synchronization.
// - Caching HashCode: Enables fast hashing in HashMaps/HashSets.
// ============================================================
*/

// ============================================================
// 5. Check whether one string is a rotation of another
// ============================================================
bool areRotations(string s1, string s2) {
    if (s1.length() != s2.length()) return false;
    string temp = s1 + s1;
    return temp.find(s2) != string::npos;
}

// ============================================================
// 6. Check whether a string is a valid shuffle of two strings
// ============================================================
bool isValidShuffle(string s1, string s2, string res) {
    if (s1.length() + s2.length() != res.length()) return false;
    int i = 0, j = 0, k = 0;
    while (k < res.length()) {
        if (i < s1.length() && s1[i] == res[k]) i++;
        else if (j < s2.length() && s2[j] == res[k]) j++;
        else return false;
        k++;
    }
    return (i == s1.length() && j == s2.length());
}

// ============================================================
// 7. Count and Say problem
// ============================================================
string countAndSay(int n) {
    if (n == 1) return "1";
    string prev = countAndSay(n - 1);
    string res = "";
    int count = 1;
    for (int i = 0; i < prev.length(); i++) {
        if (i + 1 < prev.length() && prev[i] == prev[i + 1]) {
            count++;
        } else {
            res += to_string(count) + prev[i];
            count = 1;
        }
    }
    return res;
}

// ============================================================
// 8. Longest Palindromic Substring
// ============================================================
string longestPalindromeSubstring(string s) {
    int n = s.length();
    if (n < 2) return s;
    int start = 0, maxLen = 1;

    for (int i = 0; i < n; i++) {
        // Odd length center
        int l = i, r = i;
        while (l >= 0 && r < n && s[l] == s[r]) {
            if (r - l + 1 > maxLen) { start = l; maxLen = r - l + 1; }
            l--; r++;
        }
        // Even length center
        l = i; r = i + 1;
        while (l >= 0 && r < n && s[l] == s[r]) {
            if (r - l + 1 > maxLen) { start = l; maxLen = r - l + 1; }
            l--; r++;
        }
    }
    return s.substr(start, maxLen);
}

// ============================================================
// 9. Find Longest Recurring Subsequence in String
// ============================================================
int longestRepeatingSubsequence(string s) {
    int n = s.length();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (s[i - 1] == s[j - 1] && i != j) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][n];
}

// ============================================================
// 10. Print all Subsequences of a string
// ============================================================
void printSubsequences(string s, string output, int idx) {
    if (idx == s.length()) {
        cout << output << " ";
        return;
    }
    printSubsequences(s, output + s[idx], idx + 1); // Include
    printSubsequences(s, output, idx + 1);          // Exclude
}

// ============================================================
// 11. Print all the permutations of the given string
// ============================================================
void permuteString(string s, int l, int r) {
    if (l == r) {
        cout << s << " ";
        return;
    }
    for (int i = l; i <= r; i++) {
        swap(s[l], s[i]);
        permuteString(s, l + 1, r);
        swap(s[l], s[i]);
    }
}

// ============================================================
// 12. Split Binary String into Substrings with Equal 0s and 1s
// ============================================================
int maxBinarySplits(string s) {
    int count0 = 0, count1 = 0, splits = 0;
    for (char c : s) {
        if (c == '0') count0++;
        else count1++;
        if (count0 == count1) splits++;
    }
    return (count0 == count1) ? splits : -1;
}

// ============================================================
// 13. Word Wrap Problem
// ============================================================
int wordWrap(vector<int>& arr, int k) {
    int n = arr.size();
    vector<int> dp(n, 0);
    vector<int> ans(n, 0);

    for (int i = n - 1; i >= 0; i--) {
        int curLen = -1;
        dp[i] = INT_MAX;
        for (int j = i; j < n; j++) {
            curLen += (arr[j] + 1);
            if (curLen > k) break;
            if (j == n - 1) {
                dp[i] = 0;
                break;
            }
            int cost = (k - curLen) * (k - curLen) + dp[j + 1];
            dp[i] = min(dp[i], cost);
        }
    }
    return dp[0];
}

// ============================================================
// 14. EDIT Distance
// ============================================================
int editDistance(string s1, string s2) {
    int m = s1.length(), n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }
    }
    return dp[m][n];
}

// ============================================================
// 15. Next Greater Number with Same Digits
// ============================================================
string nextGreaterPermutation(string s) {
    int n = s.length(), i = n - 2;
    while (i >= 0 && s[i] >= s[i + 1]) i--;
    if (i >= 0) {
        int j = n - 1;
        while (s[j] <= s[i]) j--;
        swap(s[i], s[j]);
        reverse(s.begin() + i + 1, s.end());
        return s;
    }
    return "-1";
}

// ============================================================
// 16. Balanced Parenthesis Problem
// ============================================================
bool isBalancedParentheses(string expr) {
    stack<char> st;
    for (char c : expr) {
        if (c == '(' || c == '{' || c == '[') st.push(c);
        else {
            if (st.empty()) return false;
            char t = st.top();
            if ((c == ')' && t == '(') || (c == '}' && t == '{') || (c == ']' && t == '[')) st.pop();
            else return false;
        }
    }
    return st.empty();
}

// ============================================================
// 17. Word Break Problem
// ============================================================
bool wordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> dict(wordDict.begin(), wordDict.end());
    int n = s.length();
    vector<bool> dp(n + 1, false);
    dp[0] = true;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (dp[j] && dict.count(s.substr(j, i - j))) {
                dp[i] = true;
                break;
            }
        }
    }
    return dp[n];
}

// ============================================================
// 18. Rabin-Karp Algorithm for Pattern Searching
// ============================================================
void searchRabinKarp(string pat, string txt, int q = 101) {
    int d = 256;
    int M = pat.length(), N = txt.length();
    int p = 0, t = 0, h = 1;

    for (int i = 0; i < M - 1; i++) h = (h * d) % q;

    for (int i = 0; i < M; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    for (int i = 0; i <= N - M; i++) {
        if (p == t) {
            bool match = true;
            for (int j = 0; j < M; j++) {
                if (txt[i + j] != pat[j]) { match = false; break; }
            }
            if (match) cout << "Pattern found at index " << i << "\n";
        }
        if (i < N - M) {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;
            if (t < 0) t = (t + q);
        }
    }
}

// ============================================================
// 19. KMP Algorithm for Pattern Searching
// ============================================================
vector<int> computeLPSArray(string pat) {
    int m = pat.length(), len = 0, i = 1;
    vector<int> lps(m, 0);
    while (i < m) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i++] = len;
        } else {
            if (len != 0) len = lps[len - 1];
            else lps[i++] = 0;
        }
    }
    return lps;
}

void KMPSearch(string pat, string txt) {
    int M = pat.length(), N = txt.length();
    vector<int> lps = computeLPSArray(pat);
    int i = 0, j = 0;
    while (i < N) {
        if (pat[j] == txt[i]) { i++; j++; }
        if (j == M) {
            cout << "Pattern found at index " << i - j << "\n";
            j = lps[j - 1];
        } else if (i < N && pat[j] != txt[i]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
}

// ============================================================
// 20. Convert a Sentence into its Mobile Numeric Keypad Sequence
// ============================================================
string printSentenceKeypad(string input) {
    string str[] = {"2","22","222", "3","33","333", "4","44","444",
                    "5","55","555", "6","66","666", "7","77","777","7777",
                    "8","88","888", "9","99","999","9999"};
    string output = "";
    for (char c : input) {
        if (c == ' ') output += "0";
        else output += str[c - 'A'];
    }
    return output;
}

// ============================================================
// 21. Minimum Number of Bracket Reversals Needed
// ============================================================
int countMinBracketReversals(string s) {
    if (s.length() % 2 != 0) return -1;
    int open = 0, close = 0;
    for (char c : s) {
        if (c == '{') open++;
        else {
            if (open > 0) open--;
            else close++;
        }
    }
    return (open + 1) / 2 + (close + 1) / 2;
}

// ============================================================
// 22. Count All Palindromic Subsequences
// ============================================================
long long countPS(string str) {
    int n = str.length();
    vector<vector<long long>> dp(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) dp[i][i] = 1;

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (str[i] == str[j]) {
                dp[i][j] = dp[i + 1][j] + dp[i][j - 1] + 1;
            } else {
                dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1];
            }
        }
    }
    return dp[0][n - 1];
}

// ============================================================
// 23. Count occurrences of a given string in 2D Character Array
// ============================================================
int count2DStringOccurrences(vector<vector<char>>& grid, string target, int r, int c, int idx) {
    int found = 0;
    if (r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size() && target[idx] == grid[r][c]) {
        char temp = target[idx];
        grid[r][c] = '#';
        if (idx == target.length() - 1) {
            found = 1;
        } else {
            found += count2DStringOccurrences(grid, target, r + 1, c, idx + 1);
            found += count2DStringOccurrences(grid, target, r - 1, c, idx + 1);
            found += count2DStringOccurrences(grid, target, r, c + 1, idx + 1);
            found += count2DStringOccurrences(grid, target, r, c - 1, idx + 1);
        }
        grid[r][c] = temp;
    }
    return found;
}

// ============================================================
// 24. Search a Word in a 2D Grid of Characters
// ============================================================
bool search2DGridWord(vector<vector<char>>& grid, string word, int row, int col) {
    if (grid[row][col] != word[0]) return false;
    int x[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int y[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int dir = 0; dir < 8; dir++) {
        int rd = row + x[dir], cd = col + y[dir], k;
        for (k = 1; k < word.length(); k++) {
            if (rd < 0 || rd >= grid.size() || cd < 0 || cd >= grid[0].size() || grid[rd][cd] != word[k])
                break;
            rd += x[dir];
            cd += y[dir];
        }
        if (k == word.length()) return true;
    }
    return false;
}

// ============================================================
// 25. Boyer Moore Algorithm for Pattern Searching (Bad Character)
// ============================================================
void searchBoyerMoore(string txt, string pat) {
    int m = pat.size(), n = txt.size();
    int badchar[256];
    fill(badchar, badchar + 256, -1);
    for (int i = 0; i < m; i++) badchar[(unsigned char)pat[i]] = i;

    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;
        while (j >= 0 && pat[j] == txt[s + j]) j--;
        if (j < 0) {
            cout << "Pattern occurs at shift = " << s << "\n";
            s += (s + m < n) ? m - badchar[(unsigned char)txt[s + m]] : 1;
        } else {
            s += max(1, j - badchar[(unsigned char)txt[s + j]]);
        }
    }
}

// ============================================================
// 26. Converting Roman Numerals to Decimal
// ============================================================
int romanToDecimal(string s) {
    unordered_map<char, int> val = {
        {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
        {'C', 100}, {'D', 500}, {'M', 1000}
    };
    int ans = 0;
    for (int i = 0; i < s.length(); i++) {
        if (i + 1 < s.length() && val[s[i]] < val[s[i + 1]]) {
            ans -= val[s[i]];
        } else {
            ans += val[s[i]];
        }
    }
    return ans;
}

// ============================================================
// 27. Longest Common Prefix
// ============================================================
string longestCommonPrefix(vector<string>& strs) {
    if (strs.empty()) return "";
    string prefix = strs[0];
    for (int i = 1; i < strs.size(); i++) {
        while (strs[i].find(prefix) != 0) {
            prefix = prefix.substr(0, prefix.length() - 1);
            if (prefix.empty()) return "";
        }
    }
    return prefix;
}

// ============================================================
// 28. Number of Flips to Make Binary String Alternate
// ============================================================
int minFlipsAlternate(string s) {
    int c1 = 0, c2 = 0; // c1 for 0101..., c2 for 1010...
    for (int i = 0; i < s.length(); i++) {
        char exp1 = (i % 2 == 0) ? '0' : '1';
        char exp2 = (i % 2 == 0) ? '1' : '0';
        if (s[i] != exp1) c1++;
        if (s[i] != exp2) c2++;
    }
    return min(c1, c2);
}

// ============================================================
// 29. Find the First Repeated Word in String
// ============================================================
string firstRepeatedWord(string s) {
    stringstream ss(s);
    string word;
    unordered_set<string> seen;
    while (ss >> word) {
        if (seen.count(word)) return word;
        seen.insert(word);
    }
    return "No repeated word";
}

// ============================================================
// 30. Minimum Number of Swaps for Bracket Balancing
// ============================================================
int minimumBracketSwaps(string s) {
    int count = 0, p = 0, swaps = 0;
    for (char c : s) {
        if (c == '[') {
            count--;
            if (p > 0) {
                swaps += p;
                p--;
            }
        } else {
            count++;
            p++;
        }
    }
    return swaps;
}

// ============================================================
// 31. Longest Common Subsequence between Two Strings
// ============================================================
int lcs(string s1, string s2) {
    int m = s1.length(), n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) dp[i][j] = 1 + dp[i - 1][j - 1];
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[m][n];
}

// ============================================================
// 32. Program to Generate All Possible Valid IP Addresses
// ============================================================
bool isValidPart(string s) {
    if (s.empty() || s.length() > 3 || (s[0] == '0' && s.length() > 1)) return false;
    int val = stoi(s);
    return val >= 0 && val <= 255;
}

vector<string> generateIPAddresses(string s) {
    vector<string> res;
    int n = s.length();
    for (int i = 1; i < 4 && i < n - 2; i++) {
        for (int j = i + 1; j < i + 4 && j < n - 1; j++) {
            for (int k = j + 1; k < j + 4 && k < n; k++) {
                string p1 = s.substr(0, i);
                string p2 = s.substr(i, j - i);
                string p3 = s.substr(j, k - j);
                string p4 = s.substr(k);
                if (isValidPart(p1) && isValidPart(p2) && isValidPart(p3) && isValidPart(p4)) {
                    res.push_back(p1 + "." + p2 + "." + p3 + "." + p4);
                }
            }
        }
    }
    return res;
}

// ============================================================
// 33. Smallest Window Containing All Characters of String Itself
// ============================================================
string smallestSubstrDistinctChars(string s) {
    unordered_set<char> distinct(s.begin(), s.end());
    int total = distinct.size();
    unordered_map<char, int> freq;
    int start = 0, minLen = INT_MAX, matchCount = 0, startIdx = -1;

    for (int end = 0; end < s.length(); end++) {
        freq[s[end]]++;
        if (freq[s[end]] == 1) matchCount++;

        while (matchCount == total) {
            if (end - start + 1 < minLen) {
                minLen = end - start + 1;
                startIdx = start;
            }
            freq[s[start]]--;
            if (freq[s[start]] == 0) matchCount--;
            start++;
        }
    }
    return (startIdx == -1) ? "" : s.substr(startIdx, minLen);
}

// ============================================================
// 34. Rearrange Characters such that No Two Adjacent are Same
// ============================================================
string rearrangeCharacters(string str) {
    unordered_map<char, int> freq;
    for (char c : str) freq[c]++;
    priority_queue<pair<int, char>> pq;
    for (auto it : freq) pq.push({it.second, it.first});

    string res = "";
    pair<int, char> prev = {-1, '#'};
    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        res += cur.second;
        if (prev.first > 0) pq.push(prev);
        cur.first--;
        prev = cur;
    }
    return (res.length() == str.length()) ? res : "";
}

// ============================================================
// 35. Minimum Characters Added at Front to Make String Palindrome
// ============================================================
int minCharsFrontPalindrome(string s) {
    string rev = s;
    reverse(rev.begin(), rev.end());
    string concat = s + "$" + rev;
    vector<int> lps = computeLPSArray(concat);
    return s.length() - lps.back();
}

// ============================================================
// 36. Given Sequence of Words, Print All Anagrams Together
// ============================================================
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> mp;
    for (string w : strs) {
        string sortedW = w;
        sort(sortedW.begin(), sortedW.end());
        mp[sortedW].push_back(w);
    }
    vector<vector<string>> res;
    for (auto p : mp) res.push_back(p.second);
    return res;
}

// ============================================================
// 37. Find Smallest Window in String Containing All Chars of Another
// ============================================================
string minWindowSubstring(string s, string p) {
    if (s.empty() || p.empty()) return "";
    int target[256] = {0}, window[256] = {0};
    for (char c : p) target[(unsigned char)c]++;

    int matched = 0, minLen = INT_MAX, startIdx = -1, l = 0;
    for (int r = 0; r < s.length(); r++) {
        window[(unsigned char)s[r]]++;
        if (target[(unsigned char)s[r]] > 0 && window[(unsigned char)s[r]] <= target[(unsigned char)s[r]]) {
            matched++;
        }
        while (matched == p.length()) {
            if (r - l + 1 < minLen) {
                minLen = r - l + 1;
                startIdx = l;
            }
            window[(unsigned char)s[l]]--;
            if (target[(unsigned char)s[l]] > 0 && window[(unsigned char)s[l]] < target[(unsigned char)s[l]]) {
                matched--;
            }
            l++;
        }
    }
    return (startIdx == -1) ? "" : s.substr(startIdx, minLen);
}

// ============================================================
// 38. Recursively Remove All Adjacent Duplicates
// ============================================================
string removeAdjacentDuplicates(string s) {
    string res = "";
    int i = 0, n = s.length();
    bool changed = false;

    while (i < n) {
        if (i < n - 1 && s[i] == s[i + 1]) {
            changed = true;
            while (i < n - 1 && s[i] == s[i + 1]) i++;
        } else {
            res += s[i];
        }
        i++;
    }
    return changed ? removeAdjacentDuplicates(res) : res;
}

// ============================================================
// 39. String Matching Where One Contains Wildcard Characters (*, ?)
// ============================================================
bool isWildcardMatch(string text, string pattern) {
    int m = text.length(), n = pattern.length();
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
    dp[0][0] = true;

    for (int j = 1; j <= n; j++) {
        if (pattern[j - 1] == '*') dp[0][j] = dp[0][j - 1];
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (pattern[j - 1] == '?' || pattern[j - 1] == text[i - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else if (pattern[j - 1] == '*') {
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
            }
        }
    }
    return dp[m][n];
}

// ============================================================
// 40. Number of Customers Who Could Not Get a Computer
// ============================================================
int runCustomerSimulation(int n, string seq) {
    int seen[26] = {0}; // 0 = not seen, 1 = using computer, 2 = left without
    int occupied = 0, unserved = 0;

    for (char c : seq) {
        int idx = c - 'A';
        if (seen[idx] == 0) {
            seen[idx] = 1;
            if (occupied < n) occupied++;
            else {
                seen[idx] = 2;
                unserved++;
            }
        } else if (seen[idx] == 1) {
            seen[idx] = 0;
            occupied--;
        }
    }
    return unserved;
}

// ============================================================
// 41. Transform One String to Another using Min Operations (Insert at Front)
// ============================================================
int minOpsToTransform(string A, string B) {
    if (A.length() != B.length()) return -1;
    int count[256] = {0};
    for (char c : A) count[(unsigned char)c]++;
    for (char c : B) count[(unsigned char)c]--;
    for (int i = 0; i < 256; i++) if (count[i] != 0) return -1;

    int i = A.length() - 1, j = B.length() - 1, res = 0;
    while (i >= 0) {
        if (A[i] == B[j]) j--;
        else res++;
        i--;
    }
    return res;
}

// ============================================================
// 42. Check if Two Given Strings are Isomorphic
// ============================================================
bool areIsomorphic(string s1, string s2) {
    if (s1.length() != s2.length()) return false;
    int m1[256] = {0}, m2[256] = {0};
    for (int i = 0; i < s1.length(); i++) {
        if (m1[(unsigned char)s1[i]] != m2[(unsigned char)s2[i]]) return false;
        m1[(unsigned char)s1[i]] = i + 1;
        m2[(unsigned char)s2[i]] = i + 1;
    }
    return true;
}

// ============================================================
// 43. Recursively Print All Sentences from List of Word Lists
// ============================================================
void printSentencesRec(vector<vector<string>>& words, int r, string sentence) {
    if (r == words.size()) {
        cout << sentence << "\n";
        return;
    }
    for (int c = 0; c < words[r].size(); c++) {
        string nextSentence = sentence.empty() ? words[r][c] : sentence + " " + words[r][c];
        printSentencesRec(words, r + 1, nextSentence);
    }
}

// ============================================================
// CLI MAIN RUNNER
// ============================================================
int main() {
    // 1. Basic String Checks Demo
    string str;
    cout << "Enter a string: ";
    cin >> str;

    cout << "Reversed: " << reverseString(str) << "\n";
    cout << "Is Palindrome: " << (isPalindrome(str) ? "Yes" : "No") << "\n";
    cout << "Longest Palindromic Substring: " << longestPalindromeSubstring(str) << "\n";
    cout << "Min characters to add at front to make Palindrome: " << minCharsFrontPalindrome(str) << "\n\n";

    // 2. Anagram Grouping Demo
    int n;
    cout << "Enter number of words for Anagram Grouping: ";
    cin >> n;
    vector<string> words(n);
    cout << "Enter " << n << " words: ";
    for (int i = 0; i < n; i++) cin >> words[i];

    vector<vector<string>> groups = groupAnagrams(words);
    cout << "Grouped Anagrams:\n";
    for (const auto& grp : groups) {
        cout << "[ ";
        for (const string& w : grp) cout << w << " ";
        cout << "]\n";
    }
    cout << "\n";

    // 3. Sentence Permutation Demo
    cout << "Sentence Generation from word-lists demo:\n";
    vector<vector<string>> wordTable = {
        {"you", "we"},
        {"have", "are"},
        {"sleep", "eat"}
    };
    printSentencesRec(wordTable, 0, "");

    return 0;
}