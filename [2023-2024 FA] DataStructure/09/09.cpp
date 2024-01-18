#include <iostream>
#include <sstream>
using namespace std;

struct Node {
    int key;          // Key value of the node
    Node* left;       // Pointer to the left subtree
    Node* right;      // Pointer to the right subtree

    Node(int value) {
        key = value;
        left = right = nullptr;
    }
};

Node* insert(Node* root, int key) {
    // Creating a new node if the tree/subtree is empty
    if (root == nullptr) return new Node(key);

    // Recursive insertion into the left subtree if key is smaller
    if (key < root->key)
        root->left = insert(root->left, key);
    // Recursive insertion into the right subtree if key is larger
    else if (key > root->key)
        root->right = insert(root->right, key);

    return root;
}

bool search(Node* root, int key) {
    // Returning false if the node is null (base case)
    if (root == nullptr) return false;

    // Returning true if the key matches the current node's key
    if (root->key == key) return true;

    // Recursive search in the right subtree if key is larger
    if (root->key < key) return search(root->right, key);
    // Recursive search in the left subtree if key is smaller
    return search(root->left, key);
}

// Function for inorder traversal of the BST
void inorderTraversal(Node* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);   // Traverse left subtree
        cout << root->key << "->";      // Visit the current node
        inorderTraversal(root->right);  // Traverse right subtree
    }
}

// Function to build the BST from user input
void buildTree(Node*& root) {
    cout << "Enter elements (separated by space): \n";
    string line;
    cin.ignore();  // Ignores the newline left in the buffer
    getline(cin, line);
    stringstream ss(line);
    int number;
    while (ss >> number) {
        root = insert(root, number);   // Inserting each number into the tree
    }
}

int main() {
    Node* root = nullptr; // Initializing root as nullptr
    int choice, key;


    cout << "Build a BST first!" << endl;
    buildTree(root);


    while (true) {
        cout << "\n1. Insert Element\n2. Search Element\n3. Display BST\n4. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: 
                cout << "Enter key to insert: ";
                cin >> key;
                root = insert(root, key);
                break;
            case 2:
                cout << "Enter key to search: ";
                cin >> key;
                if (search(root, key))
                    cout << "Key " << key << " found in the BST." << endl;
                else
                    cout << "Key " << key << " not found in the BST." << endl;
                break;
            case 3:
                cout << "BST Inorder Traversal: ";
                inorderTraversal(root);
                cout << endl;
                break;
            case 4: 
                return 0;
            default: // Handling invalid input
                cout << "Invalid Choice." << endl;
        }
    }

    system("pause");

    return 0;
}
