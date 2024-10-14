#include <iostream>
#include <string>
using namespace std;

string encrypt(string text, int shift) {
    string result = "";

    for (char c : text) {
        if (isupper(c)) {
            result += char(int(c + shift - 'A') % 26 + 'A');
        }
        else if (islower(c)) {
            result += char(int(c + shift - 'a') % 26 + 'a');
        } else {
            result += c;
        }
    }
    return result;
}

string decrypt(string text, int shift) {
    return encrypt(text, 26 - (shift % 26));
}

int main() {
    string text;
    int shift;
        cout << "Enter text to encrypt: ";
    getline(cin, text);
    cout << "Enter shift value (1-25): ";
    cin >> shift;
    if (shift < 1 || shift > 25) {
        cout << "Shift value must be between 1 and 25." << endl;
        return 1; // Exit with an error code
    }

    string encryptedText = encrypt(text, shift);
    cout << "\nEncrypted Text: " << encryptedText << endl;
    string decryptedText = decrypt(encryptedText, shift);
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}
