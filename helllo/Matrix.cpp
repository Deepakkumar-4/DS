#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>
#include <stack>
#include <unordered_map>

using namespace std;

// ============================================================
// 1. Spiral Traversal on a Matrix
// ============================================================
vector<int> spirallyTraverse(vector<vector<int>>& matrix, int r, int c) {
    vector<int> output;
    int top = 0, bottom = r - 1;
    int left = 0, right = c - 1;

    while (top <= bottom && left <= right) {
        // Traverse top row
        for (int i = left; i <= right; i++) output.push_back(matrix[top][i]);
        top++;

        // Traverse right column
        for (int i = top; i <= bottom; i++) output.push_back(matrix[i][right]);
        right--;

        // Traverse bottom row (if valid)
        if (top <= bottom) {
            for (int i = right; i >= left; i--) output.push_back(matrix[bottom][i]);
            bottom--;
        }

        // Traverse left column (if valid)
        if (left <= right) {
            for (int i = bottom; i >= top; i--) output.push_back(matrix[i][left]);
            left++;
        }
    }
    return output;
}

// ============================================================
// 2. Search an Element in a Matrix (Row & Column Wise Sorted)
// ============================================================
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) return false;
    int r = matrix.size();
    int c = matrix[0].size();

    // Start from top-right corner
    int i = 0, j = c - 1;
    while (i < r && j >= 0) {
        if (matrix[i][j] == target) return true;
        else if (matrix[i][j] > target) j--; // Move left
        else i++;                            // Move down
    }
    return false;
}

// ============================================================
// 3. Find Median in a Row-wise Sorted Matrix
// ============================================================
int countSmallerThanOrEqual(vector<int>& row, int mid) {
    int l = 0, h = row.size() - 1;
    while (l <= h) {
        int m = l + (h - l) / 2;
        if (row[m] <= mid) l = m + 1;
        else h = m - 1;
    }
    return l;
}

int medianRowWiseSorted(vector<vector<int>>& matrix, int r, int c) {
    int minVal = INT_MAX, maxVal = INT_MIN;
    for (int i = 0; i < r; i++) {
        minVal = min(minVal, matrix[i][0]);
        maxVal = max(maxVal, matrix[i][c - 1]);
    }

    int desired = (r * c + 1) / 2;
    while (minVal < maxVal) {
        int mid = minVal + (maxVal - minVal) / 2;
        int count = 0;
        for (int i = 0; i < r; i++) {
            count += countSmallerThanOrEqual(matrix[i], mid);
        }
        if (count < desired) minVal = mid + 1;
        else maxVal = mid;
    }
    return minVal;
}

// ============================================================
// 4. Find Row with Maximum No. of 1's (Boolean Sorted Matrix)
// ============================================================
int rowWithMax1s(vector<vector<int>>& arr, int n, int m) {
    int maxRow = -1;
    int j = m - 1; // Start at top-right

    for (int i = 0; i < n; i++) {
        while (j >= 0 && arr[i][j] == 1) {
            j--;
            maxRow = i;
        }
    }
    return maxRow;
}

// ============================================================
// 5. Print Elements in Sorted Order using Row-Column Wise Sorted Matrix
// ============================================================
struct HeapNode {
    int val, r, c;
    bool operator>(const HeapNode& other) const {
        return val > other.val;
    }
};

vector<int> sortedMatrix(vector<vector<int>>& mat, int n) {
    priority_queue<HeapNode, vector<HeapNode>, greater<HeapNode>> pq;
    vector<int> result;

    for (int i = 0; i < n; i++) {
        pq.push({mat[i][0], i, 0});
    }

    while (!pq.empty()) {
        HeapNode curr = pq.top();
        pq.pop();
        result.push_back(curr.val);

        if (curr.c + 1 < n) {
            pq.push({mat[curr.r][curr.c + 1], curr.r, curr.c + 1});
        }
    }
    return result;
}

// ============================================================
// 6. Maximum Size Rectangle (Max rectangle of 1's)
// ============================================================
int maxHistArea(vector<int>& heights) {
    int n = heights.size();
    stack<int> s;
    int maxArea = 0;

    for (int i = 0; i <= n; i++) {
        int curH = (i == n) ? 0 : heights[i];
        while (!s.empty() && heights[s.top()] >= curH) {
            int h = heights[s.top()];
            s.pop();
            int width = s.empty() ? i : (i - s.top() - 1);
            maxArea = max(maxArea, h * width);
        }
        s.push(i);
    }
    return maxArea;
}

int maxRectangle(vector<vector<int>>& M, int n, int m) {
    vector<int> height(m, 0);
    int maxArea = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (M[i][j] == 1) height[j]++;
            else height[j] = 0;
        }
        maxArea = max(maxArea, maxHistArea(height));
    }
    return maxArea;
}

// ============================================================
// 7. Find a Specific Pair in Matrix (mat[c][d] - mat[a][b] where c>a & d>b)
// ============================================================
int findMaxValuePair(vector<vector<int>>& mat, int n) {
    int maxVal = INT_MIN;
    vector<vector<int>> maxArr(n, vector<int>(n));

    maxArr[n - 1][n - 1] = mat[n - 1][n - 1];

    // Preprocess last row
    int curMax = mat[n - 1][n - 1];
    for (int j = n - 2; j >= 0; j--) {
        curMax = max(curMax, mat[n - 1][j]);
        maxArr[n - 1][j] = curMax;
    }

    // Preprocess last column
    curMax = mat[n - 1][n - 1];
    for (int i = n - 2; i >= 0; i--) {
        curMax = max(curMax, mat[i][n - 1]);
        maxArr[i][n - 1] = curMax;
    }

    // Bottom-up traversal
    for (int i = n - 2; i >= 0; i--) {
        for (int j = n - 2; j >= 0; j--) {
            if (maxArr[i + 1][j + 1] - mat[i][j] > maxVal) {
                maxVal = maxArr[i + 1][j + 1] - mat[i][j];
            }
            maxArr[i][j] = max({mat[i][j], maxArr[i + 1][j], maxArr[i][j + 1]});
        }
    }
    return maxVal;
}

// ============================================================
// 8. Rotate Matrix by 90 Degrees Clockwise
// ============================================================
void rotate90Clockwise(vector<vector<int>>& mat, int n) {
    // 1. Transpose matrix
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            swap(mat[i][j], mat[j][i]);
        }
    }
    // 2. Reverse each row
    for (int i = 0; i < n; i++) {
        reverse(mat[i].begin(), mat[i].end());
    }
}

// ============================================================
// 9. Kth Smallest Element in a Row-Column Wise Sorted Matrix
// ============================================================
int kthSmallest(vector<vector<int>>& mat, int n, int k) {
    int low = mat[0][0], high = mat[n - 1][n - 1];

    while (low < high) {
        int mid = low + (high - low) / 2;
        int count = 0;
        int j = n - 1;

        for (int i = 0; i < n; i++) {
            while (j >= 0 && mat[i][j] > mid) j--;
            count += (j + 1);
        }

        if (count < k) low = mid + 1;
        else high = mid;
    }
    return low;
}

// ============================================================
// 10. Common Elements in All Rows of a Given Matrix
// ============================================================
vector<int> findCommonElements(vector<vector<int>>& mat, int r, int c) {
    unordered_map<int, int> mp;
    vector<int> result;

    // Initialize first row
    for (int j = 0; j < c; j++) {
        mp[mat[0][j]] = 1;
    }

    // Traverse remaining rows
    for (int i = 1; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int val = mat[i][j];
            if (mp[val] == i) {
                mp[val] = i + 1;
                if (i == r - 1) result.push_back(val);
            }
        }
    }
    return result;
}

// ============================================================
// CLI MAIN RUNNER
// ============================================================
int main() {
    int r, c;
    cout << "Enter number of rows and columns (R C): ";
    cin >> r >> c;

    vector<vector<int>> matrix(r, vector<int>(c));
    cout << "Enter matrix elements (" << r * c << " values):\n";
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> matrix[i][j];
        }
    }

    // 1. Spiral Traversal
    cout << "\nSpiral Traversal: ";
    vector<int> spiral = spirallyTraverse(matrix, r, c);
    for (int val : spiral) cout << val << " ";
    cout << "\n";

    // 2. Search Target
    int target;
    cout << "\nEnter target to search in matrix: ";
    cin >> target;
    cout << "Target " << (searchMatrix(matrix, target) ? "Found" : "Not Found") << "\n";

    // 3. Row with max 1s (if binary)
    cout << "Row with max 1s: " << rowWithMax1s(matrix, r, c) << "\n";

    // 4. Common elements across rows
    vector<int> common = findCommonElements(matrix, r, c);
    cout << "Common elements across all rows: ";
    if (common.empty()) cout << "None";
    for (int val : common) cout << val << " ";
    cout << "\n";

    // 5. Rotate 90 degrees if square matrix
    if (r == c) {
        cout << "\nEnter 'k' for Kth smallest: ";
        int k;
        cin >> k;
        cout << k << "-th smallest element: " << kthSmallest(matrix, r, k) << "\n";

        rotate90Clockwise(matrix, r);
        cout << "\nMatrix after 90 Degree Clockwise Rotation:\n";
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << "\n";
        }
    }

    return 0;
}