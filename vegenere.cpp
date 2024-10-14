#include <iostream>
#include <string>
using namespace std;

string generateKey(string text, string key) {
    int textLen = text.size();
    int keyLen = key.size();
    
    for (int i = 0; i < textLen - keyLen; i++) {
        key += key[i % keyLen];
    }
    return key;
}

string encryptVigenere(string text, string key) {
    string cipherText;

    for (int i = 0; i < text.length(); i++) {
        char x = (text[i] + key[i]) % 26;
        x += 'A';
        cipherText.push_back(x);
    }
    return cipherText;
}

string decryptVigenere(string cipherText, string key) {
    string originalText;

    for (int i = 0; i < cipherText.length(); i++) {
        char x = (cipherText[i] - key[i] + 26) % 26;
        x += 'A';
        originalText.push_back(x);
    }
    return originalText;
}

int main() {
    string text, key;

    cout << "Enter the text to encrypt (uppercase letters only): ";
    getline(cin, text);

    cout << "Enter the key (uppercase letters only): ";
    getline(cin, key);

    string generatedKey = generateKey(text, key);

    string cipherText = encryptVigenere(text, generatedKey);
    cout << "Encrypted text: " << cipherText << endl;

    string decryptedText = decryptVigenere(cipherText, generatedKey);
    cout << "Decrypted text: " << decryptedText << endl;

    return 0;
}
