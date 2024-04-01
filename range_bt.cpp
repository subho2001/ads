#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

void rangeSearch(Node* root, int low, int high, vector<int>& result) {
    if (root == nullptr)
        return;

    if (root->data >= low && root->data <= high)
        result.push_back(root->data);

    if (root->data >= low)
        rangeSearch(root->left, low, high, result);

    if (root->data <= high)
        rangeSearch(root->right, low, high, result);
}

Node* createNode(int val) {
    return new Node(val);
}

Node* insert(Node* root, int val) {
    if (root == nullptr)
        return createNode(val);

    if (val < root->data)
        root->left = insert(root->left, val);
    else if (val > root->data)
        root->right = insert(root->right, val);

    return root;
}

void inputRange(int& low, int& high) {
    cout << "Enter the lower bound of the range: ";
    cin >> low;
    cout << "Enter the upper bound of the range: ";
    cin >> high;
}

void inputTree(Node*& root) {
    int num;
    cout << "Enter the number of elements in the BST: ";
    cin >> num;
    cout << "Enter the elements of the BST: ";
    while (num--) {
        int val;
        cin >> val;
        root = insert(root, val);
    }
}

int main() {
    Node* root = nullptr;

    inputTree(root);

    int low, high;
    inputRange(low, high);

    vector<int> result;
    rangeSearch(root, low, high, result);

    cout << "Elements in range [" << low << ", " << high << "]: ";
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
