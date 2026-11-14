#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>
#include <unordered_set>

using namespace std;

// ============================================================
// 0. BASIC BST NODE STRUCTURE (NO OOP)
// ============================================================
struct Node {
    int data;
    Node* left;
    Node* right;
    Node* next; // Used for Question 6 (Populate Inorder Successor)
    Node(int val) {
        data = val;
        left = NULL;
        right = NULL;
        next = NULL;
    }
};

// Standard BST Insert
Node* insertBST(Node* root, int val) {
    if (!root) return new Node(val);
    if (val < root->data) {
        root->left = insertBST(root->left, val);
    } else {
        root->right = insertBST(root->right, val);
    }
    return root;
}

// ============================================================
// 1. Find a value in a BST
// ============================================================
Node* searchBST(Node* root, int val) {
    if (!root || root->data == val) return root;
    if (val < root->data) return searchBST(root->left, val);
    return searchBST(root->right, val);
}

// ============================================================
// 2. Deletion of a node in a BST
// ============================================================
Node* findMinNode(Node* root) {
    while (root && root->left != NULL) root = root->left;
    return root;
}

Node* deleteNode(Node* root, int key) {
    if (!root) return NULL;

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        // Node with 0 or 1 child
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        // Node with 2 children: get inorder successor
        Node* temp = findMinNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// ============================================================
// 3. Find min and max value in a BST
// ============================================================
int findMin(Node* root) {
    if (!root) return -1;
    while (root->left != NULL) root = root->left;
    return root->data;
}

int findMax(Node* root) {
    if (!root) return -1;
    while (root->right != NULL) root = root->right;
    return root->data;
}

// ============================================================
// 4. Find Inorder Successor and Inorder Predecessor in a BST
// ============================================================
void findPreSuc(Node* root, Node*& pre, Node*& suc, int key) {
    if (!root) return;

    if (root->data == key) {
        if (root->left) {
            Node* temp = root->left;
            while (temp->right) temp = temp->right;
            pre = temp;
        }
        if (root->right) {
            Node* temp = root->right;
            while (temp->left) temp = temp->left;
            suc = temp;
        }
        return;
    }

    if (key < root->data) {
        suc = root;
        findPreSuc(root->left, pre, suc, key);
    } else {
        pre = root;
        findPreSuc(root->right, pre, suc, key);
    }
}

// ============================================================
// 5. Check if a tree is a BST or not
// ============================================================
bool isBSTUtil(Node* root, long long minVal, long long maxVal) {
    if (!root) return true;
    if (root->data <= minVal || root->data >= maxVal) return false;
    return isBSTUtil(root->left, minVal, root->data) &&
           isBSTUtil(root->right, root->data, maxVal);
}

bool isBST(Node* root) {
    return isBSTUtil(root, LLONG_MIN, LLONG_MAX);
}

// ============================================================
// 6. Populate Inorder Successor of all nodes
// ============================================================
void populateNext(Node* root, Node*& prev) {
    if (!root) return;
    populateNext(root->right, prev);
    root->next = prev;
    prev = root;
    populateNext(root->left, prev);
}

// ============================================================
// 7. Find LCA of 2 nodes in a BST
// ============================================================
Node* findLCABST(Node* root, int n1, int n2) {
    if (!root) return NULL;
    if (n1 < root->data && n2 < root->data) return findLCABST(root->left, n1, n2);
    if (n1 > root->data && n2 > root->data) return findLCABST(root->right, n1, n2);
    return root;
}

// ============================================================
// 8. Construct BST from Preorder Traversal
// ============================================================
Node* bstFromPreorderUtil(vector<int>& pre, int& idx, int bound) {
    if (idx >= pre.size() || pre[idx] > bound) return NULL;
    Node* root = new Node(pre[idx++]);
    root->left = bstFromPreorderUtil(pre, idx, root->data);
    root->right = bstFromPreorderUtil(pre, idx, bound);
    return root;
}

Node* bstFromPreorder(vector<int>& pre) {
    int idx = 0;
    return bstFromPreorderUtil(pre, idx, INT_MAX);
}

// ============================================================
// 9. Convert Binary Tree into BST
// ============================================================
void storeInorder(Node* root, vector<int>& v) {
    if (!root) return;
    storeInorder(root->left, v);
    v.push_back(root->data);
    storeInorder(root->right, v);
}

void arrayToBST(Node* root, vector<int>& v, int& idx) {
    if (!root) return;
    arrayToBST(root->left, v, idx);
    root->data = v[idx++];
    arrayToBST(root->right, v, idx);
}

void binaryTreeToBST(Node* root) {
    vector<int> v;
    storeInorder(root, v);
    sort(v.begin(), v.end());
    int idx = 0;
    arrayToBST(root, v, idx);
}

// ============================================================
// 10. Convert a Normal BST into a Balanced BST
// ============================================================
Node* buildBalancedTreeUtil(vector<int>& v, int start, int end) {
    if (start > end) return NULL;
    int mid = start + (end - start) / 2;
    Node* root = new Node(v[mid]);
    root->left = buildBalancedTreeUtil(v, start, mid - 1);
    root->right = buildBalancedTreeUtil(v, mid + 1, end);
    return root;
}

Node* balanceBST(Node* root) {
    vector<int> v;
    storeInorder(root, v);
    return buildBalancedTreeUtil(v, 0, v.size() - 1);
}

// ============================================================
// 11. Merge two BST [V.V.IMP]
// ============================================================
vector<int> mergeSortedArrays(vector<int>& a, vector<int>& b) {
    vector<int> res;
    int i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] < b[j]) res.push_back(a[i++]);
        else res.push_back(b[j++]);
    }
    while (i < a.size()) res.push_back(a[i++]);
    while (j < b.size()) res.push_back(b[j++]);
    return res;
}

Node* mergeTwoBSTs(Node* root1, Node* root2) {
    vector<int> v1, v2;
    storeInorder(root1, v1);
    storeInorder(root2, v2);
    vector<int> merged = mergeSortedArrays(v1, v2);
    return buildBalancedTreeUtil(merged, 0, merged.size() - 1);
}

// ============================================================
// 12. Find Kth Largest Element in a BST
// ============================================================
void kthLargestUtil(Node* root, int& k, int& ans) {
    if (!root || k <= 0) return;
    kthLargestUtil(root->right, k, ans);
    k--;
    if (k == 0) {
        ans = root->data;
        return;
    }
    kthLargestUtil(root->left, k, ans);
}

int kthLargest(Node* root, int k) {
    int ans = -1;
    kthLargestUtil(root, k, ans);
    return ans;
}

// ============================================================
// 13. Find Kth Smallest Element in a BST
// ============================================================
void kthSmallestUtil(Node* root, int& k, int& ans) {
    if (!root || k <= 0) return;
    kthSmallestUtil(root->left, k, ans);
    k--;
    if (k == 0) {
        ans = root->data;
        return;
    }
    kthSmallestUtil(root->right, k, ans);
}

int kthSmallest(Node* root, int k) {
    int ans = -1;
    kthSmallestUtil(root, k, ans);
    return ans;
}

// ============================================================
// 14. Count Pairs from 2 BST Whose Sum is Equal to Given Value "X"
// ============================================================
int countPairs(Node* root1, Node* root2, int x) {
    if (!root1 || !root2) return 0;

    stack<Node*> st1, st2;
    Node* cur1 = root1;
    Node* cur2 = root2;
    int count = 0;

    while (true) {
        while (cur1) {
            st1.push(cur1);
            cur1 = cur1->left;
        }
        while (cur2) {
            st2.push(cur2);
            cur2 = cur2->right;
        }
        if (st1.empty() || st2.empty()) break;

        Node* top1 = st1.top();
        Node* top2 = st2.top();

        if (top1->data + top2->data == x) {
            count++;
            st1.pop();
            st2.pop();
            cur1 = top1->right;
            cur2 = top2->left;
        } else if (top1->data + top2->data < x) {
            st1.pop();
            cur1 = top1->right;
        } else {
            st2.pop();
            cur2 = top2->left;
        }
    }
    return count;
}

// ============================================================
// 15. Find Median of BST in O(n) Time and O(1) Space (Morris Traversal)
// ============================================================
int countNodes(Node* root) {
    int count = 0;
    Node* cur = root;
    while (cur) {
        if (!cur->left) {
            count++;
            cur = cur->right;
        } else {
            Node* prev = cur->left;
            while (prev->right && prev->right != cur) prev = prev->right;
            if (!prev->right) {
                prev->right = cur;
                cur = cur->left;
            } else {
                prev->right = NULL;
                count++;
                cur = cur->right;
            }
        }
    }
    return count;
}

double findMedian(Node* root) {
    if (!root) return 0.0;
    int total = countNodes(root);
    int curCount = 0;
    Node* cur = root, *prevNode = NULL;
    int first = -1, second = -1;

    while (cur) {
        if (!cur->left) {
            curCount++;
            if (total % 2 != 0 && curCount == (total + 1) / 2) return cur->data;
            if (total % 2 == 0) {
                if (curCount == total / 2) first = cur->data;
                else if (curCount == total / 2 + 1) second = cur->data;
            }
            cur = cur->right;
        } else {
            Node* prev = cur->left;
            while (prev->right && prev->right != cur) prev = prev->right;
            if (!prev->right) {
                prev->right = cur;
                cur = cur->left;
            } else {
                prev->right = NULL;
                curCount++;
                if (total % 2 != 0 && curCount == (total + 1) / 2) return cur->data;
                if (total % 2 == 0) {
                    if (curCount == total / 2) first = cur->data;
                    else if (curCount == total / 2 + 1) second = cur->data;
                }
                cur = cur->right;
            }
        }
    }
    return (first + second) / 2.0;
}

// ============================================================
// 16. Count BST Nodes That Lie in a Given Range
// ============================================================
int getCountInRange(Node* root, int low, int high) {
    if (!root) return 0;
    if (root->data >= low && root->data <= high) {
        return 1 + getCountInRange(root->left, low, high) + getCountInRange(root->right, low, high);
    } else if (root->data < low) {
        return getCountInRange(root->right, low, high);
    } else {
        return getCountInRange(root->left, low, high);
    }
}

// ============================================================
// 17. Replace Every Element with the Least Greater Element on its Right
// ============================================================
Node* insertAndFindSucc(Node* root, int val, Node*& succ) {
    if (!root) return new Node(val);
    if (val < root->data) {
        succ = root;
        root->left = insertAndFindSucc(root->left, val, succ);
    } else {
        root->right = insertAndFindSucc(root->right, val, succ);
    }
    return root;
}

vector<int> replaceWithLeastGreater(vector<int>& arr) {
    Node* root = NULL;
    int n = arr.size();
    vector<int> result(n);
    for (int i = n - 1; i >= 0; i--) {
        Node* succ = NULL;
        root = insertAndFindSucc(root, arr[i], succ);
        result[i] = succ ? succ->data : -1;
    }
    return result;
}

// ============================================================
// 18. Given 'n' Appointments, Find Conflicting Appointments
// ============================================================
struct Interval {
    int low, high;
};

struct ITNode {
    Interval* i;
    int max;
    ITNode *left, *right;
    ITNode(Interval* interval) {
        i = interval;
        max = interval->high;
        left = NULL;
        right = NULL;
    }
};

ITNode* insertInterval(ITNode* root, Interval* i) {
    if (!root) return new ITNode(i);
    int l = root->i->low;
    if (i->low < l) root->left = insertInterval(root->left, i);
    else root->right = insertInterval(root->right, i);
    if (root->max < i->high) root->max = i->high;
    return root;
}

Interval* overlapSearch(ITNode* root, Interval* i) {
    if (!root) return NULL;
    if (i->low < root->i->high && root->i->low < i->high) return root->i;
    if (root->left && root->left->max >= i->low) return overlapSearch(root->left, i);
    return overlapSearch(root->right, i);
}

void printConflictingAppointments(vector<Interval> appts) {
    ITNode* root = NULL;
    for (int i = 0; i < appts.size(); i++) {
        Interval* res = overlapSearch(root, &appts[i]);
        if (res) {
            cout << "[" << appts[i].low << "," << appts[i].high 
                 << "] conflicts with [" << res->low << "," << res->high << "]\n";
        }
        root = insertInterval(root, &appts[i]);
    }
}

// ============================================================
// 19. Check Preorder is Valid or Not
// ============================================================
bool isValidPreorder(vector<int>& pre) {
    stack<int> s;
    int root = INT_MIN;
    for (int val : pre) {
        if (val < root) return false;
        while (!s.empty() && s.top() < val) {
            root = s.top();
            s.pop();
        }
        s.push(val);
    }
    return true;
}

// ============================================================
// 20. Check Whether BST Contains Dead End
// ============================================================
void getLeafAndAllNodes(Node* root, unordered_set<int>& allNodes, unordered_set<int>& leafNodes) {
    if (!root) return;
    allNodes.insert(root->data);
    if (!root->left && !root->right) {
        leafNodes.insert(root->data);
        return;
    }
    getLeafAndAllNodes(root->left, allNodes, leafNodes);
    getLeafAndAllNodes(root->right, allNodes, leafNodes);
}

bool isDeadEnd(Node* root) {
    unordered_set<int> allNodes, leafNodes;
    allNodes.insert(0); // Lower boundary for natural numbers
    getLeafAndAllNodes(root, allNodes, leafNodes);

    for (int leaf : leafNodes) {
        if (allNodes.count(leaf - 1) && allNodes.count(leaf + 1)) return true;
    }
    return false;
}

// ============================================================
// 21. Largest BST in a Binary Tree [V.V.V.V. IMP]
// ============================================================
struct BSTInfo {
    bool isBST;
    int size;
    int minVal;
    int maxVal;
};

BSTInfo largestBSTUtil(Node* root, int& maxBSTSize) {
    if (!root) return {true, 0, INT_MAX, INT_MIN};

    BSTInfo left = largestBSTUtil(root->left, maxBSTSize);
    BSTInfo right = largestBSTUtil(root->right, maxBSTSize);

    BSTInfo curr;
    curr.size = 1 + left.size + right.size;

    if (left.isBST && right.isBST && root->data > left.maxVal && root->data < right.minVal) {
        curr.isBST = true;
        curr.minVal = min(root->data, left.minVal);
        curr.maxVal = max(root->data, right.maxVal);
        maxBSTSize = max(maxBSTSize, curr.size);
    } else {
        curr.isBST = false;
        curr.minVal = 0;
        curr.maxVal = 0;
    }
    return curr;
}

int largestBST(Node* root) {
    int maxBSTSize = 0;
    largestBSTUtil(root, maxBSTSize);
    return maxBSTSize;
}

// ============================================================
// 22. Flatten BST to Sorted List (Right-skewed)
// ============================================================
void flattenUtil(Node* root, Node*& prev) {
    if (!root) return;
    flattenUtil(root->left, prev);
    prev->left = NULL;
    prev->right = root;
    prev = root;
    flattenUtil(root->right, prev);
}

Node* flattenBST(Node* root) {
    Node* dummy = new Node(-1);
    Node* prev = dummy;
    flattenUtil(root, prev);
    prev->left = NULL;
    prev->right = NULL;
    Node* res = dummy->right;
    delete dummy;
    return res;
}

// ============================================================
// CLI HELPER & MAIN EXECUTION DEMO
// ============================================================
void printInorder(Node* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->data << " ";
    printInorder(root->right);
}

int main() {
    int n;
    cout << "Enter number of elements to insert in BST: ";
    cin >> n;

    Node* root = NULL;
    cout << "Enter " << n << " space-separated integers: ";
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        root = insertBST(root, val);
    }

    cout << "\nInorder Traversal: ";
    printInorder(root);
    cout << "\n";

    cout << "Min Element: " << findMin(root) << "\n";
    cout << "Max Element: " << findMax(root) << "\n";
    cout << "Is valid BST: " << (isBST(root) ? "Yes" : "No") << "\n";
    cout << "Median of BST: " << findMedian(root) << "\n";

    int k;
    cout << "\nEnter K to find Kth Smallest and Largest: ";
    cin >> k;
    cout << k << "-th Smallest: " << kthSmallest(root, k) << "\n";
    cout << k << "-th Largest: " << kthLargest(root, k) << "\n";

    int low, high;
    cout << "\nEnter range [low, high] to count nodes: ";
    cin >> low >> high;
    cout << "Nodes in range [" << low << ", " << high << "]: " 
         << getCountInRange(root, low, high) << "\n";

    int delVal;
    cout << "\nEnter value to delete from BST: ";
    cin >> delVal;
    root = deleteNode(root, delVal);
    cout << "Inorder after deletion: ";
    printInorder(root);
    cout << "\n";

    return 0;
}