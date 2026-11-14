#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// ============================================================
// 1. Reverse the array
// ============================================================
void reverseArray(vector<int>& arr) {
    int start = 0, end = arr.size() - 1;
    while (start < end) {
        swap(arr[start], arr[end]);
        start++;
        end--;
    }
}

// ============================================================
// 2. Find the maximum and minimum element in an array
// ============================================================
pair<int, int> findMinMax(vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return {-1, -1};
    int minVal = arr[0], maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }
    return {minVal, maxVal};
}

// ============================================================
// 3. Find the "Kth" max and min element of an array
// ============================================================
pair<int, int> findKthMinMax(vector<int> arr, int k) {
    sort(arr.begin(), arr.end());
    int n = arr.size();
    if (k <= 0 || k > n) return {-1, -1};
    return {arr[k - 1], arr[n - k]};
}

// ============================================================
// 4. Sort an array of 0s, 1s, and 2s (Dutch National Flag)
// ============================================================
void sort012(vector<int>& arr) {
    int low = 0, mid = 0, high = arr.size() - 1;
    while (mid <= high) {
        if (arr[mid] == 0) {
            swap(arr[low], arr[mid]);
            low++;
            mid++;
        } else if (arr[mid] == 1) {
            mid++;
        } else {
            swap(arr[mid], arr[high]);
            high--;
        }
    }
}

// ============================================================
// 5. Move all the negative elements to one side of the array
// ============================================================
void moveNegatives(vector<int>& arr) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        if (arr[left] < 0 && arr[right] < 0) {
            left++;
        } else if (arr[left] > 0 && arr[right] < 0) {
            swap(arr[left], arr[right]);
            left++;
            right--;
        } else if (arr[left] > 0 && arr[right] > 0) {
            right--;
        } else {
            left++;
            right--;
        }
    }
}

// ============================================================
// 6. Find Union and Intersection of two sorted arrays
// ============================================================
pair<vector<int>, vector<int>> unionAndIntersection(vector<int>& a, vector<int>& b) {
    vector<int> u, inter;
    int i = 0, j = 0;
    int n = a.size(), m = b.size();

    while (i < n && j < m) {
        if (a[i] < b[j]) {
            if (u.empty() || u.back() != a[i]) u.push_back(a[i]);
            i++;
        } else if (b[j] < a[i]) {
            if (u.empty() || u.back() != b[j]) u.push_back(b[j]);
            j++;
        } else {
            if (u.empty() || u.back() != a[i]) u.push_back(a[i]);
            if (inter.empty() || inter.back() != a[i]) inter.push_back(a[i]);
            i++;
            j++;
        }
    }
    while (i < n) {
        if (u.empty() || u.back() != a[i]) u.push_back(a[i]);
        i++;
    }
    while (j < m) {
        if (u.empty() || u.back() != b[j]) u.push_back(b[j]);
        j++;
    }
    return {u, inter};
}

// ============================================================
// 7. Cyclically rotate an array by one
// ============================================================
void rotateByOne(vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) return;
    int last = arr[n - 1];
    for (int i = n - 1; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
    arr[0] = last;
}

// ============================================================
// 8 & 13. Kadane's Algorithm (Largest Sum Contiguous Subarray)
// ============================================================
int maxSubarraySum(vector<int>& arr) {
    int maxSoFar = arr[0];
    int currMax = arr[0];
    for (size_t i = 1; i < arr.size(); i++) {
        currMax = max(arr[i], currMax + arr[i]);
        maxSoFar = max(maxSoFar, currMax);
    }
    return maxSoFar;
}

// ============================================================
// 9. Minimise the maximum difference between heights (Minimize Heights II)
// ============================================================
int getMinDiff(vector<int>& arr, int k) {
    int n = arr.size();
    if (n <= 1) return 0;
    sort(arr.begin(), arr.end());
    int ans = arr[n - 1] - arr[0];

    int smallest = arr[0] + k;
    int largest = arr[n - 1] - k;

    for (int i = 0; i < n - 1; i++) {
        int minH = min(smallest, arr[i + 1] - k);
        int maxH = max(largest, arr[i] + k);
        if (minH < 0) continue;
        ans = min(ans, maxH - minH);
    }
    return ans;
}

// ============================================================
// 10. Minimum number of jumps to reach end of array
// ============================================================
int minJumps(vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) return 0;
    if (arr[0] == 0) return -1;

    int maxReach = arr[0];
    int step = arr[0];
    int jump = 1;

    for (int i = 1; i < n; i++) {
        if (i == n - 1) return jump;
        maxReach = max(maxReach, i + arr[i]);
        step--;
        if (step == 0) {
            jump++;
            if (i >= maxReach) return -1;
            step = maxReach - i;
        }
    }
    return -1;
}

// ============================================================
// 11. Find duplicate in an array of N+1 Integers (Floyd's Cycle Detection)
// ============================================================
int findDuplicate(vector<int>& nums) {
    int slow = nums[0];
    int fast = nums[0];
    do {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while (slow != fast);

    fast = nums[0];
    while (slow != fast) {
        slow = nums[slow];
        fast = nums[fast];
    }
    return slow;
}

// ============================================================
// 12. Merge 2 sorted arrays without using Extra space (Gap method)
// ============================================================
void mergeTwoSortedArrays(vector<int>& a, vector<int>& b) {
    int n = a.size(), m = b.size();
    int len = n + m;
    int gap = (len / 2) + (len % 2);

    while (gap > 0) {
        int left = 0, right = left + gap;
        while (right < len) {
            // Case 1: both pointers in a
            if (left < n && right < n) {
                if (a[left] > a[right]) swap(a[left], a[right]);
            }
            // Case 2: left in a, right in b
            else if (left < n && right >= n) {
                if (a[left] > b[right - n]) swap(a[left], b[right - n]);
            }
            // Case 3: both in b
            else if (left >= n && right >= n) {
                if (b[left - n] > b[right - n]) swap(b[left - n], b[right - n]);
            }
            left++;
            right++;
        }
        if (gap == 1) break;
        gap = (gap / 2) + (gap % 2);
    }
}

// ============================================================
// 14. Merge Overlapping Intervals
// ============================================================
vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {
    if (intervals.empty()) return {};
    sort(intervals.begin(), intervals.end());

    vector<vector<int>> merged;
    merged.push_back(intervals[0]);

    for (size_t i = 1; i < intervals.size(); i++) {
        if (intervals[i][0] <= merged.back()[1]) {
            merged.back()[1] = max(merged.back()[1], intervals[i][1]);
        } else {
            merged.push_back(intervals[i]);
        }
    }
    return merged;
}

// ============================================================
// 15. Next Permutation
// ============================================================
void nextPermutation(vector<int>& nums) {
    int n = nums.size(), i = n - 2;
    while (i >= 0 && nums[i] >= nums[i + 1]) i--;

    if (i >= 0) {
        int j = n - 1;
        while (nums[j] <= nums[i]) j--;
        swap(nums[i], nums[j]);
    }
    reverse(nums.begin() + i + 1, nums.end());
}

// ============================================================
// 16. Count Inversions (Merge Sort approach)
// ============================================================
long long mergeAndCount(vector<int>& arr, int l, int m, int r) {
    vector<int> left(arr.begin() + l, arr.begin() + m + 1);
    vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);

    int i = 0, j = 0, k = l;
    long long invCount = 0;

    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
            invCount += (left.size() - i);
        }
    }
    while (i < left.size()) arr[k++] = left[i++];
    while (j < right.size()) arr[k++] = right[j++];
    return invCount;
}

long long mergeSortInversions(vector<int>& arr, int l, int r) {
    long long count = 0;
    if (l < r) {
        int m = l + (r - l) / 2;
        count += mergeSortInversions(arr, l, m);
        count += mergeSortInversions(arr, m + 1, r);
        count += mergeAndCount(arr, l, m, r);
    }
    return count;
}

// ============================================================
// 17. Best time to buy and Sell stock (Single Transaction)
// ============================================================
int maxProfit(vector<int>& prices) {
    int minPrice = INT_MAX;
    int maxProf = 0;
    for (int p : prices) {
        minPrice = min(minPrice, p);
        maxProf = max(maxProf, p - minPrice);
    }
    return maxProf;
}

// ============================================================
// 18. Find all pairs on integer array whose sum is equal to given number
// ============================================================
int getPairsCount(vector<int>& arr, int k) {
    unordered_map<int, int> freq;
    int count = 0;
    for (int x : arr) {
        int target = k - x;
        if (freq.find(target) != freq.end()) {
            count += freq[target];
        }
        freq[x]++;
    }
    return count;
}

// ============================================================
// 19. Find common elements in 3 sorted arrays
// ============================================================
vector<int> commonElementsIn3(vector<int>& A, vector<int>& B, vector<int>& C) {
    int i = 0, j = 0, k = 0;
    int n1 = A.size(), n2 = B.size(), n3 = C.size();
    vector<int> res;

    while (i < n1 && j < n2 && k < n3) {
        if (A[i] == B[j] && B[j] == C[k]) {
            if (res.empty() || res.back() != A[i]) res.push_back(A[i]);
            i++; j++; k++;
        } else if (A[i] < B[j]) {
            i++;
        } else if (B[j] < C[k]) {
            j++;
        } else {
            k++;
        }
    }
    return res;
}

// ============================================================
// 20. Rearrange array in alternating positive and negative items with O(1) space
// ============================================================
void rotateSubarray(vector<int>& arr, int start, int end) {
    int temp = arr[end];
    for (int i = end; i > start; i--) arr[i] = arr[i - 1];
    arr[start] = temp;
}

void rearrangeAlternate(vector<int>& arr) {
    int n = arr.size();
    int wrongIndex = -1;

    for (int i = 0; i < n; i++) {
        if (wrongIndex != -1) {
            if ((arr[wrongIndex] >= 0 && arr[i] < 0) || (arr[wrongIndex] < 0 && arr[i] >= 0)) {
                rotateSubarray(arr, wrongIndex, i);
                if (i - wrongIndex >= 2) wrongIndex += 2;
                else wrongIndex = -1;
            }
        } else {
            // Even index should have positive, odd should have negative
            if ((i % 2 == 0 && arr[i] < 0) || (i % 2 != 0 && arr[i] >= 0)) {
                wrongIndex = i;
            }
        }
    }
}

// ============================================================
// 21. Find if there is any subarray with sum equal to 0
// ============================================================
bool hasZeroSumSubarray(vector<int>& arr) {
    unordered_set<int> prefixSums;
    int sum = 0;
    for (int x : arr) {
        sum += x;
        if (sum == 0 || prefixSums.count(sum)) return true;
        prefixSums.insert(sum);
    }
    return false;
}

// ============================================================
// 22. Find factorial of a large number
// ============================================================
vector<int> factorialLarge(int n) {
    vector<int> res;
    res.push_back(1);

    for (int x = 2; x <= n; x++) {
        int carry = 0;
        for (size_t i = 0; i < res.size(); i++) {
            int prod = res[i] * x + carry;
            res[i] = prod % 10;
            carry = prod / 10;
        }
        while (carry) {
            res.push_back(carry % 10);
            carry /= 10;
        }
    }
    reverse(res.begin(), res.end());
    return res;
}

// ============================================================
// 23. Find maximum product subarray
// ============================================================
long long maxProductSubarray(vector<int>& arr) {
    int n = arr.size();
    long long maxProd = arr[0];
    long long minProd = arr[0];
    long long ans = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] < 0) swap(maxProd, minProd);
        maxProd = max((long long)arr[i], maxProd * arr[i]);
        minProd = min((long long)arr[i], minProd * arr[i]);
        ans = max(ans, maxProd);
    }
    return ans;
}

// ============================================================
// 24. Find longest consecutive subsequence
// ============================================================
int findLongestConsecutiveSubseq(vector<int>& arr) {
    unordered_set<int> s(arr.begin(), arr.end());
    int longest = 0;

    for (int val : s) {
        // If it's the start of a streak
        if (!s.count(val - 1)) {
            int currVal = val;
            int count = 1;
            while (s.count(currVal + 1)) {
                currVal++;
                count++;
            }
            longest = max(longest, count);
        }
    }
    return longest;
}

// ============================================================
// 25. Elements that appear more than n/k times
// ============================================================
vector<int> moreThanNdK(vector<int>& arr, int k) {
    int n = arr.size();
    unordered_map<int, int> freq;
    for (int x : arr) freq[x]++;

    vector<int> ans;
    for (auto it : freq) {
        if (it.second > n / k) ans.push_back(it.first);
    }
    return ans;
}

// ============================================================
// 26. Maximum profit by buying and selling a share at most twice
// ============================================================
int maxProfitTwice(vector<int>& price) {
    int n = price.size();
    if (n <= 1) return 0;

    vector<int> profit(n, 0);
    int maxPrice = price[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        maxPrice = max(maxPrice, price[i]);
        profit[i] = max(profit[i + 1], maxPrice - price[i]);
    }

    int minPrice = price[0];
    for (int i = 1; i < n; i++) {
        minPrice = min(minPrice, price[i]);
        profit[i] = max(profit[i - 1], profit[i] + (price[i] - minPrice));
    }
    return profit[n - 1];
}

// ============================================================
// 27. Find whether an array is a subset of another array
// ============================================================
bool isSubset(vector<int>& a1, vector<int>& a2) {
    unordered_map<int, int> freq;
    for (int x : a1) freq[x]++;
    for (int x : a2) {
        if (freq[x] <= 0) return false;
        freq[x]--;
    }
    return true;
}

// ============================================================
// 28. Find the triplet that sum to a given value
// ============================================================
bool find3Numbers(vector<int> arr, int X) {
    int n = arr.size();
    sort(arr.begin(), arr.end());

    for (int i = 0; i < n - 2; i++) {
        int l = i + 1, r = n - 1;
        while (l < r) {
            int currentSum = arr[i] + arr[l] + arr[r];
            if (currentSum == X) return true;
            else if (currentSum < X) l++;
            else r--;
        }
    }
    return false;
}

// ============================================================
// 29. Trapping Rain Water problem
// ============================================================
long long trappingWater(vector<int>& arr) {
    int n = arr.size();
    int left = 0, right = n - 1;
    int leftMax = 0, rightMax = 0;
    long long water = 0;

    while (left <= right) {
        if (arr[left] <= arr[right]) {
            if (arr[left] >= leftMax) leftMax = arr[left];
            else water += leftMax - arr[left];
            left++;
        } else {
            if (arr[right] >= rightMax) rightMax = arr[right];
            else water += rightMax - arr[right];
            right--;
        }
    }
    return water;
}

// ============================================================
// 30. Chocolate Distribution problem
// ============================================================
long long chocolateDistribution(vector<int>& arr, int m) {
    int n = arr.size();
    if (m == 0 || n == 0 || m > n) return 0;
    sort(arr.begin(), arr.end());

    long long minDiff = LLONG_MAX;
    for (int i = 0; i + m - 1 < n; i++) {
        long long diff = arr[i + m - 1] - arr[i];
        minDiff = min(minDiff, diff);
    }
    return minDiff;
}

// ============================================================
// 31. Smallest Subarray with sum greater than a given value
// ============================================================
int smallestSubWithSum(vector<int>& arr, int x) {
    int n = arr.size();
    int currSum = 0, minLen = n + 1;
    int start = 0, end = 0;

    while (end < n) {
        while (currSum <= x && end < n) currSum += arr[end++];
        while (currSum > x && start < n) {
            minLen = min(minLen, end - start);
            currSum -= arr[start++];
        }
    }
    return (minLen > n) ? 0 : minLen;
}

// ============================================================
// 32. Three way partitioning of an array around a given value range [a, b]
// ============================================================
void threeWayPartition(vector<int>& arr, int a, int b) {
    int low = 0, mid = 0, high = arr.size() - 1;
    while (mid <= high) {
        if (arr[mid] < a) {
            swap(arr[low++], arr[mid++]);
        } else if (arr[mid] > b) {
            swap(arr[mid], arr[high--]);
        } else {
            mid++;
        }
    }
}

// ============================================================
// 33. Minimum swaps required to bring elements <= K together
// ============================================================
int minSwap(vector<int>& arr, int k) {
    int n = arr.size();
    int count = 0;
    for (int x : arr) if (x <= k) count++;

    int bad = 0;
    for (int i = 0; i < count; i++) if (arr[i] > k) bad++;

    int ans = bad;
    for (int i = 0, j = count; j < n; i++, j++) {
        if (arr[i] > k) bad--;
        if (arr[j] > k) bad++;
        ans = min(ans, bad);
    }
    return ans;
}

// ============================================================
// 34. Minimum number of operations required to make an array palindrome
// ============================================================
int minOpsToMakePalindrome(vector<int>& arr) {
    int i = 0, j = arr.size() - 1;
    int ops = 0;

    while (i <= j) {
        if (arr[i] == arr[j]) {
            i++;
            j--;
        } else if (arr[i] < arr[j]) {
            arr[i + 1] += arr[i];
            i++;
            ops++;
        } else {
            arr[j - 1] += arr[j];
            j--;
            ops++;
        }
    }
    return ops;
}

// ============================================================
// 35. Median of 2 sorted arrays of equal size
// ============================================================
double medianEqualSize(vector<int>& ar1, vector<int>& ar2) {
    int n = ar1.size();
    int i = 0, j = 0;
    int m1 = -1, m2 = -1;

    for (int count = 0; count <= n; count++) {
        m2 = m1;
        if (i == n) {
            m1 = ar2[j++];
        } else if (j == n) {
            m1 = ar1[i++];
        } else if (ar1[i] <= ar2[j]) {
            m1 = ar1[i++];
        } else {
            m1 = ar2[j++];
        }
    }
    return (m1 + m2) / 2.0;
}

// ============================================================
// 36. Median of 2 sorted arrays of different size (Binary Search O(log(min(N, M))))
// ============================================================
double medianDiffSize(vector<int>& a, vector<int>& b) {
    if (a.size() > b.size()) return medianDiffSize(b, a);
    int n1 = a.size(), n2 = b.size();
    int low = 0, high = n1;

    while (low <= high) {
        int cut1 = (low + high) / 2;
        int cut2 = (n1 + n2 + 1) / 2 - cut1;

        int l1 = (cut1 == 0) ? INT_MIN : a[cut1 - 1];
        int l2 = (cut2 == 0) ? INT_MIN : b[cut2 - 1];
        int r1 = (cut1 == n1) ? INT_MAX : a[cut1];
        int r2 = (cut2 == n2) ? INT_MAX : b[cut2];

        if (l1 <= r2 && l2 <= r1) {
            if ((n1 + n2) % 2 == 1) return max(l1, l2);
            return (max(l1, l2) + min(r1, r2)) / 2.0;
        } else if (l1 > r2) {
            high = cut1 - 1;
        } else {
            low = cut1 + 1;
        }
    }
    return 0.0;
}

// ============================================================
// CLI MAIN RUNNER
// ============================================================
int main() {
    int n;
    cout << "Enter number of elements for array: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) cin >> arr[i];

    // 1. Min and Max
    pair<int, int> minMax = findMinMax(arr);
    cout << "\nMinimum Element: " << minMax.first;
    cout << "\nMaximum Element: " << minMax.second << "\n";

    // 2. Kadane's Algorithm
    cout << "Largest Contiguous Subarray Sum: " << maxSubarraySum(arr) << "\n";

    // 3. Trapping Rain Water
    cout << "Water Trapped: " << trappingWater(arr) << " units\n";

    // 4. Large Factorial Demo
    int factNum;
    cout << "\nEnter a number to calculate its large factorial: ";
    cin >> factNum;
    vector<int> factDigits = factorialLarge(factNum);
    cout << "Factorial: ";
    for (int d : factDigits) cout << d;
    cout << "\n\n";

    // 5. Reverse Array Demo
    reverseArray(arr);
    cout << "Reversed Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    return 0;
}