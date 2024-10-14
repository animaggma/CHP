#include <iostream>
#include <string>
using namespace std;

string runLengthEncoding(const string& input) {
    string encoded = "";
    int n = input.length();

    for (int i = 0; i < n; i++) {
        int count = 1;
        while (i < n - 1 && input[i] == input[i + 1]) {
            count++;
            i++;
        }
        encoded += input[i];
        encoded += to_string(count);
    }

    return encoded;
}

string runLengthDecoding(const string& encoded) {
    string decoded = "";
    int n = encoded.length();

    for (int i = 0; i < n; i++) {
        char currentChar = encoded[i];
        i++;
        int count = encoded[i] - '0';
        
        for (int j = 0; j < count; j++) {
            decoded += currentChar;
        }
    }

    return decoded;
}

int main() {
    string input;
    cout << "Enter the string to be encoded: ";
    cin >> input;

    string encoded = runLengthEncoding(input);
    cout << "Encoded string: " << encoded << endl;

    string decoded = runLengthDecoding(encoded);
    cout << "Decoded string: " << decoded << endl;

    return 0;
}
