#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int SHIFT = 3;

bool isCapital(char letter){
    return (letter >= 65 && letter <= 90);

}
string encryptCaesar(string message){
    // map letters => 0, 25 scheme
    string mappedMessage = "";
    for(char letter : message){
        // handle spaces
        if(letter != ' ')
            mappedMessage += (char) (letter - 'a');
        else 
            mappedMessage += " ";
    }

    string encryptedMessage = "";
    // use a shift
    for(char mappedLetter : mappedMessage){
        if(mappedLetter == ' '){
            encryptedMessage += ' ';
            continue;
        }
        int finalLocation = ((mappedLetter + SHIFT) % 26);
        char encryptedLetter = finalLocation + 'a';
        encryptedMessage += encryptedLetter;
    }

    return encryptedMessage;
    // make final code
}

// only stay in the realm of letters

string decryptCaesar(string encodedMessage){
    // map
    string mappedMessage = "";
    for(char letter : encodedMessage){
        if(letter == ' '){
            mappedMessage += ' ';
            continue;
        }

        mappedMessage += (letter - 'a');
    }
    string originalMessage = "";
    // encrypt the message
    for(char mappedLetter : mappedMessage){
        if(mappedLetter == ' '){
            originalMessage += ' ';
            continue;
        }
        // 0 ... 25
        int finalShift = (mappedLetter - SHIFT) >= 0 ? (mappedLetter - SHIFT) : (26 + mappedLetter - SHIFT);
        
        char originalLetter = finalShift + 'a';
        originalMessage += originalLetter;

    }

    return originalMessage;
    
}


int main()
{
    string message = "this is a message xyztw";

    string encryptedText = encryptCaesar(message);

    cout << "Encrypted Message = " << endl;
    cout << encryptedText << endl;


    cout << "................." << endl;
    string originalMessage = decryptCaesar(encryptedText);
    cout << "Original message was = " << endl;
    cout << originalMessage << endl;
}