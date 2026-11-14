#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <cctype>

using namespace std;

// ============================================================
// 1. Implement Stack from Scratch (Array-based)
// ============================================================
struct ArrayStack
{
    int arr[1000];
    int topIdx;
    ArrayStack() { topIdx = -1; }
    void push(int x)
    {
        if (topIdx < 999)
            arr[++topIdx] = x;
    }
    int pop() { return (topIdx == -1) ? -1 : arr[topIdx--]; }
    int peek() { return (topIdx == -1) ? -1 : arr[topIdx]; }
    bool empty() { return topIdx == -1; }
};

// ============================================================
// 2. Implement Queue from Scratch (Array-based)
// ============================================================
struct ArrayQueue
{
    int arr[1000];
    int frontIdx, rearIdx;
    ArrayQueue()
    {
        frontIdx = 0;
        rearIdx = 0;
    }
    void push(int x)
    {
        if (rearIdx < 1000)
            arr[rearIdx++] = x;
    }
    int pop() { return (frontIdx == rearIdx) ? -1 : arr[frontIdx++]; }
    int front() { return (frontIdx == rearIdx) ? -1 : arr[frontIdx]; }
    bool empty() { return frontIdx == rearIdx; }
};

// ============================================================
// 3. Implement 2 Stacks in an Array
// ============================================================
struct TwoStacks
{
    int arr[1000];
    int top1, top2, size;
    TwoStacks(int n = 1000)
    {
        size = n;
        top1 = -1;
        top2 = n;
    }
    void push1(int x)
    {
        if (top1 < top2 - 1)
            arr[++top1] = x;
    }
    void push2(int x)
    {
        if (top1 < top2 - 1)
            arr[--top2] = x;
    }
    int pop1()
    {
        return (top1 >= 0) ? arr[top1--] : -1;
    }
    int pop2()
    {
        return (top2 < size) ? arr[top2++] : -1;
    }
};

// ============================================================
// 4. Find the Middle Element of a Stack (DLL-based O(1))
// ============================================================
struct MidStackNode
{
    int val;
    MidStackNode *prev;
    MidStackNode *next;
    MidStackNode(int v) : val(v), prev(NULL), next(NULL) {}
};

struct MidStack
{
    MidStackNode *head = NULL;
    MidStackNode *mid = NULL;
    int count = 0;

    void push(int x)
    {
        MidStackNode *node = new MidStackNode(x);
        node->next = head;
        if (head)
            head->prev = node;
        head = node;
        count++;
        if (count == 1)
            mid = node;
        else if (count % 2 != 0)
            mid = mid->prev;
    }

    int pop()
    {
        if (!head)
            return -1;
        MidStackNode *temp = head;
        int res = head->val;
        head = head->next;
        if (head)
            head->prev = NULL;
        count--;
        if (count % 2 == 0 && mid)
            mid = mid->next;
        delete temp;
        return res;
    }

    int findMiddle()
    {
        return mid ? mid->val : -1;
    }
};

// ============================================================
// 5. Implement "N" Stacks in an Array
// ============================================================
struct KStacks
{
    vector<int> arr, topArr, nextArr;
    int freeSpot;
    KStacks(int k, int n)
    {
        arr.resize(n);
        nextArr.resize(n);
        topArr.assign(k, -1);
        freeSpot = 0;
        for (int i = 0; i < n - 1; i++)
            nextArr[i] = i + 1;
        nextArr[n - 1] = -1;
    }
    void push(int item, int sn)
    {
        if (freeSpot == -1)
            return;
        int i = freeSpot;
        freeSpot = nextArr[i];
        nextArr[i] = topArr[sn];
        topArr[sn] = i;
        arr[i] = item;
    }
    int pop(int sn)
    {
        if (topArr[sn] == -1)
            return -1;
        int i = topArr[sn];
        topArr[sn] = nextArr[i];
        nextArr[i] = freeSpot;
        freeSpot = i;
        return arr[i];
    }
};

// ============================================================
// 6. Check Valid or Balanced Parentheses
// ============================================================
bool isBalanced(string expr)
{
    stack<char> s;
    for (char c : expr)
    {
        if (c == '(' || c == '{' || c == '[')
            s.push(c);
        else if (c == ')' || c == '}' || c == ']')
        {
            if (s.empty())
                return false;
            char t = s.top();
            if ((c == ')' && t == '(') || (c == '}' && t == '{') || (c == ']' && t == '['))
                s.pop();
            else
                return false;
        }
    }
    return s.empty();
}

// ============================================================
// 7. Reverse a String using Stack
// ============================================================
string reverseStringStack(string str)
{
    stack<char> s;
    for (char c : str)
        s.push(c);
    for (int i = 0; i < (int)str.size(); i++)
    {
        str[i] = s.top();
        s.pop();
    }
    return str;
}

// ============================================================
// 8. Design a Stack supporting getMin() in O(1) Time & Space
// ============================================================
struct SpecialStack
{
    stack<long long> s;
    long long minVal;

    void push(int x)
    {
        if (s.empty())
        {
            s.push(x);
            minVal = x;
        }
        else if (x < minVal)
        {
            s.push(2LL * x - minVal);
            minVal = x;
        }
        else
        {
            s.push(x);
        }
    }

    int pop()
    {
        if (s.empty())
            return -1;
        long long t = s.top();
        s.pop();
        if (t < minVal)
        {
            int prevMin = minVal;
            minVal = 2 * minVal - t;
            return prevMin;
        }
        return t;
    }

    int getMin()
    {
        return s.empty() ? -1 : minVal;
    }
};

// ============================================================
// 9. Find Next Greater Element
// ============================================================
vector<int> nextGreaterElement(vector<int> &arr)
{
    int n = arr.size();
    vector<int> ans(n, -1);
    stack<int> st;
    for (int i = n - 1; i >= 0; i--)
    {
        while (!st.empty() && st.top() <= arr[i])
            st.pop();
        if (!st.empty())
            ans[i] = st.top();
        st.push(arr[i]);
    }
    return ans;
}

// ============================================================
// 10. The Celebrity Problem
// ============================================================
int findCelebrity(vector<vector<int>> &M, int n)
{
    stack<int> s;
    for (int i = 0; i < n; i++)
        s.push(i);

    while (s.size() > 1)
    {
        int a = s.top();
        s.pop();
        int b = s.top();
        s.pop();
        if (M[a][b] == 1)
            s.push(b);
        else
            s.push(a);
    }
    int cand = s.top();
    for (int i = 0; i < n; i++)
    {
        if (i != cand && (M[cand][i] == 1 || M[i][cand] == 0))
            return -1;
    }
    return cand;
}

// ============================================================
// 11. Arithmetic Expression Evaluation (Infix)
// ============================================================
int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

int applyOp(int a, int b, char op)
{
    if (op == '+')
        return a + b;
    if (op == '-')
        return a - b;
    if (op == '*')
        return a * b;
    if (op == '/')
        return (b != 0) ? (a / b) : 0;
    return 0;
}

int evaluateInfix(string exp)
{
    stack<int> values;
    stack<char> ops;
    for (int i = 0; i < (int)exp.length(); i++)
    {
        if (exp[i] == ' ')
            continue;
        if (isdigit(exp[i]))
        {
            int val = 0;
            while (i < (int)exp.length() && isdigit(exp[i]))
            {
                val = (val * 10) + (exp[i] - '0');
                i++;
            }
            values.push(val);
            i--;
        }
        else if (exp[i] == '(')
        {
            ops.push(exp[i]);
        }
        else if (exp[i] == ')')
        {
            while (!ops.empty() && ops.top() != '(')
            {
                int val2 = values.top();
                values.pop();
                int val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            if (!ops.empty())
                ops.pop();
        }
        else
        {
            while (!ops.empty() && precedence(ops.top()) >= precedence(exp[i]))
            {
                int val2 = values.top();
                values.pop();
                int val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(exp[i]);
        }
    }
    while (!ops.empty())
    {
        int val2 = values.top();
        values.pop();
        int val1 = values.top();
        values.pop();
        char op = ops.top();
        ops.pop();
        values.push(applyOp(val1, val2, op));
    }
    return values.top();
}

// ============================================================
// 12. Evaluation of Postfix Expression
// ============================================================
int evaluatePostfix(string exp)
{
    stack<int> st;
    for (char c : exp)
    {
        if (isdigit(c))
        {
            st.push(c - '0');
        }
        else
        {
            int val2 = st.top();
            st.pop();
            int val1 = st.top();
            st.pop();
            st.push(applyOp(val1, val2, c));
        }
    }
    return st.top();
}

// ============================================================
// 13. Insert an Element at the Bottom of Stack without Extra DS
// ============================================================
void insertAtBottom(stack<int> &st, int x)
{
    if (st.empty())
    {
        st.push(x);
        return;
    }
    int num = st.top();
    st.pop();
    insertAtBottom(st, x);
    st.push(num);
}

// ============================================================
// 14. Reverse a Stack using Recursion
// ============================================================
void reverseStack(stack<int> &st)
{
    if (st.empty())
        return;
    int num = st.top();
    st.pop();
    reverseStack(st);
    insertAtBottom(st, num);
}

// ============================================================
// 15. Sort a Stack using Recursion
// ============================================================
void sortedInsert(stack<int> &st, int element)
{
    if (st.empty() || st.top() <= element)
    {
        st.push(element);
        return;
    }
    int topVal = st.top();
    st.pop();
    sortedInsert(st, element);
    st.push(topVal);
}

void sortStack(stack<int> &st)
{
    if (st.empty())
        return;
    int num = st.top();
    st.pop();
    sortStack(st);
    sortedInsert(st, num);
}

// ============================================================
// 16. Merge Overlapping Intervals
// ============================================================
struct Interval
{
    int start, end;
};

vector<Interval> mergeIntervals(vector<Interval> &intervals)
{
    if (intervals.empty())
        return {};
    sort(intervals.begin(), intervals.end(), [](Interval a, Interval b)
         { return a.start < b.start; });

    stack<Interval> st;
    st.push(intervals[0]);
    for (size_t i = 1; i < intervals.size(); i++)
    {
        Interval top = st.top();
        if (top.end < intervals[i].start)
        {
            st.push(intervals[i]);
        }
        else if (top.end < intervals[i].end)
        {
            top.end = intervals[i].end;
            st.pop();
            st.push(top);
        }
    }
    vector<Interval> res;
    while (!st.empty())
    {
        res.push_back(st.top());
        st.pop();
    }
    reverse(res.begin(), res.end());
    return res;
}

// ============================================================
// 17. Largest Rectangular Area in Histogram
// ============================================================
int getMaxAreaHistogram(vector<int> &heights)
{
    int n = heights.size();
    stack<int> s;
    int maxArea = 0;
    for (int i = 0; i <= n; i++)
    {
        int curH = (i == n) ? 0 : heights[i];
        while (!s.empty() && heights[s.top()] >= curH)
        {
            int h = heights[s.top()];
            s.pop();
            int width = s.empty() ? i : i - s.top() - 1;
            maxArea = max(maxArea, h * width);
        }
        s.push(i);
    }
    return maxArea;
}

// ============================================================
// 18. Length of the Longest Valid Substring
// ============================================================
int findMaxLenValidParentheses(string str)
{
    stack<int> st;
    st.push(-1);
    int maxLen = 0;
    for (int i = 0; i < (int)str.length(); i++)
    {
        if (str[i] == '(')
            st.push(i);
        else
        {
            st.pop();
            if (!st.empty())
                maxLen = max(maxLen, i - st.top());
            else
                st.push(i);
        }
    }
    return maxLen;
}

// ============================================================
// 19. Expression Contains Redundant Bracket or Not
// ============================================================
bool checkRedundancy(string s)
{
    stack<char> st;
    for (char ch : s)
    {
        if (ch == ')')
        {
            char top = st.top();
            st.pop();
            bool hasOp = false;
            while (!st.empty() && top != '(')
            {
                if (top == '+' || top == '-' || top == '*' || top == '/')
                    hasOp = true;
                top = st.top();
                st.pop();
            }
            if (!hasOp)
                return true;
        }
        else
        {
            st.push(ch);
        }
    }
    return false;
}

// ============================================================
// 20. Implement Stack using Queue
// ============================================================
struct StackUsingQueue
{
    queue<int> q;
    void push(int x)
    {
        int s = q.size();
        q.push(x);
        for (int i = 0; i < s; i++)
        {
            q.push(q.front());
            q.pop();
        }
    }
    int pop()
    {
        if (q.empty())
            return -1;
        int val = q.front();
        q.pop();
        return val;
    }
};

// ============================================================
// 21. Implement Stack using Deque
// ============================================================
struct StackUsingDeque
{
    deque<int> dq;
    void push(int x) { dq.push_back(x); }
    int pop()
    {
        if (dq.empty())
            return -1;
        int val = dq.back();
        dq.pop_back();
        return val;
    }
};

// ============================================================
// 22. Stack Permutations
// ============================================================
bool checkStackPermutation(vector<int> &input, vector<int> &output)
{
    stack<int> st;
    int j = 0;
    for (int x : input)
    {
        st.push(x);
        while (!st.empty() && st.top() == output[j])
        {
            st.pop();
            j++;
        }
    }
    return (st.empty() && j == (int)output.size());
}

// ============================================================
// 23. Implement Queue using Stack
// ============================================================
struct QueueUsingStack
{
    stack<int> s1, s2;
    void push(int x) { s1.push(x); }
    int pop()
    {
        if (s1.empty() && s2.empty())
            return -1;
        if (s2.empty())
        {
            while (!s1.empty())
            {
                s2.push(s1.top());
                s1.pop();
            }
        }
        int val = s2.top();
        s2.pop();
        return val;
    }
};

// ============================================================
// 24. Implement "N" Queues in an Array
// ============================================================
struct KQueues
{
    vector<int> arr, frontArr, rearArr, nextArr;
    int freeSpot;
    KQueues(int k, int n)
    {
        arr.resize(n);
        nextArr.resize(n);
        frontArr.assign(k, -1);
        rearArr.assign(k, -1);
        freeSpot = 0;
        for (int i = 0; i < n - 1; i++)
            nextArr[i] = i + 1;
        nextArr[n - 1] = -1;
    }
    void enqueue(int item, int qn)
    {
        if (freeSpot == -1)
            return;
        int i = freeSpot;
        freeSpot = nextArr[i];
        if (frontArr[qn] == -1)
            frontArr[qn] = i;
        else
            nextArr[rearArr[qn]] = i;
        nextArr[i] = -1;
        rearArr[qn] = i;
        arr[i] = item;
    }
    int dequeue(int qn)
    {
        if (frontArr[qn] == -1)
            return -1;
        int i = frontArr[qn];
        frontArr[qn] = nextArr[i];
        nextArr[i] = freeSpot;
        freeSpot = i;
        return arr[i];
    }
};

// ============================================================
// 25. Implement a Circular Queue
// ============================================================
struct CircularQueue
{
    int arr[1000];
    int frontIdx, rearIdx, size;
    CircularQueue(int k = 1000)
    {
        size = k;
        frontIdx = rearIdx = -1;
    }
    bool enqueue(int val)
    {
        if ((frontIdx == 0 && rearIdx == size - 1) || (rearIdx == (frontIdx - 1) % (size - 1)))
            return false;
        if (frontIdx == -1)
        {
            frontIdx = rearIdx = 0;
        }
        else if (rearIdx == size - 1 && frontIdx != 0)
        {
            rearIdx = 0;
        }
        else
        {
            rearIdx++;
        }
        arr[rearIdx] = val;
        return true;
    }
    int dequeue()
    {
        if (frontIdx == -1)
            return -1;
        int res = arr[frontIdx];
        if (frontIdx == rearIdx)
        {
            frontIdx = rearIdx = -1;
        }
        else if (frontIdx == size - 1)
        {
            frontIdx = 0;
        }
        else
        {
            frontIdx++;
        }
        return res;
    }
};

// ============================================================
// 26. LRU Cache Implementation
// ============================================================
struct LRUCache
{
    int capacity;
    list<pair<int, int>> dll;
    unordered_map<int, list<pair<int, int>>::iterator> cache;

    LRUCache(int cap) : capacity(cap) {}

    int get(int key)
    {
        if (cache.find(key) == cache.end())
            return -1;
        dll.splice(dll.begin(), dll, cache[key]);
        return cache[key]->second;
    }

    void put(int key, int value)
    {
        if (cache.find(key) != cache.end())
        {
            cache[key]->second = value;
            dll.splice(dll.begin(), dll, cache[key]);
            return;
        }
        if ((int)dll.size() == capacity)
        {
            int oldKey = dll.back().first;
            dll.pop_back();
            cache.erase(oldKey);
        }
        dll.push_front({key, value});
        cache[key] = dll.begin();
    }
};

// ============================================================
// 27. Reverse a Queue using Recursion
// ============================================================
void reverseQueue(queue<int> &q)
{
    if (q.empty())
        return;
    int front = q.front();
    q.pop();
    reverseQueue(q);
    q.push(front);
}

// ============================================================
// 28. Reverse the First "K" Elements of a Queue
// ============================================================
queue<int> reverseFirstK(queue<int> q, int k)
{
    stack<int> s;
    for (int i = 0; i < k; i++)
    {
        s.push(q.front());
        q.pop();
    }
    while (!s.empty())
    {
        q.push(s.top());
        s.pop();
    }
    int n = q.size();
    for (int i = 0; i < n - k; i++)
    {
        q.push(q.front());
        q.pop();
    }
    return q;
}

// ============================================================
// 29. Interleave the First Half of the Queue with Second Half
// ============================================================
void interleaveQueue(queue<int> &q)
{
    stack<int> s;
    int halfSize = q.size() / 2;

    for (int i = 0; i < halfSize; i++)
    {
        s.push(q.front());
        q.pop();
    }
    while (!s.empty())
    {
        q.push(s.top());
        s.pop();
    }
    for (int i = 0; i < halfSize; i++)
    {
        q.push(q.front());
        q.pop();
    }
    for (int i = 0; i < halfSize; i++)
    {
        s.push(q.front());
        q.pop();
    }
    while (!s.empty())
    {
        q.push(s.top());
        s.pop();
        q.push(q.front());
        q.pop();
    }
}

// ============================================================
// 30. First Circular Tour that Visits All Petrol Pumps
// ============================================================
struct PetrolPump
{
    int petrol, distance;
};

int tour(vector<PetrolPump> &p)
{
    int start = 0, deficit = 0, capacity = 0;
    for (int i = 0; i < (int)p.size(); i++)
    {
        capacity += p[i].petrol - p[i].distance;
        if (capacity < 0)
        {
            start = i + 1;
            deficit += capacity;
            capacity = 0;
        }
    }
    return (capacity + deficit >= 0) ? start : -1;
}

// ============================================================
// 31. Minimum Time Required to Rot All Oranges
// ============================================================
int orangesRotting(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();
    queue<pair<int, int>> q;
    int fresh = 0, time = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 2)
                q.push({i, j});
            else if (grid[i][j] == 1)
                fresh++;
        }
    }
    int dRow[] = {-1, 1, 0, 0};
    int dCol[] = {0, 0, -1, 1};

    while (!q.empty() && fresh > 0)
    {
        int sz = q.size();
        time++;
        while (sz--)
        {
            auto p = q.front();
            q.pop();
            int r = p.first, c = p.second;
            for (int i = 0; i < 4; i++)
            {
                int nr = r + dRow[i], nc = c + dCol[i];
                if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] == 1)
                {
                    grid[nr][nc] = 2;
                    fresh--;
                    q.push({nr, nc});
                }
            }
        }
    }
    return fresh == 0 ? time : -1;
}

// ============================================================
// 32. Distance of Nearest Cell Having 1 in a Binary Matrix
// ============================================================
vector<vector<int>> nearest(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int, int>> q;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 1)
            {
                dist[i][j] = 0;
                q.push({i, j});
            }
        }
    }
    int dRow[] = {-1, 1, 0, 0};
    int dCol[] = {0, 0, -1, 1};

    while (!q.empty())
    {
        auto p = q.front();
        q.pop();
        int r = p.first, c = p.second;
        for (int i = 0; i < 4; i++)
        {
            int nr = r + dRow[i], nc = c + dCol[i];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && dist[nr][nc] == -1)
            {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
    return dist;
}

// ============================================================
// 33. First Negative Integer in Every Window of Size "k"
// ============================================================
vector<int> printFirstNegativeInteger(vector<int> &arr, int k)
{
    deque<int> dq;
    vector<int> ans;
    int n = arr.size();

    for (int i = 0; i < n; i++)
    {
        if (arr[i] < 0)
            dq.push_back(i);
        if (i >= k - 1)
        {
            while (!dq.empty() && dq.front() <= i - k)
                dq.pop_front();
            ans.push_back(!dq.empty() ? arr[dq.front()] : 0);
        }
    }
    return ans;
}

// ============================================================
// 34. Check if All Levels of Two Trees are Anagrams
// ============================================================
struct TreeNode
{
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

bool areAnagrams(TreeNode *root1, TreeNode *root2)
{
    if (!root1 && !root2)
        return true;
    if (!root1 || !root2)
        return false;

    queue<TreeNode *> q1, q2;
    q1.push(root1);
    q2.push(root2);

    while (!q1.empty() && !q2.empty())
    {
        int n1 = q1.size(), n2 = q2.size();
        if (n1 != n2)
            return false;

        vector<int> currLevel1, currLevel2;
        while (n1--)
        {
            TreeNode *t1 = q1.front();
            q1.pop();
            TreeNode *t2 = q2.front();
            q2.pop();
            currLevel1.push_back(t1->val);
            currLevel2.push_back(t2->val);
            if (t1->left)
                q1.push(t1->left);
            if (t1->right)
                q1.push(t1->right);
            if (t2->left)
                q2.push(t2->left);
            if (t2->right)
                q2.push(t2->right);
        }
        sort(currLevel1.begin(), currLevel1.end());
        sort(currLevel2.begin(), currLevel2.end());
        if (currLevel1 != currLevel2)
            return false;
    }
    return true;
}

// ============================================================
// 35. Sum of Min and Max Elements of All Subarrays of Size "k"
// ============================================================
int sumOfMinAndMax(vector<int> &arr, int k)
{
    deque<int> maxDq, minDq;
    int total = 0;

    for (int i = 0; i < (int)arr.size(); i++)
    {
        while (!maxDq.empty() && maxDq.front() <= i - k)
            maxDq.pop_front();
        while (!minDq.empty() && minDq.front() <= i - k)
            minDq.pop_front();

        while (!maxDq.empty() && arr[maxDq.back()] <= arr[i])
            maxDq.pop_back();
        while (!minDq.empty() && arr[minDq.back()] >= arr[i])
            minDq.pop_back();

        maxDq.push_back(i);
        minDq.push_back(i);

        if (i >= k - 1)
            total += arr[maxDq.front()] + arr[minDq.front()];
    }
    return total;
}

// ============================================================
// 36. Minimum Sum of Squares of Character Counts After Removing "k" Chars
// ============================================================
int minStringValue(string s, int k)
{
    if (k >= (int)s.length())
        return 0;
    int freq[26] = {0};
    for (char c : s)
        freq[c - 'a']++;

    priority_queue<int> pq;
    for (int i = 0; i < 26; i++)
    {
        if (freq[i] > 0)
            pq.push(freq[i]);
    }
    while (k-- > 0 && !pq.empty())
    {
        int temp = pq.top();
        pq.pop();
        temp--;
        if (temp > 0)
            pq.push(temp);
    }
    int result = 0;
    while (!pq.empty())
    {
        int val = pq.top();
        pq.pop();
        result += val * val;
    }
    return result;
}

// ============================================================
// 37. Queue-based Approach for First Non-Repeating Character in a Stream
// ============================================================
string firstNonRepeating(string s)
{
    int freq[26] = {0};
    queue<char> q;
    string ans = "";

    for (char c : s)
    {
        freq[c - 'a']++;
        q.push(c);
        while (!q.empty() && freq[q.front() - 'a'] > 1)
        {
            q.pop();
        }
        ans += q.empty() ? '#' : q.front();
    }
    return ans;
}

// ============================================================
// 38. Next Smaller Element
// ============================================================
vector<int> nextSmallerElement(vector<int> &arr)
{
    int n = arr.size();
    vector<int> ans(n, -1);
    stack<int> st;
    for (int i = n - 1; i >= 0; i--)
    {
        while (!st.empty() && st.top() >= arr[i])
            st.pop();
        if (!st.empty())
            ans[i] = st.top();
        st.push(arr[i]);
    }
    return ans;
}

// ============================================================
// CLI MAIN RUNNER
// ============================================================
int main()
{
    // 1. Balanced Parentheses Demo
    string expr;
    cout << "Enter parentheses expression (e.g. {[()]}): ";
    cin >> expr;
    cout << "Expression is " << (isBalanced(expr) ? "Balanced" : "Not Balanced") << "\n\n";

    // 2. Next Greater Element Demo
    int n;
    cout << "Enter size of array for Next Greater Element: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    vector<int> nge = nextGreaterElement(arr);
    cout << "Next Greater Elements: ";
    for (int x : nge)
        cout << x << " ";
    cout << "\n\n";

    // 3. Largest Rectangle in Histogram Demo
    int hn;
    cout << "Enter size of histogram: ";
    cin >> hn;
    vector<int> hist(hn);
    cout << "Enter " << hn << " bar heights: ";
    for (int i = 0; i < hn; i++)
        cin >> hist[i];
    cout << "Max Rectangular Area: " << getMaxAreaHistogram(hist) << "\n\n";

    // 4. First Non-Repeating Stream Demo
    string streamStr;
    cout << "Enter stream characters (e.g. aabc): ";
    cin >> streamStr;
    cout << "Processed Stream: " << firstNonRepeating(streamStr) << "\n";

    return 0;
}