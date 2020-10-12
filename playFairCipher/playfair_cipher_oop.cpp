#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <utility>

using namespace std;

#define Row vector<char>

class PlayfairCipher
{
    string key;
    vector<Row> Matrix;
    unordered_map<char, pair<int, int>> location;

    void createMatrix()
    {
        int rowIdx = 0, colIdx = 0;
        int i = 0;

        for (i = 0; i < key.size(); i++)
        {
            // else we are going to insert in sameLoc just using different character
            if (location.find(key[i]) == location.end())
            {
                this->Matrix[rowIdx][colIdx] = key[i];

                // we didn't insert an entry in the hash table
                pair<int, int> newPair(rowIdx, colIdx);
                this->location[key[i]] = newPair;

                colIdx++;
                if (colIdx == 5)
                {
                    colIdx = 0, rowIdx++;
                }
            }
            // i++;
        }

        // fill the rest of the matrix

        for (int i = 0; i < 26; i++)
        {
            char respectiveChar = i + 'a';
            if (respectiveChar == 'j')
                continue;

            if (location.find(respectiveChar) == location.end())
            {
                this->Matrix[rowIdx][colIdx] = respectiveChar;

                // we didn't insert an entry in the hash table
                pair<int, int> newPair(rowIdx, colIdx);
                this->location[respectiveChar] = newPair;

                colIdx++;
                if (colIdx == 5)
                {
                    colIdx = 0, rowIdx++;
                }
            }
        }
    }

    string improvePlainText(string plainText)
    {
        for (int i = 0; i < plainText.size(); i += 2)
        {
            if (plainText[i] == plainText[i + 1])
            {
                plainText.insert(plainText.begin() + i + 1, 'x');
            }
        }

        if (plainText.size() % 2 != 0)
            plainText += 'x';

        // cout << copyPlainText << ' ' << plainText << endl;

        return plainText;
    }

    void printMatrix()
    {
        for (Row r : Matrix)
        {
            for (char cell : r)
            {
                cout << cell << ' ';
            }
            cout << endl;
        }
    }

public:
    PlayfairCipher(string key)
    {
        this->key = key;

        this->Matrix.resize(5, Row(5));
        createMatrix();
        // printMatrix();
    }

    // ecnrypt function
    string encrypt(string plainText)
    {
        plainText = this->improvePlainText(plainText);
        // cout << plainText << endl;
        string cipherText = "";
        for (int i = 0; i < plainText.size() - 1; i += 2)
        {
            char firstChar = plainText[i], secondChar = plainText[i + 1];
            // cout << firstChar << ' ' << secondChar << endl;

            pair<int, int> locFirstChar = this->location[firstChar];
            pair<int, int> locSecondChar = this->location[secondChar];

            int rowFirstChar = locFirstChar.first, colFirstChar = locFirstChar.second;
            int rowSecondChar = locSecondChar.first, colSecondChar = locSecondChar.second;

            if (rowFirstChar == rowSecondChar)
            {
                cipherText += this->Matrix[rowFirstChar][(colFirstChar + 1) % 5];
                cipherText += this->Matrix[rowFirstChar][(colSecondChar + 1) % 5];
            }
            else if (colFirstChar == colSecondChar)
            {
                cipherText += this->Matrix[(rowFirstChar + 1) % 5][colFirstChar];
                cipherText += this->Matrix[(rowSecondChar + 1) % 5][colSecondChar];
            }
            else
            {
                cipherText += this->Matrix[rowFirstChar][colSecondChar];
                cipherText += this->Matrix[rowSecondChar][colFirstChar];
            }
        }

        // cout << cipherText << endl;
        return cipherText;
    }

    // decrypting function
    string decrypt(string cipherText)
    {
        string originalPlainText = "";
        for (int i = 0; i < cipherText.size() - 1; i += 2)
        {
            char firstChar = cipherText[i], secondChar = cipherText[i + 1];

            pair<int, int> locFirstChar = this->location[firstChar];
            pair<int, int> locSecondChar = this->location[secondChar];

            int rowFirstChar = locFirstChar.first, colFirstChar = locFirstChar.second;
            int rowSecondChar = locSecondChar.first, colSecondChar = locSecondChar.second;

            if (rowFirstChar == rowSecondChar)
            {
                int colOne = colFirstChar == 0 ? 4 : colFirstChar - 1;
                int colTwo = colSecondChar == 0 ? 4 : colSecondChar - 1;
                originalPlainText += this->Matrix[rowFirstChar][colOne];
                originalPlainText += this->Matrix[rowFirstChar][colTwo];
            }
            else if (colFirstChar == colSecondChar)
            {
                int rowOne = (rowFirstChar == 0) ? 4 : rowFirstChar - 1;
                int rowTwo = (rowSecondChar == 0) ? 4 : rowSecondChar - 1;
                originalPlainText += this->Matrix[rowOne][colFirstChar];
                originalPlainText += this->Matrix[rowTwo][colSecondChar];
            }
            else
            {
                originalPlainText += this->Matrix[rowFirstChar][colSecondChar];
                originalPlainText += this->Matrix[rowSecondChar][colFirstChar];
            }
        }

        return originalPlainText;
    }
};

int main()
{
    string plainText = "tattckatthedawn";
    cout << "Enter the text you want to encrypt : ";
    cin >> plainText;

    string key = "monarchy";

    PlayfairCipher pfCipher(key);

    string cipherText = pfCipher.encrypt(plainText);
    cout << "Text after encryption : " << cipherText << endl;

    string originalPlainText = pfCipher.decrypt(cipherText);
    cout << "Original text was : " << originalPlainText << endl;
}