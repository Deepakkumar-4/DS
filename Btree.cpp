#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

// ============================================================
// 0. BASIC BINARY TREE NODE (NO OOP)
// ============================================================
struct Node
{
    int data;
    Node *left;
    Node *right;
    Node(int val)
    {
        data = val;
        left = NULL;
        right = NULL;
    }
};

// ============================================================
// 1. Level Order Traversal
// ============================================================
vector<int> levelOrder(Node *root)
{
    vector<int> ans;
    if (!root)
        return ans;
    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        Node *curr = q.front();
        q.pop();
        ans.push_back(curr->data);
        if (curr->left)
            q.push(curr->left);
        if (curr->right)
            q.push(curr->right);
    }
    return ans;
}

// ============================================================
// 2. Reverse Level Order Traversal
// ============================================================
vector<int> reverseLevelOrder(Node *root)
{
    vector<int> ans;
    if (!root)
        return ans;
    queue<Node *> q;
    stack<int> s;
    q.push(root);
    while (!q.empty())
    {
        Node *curr = q.front();
        q.pop();
        s.push(curr->data);
        if (curr->right)
            q.push(curr->right); // Right pushed first
        if (curr->left)
            q.push(curr->left);
    }
    while (!s.empty())
    {
        ans.push_back(s.top());
        s.pop();
    }
    return ans;
}

// ============================================================
// 3. Height of a Tree
// ============================================================
int height(Node *root)
{
    if (!root)
        return 0;
    return 1 + max(height(root->left), height(root->right));
}

// ============================================================
// 4. Diameter of a Tree
// ============================================================
int diameterHelper(Node *root, int &dia)
{
    if (!root)
        return 0;
    int lh = diameterHelper(root->left, dia);
    int rh = diameterHelper(root->right, dia);
    dia = max(dia, lh + rh + 1);
    return 1 + max(lh, rh);
}

int diameter(Node *root)
{
    int dia = 0;
    diameterHelper(root, dia);
    return dia;
}

// ============================================================
// 5. Mirror of a Tree
// ============================================================
Node *mirror(Node *root)
{
    if (!root)
        return NULL;
    Node *leftMirror = mirror(root->left);
    Node *rightMirror = mirror(root->right);
    root->left = rightMirror;
    root->right = leftMirror;
    return root;
}

// ============================================================
// 6. Inorder Traversal (Recursive & Iterative)
// ============================================================
void inorderRec(Node *root)
{
    if (!root)
        return;
    inorderRec(root->left);
    cout << root->data << " ";
    inorderRec(root->right);
}

void inorderIter(Node *root)
{
    stack<Node *> s;
    Node *curr = root;
    while (curr != NULL || !s.empty())
    {
        while (curr != NULL)
        {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top();
        s.pop();
        cout << curr->data << " ";
        curr = curr->right;
    }
}

// ============================================================
// 7. Preorder Traversal (Recursive & Iterative)
// ============================================================
void preorderRec(Node *root)
{
    if (!root)
        return;
    cout << root->data << " ";
    preorderRec(root->left);
    preorderRec(root->right);
}

void preorderIter(Node *root)
{
    if (!root)
        return;
    stack<Node *> s;
    s.push(root);
    while (!s.empty())
    {
        Node *curr = s.top();
        s.pop();
        cout << curr->data << " ";
        if (curr->right)
            s.push(curr->right);
        if (curr->left)
            s.push(curr->left);
    }
}

// ============================================================
// 8. Postorder Traversal (Recursive & Iterative)
// ============================================================
void postorderRec(Node *root)
{
    if (!root)
        return;
    postorderRec(root->left);
    postorderRec(root->right);
    cout << root->data << " ";
}

void postorderIter(Node *root)
{
    if (!root)
        return;
    stack<Node *> s1, s2;
    s1.push(root);
    while (!s1.empty())
    {
        Node *curr = s1.top();
        s1.pop();
        s2.push(curr);
        if (curr->left)
            s1.push(curr->left);
        if (curr->right)
            s1.push(curr->right);
    }
    while (!s2.empty())
    {
        cout << s2.top()->data << " ";
        s2.pop();
    }
}

// ============================================================
// 9. Left View of a Tree
// ============================================================
void leftViewHelper(Node *root, int level, int &maxLevel)
{
    if (!root)
        return;
    if (level > maxLevel)
    {
        cout << root->data << " ";
        maxLevel = level;
    }
    leftViewHelper(root->left, level + 1, maxLevel);
    leftViewHelper(root->right, level + 1, maxLevel);
}

void leftView(Node *root)
{
    int maxLevel = 0;
    leftViewHelper(root, 1, maxLevel);
}

// ============================================================
// 10. Right View of a Tree
// ============================================================
void rightViewHelper(Node *root, int level, int &maxLevel)
{
    if (!root)
        return;
    if (level > maxLevel)
    {
        cout << root->data << " ";
        maxLevel = level;
    }
    rightViewHelper(root->right, level + 1, maxLevel);
    rightViewHelper(root->left, level + 1, maxLevel);
}

void rightView(Node *root)
{
    int maxLevel = 0;
    rightViewHelper(root, 1, maxLevel);
}

// ============================================================
// 11. Top View of a Tree
// ============================================================
void topView(Node *root)
{
    if (!root)
        return;
    map<int, int> topNode; // hd -> val
    queue<pair<Node *, int>> q;
    q.push({root, 0});

    while (!q.empty())
    {
        auto p = q.front();
        q.pop();
        Node *curr = p.first;
        int hd = p.second;

        if (topNode.find(hd) == topNode.end())
        {
            topNode[hd] = curr->data;
        }
        if (curr->left)
            q.push({curr->left, hd - 1});
        if (curr->right)
            q.push({curr->right, hd + 1});
    }
    for (auto it : topNode)
        cout << it.second << " ";
}

// ============================================================
// 12. Bottom View of a Tree
// ============================================================
void bottomView(Node *root)
{
    if (!root)
        return;
    map<int, int> bottomNode; // hd -> val
    queue<pair<Node *, int>> q;
    q.push({root, 0});

    while (!q.empty())
    {
        auto p = q.front();
        q.pop();
        Node *curr = p.first;
        int hd = p.second;

        bottomNode[hd] = curr->data; // Overwrite to get the lowest node
        if (curr->left)
            q.push({curr->left, hd - 1});
        if (curr->right)
            q.push({curr->right, hd + 1});
    }
    for (auto it : bottomNode)
        cout << it.second << " ";
}

// ============================================================
// 13. Zig-Zag Traversal of a Binary Tree
// ============================================================
vector<int> zigZagTraversal(Node *root)
{
    vector<int> ans;
    if (!root)
        return ans;
    queue<Node *> q;
    q.push(root);
    bool leftToRight = true;

    while (!q.empty())
    {
        int size = q.size();
        vector<int> row(size);
        for (int i = 0; i < size; i++)
        {
            Node *curr = q.front();
            q.pop();
            int index = leftToRight ? i : (size - 1 - i);
            row[index] = curr->data;

            if (curr->left)
                q.push(curr->left);
            if (curr->right)
                q.push(curr->right);
        }
        leftToRight = !leftToRight;
        for (int val : row)
            ans.push_back(val);
    }
    return ans;
}

// ============================================================
// 14. Check if a Tree is Balanced or Not
// ============================================================
int checkBalanced(Node *root)
{
    if (!root)
        return 0;
    int lh = checkBalanced(root->left);
    if (lh == -1)
        return -1;
    int rh = checkBalanced(root->right);
    if (rh == -1)
        return -1;

    if (abs(lh - rh) > 1)
        return -1;
    return 1 + max(lh, rh);
}

bool isBalanced(Node *root)
{
    return checkBalanced(root) != -1;
}

// ============================================================
// 15. Diagonal Traversal of a Binary Tree
// ============================================================
vector<int> diagonal(Node *root)
{
    vector<int> ans;
    if (!root)
        return ans;
    queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        Node *curr = q.front();
        q.pop();
        while (curr)
        {
            ans.push_back(curr->data);
            if (curr->left)
                q.push(curr->left);
            curr = curr->right;
        }
    }
    return ans;
}

// ============================================================
// 16. Boundary Traversal of a Binary Tree
// ============================================================
bool isLeaf(Node *node)
{
    return !node->left && !node->right;
}

void addLeftBoundary(Node *root, vector<int> &res)
{
    Node *curr = root->left;
    while (curr)
    {
        if (!isLeaf(curr))
            res.push_back(curr->data);
        if (curr->left)
            curr = curr->left;
        else
            curr = curr->right;
    }
}

void addLeaves(Node *root, vector<int> &res)
{
    if (!root)
        return;
    if (isLeaf(root))
    {
        res.push_back(root->data);
        return;
    }
    addLeaves(root->left, res);
    addLeaves(root->right, res);
}

void addRightBoundary(Node *root, vector<int> &res)
{
    Node *curr = root->right;
    vector<int> temp;
    while (curr)
    {
        if (!isLeaf(curr))
            temp.push_back(curr->data);
        if (curr->right)
            curr = curr->right;
        else
            curr = curr->left;
    }
    for (int i = temp.size() - 1; i >= 0; i--)
        res.push_back(temp[i]);
}

vector<int> boundary(Node *root)
{
    vector<int> res;
    if (!root)
        return res;
    if (!isLeaf(root))
        res.push_back(root->data);
    addLeftBoundary(root, res);
    addLeaves(root, res);
    addRightBoundary(root, res);
    return res;
}

// ============================================================
// 17. Construct Tree from String with Bracket Representation
// ============================================================
int findCloseIndex(string s, int start, int end)
{
    if (start > end)
        return -1;
    stack<char> st;
    for (int i = start; i <= end; i++)
    {
        if (s[i] == '(')
            st.push(s[i]);
        else if (s[i] == ')')
        {
            if (st.top() == '(')
            {
                st.pop();
                if (st.empty())
                    return i;
            }
        }
    }
    return -1;
}

Node *treeFromString(string s, int start, int end)
{
    if (start > end)
        return NULL;

    int num = 0;
    while (start <= end && s[start] >= '0' && s[start] <= '9')
    {
        num = num * 10 + (s[start] - '0');
        start++;
    }
    Node *root = new Node(num);
    int index = -1;

    if (start <= end && s[start] == '(')
    {
        index = findCloseIndex(s, start, end);
    }
    if (index != -1)
    {
        root->left = treeFromString(s, start + 1, index - 1);
        root->right = treeFromString(s, index + 2, end - 1);
    }
    return root;
}

// ============================================================
// 18. Convert Binary Tree into Doubly Linked List (Inplace)
// ============================================================
void bToDLL(Node *root, Node *&head, Node *&prev)
{
    if (!root)
        return;
    bToDLL(root->left, head, prev);
    if (prev == NULL)
    {
        head = root;
    }
    else
    {
        root->left = prev;
        prev->right = root;
    }
    prev = root;
    bToDLL(root->right, head, prev);
}

// ============================================================
// 19. Convert Binary Tree into Sum Tree
// ============================================================
int toSumTree(Node *root)
{
    if (!root)
        return 0;
    int oldVal = root->data;
    root->data = toSumTree(root->left) + toSumTree(root->right);
    return root->data + oldVal;
}

// ============================================================
// 20. Construct Binary Tree from Inorder and Preorder
// ============================================================
int preIndex = 0;
Node *buildTreeFromInPre(int in[], int pre[], int inSt, int inEnd, unordered_map<int, int> &mp)
{
    if (inSt > inEnd)
        return NULL;
    int curr = pre[preIndex++];
    Node *node = new Node(curr);
    if (inSt == inEnd)
        return node;

    int pos = mp[curr];
    node->left = buildTreeFromInPre(in, pre, inSt, pos - 1, mp);
    node->right = buildTreeFromInPre(in, pre, pos + 1, inEnd, mp);
    return node;
}

// ============================================================
// 21. Minimum Swaps Required to Convert Binary Tree to BST
// ============================================================
void getInorder(Node *root, vector<int> &v)
{
    if (!root)
        return;
    getInorder(root->left, v);
    v.push_back(root->data);
    getInorder(root->right, v);
}

int minSwapsToBST(Node *root)
{
    vector<int> arr;
    getInorder(root, arr);
    int n = arr.size();

    vector<pair<int, int>> p(n);
    for (int i = 0; i < n; i++)
        p[i] = {arr[i], i};
    sort(p.begin(), p.end());

    vector<bool> visited(n, false);
    int swaps = 0;

    for (int i = 0; i < n; i++)
    {
        if (visited[i] || p[i].second == i)
            continue;
        int cycle_size = 0;
        int j = i;
        while (!visited[j])
        {
            visited[j] = true;
            j = p[j].second;
            cycle_size++;
        }
        if (cycle_size > 0)
            swaps += (cycle_size - 1);
    }
    return swaps;
}

// ============================================================
// 22. Check if Binary Tree is Sum Tree or Not
// ============================================================
int isSumTreeHelper(Node *root, bool &isSum)
{
    if (!root)
        return 0;
    if (!root->left && !root->right)
        return root->data;

    int ls = isSumTreeHelper(root->left, isSum);
    int rs = isSumTreeHelper(root->right, isSum);

    if (root->data != ls + rs)
        isSum = false;
    return root->data + ls + rs;
}

bool isSumTree(Node *root)
{
    bool isSum = true;
    isSumTreeHelper(root, isSum);
    return isSum;
}

// ============================================================
// 23. Check if all Leaf Nodes are at Same Level
// ============================================================
bool checkLeafLevel(Node *root, int level, int &leafLevel)
{
    if (!root)
        return true;
    if (!root->left && !root->right)
    {
        if (leafLevel == 0)
        {
            leafLevel = level;
            return true;
        }
        return level == leafLevel;
    }
    return checkLeafLevel(root->left, level + 1, leafLevel) &&
           checkLeafLevel(root->right, level + 1, leafLevel);
}

// ============================================================
// 24. Check if Tree contains Duplicate Subtrees of Size 2 or More
// ============================================================
string dupSubHelper(Node *root, unordered_map<string, int> &m, bool &hasDup)
{
    if (!root)
        return "$";
    string s = "";
    if (!root->left && !root->right)
    {
        s += to_string(root->data);
        return s;
    }
    s += to_string(root->data) + ",";
    s += dupSubHelper(root->left, m, hasDup) + ",";
    s += dupSubHelper(root->right, m, hasDup);

    m[s]++;
    if (m[s] >= 2)
        hasDup = true;
    return s;
}

bool dupSub(Node *root)
{
    unordered_map<string, int> m;
    bool hasDup = false;
    dupSubHelper(root, m, hasDup);
    return hasDup;
}

// ============================================================
// 25. Check if 2 Trees are Mirror or Not
// ============================================================
bool areMirrors(Node *root1, Node *root2)
{
    if (!root1 && !root2)
        return true;
    if (!root1 || !root2)
        return false;
    return (root1->data == root2->data) &&
           areMirrors(root1->left, root2->right) &&
           areMirrors(root1->right, root2->left);
}

// ============================================================
// 26. Sum of Nodes on the Longest Path from Root to Leaf
// ============================================================
void sumLongestPath(Node *root, int sum, int len, int &maxLen, int &maxSum)
{
    if (!root)
        return;
    sum += root->data;
    if (!root->left && !root->right)
    {
        if (len > maxLen)
        {
            maxLen = len;
            maxSum = sum;
        }
        else if (len == maxLen)
        {
            maxSum = max(maxSum, sum);
        }
        return;
    }
    sumLongestPath(root->left, sum, len + 1, maxLen, maxSum);
    sumLongestPath(root->right, sum, len + 1, maxLen, maxSum);
}

// ============================================================
// 27. Check if Given Graph is Tree or Not
// ============================================================
bool isCyclicUtil(int u, vector<int> adj[], vector<bool> &visited, int parent)
{
    visited[u] = true;
    for (int v : adj[u])
    {
        if (!visited[v])
        {
            if (isCyclicUtil(v, adj, visited, u))
                return true;
        }
        else if (v != parent)
            return true;
    }
    return false;
}

bool isGraphTree(int V, vector<int> adj[])
{
    vector<bool> visited(V, false);
    if (isCyclicUtil(0, adj, visited, -1))
        return false;
    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
            return false; // Not connected
    }
    return true;
}

// ============================================================
// 28. Find Largest Subtree Sum in a Tree
// ============================================================
int largestSubtreeSumHelper(Node *root, int &maxSum)
{
    if (!root)
        return 0;
    int curSum = root->data + largestSubtreeSumHelper(root->left, maxSum) +
                 largestSubtreeSumHelper(root->right, maxSum);
    maxSum = max(maxSum, curSum);
    return curSum;
}

int largestSubtreeSum(Node *root)
{
    int maxSum = INT_MIN;
    largestSubtreeSumHelper(root, maxSum);
    return maxSum;
}

// ============================================================
// 29. Maximum Sum of Nodes such that No Two are Adjacent
// ============================================================
pair<int, int> getMaxSumPair(Node *root)
{
    // {inclusive_sum, exclusive_sum}
    if (!root)
        return {0, 0};
    auto left = getMaxSumPair(root->left);
    auto right = getMaxSumPair(root->right);

    int inc = root->data + left.second + right.second;
    int exc = max(left.first, left.second) + max(right.first, right.second);
    return {inc, exc};
}

int getMaxSumNonAdjacent(Node *root)
{
    auto res = getMaxSumPair(root);
    return max(res.first, res.second);
}

// ============================================================
// 30. Print all "K" Sum Paths in a Binary Tree
// ============================================================
void printKPathHelper(Node *root, vector<int> &path, int k)
{
    if (!root)
        return;
    path.push_back(root->data);

    printKPathHelper(root->left, path, k);
    printKPathHelper(root->right, path, k);

    int sum = 0;
    for (int i = path.size() - 1; i >= 0; i--)
    {
        sum += path[i];
        if (sum == k)
        {
            for (int m = i; m < path.size(); m++)
                cout << path[m] << " ";
            cout << "\n";
        }
    }
    path.pop_back();
}

// ============================================================
// 31. Find LCA (Lowest Common Ancestor) in a Binary Tree
// ============================================================
Node *findLCA(Node *root, int n1, int n2)
{
    if (!root)
        return NULL;
    if (root->data == n1 || root->data == n2)
        return root;

    Node *left = findLCA(root->left, n1, n2);
    Node *right = findLCA(root->right, n1, n2);

    if (left && right)
        return root;
    return left ? left : right;
}

// ============================================================
// 32. Find Distance Between 2 Nodes in a Binary Tree
// ============================================================
int findLevel(Node *root, int val, int level)
{
    if (!root)
        return -1;
    if (root->data == val)
        return level;
    int l = findLevel(root->left, val, level + 1);
    return (l != -1) ? l : findLevel(root->right, val, level + 1);
}

int findDistance(Node *root, int a, int b)
{
    Node *lca = findLCA(root, a, b);
    int d1 = findLevel(lca, a, 0);
    int d2 = findLevel(lca, b, 0);
    return d1 + d2;
}

// ============================================================
// 33. Kth Ancestor of Node in a Binary Tree
// ============================================================
Node *kthAncestorHelper(Node *root, int node, int &k)
{
    if (!root)
        return NULL;
    if (root->data == node ||
        kthAncestorHelper(root->left, node, k) ||
        kthAncestorHelper(root->right, node, k))
    {
        if (k > 0)
        {
            k--;
        }
        else if (k == 0)
        {
            cout << "Kth Ancestor: " << root->data << "\n";
            return NULL;
        }
        return root;
    }
    return NULL;
}

// ============================================================
// 34. Find all Duplicate Subtrees in a Binary Tree
// ============================================================
string findDupSubtrees(Node *root, unordered_map<string, int> &m, vector<Node *> &res)
{
    if (!root)
        return "#";
    string s = to_string(root->data) + "," +
               findDupSubtrees(root->left, m, res) + "," +
               findDupSubtrees(root->right, m, res);
    m[s]++;
    if (m[s] == 2)
        res.push_back(root);
    return s;
}

// ============================================================
// 35. Tree Isomorphism Problem
// ============================================================
bool isIsomorphic(Node *n1, Node *n2)
{
    if (!n1 && !n2)
        return true;
    if (!n1 || !n2)
        return false;
    if (n1->data != n2->data)
        return false;

    return (isIsomorphic(n1->left, n2->left) && isIsomorphic(n1->right, n2->right)) ||
           (isIsomorphic(n1->left, n2->right) && isIsomorphic(n1->right, n2->left));
}

// ============================================================
// CLI BUILD HELPER (Level-order build using cin)
// ============================================================
Node *buildTreeFromInput()
{
    int val;
    cin >> val;
    if (val == -1)
        return NULL;

    Node *root = new Node(val);
    queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        Node *curr = q.front();
        q.pop();

        int leftVal, rightVal;
        cin >> leftVal;
        if (leftVal != -1)
        {
            curr->left = new Node(leftVal);
            q.push(curr->left);
        }

        cin >> rightVal;
        if (rightVal != -1)
        {
            curr->right = new Node(rightVal);
            q.push(curr->right);
        }
    }
    return root;
}

// ============================================================
// CLI MAIN EXECUTION DEMO
// ============================================================
int main()
{
    cout << "Enter tree in level order (use -1 for NULL nodes):\n";
    cout << "(Example: 1 2 3 4 5 -1 -1 -1 -1 -1 -1)\n";
    cout << "Input: ";

    Node *root = buildTreeFromInput();

    cout << "\n--- Traversals ---\n";
    cout << "Level Order: ";
    vector<int> lo = levelOrder(root);
    for (int x : lo)
        cout << x << " ";
    cout << "\n";

    cout << "Inorder: ";
    inorderRec(root);
    cout << "\n";

    cout << "Height of Tree: " << height(root) << "\n";
    cout << "Diameter of Tree: " << diameter(root) << "\n";
    cout << "Is Balanced: " << (isBalanced(root) ? "Yes" : "No") << "\n";

    cout << "\nLeft View: ";
    leftView(root);
    cout << "\nRight View: ";
    rightView(root);
    cout << "\nTop View: ";
    topView(root);
    cout << "\nBottom View: ";
    bottomView(root);
    cout << "\n";

    return 0;
}