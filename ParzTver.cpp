#include <iostream>
#include <vector>
using namespace std;

class Program {
public:
    Program(){
        generateText();
        generateKey();
    }
    void Encrypt(vector<char>&);
    void Decrypt(vector<char>&);
    void print(vector<char>);
private:
    vector<char> text;
    void generateText();
    vector<char> key;
    void generateKey();
};
void Program::generateText() {
    text.resize(26);
    for (int i = 0; i < 26; i++)
    {
        text[i] = 'A' + i;
    }
    print(text);
}
void Program::generateKey() {
    key.resize(26);
    for (int i = 0; i < 26; i++)
    {
        key[i] = 'Z' - i;
    }
    print(key);
}
void Program::Encrypt(vector<char>& word) {
    for (int i = 0; i < word.size(); i++)
    {
        for (int j = 0; j < text.size(); j++)
        {
            if (word[i] == text[j]) {
                word[i] = key[j];
                break;
            }
        }
    }
}
void Program::Decrypt(vector<char>& word) {
    for (int i = 0; i < word.size(); i++)
    {
        for (int j = 0; j < key.size(); j++)
        {
            if (word[i] == key[j]) {
                word[i] = text[j];
                break;
            }
        }
    }
}
void Program::print(vector<char> word) {
    for (int i = 0; i < word.size(); i++)
    {
        cout << word[i];
    }
    cout << endl;
}
int main()
{

    Program p;

    vector<char> word = { 'Q', 'N', 'A', 'R'};
    p.Encrypt(word);
    p.print(word);
    p.Decrypt(word);
    p.print(word);
}
