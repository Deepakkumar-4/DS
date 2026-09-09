#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;

// ==========================================
// 0. BASIC NODE STRUCTURES (NO OOP)
// ==========================================

struct Node {
    int data;
    Node* next;
    Node(int val) {
        data = val;
        next = NULL;
    }
};

struct DLLNode {
    int data;
    DLLNode* next;
    DLLNode* prev;
    DLLNode(int val) {
        data = val;
        next = NULL;
        prev = NULL;
    }
};

struct FlatNode {
    int data;
    FlatNode* next;
    FlatNode* bottom;
    FlatNode(int val) {
        data = val;
        next = NULL;
        bottom = NULL;
    }
};

struct RandomNode {
    int data;
    RandomNode* next;
    RandomNode* random;
    RandomNode(int val) {
        data = val;
        next = NULL;
        random = NULL;
    }
};

// Utility to print a Singly Linked List
void printList(Node* head) {
    Node* curr = head;
    while (curr != NULL) {
        cout << curr->data << " -> ";
        curr = curr->next;
    }
    cout << "NULL\n";
}

// ==========================================
// SOLUTIONS TO ALL QUESTIONS
// ==========================================

// 1A. Reverse Linked List (Iterative)
Node* reverseIterative(Node* head) {
    Node* prev = NULL;
    Node* curr = head;
    Node* nextNode = NULL;
    while (curr != NULL) {
        nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }
    return prev;
}

// 1B. Reverse Linked List (Recursive)
Node* reverseRecursive(Node* head) {
    if (head == NULL || head->next == NULL) return head;
    Node* newHead = reverseRecursive(head->next);
    head->next->next = head;
    head->next = NULL;
    return newHead;
}

// 2. Reverse a Linked List in groups of given size K
Node* reverseInGroups(Node* head, int k) {
    if (head == NULL) return NULL;
    Node* curr = head;
    Node* prev = NULL;
    Node* nextNode = NULL;
    int count = 0;

    while (curr != NULL && count < k) {
        nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
        count++;
    }

    if (nextNode != NULL) {
        head->next = reverseInGroups(nextNode, k);
    }
    return prev;
}

// 3. Detect loop in a linked list (Floyd's Cycle Finding Algorithm)
bool detectLoop(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

// 4. Delete loop in a linked list
void removeLoop(Node* head) {
    if (head == NULL || head->next == NULL) return;
    Node* slow = head;
    Node* fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }

    if (slow != fast) return; // No loop

    // If loop starts at head
    if (slow == head) {
        while (fast->next != head) fast = fast->next;
        fast->next = NULL;
        return;
    }

    slow = head;
    while (slow->next != fast->next) {
        slow = slow->next;
        fast = fast->next;
    }
    fast->next = NULL; // Break loop
}

// 5. Find the starting point of the loop
Node* findStartingPointOfLoop(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            slow = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow;
        }
    }
    return NULL;
}

// 6. Remove Duplicates in a sorted Linked List
Node* removeDuplicatesSorted(Node* head) {
    Node* curr = head;
    while (curr != NULL && curr->next != NULL) {
        if (curr->data == curr->next->data) {
            Node* temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
        } else {
            curr = curr->next;
        }
    }
    return head;
}

// 7. Remove Duplicates in an Unsorted Linked List
Node* removeDuplicatesUnsorted(Node* head) {
    if (head == NULL) return NULL;
    unordered_set<int> visited;
    Node* curr = head;
    Node* prev = NULL;

    while (curr != NULL) {
        if (visited.count(curr->data)) {
            prev->next = curr->next;
            delete curr;
            curr = prev->next;
        } else {
            visited.insert(curr->data);
            prev = curr;
            curr = curr->next;
        }
    }
    return head;
}

// 8. Move the last element to Front in a Linked List
Node* moveLastToFront(Node* head) {
    if (head == NULL || head->next == NULL) return head;
    Node* secLast = NULL;
    Node* last = head;
    while (last->next != NULL) {
        secLast = last;
        last = last->next;
    }
    secLast->next = NULL;
    last->next = head;
    return last;
}

// 9. Add "1" to a number represented as a Linked List
Node* addOne(Node* head) {
    head = reverseIterative(head);
    Node* curr = head;
    int carry = 1;

    while (curr != NULL && carry > 0) {
        int sum = curr->data + carry;
        curr->data = sum % 10;
        carry = sum / 10;
        if (curr->next == NULL && carry > 0) {
            curr->next = new Node(carry);
            carry = 0;
        }
        curr = curr->next;
    }
    return reverseIterative(head);
}

// 10. Add two numbers represented by linked lists
Node* addTwoLists(Node* l1, Node* l2) {
    l1 = reverseIterative(l1);
    l2 = reverseIterative(l2);

    Node* dummy = new Node(0);
    Node* curr = dummy;
    int carry = 0;

    while (l1 != NULL || l2 != NULL || carry != 0) {
        int sum = carry;
        if (l1 != NULL) { sum += l1->data; l1 = l1->next; }
        if (l2 != NULL) { sum += l2->data; l2 = l2->next; }

        carry = sum / 10;
        curr->next = new Node(sum % 10);
        curr = curr->next;
    }
    return reverseIterative(dummy->next);
}

// 11. Intersection of two Sorted Linked List
Node* findIntersectionSorted(Node* head1, Node* head2) {
    Node* dummy = new Node(0);
    Node* tail = dummy;

    while (head1 != NULL && head2 != NULL) {
        if (head1->data == head2->data) {
            tail->next = new Node(head1->data);
            tail = tail->next;
            head1 = head1->next;
            head2 = head2->next;
        } else if (head1->data < head2->data) {
            head1 = head1->next;
        } else {
            head2 = head2->next;
        }
    }
    return dummy->next;
}

// 12. Intersection Point of two Linked Lists (by reference/address)
Node* getIntersectionNode(Node* headA, Node* headB) {
    Node* a = headA;
    Node* b = headB;
    while (a != b) {
        a = (a == NULL) ? headB : a->next;
        b = (b == NULL) ? headA : b->next;
    }
    return a;
}

// Helper: Merge two sorted singly linked lists
Node* mergeLists(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;
    if (a->data <= b->data) {
        a->next = mergeLists(a->next, b);
        return a;
    } else {
        b->next = mergeLists(a, b->next);
        return b;
    }
}

// 13. Merge Sort For Linked lists
Node* mergeSort(Node* head) {
    if (head == NULL || head->next == NULL) return head;

    Node* slow = head;
    Node* fast = head->next;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* mid = slow->next;
    slow->next = NULL;

    Node* left = mergeSort(head);
    Node* right = mergeSort(mid);
    return mergeLists(left, right);
}

// 14. Quicksort for Linked Lists
Node* getTail(Node* cur) {
    while (cur != NULL && cur->next != NULL) cur = cur->next;
    return cur;
}

Node* partition(Node* head, Node* end, Node** newHead, Node** newEnd) {
    Node* pivot = end;
    Node* prev = NULL, *curr = head, *tail = pivot;

    while (curr != pivot) {
        if (curr->data < pivot->data) {
            if (*newHead == NULL) *newHead = curr;
            prev = curr;
            curr = curr->next;
        } else {
            if (prev) prev->next = curr->next;
            Node* temp = curr->next;
            curr->next = NULL;
            tail->next = curr;
            tail = curr;
            curr = temp;
        }
    }
    if (*newHead == NULL) *newHead = pivot;
    *newEnd = tail;
    return pivot;
}

Node* quickSortRecur(Node* head, Node* end) {
    if (!head || head == end) return head;

    Node *newHead = NULL, *newEnd = NULL;
    Node* pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        Node* temp = newHead;
        while (temp->next != pivot) temp = temp->next;
        temp->next = NULL;

        newHead = quickSortRecur(newHead, temp);
        temp = getTail(newHead);
        temp->next = pivot;
    }
    pivot->next = quickSortRecur(pivot->next, newEnd);
    return newHead;
}

Node* quickSort(Node* head) {
    return quickSortRecur(head, getTail(head));
}

// 15. Find the middle Element of a linked list
Node* findMiddle(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// 16. Check if a linked list is a circular linked list
bool isCircular(Node* head) {
    if (head == NULL) return true;
    Node* curr = head->next;
    while (curr != NULL && curr != head) {
        curr = curr->next;
    }
    return (curr == head);
}

// 17. Split a Circular linked list into two halves
void splitCircularList(Node* head, Node** head1, Node** head2) {
    if (head == NULL) return;
    Node* slow = head;
    Node* fast = head;

    while (fast->next != head && fast->next->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }

    if (fast->next->next == head) {
        fast = fast->next;
    }

    *head1 = head;
    if (head->next != head) {
        *head2 = slow->next;
    }
    fast->next = slow->next; // Close second circular list
    slow->next = head;       // Close first circular list
}

// 18. Check whether Singly Linked list is a palindrome
bool isPalindrome(Node* head) {
    if (head == NULL || head->next == NULL) return true;

    Node* slow = head;
    Node* fast = head;
    while (fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    slow->next = reverseIterative(slow->next);
    Node* p1 = head;
    Node* p2 = slow->next;

    bool result = true;
    while (p2 != NULL) {
        if (p1->data != p2->data) {
            result = false;
            break;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    slow->next = reverseIterative(slow->next); // Restore list
    return result;
}

// 19. Deletion from a Circular Linked List
Node* deleteNodeCircular(Node* head, int key) {
    if (head == NULL) return NULL;

    Node *curr = head, *prev = NULL;
    while (curr->data != key) {
        if (curr->next == head) return head; // Key not found
        prev = curr;
        curr = curr->next;
    }

    // Only one node in list
    if (curr->next == head && prev == NULL) {
        delete curr;
        return NULL;
    }

    // If head node is to be deleted
    if (curr == head) {
        prev = head;
        while (prev->next != head) prev = prev->next;
        head = head->next;
        prev->next = head;
        delete curr;
    } else {
        prev->next = curr->next;
        delete curr;
    }
    return head;
}

// 20. Reverse a Doubly Linked list
DLLNode* reverseDLL(DLLNode* head) {
    if (head == NULL || head->next == NULL) return head;
    DLLNode* curr = head;
    DLLNode* temp = NULL;

    while (curr != NULL) {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
    }
    if (temp != NULL) head = temp->prev;
    return head;
}

// 21. Find pairs with a given sum in a sorted DLL
void findPairsWithSum(DLLNode* head, int sum) {
    DLLNode* first = head;
    DLLNode* second = head;
    while (second->next != NULL) second = second->next;

    while (first != NULL && second != NULL && first != second && second->next != first) {
        int curSum = first->data + second->data;
        if (curSum == sum) {
            cout << "(" << first->data << ", " << second->data << ") ";
            first = first->next;
            second = second->prev;
        } else if (curSum < sum) {
            first = first->next;
        } else {
            second = second->prev;
        }
    }
    cout << "\n";
}

// 22. Count triplets in a sorted DLL whose sum equals X
int countTripletsDLL(DLLNode* head, int x) {
    int count = 0;
    DLLNode* current = head;
    DLLNode* last = head;
    while (last->next != NULL) last = last->next;

    while (current != NULL) {
        DLLNode* first = current->next;
        DLLNode* second = last;

        while (first != NULL && second != NULL && first != second && second->next != first) {
            int sum = current->data + first->data + second->data;
            if (sum == x) {
                count++;
                first = first->next;
                second = second->prev;
            } else if (sum < x) {
                first = first->next;
            } else {
                second = second->prev;
            }
        }
        current = current->next;
    }
    return count;
}

// 23. Sort a "k" sorted Doubly Linked list (using min-heap)
struct compareDLL {
    bool operator()(DLLNode* a, DLLNode* b) {
        return a->data > b->data;
    }
};

DLLNode* sortAKSortedDLL(DLLNode* head, int k) {
    if (head == NULL) return head;
    priority_queue<DLLNode*, vector<DLLNode*>, compareDLL> pq;

    DLLNode* newHead = NULL, *last = NULL;
    for (int i = 0; head != NULL && i <= k; i++) {
        pq.push(head);
        head = head->next;
    }

    while (!pq.empty()) {
        if (newHead == NULL) {
            newHead = pq.top();
            newHead->prev = NULL;
            last = newHead;
        } else {
            last->next = pq.top();
            pq.top()->prev = last;
            last = pq.top();
        }
        pq.pop();

        if (head != NULL) {
            pq.push(head);
            head = head->next;
        }
    }
    last->next = NULL;
    return newHead;
}

// 24. Rotate Doubly Linked list by N nodes
DLLNode* rotateDLL(DLLNode* head, int n) {
    if (head == NULL || n == 0) return head;
    DLLNode* curr = head;
    int count = 1;
    while (count < n && curr != NULL) {
        curr = curr->next;
        count++;
    }
    if (curr == NULL || curr->next == NULL) return head;

    DLLNode* nthNode = curr;
    DLLNode* tail = curr;
    while (tail->next != NULL) tail = tail->next;

    tail->next = head;
    head->prev = tail;

    head = nthNode->next;
    head->prev = NULL;
    nthNode->next = NULL;

    return head;
}

// 25. Rotate a Doubly Linked list in group of Given Size
DLLNode* reverseDLLInGroups(DLLNode* head, int k) {
    DLLNode* curr = head;
    DLLNode* nextNode = NULL;
    DLLNode* newHead = NULL;
    int count = 0;

    while (curr != NULL && count < k) {
        nextNode = curr->next;
        curr->next = curr->prev;
        curr->prev = nextNode;
        newHead = curr;
        curr = nextNode;
        count++;
    }

    if (curr != NULL) {
        head->next = reverseDLLInGroups(curr, k);
        if (head->next != NULL) {
            head->next->prev = head;
        }
    }
    return newHead;
}

/*
// ============================================================================
// 26. Can we reverse a linked list in less than O(n)?
// Answer:
// NO, because to reverse a standard pointer-based linked list, each of the N 
// pointers must be updated. This inherently takes Omega(N) time.
//
// 27. Why Quicksort is preferred for Arrays and Merge Sort for LinkedLists?
// Answer:
// - Arrays: Quicksort exhibits great cache locality and in-place sorting (O(1)
//   extra space). Merge Sort requires O(N) extra buffer for arrays.
// - Linked Lists: Merge Sort is preferred because:
//   1. Merging two linked lists takes O(1) extra space (just rewiring pointers).
//   2. Linked lists do not allow O(1) random index access needed by Quicksort's
//      partition step.
// ============================================================================
*/

// 28. Flatten a Linked List
FlatNode* mergeFlatten(FlatNode* a, FlatNode* b) {
    if (!a) return b;
    if (!b) return a;
    FlatNode* res;
    if (a->data < b->data) {
        res = a;
        res->bottom = mergeFlatten(a->bottom, b);
    } else {
        res = b;
        res->bottom = mergeFlatten(a, b->bottom);
    }
    res->next = NULL;
    return res;
}

FlatNode* flatten(FlatNode* root) {
    if (root == NULL || root->next == NULL) return root;
    root->next = flatten(root->next);
    root = mergeFlatten(root, root->next);
    return root;
}

// 29. Sort a LL of 0's, 1's and 2's
Node* sortZeroOneTwo(Node* head) {
    int count[3] = {0, 0, 0};
    Node* curr = head;
    while (curr != NULL) {
        count[curr->data]++;
        curr = curr->next;
    }
    curr = head;
    int idx = 0;
    while (curr != NULL) {
        if (count[idx] == 0) {
            idx++;
        } else {
            curr->data = idx;
            count[idx]--;
            curr = curr->next;
        }
    }
    return head;
}

// 30. Clone a linked list with next and random pointer
RandomNode* cloneLinkedList(RandomNode* head) {
    if (!head) return NULL;

    // Step 1: Duplicate nodes right next to original
    RandomNode* curr = head;
    while (curr) {
        RandomNode* clone = new RandomNode(curr->data);
        clone->next = curr->next;
        curr->next = clone;
        curr = clone->next;
    }

    // Step 2: Assign random pointers
    curr = head;
    while (curr) {
        if (curr->random) {
            curr->next->random = curr->random->next;
        }
        curr = curr->next->next;
    }

    // Step 3: Separate original and clone
    curr = head;
    RandomNode* clonedHead = head->next;
    RandomNode* cloneCurr = clonedHead;

    while (curr) {
        curr->next = curr->next->next;
        if (cloneCurr->next) {
            cloneCurr->next = cloneCurr->next->next;
        }
        curr = curr->next;
        cloneCurr = cloneCurr->next;
    }
    return clonedHead;
}

// 31. Merge K sorted Linked lists
Node* mergeKLists(vector<Node*>& lists) {
    auto comp = [](Node* a, Node* b) { return a->data > b->data; };
    priority_queue<Node*, vector<Node*>, decltype(comp)> pq(comp);

    for (Node* node : lists) {
        if (node) pq.push(node);
    }

    Node* dummy = new Node(0);
    Node* tail = dummy;

    while (!pq.empty()) {
        Node* minNode = pq.top();
        pq.pop();

        tail->next = minNode;
        tail = tail->next;

        if (minNode->next) pq.push(minNode->next);
    }
    return dummy->next;
}

// 32. Multiply 2 numbers represented by LL
long long multiplyTwoLists(Node* l1, Node* l2) {
    long long mod = 1000000007;
    long long num1 = 0, num2 = 0;

    while (l1 != NULL) {
        num1 = (num1 * 10 + l1->data) % mod;
        l1 = l1->next;
    }
    while (l2 != NULL) {
        num2 = (num2 * 10 + l2->data) % mod;
        l2 = l2->next;
    }
    return (num1 * num2) % mod;
}

// 33. Delete nodes which have a greater value on right side
Node* deleteGreaterOnRight(Node* head) {
    head = reverseIterative(head);
    Node* curr = head;
    int maxVal = curr->data;

    while (curr->next != NULL) {
        if (curr->next->data < maxVal) {
            Node* temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
        } else {
            curr = curr->next;
            maxVal = curr->data;
        }
    }
    return reverseIterative(head);
}

// 34. Segregate even and odd nodes in a Linked List
Node* segregateEvenOdd(Node* head) {
    Node* evenStart = NULL, *evenEnd = NULL;
    Node* oddStart = NULL, *oddEnd = NULL;
    Node* curr = head;

    while (curr != NULL) {
        int val = curr->data;
        if (val % 2 == 0) {
            if (evenStart == NULL) {
                evenStart = curr;
                evenEnd = evenStart;
            } else {
                evenEnd->next = curr;
                evenEnd = evenEnd->next;
            }
        } else {
            if (oddStart == NULL) {
                oddStart = curr;
                oddEnd = oddStart;
            } else {
                oddEnd->next = curr;
                oddEnd = oddEnd->next;
            }
        }
        curr = curr->next;
    }

    if (evenStart == NULL) return oddStart;
    if (oddStart == NULL) return evenStart;

    evenEnd->next = oddStart;
    oddEnd->next = NULL;
    return evenStart;
}

// 35. Program for n'th node from the end of a Linked List
int getNthFromEnd(Node* head, int n) {
    Node* first = head;
    Node* second = head;

    for (int i = 0; i < n; i++) {
        if (first == NULL) return -1; // n exceeds list length
        first = first->next;
    }

    while (first != NULL) {
        first = first->next;
        second = second->next;
    }
    return second ? second->data : -1;
}

// 36. Find the first non-repeating character from a stream of characters
string firstNonRepeatingCharStream(string stream) {
    int freq[26] = {0};
    queue<char> q;
    string result = "";

    for (char ch : stream) {
        freq[ch - 'a']++;
        q.push(ch);

        while (!q.empty() && freq[q.front() - 'a'] > 1) {
            q.pop();
        }

        if (q.empty()) {
            result += '#';
        } else {
            result += q.front();
        }
    }
    return result;
}

// ==========================================
// MAIN FUNCTION (QUICK DEMO)
// ==========================================
Node* takeInput(int n) {
    if (n <= 0) return NULL;

    int val;
    cin >> val;
    Node* head = new Node(val);
    Node* tail = head;

    for (int i = 1; i < n; i++) {
        cin >> val;
        tail->next = new Node(val);
        tail = tail->next;
    }
    return head;
}

int main() {
    // 1. Reverse Demo
    int n1;
    cout << "Enter number of elements for Reverse List: ";
    cin >> n1;
    cout << "Enter " << n1 << " elements: ";
    Node* head = takeInput(n1);

    cout << "Original List: ";
    printList(head);
    head = reverseIterative(head);
    cout << "Reversed List: ";
    printList(head);

    // 2. Sort 0s, 1s, 2s Demo
    int n2;
    cout << "\nEnter number of elements for 0s, 1s, 2s List: ";
    cin >> n2;
    cout << "Enter " << n2 << " elements (only 0, 1, or 2): ";
    Node* unsorted = takeInput(n2);

    cout << "Before sort: ";
    printList(unsorted);
    unsorted = sortZeroOneTwo(unsorted);
    cout << "After sort: ";
    printList(unsorted);

    // 3. First Non-Repeating Stream Demo
    string s;
    cout << "\nEnter character stream string: ";
    cin >> s;
    cout << "First non-repeating stream: " 
         << firstNonRepeatingCharStream(s) << "\n";

    return 0;
}