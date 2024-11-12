#include <iostream>
#include <string> 
#include <vector>
#include <stdexcept>
#include <algorithm> 

using namespace std;

class GeneralizedCaesarCipher {
public:
    string encrypt(const string& text, int shift) {
        string encryptedText;
        for (char c : text) {
            char shifted = static_cast<char>((static_cast<unsigned char>(c) + shift) % 256);
            encryptedText += shifted;
        }
        return encryptedText;
    }

    string decrypt(const string& text, int shift) {
        string decryptedText;
        for (char c : text) {
            char shifted = static_cast<char>((static_cast<unsigned char>(c) - shift + 256) % 256);
            decryptedText += shifted;
        }
        return decryptedText;
    }
};
class MatrixCipher {
private:
    int rows;
    int columns;
    vector<vector<char>> matrix;

public:
    MatrixCipher(int rowSize, int colSize) : rows(rowSize), columns(colSize), matrix(rowSize, vector<char>(colSize, ' ')) {}

    string encrypt(const string& text) {
        matrix.resize(rows, vector<char>(columns, ' '));

        for (int i = 0; i < text.length(); ++i) {
            matrix[i / columns][i % columns] = text[i];
        }

        string encrypted;
        for (int j = 0; j < columns; j++) {
            for (int i = 0; i < rows; i++) {
                if (matrix[i][j] != ' ') encrypted += matrix[i][j];
            }
        }
        return encrypted;
    }

    string decrypt(const string& text) {

        string decrypted;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                decrypted += matrix[i][j];
            }
        }
        return decrypted;
    }

    void printMatrix() const {
        for (const auto& row : matrix) {
            for (char c : row) {
                cout << (c == ' ' ? '.' : c) << ' ';
            }
            cout << endl;
        }
    }

};

int main() {
    GeneralizedCaesarCipher cipher;

    cout << "Enter the key for Caesar cipher: " << endl;
    int key;
    cin >> key;
    string word;
    cout << "Enter a word to encrypt: " << endl;
    cin >> word;
    int column; 
    cout << "Enter the matrix size: " << endl;
    cin >> column;
    int row = (word.length() + column - 1) / column;
    MatrixCipher prog(row, column);

    string encryptedWord = cipher.encrypt(word,key);
    cout << "Encrypted word (Cipher): " << encryptedWord << endl;

    string doubleEncryptedWord = prog.encrypt(encryptedWord);
    cout << "Double Encrypted word (Program): " << doubleEncryptedWord << endl;

    string decryptedWord = prog.decrypt(doubleEncryptedWord);
    cout << "Decrypted word (Program): " << decryptedWord << endl;

    string finalDecryptedWord = cipher.decrypt(decryptedWord, key);
    cout << "Finally Decrypted word (Cipher): " << finalDecryptedWord << endl;

    return 0;
}
