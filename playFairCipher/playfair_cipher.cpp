#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <utility>

using namespace std;

#define Row vector<char>

string key = "monarchy";

vector<Row> Matrix(5, Row(5));
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
            Matrix[rowIdx][colIdx] = key[i];

            // we didn't insert an entry in the hash table
            pair<int, int> newPair(rowIdx, colIdx);
            location[key[i]] = newPair;

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
            Matrix[rowIdx][colIdx] = respectiveChar;

            // we didn't insert an entry in the hash table
            pair<int, int> newPair(rowIdx, colIdx);
            location[respectiveChar] = newPair;

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

    // cout << copyPlainText << ' ' << plainText << endl;

    return plainText;
}

string encrypt(string plainText)
{
    string cipherText = "";
    for (int i = 0; i < plainText.size() - 1; i += 2)
    {
        char firstChar = plainText[i], secondChar = plainText[i + 1];

        pair<int, int> locFirstChar = location[firstChar];
        pair<int, int> locSecondChar = location[secondChar];

        int rowFirstChar = locFirstChar.first, colFirstChar = locFirstChar.second;
        int rowSecondChar = locSecondChar.first, colSecondChar = locSecondChar.second;

        if (rowFirstChar == rowSecondChar)
        {
            cipherText += Matrix[rowFirstChar][(colFirstChar + 1) % 5];
            cipherText += Matrix[rowFirstChar][(colSecondChar + 1) % 5];
        }
        else if (colFirstChar == colSecondChar)
        {
            cipherText += Matrix[(rowFirstChar + 1) % 5][colFirstChar];
            cipherText += Matrix[(rowSecondChar + 1) % 5][colSecondChar];
        }
        else
        {
            cipherText += Matrix[rowFirstChar][colSecondChar];
            cipherText += Matrix[rowSecondChar][colFirstChar];
        }
    }

    return cipherText;
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

int main()
{
    string plainText = "tattckatthedawn";
    cout << "Enter the text you want to encrypt : ";
    cin >> plainText;

    // construct a matrix
    createMatrix();

    string improvedPlainText = improvePlainText(plainText);

    // cout << improvedPlainText << endl;
    // encrypt
    if (improvedPlainText.size() % 2 != 0)
        improvedPlainText += 'x';

    string cipherText = encrypt(improvedPlainText);
    cout << "Text after encryption : " << cipherText << endl;

    // SRSZLDIRSZPDKCNXAW
    // srszldirszpdkcnxaw
    // srszldirszpdkcnxaw
    // srszirldllcfbrxz
    // srszszderspdkcnx
    // cloooouclcaeoolc

    printMatrix();
}