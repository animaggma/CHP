#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

using namespace std;

struct HuffmanNode {
    char ch;
    int freq;
    shared_ptr<HuffmanNode> left, right;

    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    HuffmanNode(int f, shared_ptr<HuffmanNode> l, shared_ptr<HuffmanNode> r) : ch(0), freq(f), left(l), right(r) {}
};

struct Compare {
    bool operator()(const shared_ptr<HuffmanNode>& left, const shared_ptr<HuffmanNode>& right) {
        return left->freq > right->freq;  
    }
};

shared_ptr<HuffmanNode> buildHuffmanTree(const unordered_map<char, int>& freqTable) {
    priority_queue<shared_ptr<HuffmanNode>, vector<shared_ptr<HuffmanNode>>, Compare> minHeap;

    for (const auto& pair : freqTable) {
        minHeap.push(make_shared<HuffmanNode>(pair.first, pair.second));
    }

    while (minHeap.size() > 1) {
        auto left = minHeap.top(); minHeap.pop();
        auto right = minHeap.top(); minHeap.pop();
        minHeap.push(make_shared<HuffmanNode>(left->freq + right->freq, left, right));
    }

    return minHeap.top();
}

void generateCodes(shared_ptr<HuffmanNode> node, const string& code, unordered_map<char, string>& codes) {
    if (!node) return;
    if (!node->left && !node->right) codes[node->ch] = code;
    generateCodes(node->left, code + "0", codes); 
    generateCodes(node->right, code + "1", codes); 
}

string encode(const string& text, const unordered_map<char, string>& codes) {
    string encoded;
    for (char c : text) encoded += codes.at(c);  
    return encoded;
}

string decode(const string& encoded, shared_ptr<HuffmanNode> root) {
    string decoded;
    auto node = root;
    for (char bit : encoded) {
        node = (bit == '0') ? node->left : node->right;  
        if (!node->left && !node->right) {  
            decoded += node->ch;  
            node = root;  
        }
    }
    return decoded;
}

int main() {
    string text;
    cout << "Enter the text to encode: ";  
    getline(cin, text);  

    unordered_map<char, int> freqTable;
    for (char c : text) freqTable[c]++;  

    shared_ptr<HuffmanNode> root = buildHuffmanTree(freqTable);

    unordered_map<char, string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);  

    cout << "\nHuffman Codes:\n";
    for (const auto& pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << endl; 
    }

    string encoded = encode(text, huffmanCodes); 
    cout << "\nEncoded Text:\n" << encoded << endl;  

    string decoded = decode(encoded, root);  
    cout << "\nDecoded Text:\n" << decoded << endl; 

    return 0;
}
