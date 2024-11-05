#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm> // For transform function

using namespace std;

#define N 26

class Cipher {
private:
    vector<char> arr1;
    int key;
    int effectiveKey;

public:
    Cipher() : key(0), effectiveKey(0), arr1(N) {
        for (int i = 0; i < N; i++) {
            arr1[i] = 'a' + i; // Change to uppercase
        }
    }

    void setKey(int k) {
        if (k < 0) {
            throw invalid_argument("Key must be a non-negative integer.");
        }
        key = k;
        effectiveKey = key % N;
    }

    int getKey() const {
        return key;
    }

    int getEffectiveKey() const {
        return effectiveKey;
    }

    string encrypt(const string& word) {
        string encryptedWord(word.length(), '\0');
        for (size_t i = 0; i < word.length(); i++) {
            for (int j = 0; j < N; j++) {
                if (word[i] == arr1[j]) {
                    encryptedWord[i] = arr1[(j + getEffectiveKey()) % N];
                    break;
                }
            }
        }
        return encryptedWord;
    }

    string decrypt(const string& word) {
        string decryptedWord(word.length(), '\0');
        for (size_t i = 0; i < word.length(); i++) {
            for (int j = 0; j < N; j++) {
                if (word[i] == arr1[j]) {
                    decryptedWord[i] = arr1[(j - getEffectiveKey() + N) % N];
                    break;
                }
            }
        }
        return decryptedWord;
    }
};

class Program {
public:
    Program() {
        generateText();
        generateKey();
    }
    string Encrypt(const string&);
    string Decrypt(const string&);
private:
    vector<char> text;
    void generateText();
    vector<char> key;
    void generateKey();
};

void Program::generateText() {
    text.resize(26);
    for (int i = 0; i < 26; i++) {
        text[i] = 'a' + i;
    }
}

void Program::generateKey() {
    key.resize(26);
    for (int i = 0; i < 26; i++) {
        key[i] = 'z' - i;
    }
}

string Program::Encrypt(const string& word) {
    string encrypted;
    for (char c : word) {
        for (int j = 0; j < text.size(); j++) {
            if (c == text[j]) {
                encrypted += key[j];
                break;
            }
        }
    }
    return encrypted;
}

string Program::Decrypt(const string& word) {
    string decrypted;
    for (char c : word) {
        for (int j = 0; j < key.size(); j++) {
            if (c == key[j]) {
                decrypted += text[j];
                break;
            }
        }
    }
    return decrypted;
}

int main() {
    Cipher cipher;
    Program prog;
    cout << "Enter the key: ";
    int key;
    cin >> key;

    try {
        cipher.setKey(key);

        cout << "Enter a word to encrypt: ";
        string word;
        cin >> word;


        string encryptedWord = cipher.encrypt(word);
        cout << "Encrypted word (Cipher): " << encryptedWord << endl;

        string doubleEncryptedWord = prog.Encrypt(encryptedWord);
        cout << "Double Encrypted word (Program): " << doubleEncryptedWord << endl;

        string decryptedWord = prog.Decrypt(doubleEncryptedWord);
        cout << "Decrypted word (Program): " << decryptedWord << endl;

        string finalDecryptedWord = cipher.decrypt(decryptedWord);
        cout << "Finally Decrypted word (Cipher): " << finalDecryptedWord << endl;
    }
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
