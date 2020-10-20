import numpy as np
def get_keystream(plain_text, key):
    """
    make the key as same size as plaintext by using repetitions
    eg:
    plainText = "thisismatch" ==> 11 letters
    key = "dog"
    keystream = "dogdogdogdo" ==> 11 letters
    """
    num_repetitions = int(len(plain_text) / len(key)) + 1

    key_stream_text = ''.join([key for _ in range(num_repetitions)])

    return key_stream_text[0:len(plain_text)]


def encrypt(plain_text, key):
    """
    Encrypt the plain text using key
    """
    # get keystream from the key
    key_stream = get_keystream(plain_text, key)

    print(key_stream)


    vigenere_mat = []

    # convert adjascent pairs into vigenere matrix
    ## vigenere mat:
    ## eg: possible letters ==> "a", "b", "c"
    # vigenere mat --> 
    # a b c
    # b c a   --> left shift(1 letter)
    # c a b   --> left shift(2 letters)
    for row in range(26):
        next_row = []
        for col in range(26):
            number = (row + col) % 26
            next_row.append(number)
        vigenere_mat.append(next_row)

    # print(vigenere_mat)
    encrypted_text = []
    
    for i in range(len(plain_text)):
        encrypted_char = vigenere_mat[ord(key_stream[i]) - ord('a')][ord(plain_text[i]) - ord('a')]
        encrypted_text.append(chr(encrypted_char + ord('a')))

    print("".join(encrypted_text))


    return plain_text



def main():
    plain_text = "attackatthedawn"
    key = "lemon"

    cipher_text = encrypt(plain_text, key)
    print(cipher_text)

main()