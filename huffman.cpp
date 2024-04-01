#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;
};

Node* getNode(char ch, int freq, Node* left = nullptr, Node* right = nullptr) {
    Node* node = new Node();
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

struct comp {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

void encode(Node* root, string str, unordered_map<char, string>& huffmanCode) {
    if (root == nullptr)
        return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

// void decode(Node* root, int& index, string str) {
//     if (root == nullptr)
//         return;

//     if (!root->left && !root->right) {
//         cout << root->ch;
//         return;
//     }

//     index++;

//     if (str[index] == '0')
//         decode(root->left, index, str);
//     else
//         decode(root->right, index, str);
// }

void buildHuffmanTree(string text) {
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    cout << "Character Frequencies:\n";
    for (auto pair : freq) {
        cout << pair.first << ": " << pair.second << '\n';
    }
    cout << endl;

    priority_queue<Node*, vector<Node*>, comp> pq;
    for (auto pair : freq) {
        pq.push(getNode(pair.first, pair.second));
    }

    while (pq.size() != 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }

    Node* root = pq.top();

    unordered_map<char, string> huffmanCode;
    encode(root, "", huffmanCode);

    cout << "Huffman Codes:\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << " " << pair.second << '\n';
    }
    cout << endl;

    // cout << "Original String:\n" << text << '\n';

    // string encodedString = "";
    // for (char ch : text) {
    //     encodedString += huffmanCode[ch];
    // }
    // cout << "\nEncoded String:\n" << encodedString << '\n';

    // int originalBits = text.length() * 8; 
    // int encodedBits = encodedString.length();
    // cout << "\nOriginal Bits: " << originalBits << '\n';
    // cout << "Encoded Bits: " << encodedBits << '\n';

    // cout << "\nDecoded String:\n";
    // int index = -1;
    // while (index < (int)encodedString.size() - 2) {
    //     decode(root, index, encodedString);
    // }
}

int main() {
    string text = "Hello World.";

    buildHuffmanTree(text);

    return 0;
}
