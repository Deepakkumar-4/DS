#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// ============================================================
// 0. BASIC AVL TREE NODE STRUCTURE (NO OOP)
// ============================================================
struct Node {
    int data;
    int height;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        height = 1;
        left = NULL;
        right = NULL;
    }
};

// ============================================================
// 1. HELPER FUNCTIONS
// ============================================================

// Get node height
int getHeight(Node* node) {
    if (!node) return 0;
    return node->height;
}

// Get balance factor of node (left height - right height)
int getBalance(Node* node) {
    if (!node) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Right rotation (LL Case)
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x; // New root
}

// Left rotation (RR Case)
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y; // New root
}

// Find minimum value node in subtree (for deletion successor)
Node* minValueNode(Node* node) {
    Node* curr = node;
    while (curr && curr->left != NULL) {
        curr = curr->left;
    }
    return curr;
}

// ============================================================
// 2. INSERTION IN AVL TREE (Self-Balancing)
// ============================================================
Node* insertAVL(Node* node, int key) {
    // Standard BST insertion
    if (!node) return new Node(key);

    if (key < node->data) {
        node->left = insertAVL(node->left, key);
    } else if (key > node->data) {
        node->right = insertAVL(node->right, key);
    } else {
        return node; // Duplicate keys not allowed
    }

    // Update height of current node
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Check balance factor
    int balance = getBalance(node);

    // LL Case: Left Left -> Right rotate
    if (balance > 1 && key < node->left->data) {
        return rightRotate(node);
    }

    // RR Case: Right Right -> Left rotate
    if (balance < -1 && key > node->right->data) {
        return leftRotate(node);
    }

    // LR Case: Left Right -> Left rotate child, then Right rotate node
    if (balance > 1 && key > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL Case: Right Left -> Right rotate child, then Left rotate node
    if (balance < -1 && key < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// ============================================================
// 3. DELETION IN AVL TREE (Self-Balancing)
// ============================================================
Node* deleteAVL(Node* root, int key) {
    // Standard BST deletion
    if (!root) return root;

    if (key < root->data) {
        root->left = deleteAVL(root->left, key);
    } else if (key > root->data) {
        root->right = deleteAVL(root->right, key);
    } else {
        // Node with only one child or no child
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            // Node with two children: get inorder successor
            Node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteAVL(root->right, temp->data);
        }
    }

    if (!root) return root;

    // Update height
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Check balance factor
    int balance = getBalance(root);

    // LL Case
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }

    // LR Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR Case
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }

    // RL Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// ============================================================
// 4. SEARCH & VERIFICATION
// ============================================================
bool searchAVL(Node* root, int key) {
    if (!root) return false;
    if (root->data == key) return true;
    if (key < root->data) return searchAVL(root->left, key);
    return searchAVL(root->right, key);
}

// ============================================================
// 5. TRAVERSALS & DISPLAY
// ============================================================
void printPreorder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    printPreorder(root->left);
    printPreorder(root->right);
}

void printInorder(Node* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->data << " ";
    printInorder(root->right);
}

void printLevelOrder(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int sz = q.size();
        while (sz--) {
            Node* curr = q.front();
            q.pop();
            cout << curr->data << "(BF=" << getBalance(curr) << ") ";
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        cout << "\n";
    }
}

// ============================================================
// CLI MAIN RUNNER
// ============================================================
int main() {
    int n;
    cout << "Enter number of elements to insert in AVL Tree: ";
    cin >> n;

    Node* root = NULL;
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        root = insertAVL(root, val);
    }

    cout << "\nInorder Traversal (Sorted): ";
    printInorder(root);
    cout << "\n";

    cout << "Preorder Traversal: ";
    printPreorder(root);
    cout << "\n";

    cout << "\nLevel Order Structure (Node with Balance Factor):\n";
    printLevelOrder(root);

    int searchVal;
    cout << "\nEnter value to search: ";
    cin >> searchVal;
    cout << "Value " << (searchAVL(root, searchVal) ? "Found" : "Not Found") << "\n";

    int delVal;
    cout << "\nEnter value to delete: ";
    cin >> delVal;
    root = deleteAVL(root, delVal);

    cout << "\nInorder after deletion: ";
    printInorder(root);
    cout << "\n";

    cout << "\nLevel Order Structure after deletion:\n";
    printLevelOrder(root);

    return 0;
}