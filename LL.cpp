#include <iostream>

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


// --- CLI Interactive Program ---

int main() {
    LinkedList* list = createList();
    int choice;

    while (true) {
        std::cout << "\n==============================\n";
        std::cout << "       LINKED LIST CLI\n";
        std::cout << "==============================\n";
        std::cout << "--- Basic & Traversal ---\n";
        std::cout << " 1. Traverse (Print)\n";
        std::cout << " 2. Traverse Reverse\n";
        std::cout << " 3. Check isEmpty & getSize\n";
        std::cout << " 4. Get Head & Tail Data\n";
        std::cout << " 5. Get Element at Index\n";
        std::cout << " 6. Find / Contains / GetIndex\n";
        std::cout << "--- Insertion ---\n";
        std::cout << " 7. Insert at Head\n";
        std::cout << " 8. Insert at Tail\n";
        std::cout << " 9. Insert at Index\n";
        std::cout << "10. Insert Before Value\n";
        std::cout << "11. Insert After Value\n";
        std::cout << "--- Deletion ---\n";
        std::cout << "12. Delete Head (removeFirst)\n";
        std::cout << "13. Delete Tail (removeLast)\n";
        std::cout << "14. Delete at Index\n";
        std::cout << "15. Delete Single Value\n";
        std::cout << "16. Delete All Instances of Value\n";
        std::cout << "17. Clear Entire List\n";
        std::cout << " 0. Exit\n";
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
                if (h) std::cout << "Head value: " << h->data << "\n";
                else std::cout << "Head is NULL\n";
                if (t) std::cout << "Tail value: " << t->data << "\n";
                else std::cout << "Tail is NULL\n";
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
                std::cout << "Enter value to search: ";
                std::cin >> val;
                std::cout << "contains(" << val << "): " << (contains(list, val) ? "true" : "false") << "\n";
                std::cout << "getIndex(" << val << "): " << getIndex(list, val) << "\n";
                break;
            }
            case 7: {
                int val;
                std::cout << "Enter value to insert at head: ";
                std::cin >> val;
                insertAtHead(list, val);
                break;
            }
            case 8: {
                int val;
                std::cout << "Enter value to insert at tail: ";
                std::cin >> val;
                insertAtTail(list, val);
                break;
            }
            case 9: {
                int idx, val;
                std::cout << "Enter index: ";
                std::cin >> idx;
                std::cout << "Enter value: ";
                std::cin >> val;
                if (!insertAt(list, idx, val)) std::cout << "Invalid index.\n";
                break;
            }
            case 10: {
                int target, val;
                std::cout << "Enter target value: ";
                std::cin >> target;
                std::cout << "Enter new value to insert: ";
                std::cin >> val;
                if (!insertBeforeValue(list, target, val)) std::cout << "Target value not found.\n";
                break;
            }
            case 11: {
                int target, val;
                std::cout << "Enter target value: ";
                std::cin >> target;
                std::cout << "Enter new value to insert: ";
                std::cin >> val;
                if (!insertAfterValue(list, target, val)) std::cout << "Target value not found.\n";
                break;
            }
            case 12:
                if (!removeFirst(list)) std::cout << "List is already empty.\n";
                else std::cout << "Head removed.\n";
                break;
            case 13:
                if (!removeLast(list)) std::cout << "List is already empty.\n";
                else std::cout << "Tail removed.\n";
                break;
            case 14: {
                int idx;
                std::cout << "Enter index to delete: ";
                std::cin >> idx;
                if (!deleteAt(list, idx)) std::cout << "Invalid index.\n";
                else std::cout << "Deleted node at index " << idx << "\n";
                break;
            }
            case 15: {
                int val;
                std::cout << "Enter value to delete: ";
                std::cin >> val;
                if (!deleteValue(list, val)) std::cout << "Value not found.\n";
                else std::cout << "Deleted value " << val << "\n";
                break;
            }
            case 16: {
                int val;
                std::cout << "Enter value to remove all instances of: ";
                std::cin >> val;
                int removed = deleteAll(list, val);
                std::cout << "Removed " << removed << " node(s).\n";
                break;
            }
            case 17:
                clear(list);
                std::cout << "List cleared.\n";
                break;
            default:
                std::cout << "Invalid choice.\n";
        }
    }

    clear(list);
    delete list;
    return 0;
}