
#include <bits/stdc++.h>
using namespace std;

// =====================================================
// LCS DIFF: GIT-STYLE INSERTION, DELETION AND MATCHING
// =====================================================

struct Operation {
    char type;       // '=' match, '+' insertion, '-' deletion
    string value;
    int oldLine = 0;
    int newLine = 0;
};

// Standard LCS + Diff reconstruction
vector<Operation> lcsDiff(
    vector<string>& oldFile,
    vector<string>& newFile
) {
    int n = oldFile.size();
    int m = newFile.size();

    // Step 1: Build LCS DP table
    vector<vector<int>> dp(
        n + 1, vector<int>(m + 1, 0)
    );

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {

            if (oldFile[i - 1] == newFile[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else {
                dp[i][j] = max(
                    dp[i - 1][j],
                    dp[i][j - 1]
                );
            }
        }
    }

    // Step 2: Backtracking to find operations
    vector<Operation> ops;

    int i = n;
    int j = m;

    while (i > 0 || j > 0) {

        // Case 1: Matching lines
        if (i > 0 && j > 0 &&
            oldFile[i - 1] == newFile[j - 1]) {

            ops.push_back({
                '=', oldFile[i - 1], i, j
            });

            i--;
            j--;
        }

        // Case 2: Insertion
        else if (j > 0 &&
                 (i == 0 || dp[i][j - 1] >= dp[i - 1][j])) {

            ops.push_back({
                '+', newFile[j - 1], 0, j
            });

            j--;
        }

        // Case 3: Deletion
        else {
            ops.push_back({
                '-', oldFile[i - 1], i, 0
            });

            i--;
        }
    }

    // Step 3: Reverse operations
    reverse(ops.begin(), ops.end());

    return ops;
}


// =====================================================
// PRINT DIFF
// =====================================================

void printDiff(vector<Operation>& ops) {

    int additions = 0;
    int deletions = 0;

    cout << "\nDIFF OUTPUT\n";
    cout << "-----------------------------\n";

    for (auto op : ops) {

        cout << op.type << " " << op.value << endl;

        if (op.type == '+')
            additions++;

        if (op.type == '-')
            deletions++;
    }

    cout << "\nInsertions: " << additions;
    cout << "\nDeletions: " << deletions;
    cout << "\nLCS Length: "
         << ops.size() - additions - deletions << endl;
}


// =====================================================
// EXAMPLE 1: LINE COMPARISON
// =====================================================

void lineComparison() {

    vector<string> oldFile = {
        "int main() {",
        "cout << Hello;",
        "return 0;",
        "}"
    };

    vector<string> newFile = {
        "int main() {",
        "cout << Hello;",
        "cout << Welcome;",
        "return 0;",
        "}"
    };

    vector<Operation> ops =
        lcsDiff(oldFile, newFile);

    cout << "LINE COMPARISON\n";

    printDiff(ops);
}


// =====================================================
// EXAMPLE 2: CHARACTER COMPARISON
// =====================================================

void characterComparison() {

    string oldStr = "ACGTAC";
    string newStr = "AGTCAC";

    vector<string> oldChars, newChars;

    // Convert strings into individual characters
    for (char c : oldStr)
        oldChars.push_back(string(1, c));

    for (char c : newStr)
        newChars.push_back(string(1, c));

    vector<Operation> ops =
        lcsDiff(oldChars, newChars);

    cout << "\n\nCHARACTER COMPARISON\n";

    printDiff(ops);
}


// =====================================================
// MAIN
// =====================================================

int main() {

    lineComparison();

    characterComparison();

    return 0;
}
