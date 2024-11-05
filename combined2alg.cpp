#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Program {
public:
    Program() {
        generateText();
        generateKey();
    }

    void Encrypt(vector<char>& word) {
        for (int i = 0; i < word.size(); i++) {
            for (int j = 0; j < text.size(); j++) {
                if (word[i] == text[j]) {
                    word[i] = key[j];
                    break;
                }
            }
        }
    }

    void Decrypt(vector<char>& word) {
        for (int i = 0; i < word.size(); i++) {
            for (int j = 0; j < key.size(); j++) {
                if (word[i] == key[j]) {
                    word[i] = text[j];
                    break;
                }
            }
        }
    }

    void print(vector<char> word) {
        for (int i = 0; i < word.size(); i++) {
            cout << word[i];
        }
        cout << endl;
    }

    string generateVigenereKey(string text, string key) {
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

private:
    vector<char> text;
    vector<char> key;

    void generateText() {
        text.resize(26);
        for (int i = 0; i < 26; i++) {
            text[i] = 'A' + i;
        }
        print(text);
    }

    void generateKey() {
        key.resize(26);
        for (int i = 0; i < 26; i++) {
            key[i] = 'Z' - i;
        }
        print(key);
    }
};

int main() {
    Program program;
    string message;
    int choice;
    
    cout << "Enter a message (uppercase letters only): ";
    cin >> message;
    
    vector<char> word(message.begin(), message.end());
    
    cout << "Choose action for Substitution Cipher:\n";
    cout << "1. Encrypt\n2. Decrypt\n";
    cout << "Your choice: ";
    cin >> choice;

    if (choice == 1) {
        program.Encrypt(word);  
        cout << "Encrypted message with Substitution Cipher: ";
        program.print(word);
    } else if (choice == 2) {
        program.Decrypt(word); 
        cout << "Decrypted message with Substitution Cipher: ";
        program.print(word);
    } else {
        cout << "Invalid choice.\n";
        return 1;
    }

    cout << "\nEnter a keyword for Vigenère Cipher: ";
    string key;
    cin >> key;

    string result(word.begin(), word.end());

    string vigenereKey = program.generateVigenereKey(result, key);

    cout << "Choose action for Vigenère Cipher:\n";
    cout << "1. Encrypt\n2. Decrypt\n";
    cout << "Your choice: ";
    cin >> choice;

    if (choice == 1) {
        string encryptedVigenere = program.encryptVigenere(result, vigenereKey);
        cout << "Encrypted message with Vigenère Cipher: " << encryptedVigenere << endl;
    } else if (choice == 2) {
        string decryptedVigenere = program.decryptVigenere(result, vigenereKey);
        cout << "Decrypted message with Vigenère Cipher: " << decryptedVigenere << endl;
    } else {
        cout << "Invalid choice.\n";
    }

    return 0;
}