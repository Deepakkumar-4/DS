#include <iostream>
#include <vector>

struct Node {
    int data;
    Node* next;
};

struct LinkedList {
    Node* head;
    Node* tail;
    int size;
};

// ============================================================================
// FUNCTION DOCUMENTATION
// ============================================================================

// --- Creation & Basic Functions ---
// createNode: Allocates a new node on the heap with the given value and nullptr next pointer.
// createList: Allocates and initializes an empty LinkedList struct with head=nullptr, tail=nullptr, size=0.
// initializeHead: Sets list.head directly to a given node pointer and adjusts tail/size if initially empty.
// initializeTail: Sets list.tail directly to a given node pointer.
// isEmpty: Checks if the list currently has zero nodes.
// getSize: Returns the current count of nodes stored in the list.
// clear: Deallocates every node in the list from heap memory and resets head, tail, and size to 0.

// --- Traversal & Access Functions ---
// traverse: Iterates forward from head to tail and prints every node's value.
// traverseReverse: Helper/recursive function that prints the nodes from tail to head without modifying links.
// get: Returns a pointer to the node at a specified 0-based index. Returns nullptr if out of bounds.
// getHead: Returns a pointer to the head node (or nullptr if empty).
// getTail: Returns a pointer to the tail node (or nullptr if empty).
// find: Searches for the first occurrence of a value and returns a pointer to its node.
// contains: Returns true if a value exists in the list, false otherwise.
// getIndex: Returns the 0-based index of the first node matching the value, or -1 if not found.

// --- Insertion Functions ---
// insertAtHead: Inserts a new node at the very beginning of the list.
// insertAtTail: Appends a new node to the end of the list using the tail pointer.
// insertAt: Inserts a value at a specified 0-based index.
// insertBefore: Inserts a new node with newValue immediately before a target Node pointer.
// insertAfter: Inserts a new node with newValue immediately after a target Node pointer.
// insertBeforeValue: Finds the first node matching targetValue and inserts newValue before it.
// insertAfterValue: Finds the first node matching targetValue and inserts newValue after it.

// --- Deletion Functions ---
// deleteHead: Removes the first node of the list and frees its memory.
// deleteTail: Removes the last node of the list and updates the tail pointer.
// deleteAt: Removes the node located at a specified 0-based index.
// deleteValue: Deletes the first occurrence of a node with the specified value.
// deleteAll: Deletes every occurrence of nodes matching the specified value.
// deleteNode: Deletes a specific node given its pointer.
// removeFirst: Alias/wrapper that removes the first element (calls deleteHead).
// removeLast: Alias/wrapper that removes the last element (calls deleteTail).

// --- Reversal Operations ---
// reverse: Iteratively reverses the entire list in-place by reversing next pointers.
// reverseRecursive: Recursively reverses the entire list in-place.
// reverseFirstK: Reverses only the first k nodes of the list.
// reverseBetween: Reverses nodes between 1-based indices left and right.
// reverseInGroups: Reverses nodes in consecutive chunks of size k.
// reverseAlternateK: Reverses groups of size k alternatively (reverses k, skips k, reverses k).

// --- Position / Pointer Operations ---
// findMiddle: Uses fast & slow pointer strategy to locate the middle node.
// findNthFromEnd: Finds the nth node from the tail end of the list (1-based).
// removeNthFromEnd: Deletes the nth node from the tail end of the list (1-based).
// getKthNode: Fetches the node located at 1-based position k.
// getSecondHalf: Returns a pointer to the start of the second half of the list.
// splitList: Splits list into two equal/halved LinkedLists (left half retains original list, right returned).

// --- Cycle Operations ---
// hasCycle: Detects if the list contains a loop using Floyd's Cycle-Finding algorithm.
// findCycleStart: Returns pointer to the node where a cycle begins, or nullptr.
// getCycleLength: Counts the number of nodes forming the internal cycle loop.
// removeCycle: Breaks the cycle loop by setting the tail back to nullptr.
// isCircular: Checks whether the tail points back to the head node.

// --- Comparison Operations ---
// compareLists: Compares two lists lexicographically; returns -1, 0, or 1.
// isEqual: Checks if two lists have identical size and identical node values in sequence.
// isPalindrome: Checks if the node values read the same forwards and backwards.
// findIntersection: Finds the intersecting Node pointer between two singly linked lists (Y-shaped).

// --- Merging & Sorting Operations ---
// mergeTwoLists: Merges two sorted linked lists into a single sorted list.
// mergeKLists: Merges an array/vector of k sorted linked lists into a single sorted list.
// sortList: Sorts the linked list in-place using merge sort algorithm.
// mergeSort: Helper that performs divide-and-conquer merge sort on node chains.
// insertIntoSortedList: Inserts a new value into its sorted ascending position.

// --- Duplicate Operations ---
// removeDuplicatesSorted: Deletes duplicates from an already sorted list in O(N) time.
// removeDuplicatesUnsorted: Deletes duplicates from an unsorted list in O(N^2) time without extra memory.
// removeAllDuplicates: Deletes all nodes that have duplicate values, leaving only distinct values.
// ============================================================================


// --- Creation & Basic Implementations ---

Node* createNode(int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;
    return newNode;
}

LinkedList* createList() {
    LinkedList* list = new LinkedList;
    list->head = nullptr;
    list->tail = nullptr;
    list->size = 0;
    return list;
}

void initializeHead(LinkedList* list, Node* node) {
    list->head = node;
    if (node != nullptr && list->tail == nullptr) {
        list->tail = node;
    }
    if (node != nullptr && list->size == 0) {
        list->size = 1;
    }
}

void initializeTail(LinkedList* list, Node* node) {
    list->tail = node;
}

bool isEmpty(LinkedList* list) {
    return list->head == nullptr;
}

int getSize(LinkedList* list) {
    return list->size;
}

void clear(LinkedList* list) {
    Node* curr = list->head;
    while (curr != nullptr) {
        Node* nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }
    list->head = nullptr;
    list->tail = nullptr;
    list->size = 0;
}

void updateMetadata(LinkedList* list) {
    int count = 0;
    Node* curr = list->head;
    Node* last = nullptr;
    while (curr != nullptr) {
        count++;
        last = curr;
        curr = curr->next;
    }
    list->size = count;
    list->tail = last;
}


// --- Traversal & Access Implementations ---

void traverse(LinkedList* list) {
    if (isEmpty(list)) {
        std::cout << "List is empty.\n";
        return;
    }
    Node* curr = list->head;
    while (curr != nullptr) {
        std::cout << curr->data << " -> ";
        curr = curr->next;
    }
    std::cout << "NULL\n";
}

void reversePrintHelper(Node* node) {
    if (node == nullptr) return;
    reversePrintHelper(node->next);
    std::cout << node->data << " -> ";
}

void traverseReverse(LinkedList* list) {
    if (isEmpty(list)) {
        std::cout << "List is empty.\n";
        return;
    }
    reversePrintHelper(list->head);
    std::cout << "HEAD\n";
}

Node* get(LinkedList* list, int index) {
    if (index < 0 || index >= list->size) return nullptr;
    Node* curr = list->head;
    for (int i = 0; i < index; ++i) {
        curr = curr->next;
    }
    return curr;
}

Node* getHead(LinkedList* list) {
    return list->head;
}

Node* getTail(LinkedList* list) {
    return list->tail;
}

Node* find(LinkedList* list, int value) {
    Node* curr = list->head;
    while (curr != nullptr) {
        if (curr->data == value) return curr;
        curr = curr->next;
    }
    return nullptr;
}

bool contains(LinkedList* list, int value) {
    return find(list, value) != nullptr;
}

int getIndex(LinkedList* list, int value) {
    Node* curr = list->head;
    int idx = 0;
    while (curr != nullptr) {
        if (curr->data == value) return idx;
        curr = curr->next;
        idx++;
    }
    return -1;
}


// --- Insertion Implementations ---

void insertAtHead(LinkedList* list, int value) {
    Node* newNode = createNode(value);
    newNode->next = list->head;
    list->head = newNode;
    if (list->tail == nullptr) {
        list->tail = newNode;
    }
    list->size++;
}

void insertAtTail(LinkedList* list, int value) {
    Node* newNode = createNode(value);
    if (isEmpty(list)) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->size++;
}

bool insertAt(LinkedList* list, int index, int value) {
    if (index < 0 || index > list->size) return false;
    if (index == 0) {
        insertAtHead(list, value);
        return true;
    }
    if (index == list->size) {
        insertAtTail(list, value);
        return true;
    }
    Node* prev = get(list, index - 1);
    Node* newNode = createNode(value);
    newNode->next = prev->next;
    prev->next = newNode;
    list->size++;
    return true;
}

bool insertBefore(LinkedList* list, Node* target, int newValue) {
    if (list->head == nullptr || target == nullptr) return false;
    if (list->head == target) {
        insertAtHead(list, newValue);
        return true;
    }
    Node* curr = list->head;
    while (curr != nullptr && curr->next != target) {
        curr = curr->next;
    }
    if (curr == nullptr) return false;
    Node* newNode = createNode(newValue);
    newNode->next = target;
    curr->next = newNode;
    list->size++;
    return true;
}

bool insertAfter(LinkedList* list, Node* target, int newValue) {
    if (target == nullptr) return false;
    if (target == list->tail) {
        insertAtTail(list, newValue);
        return true;
    }
    Node* newNode = createNode(newValue);
    newNode->next = target->next;
    target->next = newNode;
    list->size++;
    return true;
}

bool insertBeforeValue(LinkedList* list, int targetValue, int newValue) {
    Node* target = find(list, targetValue);
    return insertBefore(list, target, newValue);
}

bool insertAfterValue(LinkedList* list, int targetValue, int newValue) {
    Node* target = find(list, targetValue);
    return insertAfter(list, target, newValue);
}


// --- Deletion Implementations ---

bool deleteHead(LinkedList* list) {
    if (isEmpty(list)) return false;
    Node* temp = list->head;
    list->head = list->head->next;
    delete temp;
    list->size--;
    if (list->size == 0) {
        list->tail = nullptr;
    }
    return true;
}

bool deleteTail(LinkedList* list) {
    if (isEmpty(list)) return false;
    if (list->head == list->tail) {
        delete list->head;
        list->head = nullptr;
        list->tail = nullptr;
        list->size = 0;
        return true;
    }
    Node* curr = list->head;
    while (curr->next != list->tail) {
        curr = curr->next;
    }
    delete list->tail;
    curr->next = nullptr;
    list->tail = curr;
    list->size--;
    return true;
}

bool deleteAt(LinkedList* list, int index) {
    if (index < 0 || index >= list->size) return false;
    if (index == 0) return deleteHead(list);
    if (index == list->size - 1) return deleteTail(list);

    Node* prev = get(list, index - 1);
    Node* toDelete = prev->next;
    prev->next = toDelete->next;
    delete toDelete;
    list->size--;
    return true;
}

bool deleteValue(LinkedList* list, int value) {
    if (isEmpty(list)) return false;
    if (list->head->data == value) return deleteHead(list);

    Node* curr = list->head;
    while (curr->next != nullptr && curr->next->data != value) {
        curr = curr->next;
    }
    if (curr->next == nullptr) return false;

    Node* toDelete = curr->next;
    if (toDelete == list->tail) {
        list->tail = curr;
    }
    curr->next = toDelete->next;
    delete toDelete;
    list->size--;
    return true;
}

int deleteAll(LinkedList* list, int value) {
    int count = 0;
    while (list->head != nullptr && list->head->data == value) {
        deleteHead(list);
        count++;
    }
    Node* curr = list->head;
    while (curr != nullptr && curr->next != nullptr) {
        if (curr->next->data == value) {
            Node* toDelete = curr->next;
            if (toDelete == list->tail) {
                list->tail = curr;
            }
            curr->next = toDelete->next;
            delete toDelete;
            list->size--;
            count++;
        } else {
            curr = curr->next;
        }
    }
    return count;
}

bool deleteNode(LinkedList* list, Node* node) {
    if (node == nullptr || isEmpty(list)) return false;
    if (node == list->head) return deleteHead(list);
    if (node == list->tail) return deleteTail(list);

    Node* curr = list->head;
    while (curr != nullptr && curr->next != node) {
        curr = curr->next;
    }
    if (curr == nullptr) return false;

    curr->next = node->next;
    delete node;
    list->size--;
    return true;
}

bool removeFirst(LinkedList* list) {
    return deleteHead(list);
}

bool removeLast(LinkedList* list) {
    return deleteTail(list);
}


// --- Reversal Operations Implementations ---

void reverse(LinkedList* list) {
    Node* prev = nullptr;
    Node* curr = list->head;
    Node* nextNode = nullptr;
    list->tail = list->head;
    while (curr != nullptr) {
        nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }
    list->head = prev;
}

Node* reverseRecursiveHelper(Node* head) {
    if (head == nullptr || head->next == nullptr) return head;
    Node* rest = reverseRecursiveHelper(head->next);
    head->next->next = head;
    head->next = nullptr;
    return rest;
}

void reverseRecursive(LinkedList* list) {
    list->tail = list->head;
    list->head = reverseRecursiveHelper(list->head);
}

void reverseFirstK(LinkedList* list, int k) {
    if (!list->head || k <= 1) return;
    Node* curr = list->head;
    Node* prev = nullptr;
    Node* next = nullptr;
    int count = 0;
    while (curr != nullptr && count < k) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        count++;
    }
    list->head->next = curr;
    list->head = prev;
    updateMetadata(list);
}

void reverseBetween(LinkedList* list, int left, int right) {
    if (!list->head || left >= right || left < 1) return;
    Node dummy;
    dummy.next = list->head;
    Node* prev = &dummy;
    for (int i = 1; i < left && prev->next != nullptr; ++i) {
        prev = prev->next;
    }
    if (!prev->next) return;
    Node* curr = prev->next;
    for (int i = 0; i < right - left && curr->next != nullptr; ++i) {
        Node* temp = curr->next;
        curr->next = temp->next;
        temp->next = prev->next;
        prev->next = temp;
    }
    list->head = dummy.next;
    updateMetadata(list);
}

Node* reverseInGroupsHelper(Node* head, int k) {
    Node* curr = head;
    Node* prev = nullptr;
    Node* next = nullptr;
    int count = 0;
    while (curr != nullptr && count < k) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        count++;
    }
    if (next != nullptr) {
        head->next = reverseInGroupsHelper(next, k);
    }
    return prev;
}

void reverseInGroups(LinkedList* list, int k) {
    if (!list->head || k <= 1) return;
    list->head = reverseInGroupsHelper(list->head, k);
    updateMetadata(list);
}

Node* reverseAlternateKHelper(Node* head, int k) {
    Node* curr = head;
    Node* prev = nullptr;
    Node* next = nullptr;
    int count = 0;
    while (curr != nullptr && count < k) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        count++;
    }
    if (head != nullptr) {
        head->next = curr;
    }
    count = 0;
    while (curr != nullptr && count < k - 1) {
        curr = curr->next;
        count++;
    }
    if (curr != nullptr && curr->next != nullptr) {
        curr->next = reverseAlternateKHelper(curr->next, k);
    }
    return prev;
}

void reverseAlternateK(LinkedList* list, int k) {
    if (!list->head || k <= 1) return;
    list->head = reverseAlternateKHelper(list->head, k);
    updateMetadata(list);
}


// --- Position / Pointer Operations Implementations ---

Node* findMiddle(LinkedList* list) {
    if (!list->head) return nullptr;
    Node* slow = list->head;
    Node* fast = list->head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

Node* findNthFromEnd(LinkedList* list, int n) {
    if (!list->head || n <= 0) return nullptr;
    Node* fast = list->head;
    Node* slow = list->head;
    for (int i = 0; i < n; ++i) {
        if (!fast) return nullptr;
        fast = fast->next;
    }
    while (fast != nullptr) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

bool removeNthFromEnd(LinkedList* list, int n) {
    if (!list->head || n <= 0) return false;
    Node dummy;
    dummy.next = list->head;
    Node* fast = &dummy;
    Node* slow = &dummy;
    for (int i = 0; i < n; ++i) {
        fast = fast->next;
        if (!fast) return false;
    }
    while (fast->next != nullptr) {
        fast = fast->next;
        slow = slow->next;
    }
    Node* toDelete = slow->next;
    slow->next = toDelete->next;
    if (toDelete == list->tail) list->tail = slow;
    if (toDelete == list->head) list->head = slow->next;
    delete toDelete;
    list->size--;
    updateMetadata(list);
    return true;
}

Node* getKthNode(LinkedList* list, int k) {
    if (k <= 0 || k > list->size) return nullptr;
    return get(list, k - 1);
}

Node* getSecondHalf(LinkedList* list) {
    if (!list->head) return nullptr;
    return findMiddle(list);
}

LinkedList* splitList(LinkedList* list) {
    LinkedList* secondList = createList();
    if (!list->head || !list->head->next) return secondList;

    Node* slow = list->head;
    Node* fast = list->head;
    Node* prev = nullptr;

    while (fast != nullptr && fast->next != nullptr) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    prev->next = nullptr;
    secondList->head = slow;
    updateMetadata(list);
    updateMetadata(secondList);
    return secondList;
}


// --- Cycle Operations Implementations ---

bool hasCycle(LinkedList* list) {
    if (!list->head) return false;
    Node* slow = list->head;
    Node* fast = list->head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

Node* findCycleStart(LinkedList* list) {
    if (!list->head) return nullptr;
    Node* slow = list->head;
    Node* fast = list->head;
    bool hasLoop = false;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            hasLoop = true;
            break;
        }
    }
    if (!hasLoop) return nullptr;
    slow = list->head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

int getCycleLength(LinkedList* list) {
    if (!list->head) return 0;
    Node* slow = list->head;
    Node* fast = list->head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            int length = 1;
            Node* temp = slow->next;
            while (temp != slow) {
                length++;
                temp = temp->next;
            }
            return length;
        }
    }
    return 0;
}

bool removeCycle(LinkedList* list) {
    Node* start = findCycleStart(list);
    if (!start) return false;
    Node* temp = start;
    while (temp->next != start) {
        temp = temp->next;
    }
    temp->next = nullptr;
    updateMetadata(list);
    return true;
}

bool isCircular(LinkedList* list) {
    if (!list->head) return false;
    Node* curr = list->head->next;
    while (curr != nullptr && curr != list->head) {
        curr = curr->next;
    }
    return (curr == list->head);
}


// --- Comparison Implementations ---

int compareLists(LinkedList* l1, LinkedList* l2) {
    Node* c1 = l1->head;
    Node* c2 = l2->head;
    while (c1 != nullptr && c2 != nullptr) {
        if (c1->data < c2->data) return -1;
        if (c1->data > c2->data) return 1;
        c1 = c1->next;
        c2 = c2->next;
    }
    if (c1 == nullptr && c2 == nullptr) return 0;
    return (c1 != nullptr) ? 1 : -1;
}

bool isEqual(LinkedList* l1, LinkedList* l2) {
    return compareLists(l1, l2) == 0;
}

bool isPalindrome(LinkedList* list) {
    if (!list->head || !list->head->next) return true;

    Node* slow = list->head;
    Node* fast = list->head;
    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* prev = nullptr;
    Node* curr = slow->next;
    Node* next = nullptr;
    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    Node* first = list->head;
    Node* second = prev;
    bool palindrome = true;
    while (second != nullptr) {
        if (first->data != second->data) {
            palindrome = false;
            break;
        }
        first = first->next;
        second = second->next;
    }

    curr = prev;
    prev = nullptr;
    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    slow->next = prev;

    return palindrome;
}

Node* findIntersection(LinkedList* l1, LinkedList* l2) {
    if (!l1->head || !l2->head) return nullptr;
    Node* p1 = l1->head;
    Node* p2 = l2->head;
    while (p1 != p2) {
        p1 = (p1 == nullptr) ? l2->head : p1->next;
        p2 = (p2 == nullptr) ? l1->head : p2->next;
    }
    return p1;
}


// --- Merging & Sorting Implementations ---

Node* mergeTwoListsHelper(Node* l1, Node* l2) {
    Node dummy;
    Node* tail = &dummy;
    dummy.next = nullptr;
    while (l1 != nullptr && l2 != nullptr) {
        if (l1->data <= l2->data) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    tail->next = (l1 != nullptr) ? l1 : l2;
    return dummy.next;
}

LinkedList* mergeTwoLists(LinkedList* l1, LinkedList* l2) {
    LinkedList* result = createList();
    result->head = mergeTwoListsHelper(l1->head, l2->head);
    l1->head = l1->tail = nullptr;
    l1->size = 0;
    l2->head = l2->tail = nullptr;
    l2->size = 0;
    updateMetadata(result);
    return result;
}

LinkedList* mergeKLists(std::vector<LinkedList*>& lists) {
    if (lists.empty()) return createList();
    LinkedList* merged = lists[0];
    for (size_t i = 1; i < lists.size(); ++i) {
        merged = mergeTwoLists(merged, lists[i]);
    }
    return merged;
}

Node* mergeSort(Node* head) {
    if (!head || !head->next) return head;
    Node* slow = head;
    Node* fast = head->next;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node* rightHead = slow->next;
    slow->next = nullptr;

    Node* leftSorted = mergeSort(head);
    Node* rightSorted = mergeSort(rightHead);
    return mergeTwoListsHelper(leftSorted, rightSorted);
}

void sortList(LinkedList* list) {
    list->head = mergeSort(list->head);
    updateMetadata(list);
}

void insertIntoSortedList(LinkedList* list, int value) {
    Node* newNode = createNode(value);
    if (!list->head || list->head->data >= value) {
        newNode->next = list->head;
        list->head = newNode;
        updateMetadata(list);
        return;
    }
    Node* curr = list->head;
    while (curr->next != nullptr && curr->next->data < value) {
        curr = curr->next;
    }
    newNode->next = curr->next;
    curr->next = newNode;
    updateMetadata(list);
}


// --- Duplicate Operations Implementations ---

void removeDuplicatesSorted(LinkedList* list) {
    if (!list->head) return;
    Node* curr = list->head;
    while (curr->next != nullptr) {
        if (curr->data == curr->next->data) {
            Node* dup = curr->next;
            curr->next = dup->next;
            delete dup;
        } else {
            curr = curr->next;
        }
    }
    updateMetadata(list);
}

void removeDuplicatesUnsorted(LinkedList* list) {
    Node* curr1 = list->head;
    while (curr1 != nullptr) {
        Node* curr2 = curr1;
        while (curr2->next != nullptr) {
            if (curr2->next->data == curr1->data) {
                Node* dup = curr2->next;
                curr2->next = dup->next;
                delete dup;
            } else {
                curr2 = curr2->next;
            }
        }
        curr1 = curr1->next;
    }
    updateMetadata(list);
}

void removeAllDuplicates(LinkedList* list) {
    if (!list->head) return;
    Node dummy;
    dummy.next = list->head;
    Node* prev = &dummy;
    Node* curr = list->head;

    while (curr != nullptr) {
        bool isDuplicate = false;
        while (curr->next != nullptr && curr->data == curr->next->data) {
            Node* dup = curr->next;
            curr->next = dup->next;
            delete dup;
            isDuplicate = true;
        }
        if (isDuplicate) {
            Node* temp = curr;
            prev->next = curr->next;
            curr = curr->next;
            delete temp;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    list->head = dummy.next;
    updateMetadata(list);
}


// --- CLI Interactive Program ---

int main() {
    LinkedList* list = createList();
    int choice;

    while (true) {
        std::cout << "\n=======================================================\n";
        std::cout << "                 LINKED LIST FULL CLI                  \n";
        std::cout << "=======================================================\n";
        std::cout << "[BASIC & TRAVERSAL]\n";
        std::cout << "  1. Traverse (Print)              2. Traverse Reverse\n";
        std::cout << "  3. isEmpty & getSize             4. Get Head / Tail Data\n";
        std::cout << "  5. Get Node at Index             6. Find / Contains / GetIndex\n";
        std::cout << "[INSERTION]\n";
        std::cout << "  7. Insert at Head                8. Insert at Tail\n";
        std::cout << "  9. Insert at Index              10. Insert Before/After Value\n";
        std::cout << " 11. Insert Into Sorted List\n";
        std::cout << "[DELETION]\n";
        std::cout << " 12. Delete Head / Tail           13. Delete at Index\n";
        std::cout << " 14. Delete Value / All Values    15. Clear Entire List\n";
        std::cout << "[REVERSAL]\n";
        std::cout << " 16. Reverse List (Iterative)     17. Reverse List (Recursive)\n";
        std::cout << " 18. Reverse First K Nodes        19. Reverse Between Left & Right\n";
        std::cout << " 20. Reverse in Groups of K       21. Reverse Alternate K Nodes\n";
        std::cout << "[POSITION & POINTER]\n";
        std::cout << " 22. Find Middle Node             23. Find / Remove Nth From End\n";
        std::cout << " 24. Get Kth Node / Second Half   25. Split List into Halves\n";
        std::cout << "[CYCLE OPERATIONS]\n";
        std::cout << " 26. Has Cycle / Start / Length   27. Remove Cycle / isCircular\n";
        std::cout << " 28. Inject Loop (For Testing)\n";
        std::cout << "[DUPLICATES, SORTING & PALINDROME]\n";
        std::cout << " 29. Check isPalindrome           30. Sort List (MergeSort)\n";
        std::cout << " 31. Remove Duplicates (Sorted)   32. Remove Duplicates (Unsorted)\n";
        std::cout << " 33. Remove All Duplicates (Keep Unique Only)\n";
        std::cout << "  0. Exit\n";
        std::cout << "-------------------------------------------------------\n";
        std::cout << "Enter option: ";

        if (!(std::cin >> choice)) break;
        if (choice == 0) break;

        switch (choice) {
            case 1:
                traverse(list);
                break;
            case 2:
                traverseReverse(list);
                break;
            case 3:
                std::cout << "isEmpty: " << (isEmpty(list) ? "Yes" : "No") << "\n";
                std::cout << "Current Size: " << getSize(list) << "\n";
                break;
            case 4: {
                Node* h = getHead(list);
                Node* t = getTail(list);
                std::cout << "Head: " << (h ? std::to_string(h->data) : "NULL") << "\n";
                std::cout << "Tail: " << (t ? std::to_string(t->data) : "NULL") << "\n";
                break;
            }
            case 5: {
                int idx;
                std::cout << "Enter 0-based index: ";
                std::cin >> idx;
                Node* res = get(list, idx);
                if (res) std::cout << "Value at index " << idx << ": " << res->data << "\n";
                else std::cout << "Index out of bounds.\n";
                break;
            }
            case 6: {
                int val;
                std::cout << "Enter value: ";
                std::cin >> val;
                std::cout << "contains: " << (contains(list, val) ? "Yes" : "No") << "\n";
                std::cout << "getIndex: " << getIndex(list, val) << "\n";
                break;
            }
            case 7: {
                int val;
                std::cout << "Enter value: ";
                std::cin >> val;
                insertAtHead(list, val);
                break;
            }
            case 8: {
                int val;
                std::cout << "Enter value: ";
                std::cin >> val;
                insertAtTail(list, val);
                break;
            }
            case 9: {
                int idx, val;
                std::cout << "Enter index and value: ";
                std::cin >> idx >> val;
                if (!insertAt(list, idx, val)) std::cout << "Failed: invalid index.\n";
                break;
            }
            case 10: {
                int sub, target, val;
                std::cout << "1. Insert Before | 2. Insert After: ";
                std::cin >> sub;
                std::cout << "Enter target value and new value: ";
                std::cin >> target >> val;
                if (sub == 1) insertBeforeValue(list, target, val);
                else insertAfterValue(list, target, val);
                break;
            }
            case 11: {
                int val;
                std::cout << "Enter value: ";
                std::cin >> val;
                insertIntoSortedList(list, val);
                break;
            }
            case 12: {
                int sub;
                std::cout << "1. Delete Head | 2. Delete Tail: ";
                std::cin >> sub;
                if (sub == 1) deleteHead(list);
                else deleteTail(list);
                break;
            }
            case 13: {
                int idx;
                std::cout << "Enter index to delete: ";
                std::cin >> idx;
                deleteAt(list, idx);
                break;
            }
            case 14: {
                int sub, val;
                std::cout << "1. Delete First Occurrence | 2. Delete All: ";
                std::cin >> sub;
                std::cout << "Enter value: ";
                std::cin >> val;
                if (sub == 1) deleteValue(list, val);
                else deleteAll(list, val);
                break;
            }
            case 15:
                clear(list);
                std::cout << "List cleared.\n";
                break;
            case 16:
                reverse(list);
                std::cout << "Reversed iteratively.\n";
                break;
            case 17:
                reverseRecursive(list);
                std::cout << "Reversed recursively.\n";
                break;
            case 18: {
                int k;
                std::cout << "Enter k: ";
                std::cin >> k;
                reverseFirstK(list, k);
                break;
            }
            case 19: {
                int l, r;
                std::cout << "Enter left and right (1-based): ";
                std::cin >> l >> r;
                reverseBetween(list, l, r);
                break;
            }
            case 20: {
                int k;
                std::cout << "Enter k: ";
                std::cin >> k;
                reverseInGroups(list, k);
                break;
            }
            case 21: {
                int k;
                std::cout << "Enter k: ";
                std::cin >> k;
                reverseAlternateK(list, k);
                break;
            }
            case 22: {
                Node* mid = findMiddle(list);
                if (mid) std::cout << "Middle value: " << mid->data << "\n";
                else std::cout << "List is empty.\n";
                break;
            }
            case 23: {
                int sub, n;
                std::cout << "1. Find Nth From End | 2. Remove Nth From End: ";
                std::cin >> sub;
                std::cout << "Enter n: ";
                std::cin >> n;
                if (sub == 1) {
                    Node* node = findNthFromEnd(list, n);
                    if (node) std::cout << "Value: " << node->data << "\n";
                    else std::cout << "Invalid n.\n";
                } else {
                    removeNthFromEnd(list, n);
                }
                break;
            }
            case 24: {
                int k;
                std::cout << "Enter 1-based k: ";
                std::cin >> k;
                Node* node = getKthNode(list, k);
                if (node) std::cout << "Kth Node: " << node->data << "\n";
                Node* sh = getSecondHalf(list);
                if (sh) std::cout << "Second half starts at: " << sh->data << "\n";
                break;
            }
            case 25: {
                LinkedList* rightHalf = splitList(list);
                std::cout << "Left half: ";
                traverse(list);
                std::cout << "Right half: ";
                traverse(rightHalf);
                clear(rightHalf);
                delete rightHalf;
                break;
            }
            case 26: {
                std::cout << "hasCycle: " << (hasCycle(list) ? "Yes" : "No") << "\n";
                Node* start = findCycleStart(list);
                std::cout << "Cycle Start: " << (start ? std::to_string(start->data) : "None") << "\n";
                std::cout << "Cycle Length: " << getCycleLength(list) << "\n";
                break;
            }
            case 27: {
                std::cout << "isCircular: " << (isCircular(list) ? "Yes" : "No") << "\n";
                if (removeCycle(list)) std::cout << "Cycle removed successfully.\n";
                else std::cout << "No cycle detected to remove.\n";
                break;
            }
            case 28: {
                int idx;
                std::cout << "Create a test cycle pointing tail to 0-based index: ";
                std::cin >> idx;
                Node* target = get(list, idx);
                if (target && list->tail) {
                    list->tail->next = target;
                    std::cout << "Loop created for cycle testing.\n";
                } else {
                    std::cout << "Failed: index invalid or list empty.\n";
                }
                break;
            }
            case 29:
                std::cout << "isPalindrome: " << (isPalindrome(list) ? "Yes" : "No") << "\n";
                break;
            case 30:
                sortList(list);
                std::cout << "Sorted using merge sort.\n";
                break;
            case 31:
                removeDuplicatesSorted(list);
                std::cout << "Removed sorted duplicates.\n";
                break;
            case 32:
                removeDuplicatesUnsorted(list);
                std::cout << "Removed unsorted duplicates.\n";
                break;
            case 33:
                removeAllDuplicates(list);
                std::cout << "Removed all duplicate occurrences.\n";
                break;
            default:
                std::cout << "Invalid choice.\n";
        }
    }

    if (hasCycle(list)) removeCycle(list);
    clear(list);
    delete list;
    return 0;
}