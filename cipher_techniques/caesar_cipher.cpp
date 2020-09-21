#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


class CaearCipher {

    // string originalMessage, encryptedMessage;
    int SHIFT;

    static bool isCapital(char letter){
        return (letter >= 65 && letter <= 90);

    }

    string mapToRange(string message){
        string mappedMessage = "";
        for(char letter : message){
            // handle spaces
            if(letter != ' ')
                mappedMessage += (char) (letter - 'a');
            else 
                mappedMessage += " ";
        }
        return mappedMessage;
    }

public:
    CaearCipher(int SHIFT){
        this->SHIFT = SHIFT;
    }

    string encryptText(string message){
        // map letters => 0, 25 scheme
        string mappedMessage = mapToRange(message);

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

    string decryptText(string encodedMessage){
        // map
        string mappedMessage = mapToRange(encodedMessage);

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
};



int main()
{
    string message = "this is a message xyztw";

    int SHIFT = 4;
    CaearCipher caesarCipher(SHIFT);

    string encryptedText = caesarCipher.encryptText(message);

    cout << "Encrypted Message = " << endl;
    cout << encryptedText << endl;


    cout << "................." << endl;
    string originalMessage = caesarCipher.decryptText(encryptedText);
    cout << "Original message was = " << endl;
    cout << originalMessage << endl;
}