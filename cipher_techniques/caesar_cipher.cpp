#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int SHIFT = 3;

bool isCapital(char letter){
    return (letter >= 65 && letter <= 90);

}
string encryptCaesar(string message){
    string encodedMessage = "";

    for(char letter : message){
        int charToInsert = (letter + SHIFT);
        char substituteLetter = (char) charToInsert;
        encodedMessage += substituteLetter;
    }

    return encodedMessage;
}

// only stay in the realm of letters

string decryptCaesar(string encodedMessage){
    string originalMessage = "";
    for(auto letter : encodedMessage){
        char originalLetter = (char) (letter - SHIFT);
        // cout << originalLetter << ' ';
        originalMessage += originalLetter;
    }
    return originalMessage;
    
}

int main()
{
    string message = "This is a message";

    string encryptedText = encryptCaesar(message);

    cout << "Encrypted Message = " << endl;
    cout << encryptedText << endl;


    cout << "................." << endl;
    string originalMessage = decryptCaesar(encryptedText);
    cout << "Original message was = " << endl;
    cout << originalMessage << endl;
}